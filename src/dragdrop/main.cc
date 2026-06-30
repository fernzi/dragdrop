/* Copyright © 2024-2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "application.hh"

auto main(int argc, char** argv) -> int
{
  auto app = DragDrop::Application(argc, argv);
  return app.exec();
}
