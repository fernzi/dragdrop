/* Copyright © 2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#pragma once

#include <concepts>
#include <ranges>
#include <QCborStreamWriter>

namespace DragDrop::Util {

template<typename R, typename T>
concept RangeOf = std::ranges::input_range<R> &&
                  std::convertible_to<std::ranges::range_reference_t<R>, T>;

template<typename R, typename T>
concept SizedRangeOf =
  std::ranges::sized_range<R> &&
  std::convertible_to<std::ranges::range_reference_t<R>, T>;

static void writeCborStrings(
  QIODevice* device, Util::SizedRangeOf<QString> auto&& strings)
{
  auto writer = QCborStreamWriter(device);
  writer.startArray(std::ranges::size(strings));
  for (auto const& val : strings) {
    writer.append(val);
  }
  writer.endArray();
}

} // namespace DragDrop
