/* Copyright © 2022-2025 Fern Zapata
 * This file is under the terms of the GNU GPL ver. 3, or (at your
 * option) any later version. If a copy of the GPL wasn't included
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "window.hh"

namespace DragDrop {

Window::Window(const QList<QFileInfo>& files, QWidget* parent)
	: QDialog(parent)
	, mOutput(this)
	, mWriter(&mOutput)
	, mLayout(this)
	, mDrag(files, this)
	, mDrop(this)
{
	setWindowTitle(tr("Drag and Drop"));

	if (not mOutput.open(stdout, QIODevice::WriteOnly)) {
		close();
	}

	connect(&mDrop, &DropArea::filesRecv, this, &Window::onFilesRecv);
	connect(&mDrag, &DragArea::filesSent, this, &Window::onFilesSent);

	mLayout.addWidget(&mDrop);
	mLayout.addWidget(&mDrag);

	if (mDrag.count()) {
		mLayout.setCurrentWidget(&mDrag);
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
