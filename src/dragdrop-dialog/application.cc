/* Copyright © 2022-2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "application.hh"
#include <QFileInfo>

namespace DragDrop {

Application::Application(int& argc, char** argv)
  : QApplication(argc, argv)
  , mOpts(*this)
{
}

auto Application::exec() -> int
{
  for (auto const& name : mOpts.files) {
		mWindow.addFile(QFileInfo(name));
	}

  mWindow.setOnce(mOpts.once);
	mWindow.show();

	return QApplication::exec();
}

}; // namespace DragDrop
