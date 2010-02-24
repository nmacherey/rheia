#!/bin/sh

LOCALDIR=../../devel/Debug
CONTENTS=$LOCALDIR/pyedt.app/Contents
BINDIR=$LOCALDIR/bin
LIBDIR=$LOCALDIR/lib
SHAREDIR=$LOCALDIR/share
APPNAME=pyedt

rm -rf ../../devel/Debud/pyedt.app

mkdir -p $CONTENTS
mkdir -p $CONTENTS/Resources
mkdir -p $CONTENTS/MacOS
mkdir -p $CONTENTS/lib
mkdir -p $CONTENTS/Resources/share/$APPNAME

cp -r $BINDIR/pyedt-dbg $CONTENTS/MacOS/$APPNAME
cp -r $LIBDIR/*-dbg.so.* $CONTENTS/lib
cp -r $SHAREDIR/$APPNAME/* $CONTENTS/Resources/share/$APPNAME
cp icon.icns $CONTENTS/Resources/icon.icns
cp docicon.icns $CONTENTS/Resources/icon.icns
cp pyedtInfo.plist $CONTENTS/Info.plist

install_name_tool -id @executable_path/../lib/libgmirrlicht-dbg.so.1.6.1 $CONTENTS/lib/libgmirrlicht-dbg.so.1.6.1
install_name_tool -id @executable_path/../lib/librheiautils-dbg.so.1.1.1 $CONTENTS/lib/librheiautils-dbg.so.1.1.1
install_name_tool -id @executable_path/../lib/librheiabase-dbg.so.1.1.1 $CONTENTS/lib/librheiabase-dbg.so.1.1.1
install_name_tool -id @executable_path/../lib/librheialoggers-dbg.so.1.1.1 $CONTENTS/lib/librheialoggers-dbg.so.1.1.1
install_name_tool -id @executable_path/../lib/librheiapackagemgt-dbg.so.1.1.1 $CONTENTS/lib/librheiapackagemgt-dbg.so.1.1.1
install_name_tool -id @executable_path/../lib/librheiaworkspacemgt-dbg.so.1.1.1 $CONTENTS/lib/librheiaworkspacemgt-dbg.so.1.1.1
install_name_tool -id @executable_path/../lib/libgmcsirocsa-dbg.so.1.1.1 $CONTENTS/lib/libgmcsirocsa-dbg.so.1.1.1
install_name_tool -id @executable_path/../lib/libgmqsastime-dbg.so.1.1.1 $CONTENTS/lib/libgmqsastime-dbg.so.1.1.1
install_name_tool -id @executable_path/../lib/libgmplplot-dbg.so.1.1.1 $CONTENTS/lib/libgmplplot-dbg.so.1.1.1
install_name_tool -id @executable_path/../lib/libgmwxplplot-dbg.so.1.1.1 $CONTENTS/lib/libgmwxplplot-dbg.so.1.1.1

#plplot 
install_name_tool -change $LIBDIR/libgmcsirocsa-dbg.so.1.1.1 @executable_path/../lib/libgmcsirocsa-dbg.so.1.1.1 $CONTENTS/lib/libgmplplot-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmqsastime-dbg.so.1.1.1 @executable_path/../lib/libgmqsastime-dbg.so.1.1.1 $CONTENTS/lib/libgmplplot-dbg.so.1.1.1

#wxplplot
install_name_tool -change $LIBDIR/libgmcsirocsa-dbg.so.1.1.1 @executable_path/../lib/libgmcsirocsa-dbg.so.1.1.1 $CONTENTS/lib/libgmwxplplot-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmqsastime-dbg.so.1.1.1 @executable_path/../lib/libgmqsastime-dbg.so.1.1.1 $CONTENTS/lib/libgmwxplplot-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmplplot-dbg.so.1.1.1 @executable_path/../lib/libgmplplot-dbg.so.1.1.1 $CONTENTS/lib/libgmwxplplot-dbg.so.1.1.1

#rheiautils
install_name_tool -change $LIBDIR/libgmirrlicht-dbg.so.1.6.1 @executable_path/../lib/libgmirrlicht-dbg.so.1.6.1 $CONTENTS/lib/librheiautils-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmcsirocsa-dbg.so.1.1.1 @executable_path/../lib/libgmcsirocsa-dbg.so.1.1.1 $CONTENTS/lib/librheiautils-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmqsastime-dbg.so.1.1.1 @executable_path/../lib/libgmqsastime-dbg.so.1.1.1 $CONTENTS/lib/librheiautils-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmplplot-dbg.so.1.1.1 @executable_path/../lib/libgmplplot-dbg.so.1.1.1 $CONTENTS/lib/librheiautils-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmwxplplot-dbg.so.1.1.1 @executable_path/../lib/libgmwxplplot-dbg.so.1.1.1 $CONTENTS/lib/librheiautils-dbg.so.1.1.1

#rheiabase
install_name_tool -change $LIBDIR/libgmirrlicht-dbg.so.1.6.1 @executable_path/../lib/libgmirrlicht-dbg.so.1.6.1 $CONTENTS/lib/librheiabase-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmcsirocsa-dbg.so.1.1.1 @executable_path/../lib/libgmcsirocsa-dbg.so.1.1.1 $CONTENTS/lib/librheiabase-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmqsastime-dbg.so.1.1.1 @executable_path/../lib/libgmqsastime-dbg.so.1.1.1 $CONTENTS/lib/librheiabase-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmplplot-dbg.so.1.1.1 @executable_path/../lib/libgmplplot-dbg.so.1.1.1 $CONTENTS/lib/librheiabase-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmwxplplot-dbg.so.1.1.1 @executable_path/../lib/libgmwxplplot-dbg.so.1.1.1 $CONTENTS/lib/librheiabase-dbg.so.1.1.1
install_name_tool -change ../$LIBDIR/librheiautils-dbg.so.1.1.1 @executable_path/../lib/librheiautils-dbg.so.1.1.1 $CONTENTS/lib/librheiabase-dbg.so.1.1.1

#rheialoggers
install_name_tool -change $LIBDIR/libgmirrlicht-dbg.so.1.6.1 @executable_path/../lib/libgmirrlicht-dbg.so.1.6.1 $CONTENTS/lib/librheialoggers-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmcsirocsa-dbg.so.1.1.1 @executable_path/../lib/libgmcsirocsa-dbg.so.1.1.1 $CONTENTS/lib/librheialoggers-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmqsastime-dbg.so.1.1.1 @executable_path/../lib/libgmqsastime-dbg.so.1.1.1 $CONTENTS/lib/librheialoggers-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmplplot-dbg.so.1.1.1 @executable_path/../lib/libgmplplot-dbg.so.1.1.1 $CONTENTS/lib/librheialoggers-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmwxplplot-dbg.so.1.1.1 @executable_path/../lib/libgmwxplplot-dbg.so.1.1.1 $CONTENTS/lib/librheialoggers-dbg.so.1.1.1
install_name_tool -change ../$LIBDIR/librheiautils-dbg.so.1.1.1 @executable_path/../lib/librheiautils-dbg.so.1.1.1 $CONTENTS/lib/librheialoggers-dbg.so.1.1.1
install_name_tool -change ../$LIBDIR/librheiabase-dbg.so.1.1.1 @executable_path/../lib/librheiabase-dbg.so.1.1.1 $CONTENTS/lib/librheialoggers-dbg.so.1.1.1

#rheiapackagemgt
install_name_tool -change $LIBDIR/libgmirrlicht-dbg.so.1.6.1 @executable_path/../lib/libgmirrlicht-dbg.so.1.6.1 $CONTENTS/lib/librheiapackagemgt-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmcsirocsa-dbg.so.1.1.1 @executable_path/../lib/libgmcsirocsa-dbg.so.1.1.1 $CONTENTS/lib/librheiapackagemgt-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmqsastime-dbg.so.1.1.1 @executable_path/../lib/libgmqsastime-dbg.so.1.1.1 $CONTENTS/lib/librheiapackagemgt-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmplplot-dbg.so.1.1.1 @executable_path/../lib/libgmplplot-dbg.so.1.1.1 $CONTENTS/lib/librheiapackagemgt-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmwxplplot-dbg.so.1.1.1 @executable_path/../lib/libgmwxplplot-dbg.so.1.1.1 $CONTENTS/lib/librheiapackagemgt-dbg.so.1.1.1
install_name_tool -change ../$LIBDIR/librheiautils-dbg.so.1.1.1 @executable_path/../lib/librheiautils-dbg.so.1.1.1 $CONTENTS/lib/librheiapackagemgt-dbg.so.1.1.1
install_name_tool -change ../$LIBDIR/librheiabase-dbg.so.1.1.1 @executable_path/../lib/librheiabase-dbg.so.1.1.1 $CONTENTS/lib/librheiapackagemgt-dbg.so.1.1.1
install_name_tool -change ../$LIBDIR/librheialoggers-dbg.so.1.1.1 @executable_path/../lib/librheialoggers-dbg.so.1.1.1 $CONTENTS/lib/librheiapackagemgt-dbg.so.1.1.1

#rheiaworkspacemgt
install_name_tool -change $LIBDIR/libgmirrlicht-dbg.so.1.6.1 @executable_path/../lib/libgmirrlicht-dbg.so.1.6.1 $CONTENTS/lib/librheiaworkspacemgt-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmcsirocsa-dbg.so.1.1.1 @executable_path/../lib/libgmcsirocsa-dbg.so.1.1.1 $CONTENTS/lib/librheiaworkspacemgt-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmqsastime-dbg.so.1.1.1 @executable_path/../lib/libgmqsastime-dbg.so.1.1.1 $CONTENTS/lib/librheiaworkspacemgt-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmplplot-dbg.so.1.1.1 @executable_path/../lib/libgmplplot-dbg.so.1.1.1 $CONTENTS/lib/librheiaworkspacemgt-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmwxplplot-dbg.so.1.1.1 @executable_path/../lib/libgmwxplplot-dbg.so.1.1.1 $CONTENTS/lib/librheiaworkspacemgt-dbg.so.1.1.1
install_name_tool -change ../$LIBDIR/librheiautils-dbg.so.1.1.1 @executable_path/../lib/librheiautils-dbg.so.1.1.1 $CONTENTS/lib/librheiaworkspacemgt-dbg.so.1.1.1
install_name_tool -change ../$LIBDIR/librheiabase-dbg.so.1.1.1 @executable_path/../lib/librheiabase-dbg.so.1.1.1 $CONTENTS/lib/librheiaworkspacemgt-dbg.so.1.1.1
install_name_tool -change ../$LIBDIR/librheialoggers-dbg.so.1.1.1 @executable_path/../lib/librheialoggers-dbg.so.1.1.1 $CONTENTS/lib/librheiaworkspacemgt-dbg.so.1.1.1
install_name_tool -change ../$LIBDIR/librheiapackagemgt-dbg.so.1.1.1 @executable_path/../lib/librheiapackagemgt-dbg.so.1.1.1 $CONTENTS/lib/librheiaworkspacemgt-dbg.so.1.1.1

#rheiapython
install_name_tool -change $LIBDIR/libgmirrlicht-dbg.so.1.6.1 @executable_path/../lib/libgmirrlicht-dbg.so.1.6.1 $CONTENTS/lib/librheiapython-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmcsirocsa-dbg.so.1.1.1 @executable_path/../lib/libgmcsirocsa-dbg.so.1.1.1 $CONTENTS/lib/librheiapython-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmqsastime-dbg.so.1.1.1 @executable_path/../lib/libgmqsastime-dbg.so.1.1.1 $CONTENTS/lib/librheiapython-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmplplot-dbg.so.1.1.1 @executable_path/../lib/libgmplplot-dbg.so.1.1.1 $CONTENTS/lib/librheiapython-dbg.so.1.1.1
install_name_tool -change $LIBDIR/libgmwxplplot-dbg.so.1.1.1 @executable_path/../lib/libgmwxplplot-dbg.so.1.1.1 $CONTENTS/lib/librheiapython-dbg.so.1.1.1
install_name_tool -change ../$LIBDIR/librheiautils-dbg.so.1.1.1 @executable_path/../lib/librheiautils-dbg.so.1.1.1 $CONTENTS/lib/librheiapython-dbg.so.1.1.1
install_name_tool -change ../$LIBDIR/librheiabase-dbg.so.1.1.1 @executable_path/../lib/librheiabase-dbg.so.1.1.1 $CONTENTS/lib/librheiapython-dbg.so.1.1.1
install_name_tool -change ../$LIBDIR/librheialoggers-dbg.so.1.1.1 @executable_path/../lib/librheialoggers-dbg.so.1.1.1 $CONTENTS/lib/librheiapython-dbg.so.1.1.1
install_name_tool -change ../$LIBDIR/librheiapackagemgt-dbg.so.1.1.1 @executable_path/../lib/librheiapackagemgt-dbg.so.1.1.1 $CONTENTS/lib/librheiapython-dbg.so.1.1.1
install_name_tool -change ../$LIBDIR/librheiaworkspacemgt-dbg.so.1.1.1 @executable_path/../lib/librheiaworkspacemgt-dbg.so.1.1.1 $CONTENTS/lib/librheiapython-dbg.so.1.1.1

#rheia
install_name_tool -change $LIBDIR/libgmirrlicht-dbg.so.1.6.1 @executable_path/../lib/libgmirrlicht-dbg.so.1.6.1 $CONTENTS/MacOS/$APPNAME
install_name_tool -change ../$LIBDIR/librheiautils-dbg.so.1.1.1 @executable_path/../lib/librheiautils-dbg.so.1.1.1 $CONTENTS/MacOS/$APPNAME
install_name_tool -change ../$LIBDIR/librheiabase-dbg.so.1.1.1 @executable_path/../lib/librheiabase-dbg.so.1.1.1 $CONTENTS/MacOS/$APPNAME
install_name_tool -change ../$LIBDIR/librheiapython-dbg.so.1.1.1 @executable_path/../lib/librheiapython-dbg.so.1.1.1 $CONTENTS/MacOS/$APPNAME
install_name_tool -change ../$LIBDIR/librheialoggers-dbg.so.1.1.1 @executable_path/../lib/librheialoggers-dbg.so.1.1.1 $CONTENTS/MacOS/$APPNAME
install_name_tool -change ../$LIBDIR/librheiapackagemgt-dbg.so.1.1.1 @executable_path/../lib/librheiapackagemgt-dbg.so.1.1.1 $CONTENTS/MacOS/$APPNAME
install_name_tool -change ../$LIBDIR/librheiaworkspacemgt-dbg.so.1.1.1 @executable_path/../lib/librheiaworkspacemgt-dbg.so.1.1.1 $CONTENTS/MacOS/$APPNAME
install_name_tool -change $LIBDIR/libgmcsirocsa-dbg.so.1.1.1 @executable_path/../lib/libgmcsirocsa-dbg.so.1.1.1 $CONTENTS/MacOS/$APPNAME
install_name_tool -change $LIBDIR/libgmqsastime-dbg.so.1.1.1 @executable_path/../lib/libgmqsastime-dbg.so.1.1.1 $CONTENTS/MacOS/$APPNAME
install_name_tool -change $LIBDIR/libgmplplot-dbg.so.1.1.1 @executable_path/../lib/libgmplplot-dbg.so.1.1.1 $CONTENTS/MacOS/$APPNAME
install_name_tool -change $LIBDIR/libgmwxplplot-dbg.so.1.1.1 @executable_path/../lib/libgmwxplplot-dbg.so.1.1.1 $CONTENTS/MacOS/$APPNAME
