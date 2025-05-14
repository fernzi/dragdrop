/* Copyright © 2024-2025 Fern Zapata
 * This file is under the terms of the GNU GPL ver. 3, or (at your
 * option) any later version. If a copy of the GPL wasn't included
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "application.hh"
#include <QFileInfo>
#include <QProcess>
#include <QTimer>
#include <QUrl>

namespace DragDrop {

Application::Application(int& argc, char** argv)
	: QCoreApplication(argc, argv)
	, mProg(this)
	, mOutput(stdout, QIODevice::WriteOnly)
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
	mProg.setArguments(files);

	connect(&mProg, &QProcess::readyReadStandardOutput, this,
		&Application::dialogOutput);
	connect(&mProg,
		QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
		this, &Application::dialogFinished);

	mProg.start();

	return QCoreApplication::exec();
}

static auto decodeString(QCborStreamReader& reader)
{
	QString str;
	QCborStreamReader::StringResult<QString> r;
	while ((r = reader.readString()).status == QCborStreamReader::Ok) {
		str += r.data;
	}
	if (r.status == QCborStreamReader::Error) {
		str.clear();
	}
	return str;
}

static void handleStream(
	QCborStreamReader& reader, QTextStream& out, bool asUri, char term)
{
	QUrl uri;
	switch (reader.type()) {
	case QCborStreamReader::ByteArray:
	case QCborStreamReader::String:
		uri = decodeString(reader);
		out << (asUri ? uri.url() : uri.path()) << term;
		break;
	case QCborStreamReader::Array:
		reader.enterContainer();
		while (not reader.lastError() and reader.hasNext()) {
			handleStream(reader, out, asUri, term);
		}
		if (not reader.lastError()) {
			reader.leaveContainer();
		}
		break;
	default:
		reader.next();
	}
}

void Application::dialogOutput()
{
	mReader.setDevice(&mProg);
	handleStream(mReader, mOutput, args.isSet(QStringLiteral("uris")),
		args.isSet(QStringLiteral("null")) ? '\0' : '\n');
	mOutput.flush();
	if (args.isSet(QStringLiteral("once"))) {
		QTimer::singleShot(300, &mProg, &QProcess::terminate);
	}
}

void Application::dialogFinished(int code, QProcess::ExitStatus status)
{
	exit();
}

}; // namespace DragDrop
