/* Copyright © 2022-2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "window.hh"

namespace DragDrop {

Window::Window(QWidget* parent)
	: QDialog(parent)
	, mLayout(this)
	, mDrag(this)
	, mDrop(this)
{
  setWindowTitle(tr("Drag & Drop"));

  connect(&mDrop, &DropArea::filesRecv, this, &Window::filesRecv);
  connect(&mDrag, &DragArea::filesSent, this, &Window::filesSent);

	mLayout.addWidget(&mDrop);
	mLayout.addWidget(&mDrag);
}

void Window::addFile(QFileInfo const& file)
{
	mDrag.addFile(file);
	mLayout.setCurrentWidget(&mDrag);
}

void Window::addFiles(QList<QFileInfo> const& files)
{
  for (const auto& file : files) {
    mDrag.addFile(file);
  }
  mLayout.setCurrentWidget(&mDrag);
}

}; // namespace DragDrop
