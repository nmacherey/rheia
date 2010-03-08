#!/bin/sh

SWIG_OPTIONS="-new_repr -modern -fastdispatch -fvirtual -fastinit -fastunpack"
INCLUDES="-I../../include/rheia/utils -I../../include/rheia/base -I../../include/rheia/python -I../../include/rheia/loggers -I../../include/rheia/packagemgt -I../../include/rheia/workspacemgt -I/home/nicolas/Desktop/xvirc/wx291/wxPython/src -I../utils -I../base -I../loggers -I../workspacemgt -I../packagemgt"
WRAPPER_LANGUAGE="-c++"
GENERATED_LANGUAGE="-python"
FLAGS="-DLINUX"

# first create swig for rheia utils
cd utils
swig $SWIG_OPTIONS $INCLUDES $FLAGS $WRAPPER_LANGUAGE $GENERATED_LANGUAGE utils.i
cd ..
echo Rheia utils python swig created

cd base
swig $SWIG_OPTIONS $INCLUDES $FLAGS $WRAPPER_LANGUAGE $GENERATED_LANGUAGE base.i
echo Rheia base python swig created
cd ..

cd loggers
swig $SWIG_OPTIONS $INCLUDES $FLAGS $WRAPPER_LANGUAGE $GENERATED_LANGUAGE loggers.i
echo Rheia loggers python swig created
cd ..

cd packagemgt
swig $SWIG_OPTIONS $INCLUDES $FLAGS $WRAPPER_LANGUAGE $GENERATED_LANGUAGE packagemgt.i
echo Rheia packagemgt python swig created
cd ..

cd workspacemgt
swig $SWIG_OPTIONS $INCLUDES $FLAGS $WRAPPER_LANGUAGE $GENERATED_LANGUAGE workspacemgt.i
echo Rheia workspacemgt python swig created
cd ..
