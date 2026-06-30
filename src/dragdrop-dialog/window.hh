/* Copyright © 2022-2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#pragma once

#include "dragarea.hh"
#include "droparea.hh"
#include <QCborStreamWriter>
#include <QDialog>
#include <QFileInfo>
#include <QStackedLayout>
#include <QUrl>
#include <QLocalSocket>

namespace DragDrop {

class Window : public QDialog
{
	Q_OBJECT

public:
	Window(QWidget* parent = nullptr);

	void addFile(QFileInfo const& file);
	void setOnce(bool once);

public slots:
	void onFilesRecv(const QList<QUrl>& files);
	void onFilesSent();

private:
	void waitAndExit();

  bool mOnce = false;
  QLocalSocket mOutput;
	QCborStreamWriter mWriter;
	QStackedLayout mLayout;
	DragArea mDrag;
	DropArea mDrop;
};

} // namespace DragDrop
