/* Copyright © 2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#pragma once

#include <QCoreApplication>
#include <QStringList>

namespace DragDrop {

struct Options
{
  bool once = false;
  bool uris = false;
  bool null = false;
  bool dirsFirst = false;
  QString serverSocket;
  QStringList files;

  explicit Options(QCoreApplication const& app);
  explicit Options(QStringList const& args);

private:
  void init(QCoreApplication const* app, QStringList const* args);
};

} // namespace DragDrop
