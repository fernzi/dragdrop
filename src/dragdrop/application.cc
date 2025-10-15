/* Copyright © 2024-2025 Fern Zapata
 * This file is under the terms of the GNU GPL ver. 3, or (at your
 * option) any later version. If a copy of the GPL wasn't included
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "application.hh"
#include <QFileInfo>
#include <QProcess>
#include <QUrl>

namespace DragDrop {

Application::Application(int& argc, char** argv)
	: QCoreApplication(argc, argv)
	, mProg(this)
	, mOutput(stdout, QIODevice::WriteOnly)
	, mParser(&mProg, this)
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
	mProg.setProgram(applicationDirPath()
		+ "/../" LIBEXEC_DIR "/" PROGRAM_NAME "-dialog");

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
	mProg.setArguments(files);

	connect(&mParser, &FileParser::parsedURL, this,
		&Application::parserOutput);
	connect(&mParser, &FileParser::finished, this,
		&Application::parserFinished);
	connect(&mProg,
		QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
		this, &Application::dialogFinished);

	mProg.start();

	return QCoreApplication::exec();
}

void Application::parserOutput(QUrl url)
{
	auto u = args.isSet(QStringLiteral("uris"));
	auto e = args.isSet(QStringLiteral("null"));
	mOutput << (u ? url.url() : url.path());
	mOutput << (e ? '\0' : '\n');
	mOutput.flush();
}

void Application::parserFinished()
{
	if (args.isSet(QStringLiteral("once"))) {
		exit();
	}
}

void Application::dialogFinished(int code, QProcess::ExitStatus status)
{
	exit();
}

}; // namespace DragDrop
