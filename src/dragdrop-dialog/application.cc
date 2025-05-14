/* Copyright © 2022-2025 Fern Zapata
 * This file is under the terms of the GNU GPL ver. 3, or (at your
 * option) any later version. If a copy of the GPL wasn't included
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "application.hh"
#include "window.hh"
#include <QFileInfo>

namespace DragDrop {

Application::Application(int& argc, char** argv)
	: QApplication(argc, argv)
{
}

auto Application::exec() -> int
{
	QList<QFileInfo> files;

	for (const auto& name : arguments().mid(1)) {
		files << QFileInfo(name);
	}

	Window win(files);
	win.show();
	return QApplication::exec();
}

}; // namespace DragDrop
