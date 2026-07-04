/* Copyright © 2024-2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "application.hh"
#include "config.hh"
#include "server.hh"
#include "window.hh"
#include <QCborStreamWriter>
#include <QFileInfo>
#include <QLocalSocket>
#include <QProcess>
#include <QTimer>

using namespace Qt::StringLiterals;

namespace DragDrop {

Application::Application(int& argc, char** argv)
  : QApplication(argc, argv)
  , mOpts(*this)
{
  setApplicationName(PROGRAM_NAME);
  setApplicationVersion(PROGRAM_VERSION);

  if (mOpts.serverSocket.isEmpty()) {
    // We're the CLI process:
    mServer = new Server(this);
    connect(mServer, &Server::receivedURLs, this, &Application::onUrlsRecv);
    connect(mServer, &Server::disconnected, this, [] { exit(); });
  } else {
    // We're the detached dialog:
    mClient = new QLocalSocket(this);
    mClient->connectToServer(mOpts.serverSocket);
    qDebug() << "client socket:" << mClient->fullServerName();
    connect(
      mClient, &QLocalSocket::disconnected, this, &Application::waitAndExit);

    mWindow = new Window;
    connect(mWindow, &Window::filesSent, this, &Application::onFilesSent);
    connect(mWindow, &Window::filesRecv, this, &Application::onFilesRecv);
  }
}

void Application::runDialog()
{
  mOpts.files.removeIf(
    [](const auto& name) { return not QFileInfo::exists(name); });

  if (mOpts.dirsFirst) {
    std::stable_partition(mOpts.files.begin(),
      mOpts.files.end(),
      [](const auto& name) { return QFileInfo(name).isDir(); });
  }

  auto args = QStringList{u"--server-socket"_s, mServer->name(), u"--"_s};
  auto dialog = new QProcess(this);
  dialog->setProgram(applicationFilePath());
  dialog->setArguments(args + mOpts.files);
  dialog->startDetached();
}

auto Application::exec() -> int
{
  if (mServer) {
    if (auto name = Server::generateName(); not mServer->listen(name)) {
      qCritical() << "could not start server at:" << name;
      exit(1);
    }
    runDialog();
  } else {
    Q_ASSERT(mWindow);
    for (auto const& file : mOpts.files) {
      mWindow->addFile(QFileInfo(file));
    }
    mWindow->show();
  }

  return QCoreApplication::exec();
}

void Application::onUrlsRecv(QList<QUrl> const& urls) const
{
  auto outs = QTextStream(stdout, QIODevice::WriteOnly);
  auto usep = mOpts.null ? '\0' : '\n';
  if (mOpts.uris) {
    for (const auto& url : urls) {
      outs << url.url() << usep;
    }
  } else {
    for (const auto& url : urls) {
      outs << url.path() << usep;
    }
  }

  if (mOpts.once) {
    exit();
  }
}

void Application::onFilesRecv(QList<QUrl> const& files) const
{
  auto writer = QCborStreamWriter(mClient);
  writer.startArray(files.size());
  for (const auto& file : files) {
    writer.append(file.url());
  }
  writer.endArray();
}

void Application::onFilesSent() const
{
  QCborStreamWriter(mClient).append(QCborSimpleType::Null);
}

void Application::waitAndExit()
{
  mWindow->hide();
  QTimer::singleShot(30 * 1000, this, [] { exit(); });
}

}; // namespace DragDrop
