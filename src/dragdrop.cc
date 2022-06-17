/* DragDrop --- Drag and drop source for the command line
 * Copyright © 2022 Fern Zapata
 * This program is subject to the terms of the GNU GPL, either
 * version 3 of the License or (at your option) any later version.
 * You should have received a copy of the License along with this
 * file. If not, see <https://www.gnu.org/licenses/>. */

#include "dragdrop-application.hh"

int main(int argc, char** argv)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	DragDrop::Application::setAttribute(Qt::AA_EnableHighDpiScaling);
	DragDrop::Application::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
	return DragDrop::Application(argc, argv).exec();
}
