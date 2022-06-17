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

	for (const auto& file : files) {
		addFile(file);
	}
}

QSize DragArea::sizeHint() const
{
	auto screen_h = screen()->size().height();
	return QSize(sizeHintForColumn(0),
	             qMin(sizeHintForRow(0) * count(), screen_h / 3));
}

QStringList DragArea::mimeTypes() const
{
	return QStringList(QStringLiteral("text/uri-list"));
}

QMimeData* DragArea::mimeData(const QList<QListWidgetItem*> items) const
{
	auto data = new QMimeData;
	QList<QUrl> urls;
	for (const auto& item : items) {
		urls << item->data(Qt::UserRole).toUrl();
	}
	data->setUrls(urls);
	return data;
}

void DragArea::startDrag(Qt::DropActions actions)
{
	QListWidget::startDrag(actions);
	emit filesSent();
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
