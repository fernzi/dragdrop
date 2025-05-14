/* Copyright © 2022-2025 Fern Zapata
 * This file is under the terms of the GNU GPL ver. 3, or (at your
 * option) any later version. If a copy of the GPL wasn't included
 * along with this file, see <https://www.gnu.org/licenses/>. */

#pragma once

#include <QLabel>
#include <QUrl>

namespace DragDrop {

class DropArea : public QLabel
{
	Q_OBJECT

public:
	DropArea(QWidget* parent = nullptr);

protected:
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dropEvent(QDropEvent* event) override;

signals:
	void filesRecv(const QList<QUrl>& urls);
};

}; // namespace DragDrop
