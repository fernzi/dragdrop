/* Copyright © 2026 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include "options.hh"
#include <QCommandLineParser>

using qo = QObject;

namespace DragDrop {

Options::Options(QCoreApplication const& app)
{
  init(&app, nullptr);
}

Options::Options(QStringList const& args)
{
  init(nullptr, &args);
}

void Options::init(QCoreApplication const* app, QStringList const* args)
{
  auto parser = QCommandLineParser();
  parser.setApplicationDescription(
    qo::tr("Drag-and-drop file source for the terminal"));
  parser.addHelpOption();
  parser.addVersionOption();

  auto opts = QList<QCommandLineOption>{
    {
      {"o", "once"},
      qo::tr("Exit after a single drag or drop."),
    },
    {
      {"u", "uris"},
      qo::tr("Print URIs instead of paths on drop."),
    },
    {
      {"0", "null"},
      qo::tr("Separate printed paths with a null character."),
    },
    {
      "dirs-first",
      qo::tr("List directories before files."),
    },
  };

  auto optServerSocket = QCommandLineOption{
    "server-socket",
    qo::tr("Local socket ID"),
    "socket",
  };
  // Why aren't these available on the constructor?
  optServerSocket.setFlags(QCommandLineOption::HiddenFromHelp);

  parser.addOptions(opts);
  parser.addOption(optServerSocket);
  parser.addPositionalArgument(
    "files", qo::tr("Files to display"), qo::tr("[files...]"));

  if (app) {
    parser.process(*app);
  } else {
    Q_ASSERT(args);
    parser.parse(*args);
  }

  once = parser.isSet(opts[0]);
  uris = parser.isSet(opts[1]);
  null = parser.isSet(opts[2]);
  dirsFirst = parser.isSet(opts[3]);
  serverSocket = parser.value(optServerSocket);
  files = parser.positionalArguments();
}

} // namespace DragDrop
