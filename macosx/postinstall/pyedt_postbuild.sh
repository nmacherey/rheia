#!/bin/sh

LOCALDIR=../../devel/Release
CONTENTS=$LOCALDIR/pyedt.app/Contents
BINDIR=$LOCALDIR/bin
LIBDIR=$LOCALDIR/lib
SHAREDIR=$LOCALDIR/share
APPNAME=pyedt

rm -rf ../../devel/Release/pyedt.app

mkdir -p $CONTENTS
mkdir -p $CONTENTS/Resources
mkdir -p $CONTENTS/MacOS
mkdir -p $CONTENTS/lib
mkdir -p $CONTENTS/Resources/share/$APPNAME

cp -r $BINDIR/$APPNAME $CONTENTS/MacOS/$APPNAME
cp -r $LIBDIR/*.so.* $CONTENTS/lib
cp -r $SHAREDIR/$APPNAME/* $CONTENTS/Resources/share/$APPNAME
cp icon.icns $CONTENTS/Resources/icon.icns
cp docicon.icns $CONTENTS/Resources/icon.icns
cp pyedtInfo.plist $CONTENTS/Info.plist

install_name_tool -id @executable_path/../lib/libgmirrlicht.so.1.6.1 $CONTENTS/lib/libgmirrlicht.so.1.6.1
install_name_tool -id @executable_path/../lib/librheiautils.so.1.1.1 $CONTENTS/lib/librheiautils.so.1.1.1
install_name_tool -id @executable_path/../lib/librheiabase.so.1.1.1 $CONTENTS/lib/librheiabase.so.1.1.1
install_name_tool -id @executable_path/../lib/librheialoggers.so.1.1.1 $CONTENTS/lib/librheialoggers.so.1.1.1
install_name_tool -id @executable_path/../lib/librheiapackagemgt.so.1.1.1 $CONTENTS/lib/librheiapackagemgt.so.1.1.1
install_name_tool -id @executable_path/../lib/librheiaworkspacemgt.so.1.1.1 $CONTENTS/lib/librheiaworkspacemgt.so.1.1.1
install_name_tool -id @executable_path/../lib/libgmcsirocsa.so.1.1.1 $CONTENTS/lib/libgmcsirocsa.so.1.1.1
install_name_tool -id @executable_path/../lib/libgmqsastime.so.1.1.1 $CONTENTS/lib/libgmqsastime.so.1.1.1
install_name_tool -id @executable_path/../lib/libgmplplot.so.1.1.1 $CONTENTS/lib/libgmplplot.so.1.1.1
install_name_tool -id @executable_path/../lib/libgmwxplplot.so.1.1.1 $CONTENTS/lib/libgmwxplplot.so.1.1.1

#plplot 
install_name_tool -change $LIBDIR/libgmcsirocsa.so.1.1.1 @executable_path/../lib/libgmcsirocsa.so.1.1.1 $CONTENTS/lib/libgmplplot.so.1.1.1
install_name_tool -change $LIBDIR/libgmqsastime.so.1.1.1 @executable_path/../lib/libgmqsastime.so.1.1.1 $CONTENTS/lib/libgmplplot.so.1.1.1

#wxplplot
install_name_tool -change $LIBDIR/libgmcsirocsa.so.1.1.1 @executable_path/../lib/libgmcsirocsa.so.1.1.1 $CONTENTS/lib/libgmwxplplot.so.1.1.1
install_name_tool -change $LIBDIR/libgmqsastime.so.1.1.1 @executable_path/../lib/libgmqsastime.so.1.1.1 $CONTENTS/lib/libgmwxplplot.so.1.1.1
install_name_tool -change $LIBDIR/libgmplplot.so.1.1.1 @executable_path/../lib/libgmplplot.so.1.1.1 $CONTENTS/lib/libgmwxplplot.so.1.1.1

#rheiautils
install_name_tool -change $LIBDIR/libgmirrlicht.so.1.6.1 @executable_path/../lib/libgmirrlicht.so.1.6.1 $CONTENTS/lib/librheiautils.so.1.1.1
install_name_tool -change $LIBDIR/libgmcsirocsa.so.1.1.1 @executable_path/../lib/libgmcsirocsa.so.1.1.1 $CONTENTS/lib/librheiautils.so.1.1.1
install_name_tool -change $LIBDIR/libgmqsastime.so.1.1.1 @executable_path/../lib/libgmqsastime.so.1.1.1 $CONTENTS/lib/librheiautils.so.1.1.1
install_name_tool -change $LIBDIR/libgmplplot.so.1.1.1 @executable_path/../lib/libgmplplot.so.1.1.1 $CONTENTS/lib/librheiautils.so.1.1.1
install_name_tool -change $LIBDIR/libgmwxplplot.so.1.1.1 @executable_path/../lib/libgmwxplplot.so.1.1.1 $CONTENTS/lib/librheiautils.so.1.1.1

#rheiabase
install_name_tool -change $LIBDIR/libgmirrlicht.so.1.6.1 @executable_path/../lib/libgmirrlicht.so.1.6.1 $CONTENTS/lib/librheiabase.so.1.1.1
install_name_tool -change $LIBDIR/libgmcsirocsa.so.1.1.1 @executable_path/../lib/libgmcsirocsa.so.1.1.1 $CONTENTS/lib/librheiabase.so.1.1.1
install_name_tool -change $LIBDIR/libgmqsastime.so.1.1.1 @executable_path/../lib/libgmqsastime.so.1.1.1 $CONTENTS/lib/librheiabase.so.1.1.1
install_name_tool -change $LIBDIR/libgmplplot.so.1.1.1 @executable_path/../lib/libgmplplot.so.1.1.1 $CONTENTS/lib/librheiabase.so.1.1.1
install_name_tool -change $LIBDIR/libgmwxplplot.so.1.1.1 @executable_path/../lib/libgmwxplplot.so.1.1.1 $CONTENTS/lib/librheiabase.so.1.1.1
install_name_tool -change ../$LIBDIR/librheiautils.so.1.1.1 @executable_path/../lib/librheiautils.so.1.1.1 $CONTENTS/lib/librheiabase.so.1.1.1

#rheialoggers
install_name_tool -change $LIBDIR/libgmirrlicht.so.1.6.1 @executable_path/../lib/libgmirrlicht.so.1.6.1 $CONTENTS/lib/librheialoggers.so.1.1.1
install_name_tool -change $LIBDIR/libgmcsirocsa.so.1.1.1 @executable_path/../lib/libgmcsirocsa.so.1.1.1 $CONTENTS/lib/librheialoggers.so.1.1.1
install_name_tool -change $LIBDIR/libgmqsastime.so.1.1.1 @executable_path/../lib/libgmqsastime.so.1.1.1 $CONTENTS/lib/librheialoggers.so.1.1.1
install_name_tool -change $LIBDIR/libgmplplot.so.1.1.1 @executable_path/../lib/libgmplplot.so.1.1.1 $CONTENTS/lib/librheialoggers.so.1.1.1
install_name_tool -change $LIBDIR/libgmwxplplot.so.1.1.1 @executable_path/../lib/libgmwxplplot.so.1.1.1 $CONTENTS/lib/librheialoggers.so.1.1.1
install_name_tool -change ../$LIBDIR/librheiautils.so.1.1.1 @executable_path/../lib/librheiautils.so.1.1.1 $CONTENTS/lib/librheialoggers.so.1.1.1
install_name_tool -change ../$LIBDIR/librheiabase.so.1.1.1 @executable_path/../lib/librheiabase.so.1.1.1 $CONTENTS/lib/librheialoggers.so.1.1.1

#rheiapackagemgt
install_name_tool -change $LIBDIR/libgmirrlicht.so.1.6.1 @executable_path/../lib/libgmirrlicht.so.1.6.1 $CONTENTS/lib/librheiapackagemgt.so.1.1.1
install_name_tool -change $LIBDIR/libgmcsirocsa.so.1.1.1 @executable_path/../lib/libgmcsirocsa.so.1.1.1 $CONTENTS/lib/librheiapackagemgt.so.1.1.1
install_name_tool -change $LIBDIR/libgmqsastime.so.1.1.1 @executable_path/../lib/libgmqsastime.so.1.1.1 $CONTENTS/lib/librheiapackagemgt.so.1.1.1
install_name_tool -change $LIBDIR/libgmplplot.so.1.1.1 @executable_path/../lib/libgmplplot.so.1.1.1 $CONTENTS/lib/librheiapackagemgt.so.1.1.1
install_name_tool -change $LIBDIR/libgmwxplplot.so.1.1.1 @executable_path/../lib/libgmwxplplot.so.1.1.1 $CONTENTS/lib/librheiapackagemgt.so.1.1.1
install_name_tool -change ../$LIBDIR/librheiautils.so.1.1.1 @executable_path/../lib/librheiautils.so.1.1.1 $CONTENTS/lib/librheiapackagemgt.so.1.1.1
install_name_tool -change ../$LIBDIR/librheiabase.so.1.1.1 @executable_path/../lib/librheiabase.so.1.1.1 $CONTENTS/lib/librheiapackagemgt.so.1.1.1
install_name_tool -change ../$LIBDIR/librheialoggers.so.1.1.1 @executable_path/../lib/librheialoggers.so.1.1.1 $CONTENTS/lib/librheiapackagemgt.so.1.1.1

#rheiaworkspacemgt
install_name_tool -change $LIBDIR/libgmirrlicht.so.1.6.1 @executable_path/../lib/libgmirrlicht.so.1.6.1 $CONTENTS/lib/librheiaworkspacemgt.so.1.1.1
install_name_tool -change $LIBDIR/libgmcsirocsa.so.1.1.1 @executable_path/../lib/libgmcsirocsa.so.1.1.1 $CONTENTS/lib/librheiaworkspacemgt.so.1.1.1
install_name_tool -change $LIBDIR/libgmqsastime.so.1.1.1 @executable_path/../lib/libgmqsastime.so.1.1.1 $CONTENTS/lib/librheiaworkspacemgt.so.1.1.1
install_name_tool -change $LIBDIR/libgmplplot.so.1.1.1 @executable_path/../lib/libgmplplot.so.1.1.1 $CONTENTS/lib/librheiaworkspacemgt.so.1.1.1
install_name_tool -change $LIBDIR/libgmwxplplot.so.1.1.1 @executable_path/../lib/libgmwxplplot.so.1.1.1 $CONTENTS/lib/librheiaworkspacemgt.so.1.1.1
install_name_tool -change ../$LIBDIR/librheiautils.so.1.1.1 @executable_path/../lib/librheiautils.so.1.1.1 $CONTENTS/lib/librheiaworkspacemgt.so.1.1.1
install_name_tool -change ../$LIBDIR/librheiabase.so.1.1.1 @executable_path/../lib/librheiabase.so.1.1.1 $CONTENTS/lib/librheiaworkspacemgt.so.1.1.1
install_name_tool -change ../$LIBDIR/librheialoggers.so.1.1.1 @executable_path/../lib/librheialoggers.so.1.1.1 $CONTENTS/lib/librheiaworkspacemgt.so.1.1.1
install_name_tool -change ../$LIBDIR/librheiapackagemgt.so.1.1.1 @executable_path/../lib/librheiapackagemgt.so.1.1.1 $CONTENTS/lib/librheiaworkspacemgt.so.1.1.1

#rheiapython
install_name_tool -change $LIBDIR/libgmirrlicht.so.1.6.1 @executable_path/../lib/libgmirrlicht.so.1.6.1 $CONTENTS/lib/librheiapython.so.1.1.1
install_name_tool -change $LIBDIR/libgmcsirocsa.so.1.1.1 @executable_path/../lib/libgmcsirocsa.so.1.1.1 $CONTENTS/lib/librheiapython.so.1.1.1
install_name_tool -change $LIBDIR/libgmqsastime.so.1.1.1 @executable_path/../lib/libgmqsastime.so.1.1.1 $CONTENTS/lib/librheiapython.so.1.1.1
install_name_tool -change $LIBDIR/libgmplplot.so.1.1.1 @executable_path/../lib/libgmplplot.so.1.1.1 $CONTENTS/lib/librheiapython.so.1.1.1
install_name_tool -change $LIBDIR/libgmwxplplot.so.1.1.1 @executable_path/../lib/libgmwxplplot.so.1.1.1 $CONTENTS/lib/librheiapython.so.1.1.1
install_name_tool -change ../$LIBDIR/librheiautils.so.1.1.1 @executable_path/../lib/librheiautils.so.1.1.1 $CONTENTS/lib/librheiapython.so.1.1.1
install_name_tool -change ../$LIBDIR/librheiabase.so.1.1.1 @executable_path/../lib/librheiabase.so.1.1.1 $CONTENTS/lib/librheiapython.so.1.1.1
install_name_tool -change ../$LIBDIR/librheialoggers.so.1.1.1 @executable_path/../lib/librheialoggers.so.1.1.1 $CONTENTS/lib/librheiapython.so.1.1.1
install_name_tool -change ../$LIBDIR/librheiapackagemgt.so.1.1.1 @executable_path/../lib/librheiapackagemgt.so.1.1.1 $CONTENTS/lib/librheiapython.so.1.1.1
install_name_tool -change ../$LIBDIR/librheiaworkspacemgt.so.1.1.1 @executable_path/../lib/librheiaworkspacemgt.so.1.1.1 $CONTENTS/lib/librheiapython.so.1.1.1

#rheia
install_name_tool -change $LIBDIR/libgmirrlicht.so.1.6.1 @executable_path/../lib/libgmirrlicht.so.1.6.1 $CONTENTS/MacOS/$APPNAME
install_name_tool -change ../$LIBDIR/librheiautils.so.1.1.1 @executable_path/../lib/librheiautils.so.1.1.1 $CONTENTS/MacOS/$APPNAME
install_name_tool -change ../$LIBDIR/librheiabase.so.1.1.1 @executable_path/../lib/librheiabase.so.1.1.1 $CONTENTS/MacOS/$APPNAME
install_name_tool -change ../$LIBDIR/librheiapython.so.1.1.1 @executable_path/../lib/librheiapython.so.1.1.1 $CONTENTS/MacOS/$APPNAME
install_name_tool -change ../$LIBDIR/librheialoggers.so.1.1.1 @executable_path/../lib/librheialoggers.so.1.1.1 $CONTENTS/MacOS/$APPNAME
install_name_tool -change ../$LIBDIR/librheiapackagemgt.so.1.1.1 @executable_path/../lib/librheiapackagemgt.so.1.1.1 $CONTENTS/MacOS/$APPNAME
install_name_tool -change ../$LIBDIR/librheiaworkspacemgt.so.1.1.1 @executable_path/../lib/librheiaworkspacemgt.so.1.1.1 $CONTENTS/MacOS/$APPNAME
install_name_tool -change $LIBDIR/libgmcsirocsa.so.1.1.1 @executable_path/../lib/libgmcsirocsa.so.1.1.1 $CONTENTS/MacOS/$APPNAME
install_name_tool -change $LIBDIR/libgmqsastime.so.1.1.1 @executable_path/../lib/libgmqsastime.so.1.1.1 $CONTENTS/MacOS/$APPNAME
install_name_tool -change $LIBDIR/libgmplplot.so.1.1.1 @executable_path/../lib/libgmplplot.so.1.1.1 $CONTENTS/MacOS/$APPNAME
install_name_tool -change $LIBDIR/libgmwxplplot.so.1.1.1 @executable_path/../lib/libgmwxplplot.so.1.1.1 $CONTENTS/MacOS/$APPNAME
