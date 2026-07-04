/* Copyright © 2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#pragma once

#include <QObject>

class QLocalServer;
class QLocalSocket;

namespace DragDrop {

class FileParser;

class Server : public QObject
{
  Q_OBJECT

public:
  Server(QObject* parent = nullptr);
  auto listen(QString const& name) -> bool;
  auto name() const -> QString;
  void writePaths(QStringList const& paths);

  static auto generateName() -> QString;

signals:
  void connected();
  void disconnected();
  void receivedURLs(QList<QUrl> urls);

private slots:
  void onNewConnection();
  void onDisconnected();

private:
  QLocalServer* mServer = nullptr;
  QLocalSocket* mClient = nullptr;
  FileParser* mParser = nullptr;
};

} // DragDrop
