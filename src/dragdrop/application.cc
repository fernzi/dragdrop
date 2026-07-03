/* Copyright © 2024-2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "application.hh"
#include "config.hh"
#include "server.hh"
#include <QFileInfo>
#include <QProcess>

namespace {

auto const SOCKET_ENV = QStringLiteral("DRAGDROP_SOCKET");

auto makeServerName() -> QString
{
  auto pid = QCoreApplication::applicationPid();
  return QStringLiteral("%1-%2").arg(DragDrop::PROGRAM_NAME).arg(pid);
}

} // namespace

namespace DragDrop {

Application::Application(int& argc, char** argv)
  : QCoreApplication(argc, argv)
  , mOpts(*this)
  , mServerName(makeServerName())
  , mServer(new Server(mServerName, this))
{
  setApplicationName(PROGRAM_NAME);
  setApplicationVersion(PROGRAM_VERSION);

  connect(mServer, &Server::receivedURLs, this, &Application::onReceivedURLs);
  connect(mServer, &Server::disconnected, this, [] { exit(); });
}

auto Application::exec() -> int
{
  QStringList args;

  if (mOpts.once) {
    args.emplaceBack("-o");
  }

  auto pos = args.size();
  for (const auto& name : mOpts.files) {
    if (QFileInfo file(name); mOpts.dirs_first and file.isDir()) {
      args.insert(pos++, name);
    } else if (file.exists()) {
      args.append(name);
    }
  }

  auto dialog = new QProcess(this);
  auto dpath = // clang-format sucks
    QStringLiteral("%1/../%2/%3-dialog")
      .arg(applicationDirPath(), LIBEXEC_DIR, PROGRAM_NAME);
  dialog->setProgram(dpath);
  dialog->setArguments(args);

  auto env = QProcessEnvironment::systemEnvironment();
  env.insert(SOCKET_ENV, mServerName);
  dialog->setProcessEnvironment(env);

  dialog->startDetached();

  return QCoreApplication::exec();
}

void Application::onReceivedURLs(QList<QUrl> const& urls) const
{
  auto outs = QTextStream(stdout, QIODevice::WriteOnly);
  for (const auto& url : urls) {
    outs << (mOpts.uris ? url.url() : url.path());
    outs << (mOpts.null ? '\0' : '\n');
  }

  if (mOpts.once) {
    exit();
  }
}

}; // namespace DragDrop
