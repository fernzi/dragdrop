/* Copyright © 2025-2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#pragma once

#include "util.hh"
#include <QCborStreamWriter>
#include <QObject>

namespace DragDrop {

class FileParser : public QObject
{
  Q_OBJECT

public:
  explicit FileParser(QIODevice* device, QObject* parent = nullptr);

  static void writeStrings(
    QIODevice* device, Util::SizedRangeOf<QString> auto&& strings)
  {
    auto writer = QCborStreamWriter(device);
    writer.startArray(std::ranges::size(strings));
    for (auto const& val : strings) {
      writer.append(val);
    }
    writer.endArray();
  }

signals:
  void parsedStrings(QStringList const& strings);

private:
  QIODevice* mDevice;

private slots:
  void onRead();
};

}; // namespace DragDrop
