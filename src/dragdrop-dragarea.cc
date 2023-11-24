/* Copyright © 2022-2023 Fern Zapata
 * This program is subject to the terms of the GNU GPL, version 3
 * or, at your option, any later version. If a copy of it was not
 * included with this file, see https://www.gnu.org/licenses/. */

#include "dragdrop-dragarea.hh"
#include <QDrag>
#include <QListWidgetItem>
#include <QMimeData>
#include <QMimeDatabase>
#include <QScreen>
#include <QUrl>

namespace DragDrop {

DragArea::DragArea(const QList<QFileInfo>& files, QWidget* parent)
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

QMimeData* DragArea::mimeData(const QList<QListWidgetItem*>DAREA_REF items) const
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

void DragArea::addFile(const QFileInfo& file)
{
	static QMimeDatabase mime;
	auto type = mime.mimeTypeForFile(file);
	auto icon = QIcon::fromTheme(type.iconName());
	auto item = new QListWidgetItem(icon, file.fileName(), this);
	item->setData(
		Qt::UserRole, QUrl::fromLocalFile(file.canonicalFilePath()));
}

}; // namespace DragDrop
