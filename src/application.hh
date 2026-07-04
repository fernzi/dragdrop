/* Copyright © 2022-2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#pragma once

#include "options.hh"
#include <QApplication>

class QLocalSocket;

namespace DragDrop {

class Server;
class Window;

class Application : public QApplication
{
  Q_OBJECT

public:
  Application(int& argc, char** argv);
  auto exec() -> int;

private:
  void runDialog();
  void onUrlsRecv(QList<QUrl> const& urls) const;
  void onFilesRecv(QList<QUrl> const& files) const;
  void onFilesSent() const;
  void waitAndExit();

  Options mOpts;
  Server* mServer = nullptr;
  QLocalSocket* mClient = nullptr;
  Window* mWindow = nullptr;
};

}; // namespace DragDrop
