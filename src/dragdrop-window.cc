/* DragDrop --- Drag and drop source for the command line
 * Copyright © 2022 Fern Zapata
 * This program is subject to the terms of the GNU GPL, either
 * version 3 of the License or (at your option) any later version.
 * You should have received a copy of the License along with this
 * file. If not, see <https://www.gnu.org/licenses/>. */

#include "dragdrop-window.hh"
#include "dragdrop-dragarea.hh"
#include "dragdrop-droparea.hh"
#include <QVBoxLayout>
#include <QTextStream>

namespace DragDrop {

Window::Window(QList<QFileInfo> files, bool uris, bool once,
               QWidget* parent)
	: QDialog(parent)
	, m_uris(uris)
	, m_once(once)
{
	setWindowTitle(tr("Drag and Drop"));

	auto layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	QWidget* area;
	if (files.isEmpty()) {
		area = new DropArea;
		connect(static_cast<DropArea*>(area), &DropArea::filesReceived,
		        this, &Window::onFilesReceived);
	} else {
		area = new DragArea(files);
		connect(static_cast<DragArea*>(area), &DragArea::filesSent,
		        this, &Window::onFilesSent);
	}
	layout->addWidget(area);
}

void Window::onFilesSent(QList<QUrl> files)
{
	if (m_once) {
		close();
	}
}

void Window::onFilesReceived(QList<QUrl> files)
{
	QStringList paths;
	QTextStream out(stdout);
	for (auto i = files.constBegin(); i != files.constEnd(); ++i) {
		out << (m_uris ? i->url() : i->path()) << Qt::endl;
	}

	if (m_once) {
		close();
	}
}

}; // namespace DragDrop
