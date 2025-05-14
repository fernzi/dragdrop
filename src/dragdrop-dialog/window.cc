/* Copyright © 2022-2025 Fern Zapata
 * This file is under the terms of the GNU GPL ver. 3, or (at your
 * option) any later version. If a copy of the GPL wasn't included
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "window.hh"
#include "dragarea.hh"
#include "droparea.hh"
#include <QStackedLayout>

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

	auto layout = new QStackedLayout(this);
	auto drop = new DropArea(this);
	auto drag = new DragArea(files, this);

	connect(drop, &DropArea::filesRecv, this, &Window::onFilesRecv);
	connect(drag, &DragArea::filesSent, this, &Window::onFilesSent);

	layout->addWidget(drop);
	layout->addWidget(drag);

	if (drag->count()) {
		layout->setCurrentWidget(drag);
	}
}

void Window::onFilesSent()
{
	mWriter.append(QCborSimpleType::Null);
	mOutput.flush();
}

void Window::onFilesRecv(const QList<QUrl>& files)
{
	mWriter.startArray(files.length());
	for (const auto& f : files) {
		mWriter.append(f.url());
	}
	mWriter.endArray();
	mOutput.flush();
}

}; // namespace DragDrop
