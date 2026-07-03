/* Copyright © 2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#pragma once

#include <QCoreApplication>

namespace DragDrop {

struct Options
{
  bool once;
  bool uris;
  bool null;
  bool dirs_first;
  QStringList files;

  Options(QCoreApplication const& app);
};

} // namespace DragDrop
