/* Copyright © 2022-2025 Fern Zapata
 * This file is under the terms of the GNU GPL ver. 3, or (at your
 * option) any later version. If a copy of the GPL wasn't included
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "application.hh"
#include <QFileInfo>

namespace DragDrop {

Application::Application(int& argc, char** argv)
	: QApplication(argc, argv)
{
	mArgs.addOptions({
		{{"o", "once"}, ""},
	});
	mArgs.process(*this);
}

auto Application::exec() -> int
{
	for (auto const& name : mArgs.positionalArguments()) {
		mWindow.addFile(QFileInfo(name));
	}

	mWindow.setOnce(mArgs.isSet(QStringLiteral("once")));
	mWindow.show();

	return QApplication::exec();
}

}; // namespace DragDrop
