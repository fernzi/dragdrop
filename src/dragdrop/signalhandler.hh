/* Copyright © 2025 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#pragma once

#include <QSet>
#include <QSocketNotifier>

namespace DragDrop {

class SignalHandler : public QObject
{
	Q_OBJECT

public:
	SignalHandler(QObject* parent = nullptr);

	void connectSignal(int sig);

	template <typename... Args> void connectSignals(Args... sigs)
	{
		(connectSignal(sigs), ...);
	}

signals:
	void activated(int signal);

private:
	QSet<int> mSignals;
	QSocketNotifier* mNotifier;

private slots:
	void checkSocket();
};

} // namespace DragDrop
