#!/bin/sh
#

set -e

# Build premake
PREMAKE_DIR=premake/bin/macos
(cd $PREMAKE_DIR && make CONFIG=Release -CSrc -f Makefile)

# Autodetect wxWidgets settings
if wx-config --unicode >/dev/null 2>/dev/null; then
	unicode="--unicode"
fi
if ! wx-config --debug >/dev/null 2>/dev/null; then
	debug="--disable-wx-debug"
fi

plat="codelite"
wxver=""

for a in $*; do
   	if [ $a = "codelite" ]; then
   		plat="codelite"
	fi
	if [ $a = "codeblocks" ]; then
   		plat="codeblocks"
	fi
	if [ $a = "makefile-gnu" ]; then
   		plat="makefile-gnu"
	fi
	if [ $a = "--with-wx-28" ]; then
   		wxver="--with-wx-28"
	fi
done

if [ $plat = "codelite" ]; then
#build codelite
$PREMAKE_DIR/premake --target cl-gcc $unicode $debug $wxver
echo done...
echo
fi

if [ $plat = "codeblocks" ]; then
#build codeblocks
$PREMAKE_DIR/premake --target cb-gcc $unicode $debug $wxver
echo done...
echo
fi

if [ $plat = "makefile-gnu" ]; then
#build makefile
$PREMAKE_DIR/premake --target gnu $unicode $debug $wxver
echo done...
echo
fi
#
echo Done generating all project files for rheia.
