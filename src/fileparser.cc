/* Copyright © 2025-2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "fileparser.hh"
#include <QCborStreamReader>
#include <QIODevice>

using namespace Qt::StringLiterals;

namespace {

auto decodeString(QCborStreamReader& reader) -> QString
{
  QString str;
  str.reserve(reader.currentStringChunkSize());

  while (true) {
    auto res = reader.readString();
    if (res.status == QCborStreamReader::EndOfString) {
      return str;
    }
    if (res.status != QCborStreamReader::Ok) {
      return u""_s;
    }
    str += res.data;
  }
}

template<typename F>
void handleStream(QCborStreamReader& mReader, F onParsed)
{
  switch (mReader.type()) {
    case QCborStreamReader::ByteArray:
    case QCborStreamReader::String:
      onParsed(decodeString(mReader));
      break;
    case QCborStreamReader::Array:
      mReader.enterContainer();
      while (not mReader.lastError() and mReader.hasNext()) {
        handleStream(mReader, onParsed);
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
  handleStream(reader, [this](auto const& url) { emit parsedURL(url); });
  emit finished();
}

}; // namespace DragDrop
