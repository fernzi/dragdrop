/* Copyright © 2024 Fern Zapata
 * This file is under the terms of the GNU GPL ver. 3.
 * If a copy of the GNU GPL was not included with this
 * file, see <https://www.gnu.org/licenses/>. */

#include "application.hh"

int main(int argc, char** argv)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	DragDrop::Application::setAttribute(Qt::AA_EnableHighDpiScaling);
	DragDrop::Application::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
	return DragDrop::Application(argc, argv).exec();
}
