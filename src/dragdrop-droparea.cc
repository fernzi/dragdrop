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
	: QWidget(parent)
{
	setAcceptDrops(true);
	auto layout = new QVBoxLayout(this);
	layout->setContentsMargins(32, 32, 32, 32);
	layout->setAlignment(Qt::AlignCenter);
	auto icon = QIcon::fromTheme("folder-open-symbolic");
	auto label = new QLabel;
	label->setPixmap(icon.pixmap(48));
	layout->addWidget(label, Qt::AlignCenter);
}

void DropArea::dragEnterEvent(QDragEnterEvent* event)
{
	if (event->mimeData()->hasUrls()) {
		event->accept();
	} else {
		event->ignore();
	}
}

void DropArea::dropEvent(QDropEvent* event)
{
	emit filesReceived(event->mimeData()->urls());
}

}; // namespace DragDrop
