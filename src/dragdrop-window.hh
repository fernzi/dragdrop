/* DragDrop --- Drag and drop source for the command line
 * Copyright © 2022 Fern Zapata
 * This program is subject to the terms of the GNU GPL, either
 * version 3 of the License or (at your option) any later version.
 * You should have received a copy of the License along with this
 * file. If not, see <https://www.gnu.org/licenses/>. */

#ifndef DRAGDROP_WINDOW_HH
#define DRAGDROP_WINDOW_HH

#include <QDialog>
#include <QFileInfo>
#include <QUrl>

namespace DragDrop {

class Window : public QDialog
{
	Q_OBJECT

public:
	Window(QList<QFileInfo> files, QWidget* parent = nullptr);

public slots:
	void onFilesReceived(QList<QUrl> files);

private:
	bool m_uris;
	bool m_once;
};

}; // namespace DragDrop

#endif // DRAGDROP_WINDOW_HH
