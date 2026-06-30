/* Copyright © 2025 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "fileparser.hh"

namespace DragDrop {

FileParser::FileParser(QIODevice* device, QObject* parent)
	: QObject(parent)
	, mDevice(device)
{
	connect(mDevice, &QIODevice::readyRead, this, &FileParser::onRead);
}

static auto decodeString(QCborStreamReader& reader)
{
	QString str;
	QCborStreamReader::StringResult<QString> r;
	while ((r = reader.readString()).status == QCborStreamReader::Ok) {
		str += r.data;
	}
	if (r.status == QCborStreamReader::Error) {
		str.clear();
	}
	return str;
}

void FileParser::handleStream()
{
	switch (mReader.type()) {
	case QCborStreamReader::ByteArray:
	case QCborStreamReader::String:
		emit parsedURL(decodeString(mReader));
		break;
	case QCborStreamReader::Array:
		mReader.enterContainer();
		while (not mReader.lastError() and mReader.hasNext()) {
			handleStream();
		}
		if (not mReader.lastError()) {
			mReader.leaveContainer();
		}
		break;
	default:
		mReader.next();
	}
}

void FileParser::onRead()
{
	mReader.setDevice(mDevice);
	handleStream();
	emit finished();
}

}; // namespace DragDrop
