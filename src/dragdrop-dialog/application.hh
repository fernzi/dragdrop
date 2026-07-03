/* Copyright © 2022-2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#pragma once

#include "window.hh"
#include <QApplication>
#include "options.hh"

namespace DragDrop {

class Application : public QApplication
{
	Q_OBJECT

public:
	Application(int& argc, char** argv);
	auto exec() -> int;

private:
  Options mOpts;
	Window mWindow;
};

}; // namespace DragDrop
