/* Copyright © 2022-2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "window.hh"
#include <QApplication>
#include <QTimer>

namespace DragDrop {

Window::Window(QWidget* parent)
	: QDialog(parent)
	, mOutput(this)
	, mWriter(&mOutput)
	, mLayout(this)
	, mDrag(this)
	, mDrop(this)
{
	setWindowTitle(tr("Drag and Drop"));

  auto name = qEnvironmentVariable("DRAGDROP_SOCKET");
  mOutput.connectToServer(name);
  qDebug() << "client socket:" << mOutput.fullServerName();

	connect(&mDrop, &DropArea::filesRecv, this, &Window::onFilesRecv);
	connect(&mDrag, &DragArea::filesSent, this, &Window::onFilesSent);

	mLayout.addWidget(&mDrop);
	mLayout.addWidget(&mDrag);
}

void Window::addFile(QFileInfo const& file)
{
	mDrag.addFile(file);
	mLayout.setCurrentWidget(&mDrag);
}

void Window::setOnce(bool once)
{
	mOnce = once;
}

void Window::onFilesSent()
{
	mWriter.append(QCborSimpleType::Null);
	mOutput.flush();
	waitAndExit();
}

void Window::onFilesRecv(const QList<QUrl>& files)
{
	mWriter.startArray(files.length());
	for (const auto& f : files) {
		mWriter.append(f.url());
	}
	mWriter.endArray();
	mOutput.flush();
	waitAndExit();
}

void Window::waitAndExit()
{
	if (mOnce) {
		hide();
		QTimer::singleShot(30000, this, [] { QApplication::exit(); });
	}
}

}; // namespace DragDrop
