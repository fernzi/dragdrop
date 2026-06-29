/* Copyright © 2025-2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#pragma once

#include <QProcess>

namespace DragDrop {

class Process : public QProcess
{
	Q_OBJECT

public:
	Process(QObject* parent = nullptr);
	~Process() override;
};

} // namespace DragDrop
