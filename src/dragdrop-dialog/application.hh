/* Copyright © 2022-2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#pragma once

#include "options.hh"
#include "window.hh"
#include <QApplication>

class QLocalSocket;

namespace DragDrop {

class Application : public QApplication
{
	Q_OBJECT

public:
	Application(int& argc, char** argv);
	auto exec() -> int;

private:
  void onFilesRecv(const QList<QUrl>& files);
  void onFilesSent();
  void waitAndExit();

  Options mOpts;
  QLocalSocket* mClient = nullptr;
	Window mWindow;
};

}; // namespace DragDrop
