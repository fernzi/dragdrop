/* DragDrop --- Drag and drop source for the command line
 * Copyright © 2022 Fern Zapata
 * This program is subject to the terms of the GNU GPL, either
 * version 3 of the License or (at your option) any later version.
 * You should have received a copy of the License along with this
 * file. If not, see <https://www.gnu.org/licenses/>. */

#include "dragdrop-dragarea.hh"
#include <QDrag>
#include <QListWidgetItem>
#include <QMimeData>
#include <QMimeDatabase>
#include <QScreen>
#include <QUrl>

namespace DragDrop {

DragArea::DragArea(QList<QFileInfo> files, QWidget* parent)
	: QListWidget(parent)
{
	setSelectionMode(DragArea::ExtendedSelection);
	setDragDropMode(DragArea::DragOnly);
	setIconSize(QSize(32, 32));
	setFrameShape(DragArea::NoFrame);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setSizeAdjustPolicy(DragArea::AdjustToContents);

	for (auto i = files.constBegin(); i != files.constEnd(); ++i) {
		addFile(*i);
	}
}

QSize DragArea::sizeHint() const {
	auto screen_h = screen()->size().height();
	return QSize(sizeHintForColumn(0),
	             qMin(sizeHintForRow(0) * count(), screen_h / 3));
}

void DragArea::startDrag(Qt::DropActions actions)
{
	auto items = selectedItems();
	auto mime = new QMimeData;
	QList<QUrl> urls;
	for (auto i = items.constBegin(); i != items.constEnd(); ++i) {
		urls << (*i)->data(Qt::UserRole).toUrl();
	}
	mime->setUrls(urls);
	auto drag = new QDrag(this);
	drag->setMimeData(mime);

	auto res = drag->exec(Qt::CopyAction | Qt::LinkAction);
	if (res != Qt::IgnoreAction) {
		emit filesSent(urls);
	}
}

void DragArea::addFile(QFileInfo file)
{
	static QMimeDatabase mime;
	auto type = mime.mimeTypeForFile(file);
	auto icon = QIcon::fromTheme(type.iconName());
	auto item = new QListWidgetItem(icon, file.fileName(), this);
	item->setData(
		Qt::UserRole, QUrl::fromLocalFile(file.canonicalFilePath()));
}

}; // namespace DragDrop
