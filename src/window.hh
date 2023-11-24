/* Copyright © 2022 Fern Zapata
 * This program is subject to the terms of the GNU GPL, version 3
 * or, at your option, any later version. If a copy of it was not
 * included with this file, see https://www.gnu.org/licenses/. */

#ifndef DRAGDROP_WINDOW_HH
#define DRAGDROP_WINDOW_HH

#include <QDialog>
#include <QFileInfo>
#include <QUrl>

namespace DragDrop {

class Window : public QDialog
{
	Q_OBJECT

public:
	enum Option {
		None = 0,
		URIs = 1 << 0,
		Once = 1 << 1,
		Null = 1 << 2,
	};
	Q_DECLARE_FLAGS(Options, Option)

	Window(const QList<QFileInfo>& files,
	       const Options& opts = Option::None,
	       QWidget* parent = nullptr);

public slots:
	void onFilesReceived(const QList<QUrl>& files);
	void onFilesSent();

private:
	const Options m_opts;
	const char m_term;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Window::Options)

}; // namespace DragDrop

#endif // DRAGDROP_WINDOW_HH
