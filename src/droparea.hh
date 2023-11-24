/* Copyright © 2022 Fern Zapata
 * This program is subject to the terms of the GNU GPL, version 3
 * or, at your option, any later version. If a copy of it was not
 * included with this file, see https://www.gnu.org/licenses/. */

#ifndef DRAGDROP_DROPAREA_HH
#define DRAGDROP_DROPAREA_HH

#include <QLabel>
#include <QUrl>

namespace DragDrop {

class DropArea : public QLabel
{
	Q_OBJECT

public:
	DropArea(QWidget* parent = nullptr);

protected:
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dropEvent(QDropEvent* event) override;

signals:
	void filesReceived(const QList<QUrl>& urls);
};

}; // namespace DragDrop

#endif // DRAGDROP_DROPAREA_HH
