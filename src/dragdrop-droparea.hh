/* DragDrop --- Drag and drop source for the command line
 * Copyright © 2022 Fern Zapata
 * This program is subject to the terms of the GNU GPL, either
 * version 3 of the License or (at your option) any later version.
 * You should have received a copy of the License along with this
 * file. If not, see <https://www.gnu.org/licenses/>. */

#ifndef DRAGDROP_DROPAREA_HH
#define DRAGDROP_DROPAREA_HH

#include <QWidget>
#include <QUrl>

namespace DragDrop {

class DropArea : public QWidget
{
	Q_OBJECT

public:
	DropArea(QWidget* parent = nullptr);

protected:
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dropEvent(QDropEvent* event) override;

signals:
	void filesReceived(QList<QUrl> urls);
};

}; // namespace DragDrop

#endif // DRAGDROP_DROPAREA_HH
