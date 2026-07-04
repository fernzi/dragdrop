/* Copyright © 2022-2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "application.hh"
#include <QCborStreamWriter>
#include <QFileInfo>
#include <QLocalSocket>
#include <QTimer>

namespace DragDrop {

Application::Application(int& argc, char** argv)
  : QApplication(argc, argv)
  , mOpts(*this)
  , mClient(new QLocalSocket(this))
{
  mClient->connectToServer(mOpts.serverSocket);
  qDebug() << "client socket:" << mClient->fullServerName();

  connect(
    mClient, &QLocalSocket::disconnected, this, &Application::waitAndExit);
  connect(&mWindow, &Window::filesSent, this, &Application::onFilesSent);
  connect(&mWindow, &Window::filesRecv, this, &Application::onFilesRecv);
}

auto Application::exec() -> int
{
  for (auto const& name : mOpts.files) {
		mWindow.addFile(QFileInfo(name));
	}
	mWindow.show();

	return QApplication::exec();
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
  mWindow.hide();
  QTimer::singleShot(30 * 1000, this, [] { exit(); });
}

}; // namespace DragDrop
