/* Copyright © 2022-2023 Fern Zapata
 * This program is subject to the terms of the GNU GPL, version 3
 * or, at your option, any later version. If a copy of it was not
 * included with this file, see https://www.gnu.org/licenses/. */

#include "window.hh"
#include "dragarea.hh"
#include "droparea.hh"
#include <QVBoxLayout>
#include <QTextStream>
#include <QTimer>

namespace DragDrop {

Window::Window(const QList<QFileInfo>& files, const Options& opts,
               QWidget* parent)
	: QDialog(parent)
	, m_opts(opts)
	, m_term(opts & Option::Null ? '\0' : '\n')
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
		QTimer::singleShot(500, this, &Window::close);
	}
}

void Window::onFilesReceived(const QList<QUrl>& files)
{
	QTextStream out(stdout);
	for (const auto& f : files) {
		out << (m_opts & Option::URIs ? f.url() : f.path())
		    << m_term
		    << Qt::flush;
	}

	if (m_opts & Option::Once) {
		close();
	}
}

}; // namespace DragDrop
