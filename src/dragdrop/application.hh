/* Copyright © 2024-2025 Fern Zapata
 * This file is under the terms of the GNU GPL ver. 3, or (at your
 * option) any later version. If a copy of the GPL wasn't included
 * along with this file, see <https://www.gnu.org/licenses/>. */

#pragma once

#include <QCborStreamReader>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QProcess>

namespace DragDrop {

class Application : public QCoreApplication
{
	Q_OBJECT

public:
	Application(int& argc, char** argv);
	auto exec() -> int;

private:
	QCborStreamReader mReader;
	QCommandLineParser args;
	QProcess mProg;
	QTextStream mOutput;

private slots:
	void dialogOutput();
	void dialogFinished(int code, QProcess::ExitStatus exitStatus);
};

}; // namespace DragDrop
