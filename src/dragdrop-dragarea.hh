/* DragDrop --- Drag and drop source for the command line
 * Copyright © 2022 Fern Zapata
 * This program is subject to the terms of the GNU GPL, either
 * version 3 of the License or (at your option) any later version.
 * You should have received a copy of the License along with this
 * file. If not, see <https://www.gnu.org/licenses/>. */

#ifndef DRAGDROP_DRAGAREA_HH
#define DRAGDROP_DRAGAREA_HH

#include <QListWidget>
#include <QFileInfo>
#include <QUrl>

namespace DragDrop {

class DragArea : public QListWidget
{
	Q_OBJECT

public:
	DragArea(QList<QFileInfo> files, QWidget* parent = nullptr);
	QSize sizeHint() const override;

	void addFile(QFileInfo file);

protected:
	void startDrag(Qt::DropActions actions) override;

signals:
	void filesSent(QList<QUrl> files);
};

}; // namespace DragDrop

#endif // DRAGDROP_DRAGAREA_HH
