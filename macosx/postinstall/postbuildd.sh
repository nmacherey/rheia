#!/bin/sh

LOCALDIR=../../devel/Debug
CONTENTS=$LOCALDIR/rheia_exe.app/Contents
BINDIR=$LOCALDIR/bin
LIBDIR=$LOCALDIR/lib
SHAREDIR=$LOCALDIR/share
APPNAME=rheia-dbg
APPNAME_EXE=rheia_exe
APPNAME_EXED=rheia_exed.sh

rm -rf ../../devel/Debug/rheia_exe.app

mkdir -p $CONTENTS
mkdir -p $CONTENTS/Resources
mkdir -p $CONTENTS/MacOS
mkdir -p $CONTENTS/Resources/share/$APPNAME

cp -r $BINDIR/$APPNAME $CONTENTS/MacOS/$APPNAME
cp -r $APPNAME_EXED $CONTENTS/MacOS/$APPNAME_EXE
chmod a+x $CONTENTS/MacOS/$APPNAME_EXE
cp -r $LIBDIR/* $CONTENTS/MacOS
cp -r $SHAREDIR/$APPNAME/* $CONTENTS/Resources/share/$APPNAME
cp icon.icns $CONTENTS/Resources/icon.icns
cp docicon.icns $CONTENTS/Resources/icon.icns
cp Info.plist $CONTENTS/Info.plist

#install_name_tool -id @executable_path/libgmirrlicht.so.1.6.1 $CONTENTS/MacOS/libgmirrlicht.so.1.6.1
#install_name_tool -id @executable_path/librheiautils.so.1.1.1 $CONTENTS/MacOS/librheiautils.so.1.1.1
#install_name_tool -id @executable_path/librheiabase.so.1.1.1 $CONTENTS/MacOS/librheiabase.so.1.1.1
#install_name_tool -id @executable_path/librheialoggers.so.1.1.1 $CONTENTS/MacOS/librheialoggers.so.1.1.1
#install_name_tool -id @executable_path/librheiapackagemgt.so.1.1.1 $CONTENTS/MacOS/librheiapackagemgt.so.1.1.1
#install_name_tool -id @executable_path/librheiaworkspacemgt.so.1.1.1 $CONTENTS/MacOS/librheiaworkspacemgt.so.1.1.1

#install_name_tool -change $LIBDIR/libgmirrlicht.so.1.6.1 @executable_path/libgmirrlicht.so.1.6.1 $CONTENTS/MacOS/libgmirrlicht.so.1.6.1
#install_name_tool -change $LIBDIR/librheiautils.so.1.1.1 @executable_path/librheiautils.so.1.1.1 $CONTENTS/MacOS/librheiautils.so.1.1.1
#install_name_tool -change $LIBDIR/librheiabase.so.1.1.1 @executable_path/librheiabase.so.1.1.1 $CONTENTS/MacOS/librheiabase.so.1.1.1
#install_name_tool -change $LIBDIR/librheiloggers.so.1.1.1 @executable_path/librheialoggers.so.1.1.1 $CONTENTS/MacOS/librheialoggers.so.1.1.1
#install_name_tool -change $LIBDIR/librheiapackagemgt.so.1.1.1 @executable_path/librheiapackagemgt.so.1.1.1 $CONTENTS/MacOS/librheiapackagemgt.so.1.1.1
#install_name_tool -change $LIBDIR/librheiaworkspacemgt.so.1.1.1 @executable_path/librheiaworkspacemgt.so.1.1.1 $CONTENTS/MacOS/librheiaworkspacemgt.so.1.1.1
