/* Copyright © 2022-2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#pragma once

#include "options.hh"
#include <QApplication>

class QLocalSocket;

namespace DragDrop {

class Client;
class Server;
class Window;

class Application : public QApplication
{
  Q_OBJECT

public:
  explicit Application(int& argc, char** argv);

  auto isServer() const -> bool;
  auto startServer() -> bool;
  auto startClient() -> bool;

private:
  void onClientConnected();
  void onUrlsRecv(QList<QUrl> const& urls) const;

  Options mOpts;
  Server* mServer = nullptr;
  Client* mClient = nullptr;
  Window* mWindow = nullptr;
};

}; // namespace DragDrop
