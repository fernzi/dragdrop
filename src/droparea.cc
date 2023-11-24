/* Copyright © 2022-2023 Fern Zapata
 * This program is subject to the terms of the GNU GPL, version 3
 * or, at your option, any later version. If a copy of it was not
 * included with this file, see https://www.gnu.org/licenses/. */

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
	setMargin(32);
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
	emit filesReceived(event->mimeData()->urls());
	event->setDropAction(Qt::CopyAction);
	event->accept();
}

}; // namespace DragDrop
