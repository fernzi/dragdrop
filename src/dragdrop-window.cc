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

Window::Window(const QList<QFileInfo>& files, const Options& opts,
               QWidget* parent)
	: QDialog(parent)
	, m_opts(opts)
{
	setWindowTitle(tr("Drag and Drop"));

	auto layout = new QVBoxLayout(this);
	layout->setContentsMargins({});
	QWidget* area = nullptr;
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

void Window::onFilesSent()
{
	if (m_opts & Option::Once) {
		close();
	}
}

void Window::onFilesReceived(const QList<QUrl>& files)
{
	QTextStream out(stdout);
	for (const auto& f : files) {
		out << (m_opts & Option::URIs ? f.url() : f.path())
		    << Qt::endl;
	}

	if (m_opts & Option::Once) {
		close();
	}
}

}; // namespace DragDrop
