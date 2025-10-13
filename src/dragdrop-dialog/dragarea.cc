/* Copyright © 2022-2023 Fern Zapata
 * This program is subject to the terms of the GNU GPL, version 3
 * or, at your option, any later version. If a copy of it was not
 * included with this file, see https://www.gnu.org/licenses/. */

#include "dragarea.hh"
#include <QDrag>
#include <QListWidgetItem>
#include <QMimeData>
#include <QMimeDatabase>
#include <QScreen>
#include <QUrl>

namespace DragDrop {

DragArea::DragArea(QWidget* parent)
	: QListWidget(parent)
{
	setSelectionMode(DragArea::ExtendedSelection);
	setDragDropMode(DragArea::DragOnly);
	setIconSize(QSize(32, 32));
	setFrameShape(DragArea::NoFrame);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setSizeAdjustPolicy(DragArea::AdjustToContents);
}

auto DragArea::sizeHint() const -> QSize
{
	auto screen_h = screen()->size().height();
	return QSize(sizeHintForColumn(0),
		qMin(sizeHintForRow(0) * count(), screen_h / 3));
}

auto DragArea::mimeTypes() const -> QStringList
{
	return QStringList(QStringLiteral("text/uri-list"));
}

auto DragArea::mimeData(
	const QList<QListWidgetItem*> DAREA_REF items) const -> QMimeData*
{
	auto data = new QMimeData;
	QList<QUrl> urls;
	for (auto const& item : items) {
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

void DragArea::addFile(QFileInfo const& file)
{
	static QMimeDatabase mime;
	auto type = mime.mimeTypeForFile(file);
	auto icon = QIcon::fromTheme(type.iconName());
	auto item = new QListWidgetItem(icon, file.fileName(), this);
	item->setData(
		Qt::UserRole, QUrl::fromLocalFile(file.canonicalFilePath()));
}

}; // namespace DragDrop
