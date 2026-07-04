/* Copyright © 2022-2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#pragma once

#include <QFileInfo>
#include <QListWidget>

namespace DragDrop {

class DragArea : public QListWidget
{
	Q_OBJECT

public:
	DragArea(QWidget* parent = nullptr);
	auto sizeHint() const -> QSize override;

	void addFile(const QFileInfo& file);

protected:
	void startDrag(Qt::DropActions actions) override;
	auto mimeTypes() const -> QStringList override;
	auto mimeData(const QList<QListWidgetItem*>& items) const
		-> QMimeData* override;

signals:
	void filesSent();
};

}; // namespace DragDrop
