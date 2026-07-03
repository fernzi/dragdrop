/* Copyright © 2024-2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#pragma once

#include "options.hh"
#include <QCoreApplication>
#include <QUrl>

namespace DragDrop {

class Server;

class Application : public QCoreApplication
{
	Q_OBJECT

public:
	Application(int& argc, char** argv);
	auto exec() -> int;

private:
  Options mOpts;
  QString mServerName;
  Server* mServer = nullptr;

private slots:
  void onReceivedURLs(QList<QUrl> const& urls) const;
};

}; // namespace DragDrop
