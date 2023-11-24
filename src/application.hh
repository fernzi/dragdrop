/* Copyright © 2022 Fern Zapata
 * This program is subject to the terms of the GNU GPL, version 3
 * or, at your option, any later version. If a copy of it was not
 * included with this file, see https://www.gnu.org/licenses/. */

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
