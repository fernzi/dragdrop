/* Copyright © 2025 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "signalhandler.hh"
#include <array>
#include <csignal>
#include <sys/socket.h>

static auto sockfd = std::array<int, 2> {};

static void dispatchSignal(int sig)
{
	Q_ASSERT(sockfd[0]);
	if (::write(sockfd[0], &sig, sizeof(sig)) == -1) {
		qFatal("Could not write to the signal socket");
	}
}

namespace DragDrop {

SignalHandler::SignalHandler(QObject* parent)
	: QObject(parent)
{
	if (not sockfd[0]) {
		if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sockfd.data())) {
			qFatal("Could not create signal socket pair");
		}
	}

	mNotifier
		= new QSocketNotifier(sockfd[1], QSocketNotifier::Read, this);
	connect(mNotifier, &QSocketNotifier::activated, this,
		&SignalHandler::checkSocket);
}

void SignalHandler::connectSignal(int sig)
{
	mSignals << sig;

	struct sigaction action = {};
	action.sa_handler = dispatchSignal;
	action.sa_flags |= SA_RESTART;
	sigemptyset(&action.sa_mask);

	if (::sigaction(sig, &action, nullptr)) {
		qFatal("Could not set up signal `%d` callback", sig);
	}
}

void SignalHandler::checkSocket()
{
	Q_ASSERT(sockfd[1]);
	mNotifier->setEnabled(false);

	auto sig = 0;
	if (::read(sockfd[1], &sig, sizeof(sig)) != sizeof(sig)) {
		qWarning("No bytes read on the signal socket");
	}
	qDebug("Signal `%d` received", sig);

	if (mSignals.contains(sig)) {
		emit activated(sig);
	}

	mNotifier->setEnabled(true);
}

} // namespace DragDrop
