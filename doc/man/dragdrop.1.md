# DRAGDROP 1 2023-04-13 "DragDrop @PROJECT_VERSION@"

## NAME

dragdrop - file drag-and-drop source

## SYNOPSIS

**dragdrop** [**-0houv**] [_files_...]

## DESCRIPTION

The **dragdrop** utility acts as a source or sink
for dragging and dropping files into programs running in a terminal emulator.

When started with file names as its arguments,
it will display those files in a window
from which they can be dragged into a graphical application,
like a file manager or web browser.
If started with no files specified,
the window will act as a sink in which files can be dropped
and their paths will be printed to the standard output.

The options are as follows:

**-0, --null**
: Separate printed paths with a null character.

**-o, --once**
: Exit after a single drag or drop.

**-u, --uris**
: Print URIs instead of file paths on drop.

**--dirs-first**
: List directories before files on the source dialog.

**-h, --help**
: Show help information, then exit.

**-v, --version**
: Show version information, then exit.

## AUTHORS

Written by Fern Zapata. Current sources can be found at:
: https://github.com/fernzi/dragdrop

## COPYRIGHT

Copyright © 2022 Fern Zapata.

License GPLv3+: GNU GPL version 3 or later:
: https://gnu.org/licenses/gpl.html

This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
