/* Copyright © 2024-2025 Fern Zapata
 * This file is under the terms of the GNU GPL ver. 3, or (at your
 * option) any later version. If a copy of the GPL wasn't included
 * along with this file, see <https://www.gnu.org/licenses/>. */

#pragma once

#include "process.hh"
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QUrl>
#include <fileparser.hh>

namespace DragDrop {

class Application : public QCoreApplication
{
	Q_OBJECT

public:
	Application(int& argc, char** argv);
	auto exec() -> int;

private:
	QCommandLineParser args;
	Process mProg;
	QTextStream mOutput;
	FileParser mParser;

private slots:
	void parserOutput(QUrl url);
	void parserFinished();
};

}; // namespace DragDrop
