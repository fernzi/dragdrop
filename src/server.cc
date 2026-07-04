/* Copyright © 2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "server.hh"
#include "fileparser.hh"
#include <QDebug>
#include <QLocalServer>
#include <QLocalSocket>

namespace DragDrop {

Server::Server(QString const& name, QObject* parent)
  : QObject(parent)
  , mServer(new QLocalServer(this))
{
  QLocalServer::removeServer(name);
  mServer->setSocketOptions(QLocalServer::UserAccessOption);
  connect(
    mServer, &QLocalServer::newConnection, this, &Server::onNewConnection);
  mServer->listen(name);
  qDebug() << "server socket:" << mServer->fullServerName();
}

void Server::onNewConnection()
{
  mClient = mServer->nextPendingConnection();
  mParser = new FileParser(mClient, this);
  connect(mClient, &QLocalSocket::disconnected, this, &Server::onDisconnected);
  connect(mParser, &FileParser::parsedURL, this, &Server::onParsedURL);
  connect(mParser, &FileParser::finished, this, &Server::onParserFinished);

  // This doesn't disconnect existing clients,
  // only closes the server to new connections.
  mServer->close();
}

void Server::onDisconnected()
{
  if (mParser) {
    mParser->deleteLater();
    mParser = nullptr;
  }
  emit disconnected();
}

void Server::onParsedURL(QUrl const& url)
{
  mURLs << url;
}

void Server::onParserFinished()
{
  emit receivedURLs(mURLs);
  mURLs.clear();
}

} // DragDrop
