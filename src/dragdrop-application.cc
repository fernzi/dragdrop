/* DragDrop --- Drag and drop source for the command line
 * Copyright © 2022 Fern Zapata
 * This program is subject to the terms of the GNU GPL, either
 * version 3 of the License or (at your option) any later version.
 * You should have received a copy of the License along with this
 * file. If not, see <https://www.gnu.org/licenses/>. */

#include "dragdrop-application.hh"
#include "dragdrop-window.hh"
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
	for (const QFileInfo& file : args) {
		if (dirs_1st && file.isDir()) {
			files.insert(last_dir++, file);
		} else if (file.exists()) {
			files << file;
		}
	}

	const auto opts = Window::Options()
		.setFlag(Window::Option::URIs, parser.isSet(QStringLiteral("uris")))
		.setFlag(Window::Option::Once, parser.isSet(QStringLiteral("once")));

	Window win(files, opts);
	win.show();
	return QApplication::exec();
}

}; // namespace DragDrop
