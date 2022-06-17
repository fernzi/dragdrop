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
	});
	parser.process(*this);
}

int Application::exec()
{
	QList<QFileInfo> files;
	const auto args = parser.positionalArguments();
	for (auto i = args.constBegin(); i != args.constEnd(); ++i) {
		QFileInfo file(*i);
		if (file.exists()) {
			files << file;
		}
	}
	Window win(files);
	win.show();
	return QApplication::exec();
}

}; // namespace DragDrop
