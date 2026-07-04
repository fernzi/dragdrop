/* Copyright © 2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "client.hh"
#include "fileparser.hh"
#include <QCborStreamWriter>
#include <QDebug>
#include <QLocalSocket>

namespace DragDrop {

Client::Client(QObject* parent)
  : QObject(parent)
  , mSocket(new QLocalSocket(this))
{
  connect(mSocket, &QLocalSocket::connected, this, [this] {
    mParser = new FileParser(mSocket, this);
    connect(mParser, &FileParser::parsedStrings, this, &Client::readPaths);
    emit connected();
  });
  connect(mSocket, &QLocalSocket::disconnected, this, [this] {
    if (mParser) {
      mParser->deleteLater();
      mParser = nullptr;
    }
    emit disconnected();
  });
}

void Client::connectToServer(QString const& name)
{
  mSocket->connectToServer(name);
}

void Client::writeUrls(QList<QUrl> const& urls)
{
  auto writer = QCborStreamWriter(mSocket);
  writer.startArray(urls.size());
  for (const auto& url : urls) {
    writer.append(url.url());
  }
  writer.endArray();
}

void Client::writePing()
{
  QCborStreamWriter(mSocket).append(QCborSimpleType::Null);
}

} // namespace DragDrop
