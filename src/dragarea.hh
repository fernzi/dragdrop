/* Copyright © 2022-2024 Fern Zapata
 * This program is subject to the terms of the GNU GPL, version 3
 * or, at your option, any later version. If a copy of it was not
 * included with this file, see https://www.gnu.org/licenses/. */

#pragma once

#include <QListWidget>
#include <QFileInfo>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#define DAREA_REF &
#else
#define DAREA_REF
#endif

namespace DragDrop {

class DragArea : public QListWidget
{
	Q_OBJECT

public:
	DragArea(const QList<QFileInfo>& files, QWidget* parent = nullptr);
	QSize sizeHint() const override;

	void addFile(const QFileInfo& file);

protected:
	void startDrag(Qt::DropActions actions) override;
	QStringList mimeTypes() const override;
	QMimeData* mimeData(const QList<QListWidgetItem*>DAREA_REF items) const override;

signals:
	void filesSent();
};

}; // namespace DragDrop
