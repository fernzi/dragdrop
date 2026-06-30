/* Copyright © 2025 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#pragma once

#include <QCborStreamReader>
#include <QFileInfo>
#include <QIODevice>
#include <QUrl>

namespace DragDrop {

class FileParser : public QObject
{
	Q_OBJECT

public:
	FileParser(QIODevice* device, QObject* parent = nullptr);

signals:
	void parsedURL(QUrl url);
	void finished();

private:
	QIODevice* mDevice;
	QCborStreamReader mReader;

	void handleStream();

private slots:
	void onRead();
};

}; // namespace DragDrop
