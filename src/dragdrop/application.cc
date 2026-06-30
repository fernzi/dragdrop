/* Copyright © 2024-2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "application.hh"
#include "server.hh"
#include <QFileInfo>
#include <QProcess>

namespace {

auto const SOCKET_ENV = QStringLiteral("DRAGDROP_SOCKET");

auto makeServerName() -> QString
{
  auto pid = QCoreApplication::applicationPid();
  return QStringLiteral(PROGRAM_NAME "-%1").arg(pid);
}

} // namespace

namespace DragDrop {

Application::Application(int& argc, char** argv)
  : QCoreApplication(argc, argv)
  , mServerName(makeServerName())
  , mServer(new Server(mServerName, this))
{
	setApplicationName(QStringLiteral(PROGRAM_NAME));
	setApplicationVersion(QStringLiteral(PROGRAM_VERSION));

	args.setApplicationDescription(
		tr("Drag-and-drop file source for the terminal"));
	args.addHelpOption();
	args.addVersionOption();

	args.addOptions({
		{{"o", "once"}, tr("Exit after a single drag or drop.")},
		{{"u", "uris"}, tr("Print URIs instead of paths on drop.")},
		{{"0", "null"},
			tr("Separate printed paths with a null character.")},
		{"dirs-first",
			tr("List directories before files on the source dialog")},
	});
	args.addPositionalArgument(
		"files", tr("Files to display"), tr("[files...]"));

	args.process(*this);

  connect(mServer, &Server::receivedURLs, this, &Application::onReceivedURLs);
  connect(mServer, &Server::disconnected, this, [] { exit(); });
}

auto Application::exec() -> int
{
	int dirPos = 0;
	QStringList files;
	for (const auto& name : args.positionalArguments()) {
		const QFileInfo file(name);
		if (args.isSet(QStringLiteral("dirs-first")) and file.isDir()) {
			files.insert(dirPos++, name);
		} else if (file.exists()) {
			files << name;
		}
	}
	if (args.isSet(QStringLiteral("once"))) {
		files << "-o";
	}

  auto dialog = new QProcess(this);
  dialog->setProgram(
    applicationDirPath() + "/../" LIBEXEC_DIR "/" PROGRAM_NAME "-dialog");
  dialog->setArguments(files);

  auto env = QProcessEnvironment::systemEnvironment();
  env.insert(SOCKET_ENV, mServerName);
  dialog->setProcessEnvironment(env);

  dialog->startDetached();

  return QCoreApplication::exec();
}

void Application::onReceivedURLs(QList<QUrl> const& urls)
{
  auto puri = args.isSet(QStringLiteral("uris"));
  auto pnul = args.isSet(QStringLiteral("null"));
  auto outs = QTextStream(stdout, QIODevice::WriteOnly);
  for (const auto& url : urls) {
    outs << (puri ? url.url() : url.path()) << (pnul ? '\0' : '\n');
  }

  if (args.isSet(QStringLiteral("once"))) {
    exit();
  }
}

}; // namespace DragDrop
