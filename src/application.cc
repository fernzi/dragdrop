/* Copyright © 2024-2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "application.hh"
#include "client.hh"
#include "config.hh"
#include "server.hh"
#include "window.hh"
#include <QFileInfo>
#include <QProcess>
#include <QTimer>

using namespace Qt::StringLiterals;

namespace {

void runDialog(QString const& name, QObject* parent = nullptr)
{
  auto dialog = new QProcess(parent);
  dialog->setProgram(QCoreApplication::applicationFilePath());
  dialog->setArguments({u"--server-socket"_s, name});
  dialog->startDetached();
}

} // namespace

namespace DragDrop {

Application::Application(int& argc, char** argv)
  : QApplication(argc, argv)
  , mOpts(*this)
{
  setApplicationName(PROGRAM_NAME);
  setApplicationVersion(PROGRAM_VERSION);

  mOpts.files.removeIf(
    [](const auto& name) { return not QFileInfo::exists(name); });

  if (mOpts.dirsFirst) {
    std::stable_partition(mOpts.files.begin(),
      mOpts.files.end(),
      [](const auto& name) { return QFileInfo(name).isDir(); });
  }
}

auto Application::isServer() const -> bool
{
  return mOpts.serverSocket.isEmpty();
}

auto Application::startServer() -> bool
{
  mServer = new Server(this);
  connect(mServer, &Server::receivedURLs, this, &Application::onUrlsRecv);
  connect(mServer, &Server::connected, this, &Application::onClientConnected);
  connect(mServer, &Server::disconnected, this, [] { exit(); });

  if (auto name = Server::generateName(); not mServer->listen(name)) {
    qCritical() << "could not start server at:" << name;
    return false;
  }
  runDialog(mServer->name(), this);
  return true;
}

auto Application::startClient() -> bool
{
  mClient = new Client(this);
  connect(mClient, &Client::disconnected, this, [this] {
    mWindow->hide();
    QTimer::singleShot(30 * 1000, this, [] { exit(); });
  });

  mWindow = new Window;
  connect(mWindow, &Window::filesSent, mClient, &Client::writePing);
  connect(mWindow, &Window::filesRecv, mClient, &Client::writeUrls);

  connect(mClient, &Client::connected, mWindow, &Window::show);
  connect(mClient, &Client::readPaths, mWindow, [this](auto const& paths) {
    for (auto const& path : paths) {
      mWindow->addFile(QFileInfo(path));
    }
    mWindow->adjustSize();
  });

  mClient->connectToServer(mOpts.serverSocket);
  return true;
}

void Application::onClientConnected()
{
  auto files = mOpts.files;
  if (files.empty()) {
    return;
  }

  mServer->writePaths(files);
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

}; // namespace DragDrop
