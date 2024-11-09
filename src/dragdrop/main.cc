/* Copyright © 2024 Fern Zapata
 * This file is under the terms of the GNU GPL ver. 3, or, at your
 * option, any later version. If a copy of the GPL wasn't included
 * with this file, see <https://www.gnu.org/licenses/>. */

#include "application.hh"

auto main(int argc, char** argv) -> int
{
	return DragDrop::Application(argc, argv).exec();
}
