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

  static auto generateName() -> QString;

signals:
  void disconnected();
  void receivedURLs(QList<QUrl> urls);

private slots:
  void onNewConnection();
  void onDisconnected();
  void onParsedURL(QUrl const& url);
  void onParserFinished();

private:
  QLocalServer* mServer = nullptr;
  QLocalSocket* mClient = nullptr;
  FileParser* mParser = nullptr;
  QList<QUrl> mURLs;
};

} // DragDrop
