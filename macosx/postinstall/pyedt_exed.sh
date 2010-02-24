#!/bin/sh

# rheia.sh
# 
#
# Created by Nicolas Macherey on 24/02/10.
# Copyright 2010 __MyCompanyName__. All rights reserved.

DIR="`dirname \"$0\"`/.."

BIN="$DIR/MacOS"
LIB="$DIR/lib"

DYLD_LIBRARY_PATH="$DYLD_LIBRARY_PATH:$LIB:$DIR:$BIN"
export DYLD_LIBRARY_PATH

exec "$BIN/pyedt-dbg" --prefix="$DIR"




