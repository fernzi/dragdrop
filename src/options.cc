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
  auto args = QCommandLineParser();
  args.setApplicationDescription(
    qo::tr("Drag-and-drop file source for the terminal"));
  args.addHelpOption();
  args.addVersionOption();

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

  args.addOptions(opts);
  args.addPositionalArgument(
    "files", qo::tr("Files to display"), qo::tr("[files...]"));

  args.process(app);

  once = args.isSet(opts[0]);
  uris = args.isSet(opts[1]);
  null = args.isSet(opts[2]);
  dirs_first = args.isSet(opts[3]);
  files = args.positionalArguments();
}

} // namespace DragDrop
