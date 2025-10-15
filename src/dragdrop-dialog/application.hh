/* Copyright © 2022-2025 Fern Zapata
 * This file is under the terms of the GNU GPL ver. 3, or (at your
 * option) any later version. If a copy of the GPL wasn't included
 * along with this file, see <https://www.gnu.org/licenses/>. */

#pragma once

#include "window.hh"
#include <QApplication>
#include <QCommandLineParser>

namespace DragDrop {

class Application : public QApplication
{
	Q_OBJECT

public:
	Application(int& argc, char** argv);
	auto exec() -> int;

private:
	QCommandLineParser mArgs;
	Window mWindow;
};

}; // namespace DragDrop
