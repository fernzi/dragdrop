/* DragDrop --- Drag and drop source for the command line
 * Copyright © 2022 Fern Zapata
 * This program is subject to the terms of the GNU GPL, either
 * version 3 of the License or (at your option) any later version.
 * You should have received a copy of the License along with this
 * file. If not, see <https://www.gnu.org/licenses/>. */

#ifndef DRAGDROP_APPLICATION_HH
#define DRAGDROP_APPLICATION_HH

#include <QApplication>
#include <QCommandLineParser>

namespace DragDrop {

class Application : public QApplication
{
	Q_OBJECT

public:
	Application(int& argc, char** argv);
	int exec();

private:
	QCommandLineParser parser;
};

}; // namespace DragDrop

#endif // DRAGDROP_APPLICATION_HH
