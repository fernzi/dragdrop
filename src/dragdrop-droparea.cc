/* DragDrop --- Drag and drop source for the command line
 * Copyright © 2022 Fern Zapata
 * This program is subject to the terms of the GNU GPL, either
 * version 3 of the License or (at your option) any later version.
 * You should have received a copy of the License along with this
 * file. If not, see <https://www.gnu.org/licenses/>. */

#include "dragdrop-droparea.hh"
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
