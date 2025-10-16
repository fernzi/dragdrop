/* Copyright © 2025 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "process.hh"
#include <unistd.h>

static void modifyProcess()
{
	::setsid();
	::close_range(STDERR_FILENO + 1, std::numeric_limits<int>::max(),
		CLOSE_RANGE_CLOEXEC);
}

namespace DragDrop {

Process::Process(QObject* parent)
	: QProcess(parent)
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
	setChildProcessModifier(modifyProcess);
#endif
}

Process::~Process()
{
	// We want the dialog process to stay alive after quitting,
	// but `startDetached` makes it impossible to capture output,
	// so we just lie here so `QProcess` doesn't kill the dialog.

	if (state() == Running) {
		setProcessState(NotRunning);
	}
}

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
void Process::setupChildProcess()
{
	modifyProcess();
}
#endif

} // namespace DragDrop
