/* Copyright © 2022-2025 Fern Zapata
 * This file is under the terms of the GNU GPL ver. 3, or (at your
 * option) any later version. If a copy of the GPL wasn't included
 * along with this file, see <https://www.gnu.org/licenses/>. */

#pragma once

#include "dragarea.hh"
#include "droparea.hh"
#include <QCborStreamWriter>
#include <QDialog>
#include <QFileInfo>
#include <QStackedLayout>
#include <QUrl>

namespace DragDrop {

class Window : public QDialog
{
	Q_OBJECT

public:
	Window(const QList<QFileInfo>& files, QWidget* parent = nullptr);

public slots:
	void onFilesRecv(const QList<QUrl>& files);
	void onFilesSent();

private:
	QFile mOutput;
	QCborStreamWriter mWriter;
	QStackedLayout mLayout;
	DragArea mDrag;
	DropArea mDrop;
};

} // namespace DragDrop
