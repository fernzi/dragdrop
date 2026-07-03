/* Copyright © 2022-2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "droparea.hh"
#include <QDragEnterEvent>
#include <QIcon>
#include <QLabel>
#include <QMimeData>
#include <QVBoxLayout>

using namespace Qt::StringLiterals;

namespace DragDrop {

DropArea::DropArea(QWidget* parent)
	: QLabel(parent)
{
	setAcceptDrops(true);
	setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  setPixmap(QIcon::fromTheme(u"folder-open-symbolic"_s).pixmap(48));
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
