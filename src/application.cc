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

namespace {

auto const SOCKET_ENV = u"DRAGDROP_SOCKET"_s;

auto makeServerName() -> QString
{
  auto pid = QCoreApplication::applicationPid();
  return "%1-%2"_L1.arg(DragDrop::PROGRAM_NAME).arg(pid);
}

} // namespace

namespace DragDrop {

Application::Application(int& argc, char** argv)
  : QApplication(argc, argv)
  , mOpts(*this)
  , mServerName(makeServerName())
{
  setApplicationName(PROGRAM_NAME);
  setApplicationVersion(PROGRAM_VERSION);

  if (mOpts.serverSocket.isEmpty()) {
    // We're the CLI process:
    mServer = new Server(mServerName, this);
    connect(mServer, &Server::receivedURLs, this, &Application::onReceivedURLs);
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
  QStringList args;
  args << u"--server-socket"_s << mServerName;

  auto pos = args.size();
  for (const auto& name : mOpts.files) {
    if (QFileInfo file(name); mOpts.dirsFirst and file.isDir()) {
      args.insert(pos++, name);
    } else if (file.exists()) {
      args.append(name);
    }
  }

  auto dialog = new QProcess(this);
  dialog->setProgram(applicationFilePath());
  dialog->setArguments(args);
  dialog->startDetached();
}

auto Application::exec() -> int
{
  if (mServer) {
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

void Application::onReceivedURLs(QList<QUrl> const& urls) const
{
  auto outs = QTextStream(stdout, QIODevice::WriteOnly);
  for (const auto& url : urls) {
    outs << (mOpts.uris ? url.url() : url.path());
    outs << (mOpts.null ? '\0' : '\n');
  }

  if (mOpts.once) {
    exit();
  }
}

void Application::onFilesRecv(const QList<QUrl>& files)
{
  auto writer = QCborStreamWriter(mClient);
  writer.startArray(files.size());
  for (const auto& file : files) {
    writer.append(file.url());
  }
  writer.endArray();
}

void Application::onFilesSent()
{
  QCborStreamWriter(mClient).append(QCborSimpleType::Null);
}

void Application::waitAndExit()
{
  mWindow->hide();
  QTimer::singleShot(30 * 1000, this, [] { exit(); });
}

}; // namespace DragDrop
