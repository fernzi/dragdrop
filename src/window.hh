/* Copyright © 2022-2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#pragma once

#include "dragarea.hh"
#include "droparea.hh"
#include "util.hh"
#include <QDialog>
#include <QFileInfo>
#include <QStackedLayout>
#include <QUrl>

namespace DragDrop {

class Window : public QDialog
{
  Q_OBJECT

public:
  explicit Window(QWidget* parent = nullptr);

  void addFile(QFileInfo const& file);
  void addFiles(Util::RangeOf<QFileInfo> auto&& files)
  {
    for (const auto& file : files) {
      mDrag.addFile(file);
    }
    mLayout.setCurrentWidget(&mDrag);
  }

signals:
  void filesRecv(const QList<QUrl>& files);
  void filesSent();

private:
  QStackedLayout mLayout;
  DragArea mDrag;
  DropArea mDrop;
};

} // namespace DragDrop
