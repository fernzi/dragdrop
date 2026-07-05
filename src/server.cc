/* Copyright © 2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "server.hh"
#include "config.hh"
#include "fileparser.hh"
#include <QCborStreamWriter>
#include <QCoreApplication>
#include <QLocalServer>
#include <QLocalSocket>
#include <QStandardPaths>

using namespace Qt::StringLiterals;

namespace DragDrop {

Server::Server(QObject* parent)
  : QObject(parent)
  , mServer(new QLocalServer(this))
{
  mServer->setSocketOptions(QLocalServer::UserAccessOption);
  connect(
    mServer, &QLocalServer::newConnection, this, &Server::onNewConnection);
}

auto Server::listen(QString const& name) -> bool
{
  QLocalServer::removeServer(name);
  return mServer->listen(name);
}

auto Server::name() const -> QString
{
  return mServer->serverName();
}

void Server::writePaths(QStringList const& paths)
{
  auto writer = QCborStreamWriter(mClient);
  writer.startArray(paths.size());
  for (const auto& path : paths) {
    writer.append(path);
  }
  writer.endArray();
}

auto Server::generateName() -> QString
{
  QString pfx;
#if defined(Q_OS_UNIX) && !defined(Q_OS_APPLE)
  pfx = QStandardPaths::writableLocation(QStandardPaths::RuntimeLocation) + '/';
#endif
  auto pid = QCoreApplication::applicationPid();
  return "%1%2-%3"_L1.arg(pfx, DragDrop::PROGRAM_NAME).arg(pid);
}

void Server::onNewConnection()
{
  mClient = mServer->nextPendingConnection();
  mParser = new FileParser(mClient, this);
  connect(mClient, &QLocalSocket::disconnected, this, [this] {
    if (mParser) {
      mParser->deleteLater();
      mParser = nullptr;
    }
    emit disconnected();
  });
  connect(mParser, &FileParser::parsedStrings, this, [this](auto const& strs) {
    auto urls = QUrl::fromStringList(strs, QUrl::StrictMode);
    emit receivedURLs(urls);
  });

  // This doesn't disconnect existing clients,
  // only closes the server to new connections.
  mServer->close();

  emit connected();
}

} // DragDrop
