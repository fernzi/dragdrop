/* Copyright © 2022-2025 Fern Zapata
 * This file is under the terms of the GNU GPL ver. 3, or (at your
 * option) any later version. If a copy of the GPL wasn't included
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "window.hh"
#include "dragarea.hh"
#include "droparea.hh"
#include <QVBoxLayout>

namespace DragDrop {

Window::Window(const QList<QFileInfo>& files, QWidget* parent)
	: QDialog(parent)
	, mOutput(this)
	, mWriter(&mOutput)
{
	setWindowTitle(tr("Drag and Drop"));

	if (not mOutput.open(stdout, QIODevice::WriteOnly)) {
		close();
	}

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
	mWriter.append(QCborSimpleType::Null);
	mOutput.flush();
}

void Window::onFilesReceived(const QList<QUrl>& files)
{
	mWriter.startArray(files.length());
	for (const auto& f : files) {
		mWriter.append(f.url());
	}
	mWriter.endArray();
	mOutput.flush();
}

}; // namespace DragDrop
