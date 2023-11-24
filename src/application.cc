/* Copyright © 2022-2023 Fern Zapata
 * This program is subject to the terms of the GNU GPL, version 3
 * or, at your option, any later version. If a copy of it was not
 * included with this file, see https://www.gnu.org/licenses/. */

#include "application.hh"
#include "window.hh"
#include <QFileInfo>

namespace DragDrop {

Application::Application(int& argc, char** argv)
	: QApplication(argc, argv)
{
	setApplicationName(QStringLiteral(DRAGDROP_NAME));
	setApplicationVersion(QStringLiteral(DRAGDROP_VERSION));
	parser.setApplicationDescription(
		tr("Drag and drop in the terminal."));
	parser.addHelpOption();
	parser.addVersionOption();
	parser.addPositionalArgument(
		"files", tr("File to display"), tr("[files...]"));
	parser.addOptions({
		{{"o", "once"},
			tr("Exit after a single drag or drop.")},
		{{"u", "uris"},
			tr("Print URIs instead of paths on drop.")},
		{{"0", "null"},
			tr("Separate printed paths with a null character.")},
		{"dirs-first",
			tr("List directories before files on the source dialog")},
	});
	parser.process(*this);
}

int Application::exec()
{
	QList<QFileInfo> files;
	int last_dir = 0;
	bool dirs_1st = parser.isSet(QStringLiteral("dirs-first"));
	const auto args = parser.positionalArguments();

	for (const QString& filename : args) {
		const QFileInfo file(filename);
		if (dirs_1st && file.isDir()) {
			files.insert(last_dir++, file);
		} else if (file.exists()) {
			files << file;
		}
	}

	const auto opts = Window::Options()
		.setFlag(Window::Option::Null, parser.isSet(QStringLiteral("null")))
		.setFlag(Window::Option::URIs, parser.isSet(QStringLiteral("uris")))
		.setFlag(Window::Option::Once, parser.isSet(QStringLiteral("once")));

	Window win(files, opts);
	win.show();
	return QApplication::exec();
}

}; // namespace DragDrop

int main(int argc, char** argv)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	DragDrop::Application::setAttribute(Qt::AA_EnableHighDpiScaling);
	DragDrop::Application::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
	return DragDrop::Application(argc, argv).exec();
}
