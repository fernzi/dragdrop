/* Copyright © 2024 Fern Zapata
 * This file is under the terms of the GNU GPL ver. 3, or, at your
 * option, any later version. If a copy of the GPL wasn't included
 * with this file, see <https://www.gnu.org/licenses/>. */

#include "application.hh"
#include <QProcess>

namespace DragDrop {

Application::Application(int& argc, char** argv)
	: QCoreApplication(argc, argv)
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
}

auto Application::exec() -> int
{
	auto command = applicationDirPath()
		+ QStringLiteral("/../" LIBEXEC_DIR "/" PROGRAM_NAME "-dialog");
	prog.setProgram(command);
	prog.setArguments(arguments().mid(1));
	prog.setProcessChannelMode(
		QProcess::ProcessChannelMode::ForwardedChannels);

	connect(&prog,
		QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
		this, &Application::dialogFinished);

	prog.start();

	return QCoreApplication::exec();
}

void Application::dialogFinished(int code, QProcess::ExitStatus status)
{
	exit();
}

}; // namespace DragDrop
