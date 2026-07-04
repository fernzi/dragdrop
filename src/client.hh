/* Copyright © 2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#pragma once

#include <QObject>
#include <QUrl>

class QLocalSocket;

namespace DragDrop {

class FileParser;

class Client : public QObject
{
  Q_OBJECT

public:
  Client(QObject* parent = nullptr);
  void connectToServer(QString const& name);
  void writeUrls(QList<QUrl> const& urls);
  void writePing();

signals:
  void connected();
  void disconnected();
  void readPaths(QStringList const& urls);

private:
  QLocalSocket* mSocket = nullptr;
  FileParser* mParser = nullptr;
};

} // namespace DragDrop
