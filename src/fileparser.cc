/* Copyright © 2025-2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "fileparser.hh"
#include <QCborStreamReader>
#include <QIODevice>

namespace {

auto decodeString(QCborStreamReader& reader) -> QString
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 7, 0)
  return reader.readAllString();
#else
  QString str;
  str.reserve(reader.currentStringChunkSize());

  decltype(reader.readString()) res;
  while ((res = reader.readString()).status == QCborStreamReader::Ok) {
    str += res.data;
  }
  return res.status != QCborStreamReader::Error ? str : QString{};
#endif
}

void handleStream(QCborStreamReader& mReader, QStringList& output)
{
  using enum QCborStreamReader::Type;

  switch (mReader.type()) {
    case ByteArray:
    case String:
      output.append(decodeString(mReader));
      break;
    case Array:
      mReader.enterContainer();
      while (not mReader.lastError() and mReader.hasNext()) {
        handleStream(mReader, output);
      }
      if (not mReader.lastError()) {
        mReader.leaveContainer();
      }
      break;
    default:
      mReader.next();
  }
}

} // namespace

namespace DragDrop {

FileParser::FileParser(QIODevice* device, QObject* parent)
  : QObject(parent)
  , mDevice(device)
{
  connect(mDevice, &QIODevice::readyRead, this, &FileParser::onRead);
}

void FileParser::onRead()
{
  static QCborStreamReader reader;
  reader.setDevice(mDevice);
  QStringList strings;
  handleStream(reader, strings);
  emit parsedStrings(strings);
}

}; // namespace DragDrop
