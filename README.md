# DragDrop

A small drag-and-drop source for the command line.

Have you ever noticed how a lot of things
(specially web apps) now expect you to drag files into them,
rather than using the good ol' file browser dialog?
But doing that it's not particularly comfortable
when you don't really use a file manager,
or prefer a command line one.

So instead of having to launch a graphical file manager
each time you need some files dragged,
you can use `dragdrop` to get a quick pop-up
dialog with files ready to drag right from the terminal.

You can run something like

```sh
dragdrop file1.png file2.txt file3.cc
```

to get a source to drag files from, or just

```sh
dragdrop
```

on its own to get a sink to drop files into,
which will then print their names into the standard output.

See the manual at [dragdrop(1)](doc/man/dragdrop.1.scd)
for all the detailed options.

## Installation

If DragDrop is not available
from your favourite distro's repositories,
you'll need to build it from source.
So first you have to install its dependencies.

Package naming is not consistent across all distributions,
but you'll probably have some luck with these:

```sh
# For Debian, Ubuntu, and derivatives:
apt install build-essential cmake qtbase5-dev scdoc

# For Arch, Manjaro, and the rest:
pacman -S base-devel cmake qt5-base scdoc
```

Once that's installed,
you can use CMake to build the program with the commands

```sh
cmake -B build .
cmake --build build
cmake --install build
```

which should build and install DragDrop
into the `/usr/local` prefix by default.
