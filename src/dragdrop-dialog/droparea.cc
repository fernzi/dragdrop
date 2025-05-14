/* Copyright © 2022-2025 Fern Zapata
 * This file is under the terms of the GNU GPL ver. 3, or (at your
 * option) any later version. If a copy of the GPL wasn't included
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "droparea.hh"
#include <QDragEnterEvent>
#include <QIcon>
#include <QLabel>
#include <QMimeData>
#include <QVBoxLayout>

namespace DragDrop {

DropArea::DropArea(QWidget* parent)
	: QLabel(parent)
{
	setAcceptDrops(true);
	setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	setPixmap(QIcon::fromTheme("folder-open-symbolic").pixmap(48));
}

void DropArea::dragEnterEvent(QDragEnterEvent* event)
{
	if (event->mimeData()->hasUrls()) {
		event->acceptProposedAction();
	}
}

void DropArea::dropEvent(QDropEvent* event)
{
	emit filesRecv(event->mimeData()->urls());
	event->setDropAction(Qt::CopyAction);
	event->accept();
}

}; // namespace DragDrop
