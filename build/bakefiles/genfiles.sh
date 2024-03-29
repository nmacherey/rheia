#!/bin/bash
# Author: Nicolas MACHEREY
# Creation date: 17/04/2010
#
# A simple script to generate the files.bkl so no need to add new files manually when 
# working on the application

# Let's first define the file name in which all this stuff will be generated
FILE=files.bkl
# Store the current directory
CURRENT_DIR=`pwd`

# Store the main rheia directory
RHEIA_DIR="$CURRENT_DIR/../../"

#utils directory stuff
UTILS_SRC_PREFIX="src/rheia/utils/"
UTILS_HDR_PREFIX="include/rheia/utils/"
UTILS_SRC_DIR=$RHEIA_DIR$UTILS_SRC_PREFIX
UTILS_HDR_DIR=$RHEIA_DIR$UTILS_HDR_PREFIX

#base directory stuff
BASE_SRC_PREFIX="src/rheia/base/"
BASE_HDR_PREFIX="include/rheia/base/"
BASE_SRC_DIR=$RHEIA_DIR$BASE_SRC_PREFIX
BASE_HDR_DIR=$RHEIA_DIR$BASE_HDR_PREFIX

#loggers directory stuff
LOGGERS_SRC_PREFIX="src/rheia/loggers/"
LOGGERS_HDR_PREFIX="include/rheia/loggers/"
LOGGERS_SRC_DIR=$RHEIA_DIR$LOGGERS_SRC_PREFIX
LOGGERS_HDR_DIR=$RHEIA_DIR$LOGGERS_HDR_PREFIX

#packagemgt directory stuff
PACKAGES_SRC_PREFIX="src/rheia/packagemgt/"
PACKAGES_HDR_PREFIX="include/rheia/packagemgt/"
PACKAGES_SRC_DIR=$RHEIA_DIR$PACKAGES_SRC_PREFIX
PACKAGES_HDR_DIR=$RHEIA_DIR$PACKAGES_HDR_PREFIX

#workspacemgt directory stuff
WORKSPACES_SRC_PREFIX="src/rheia/workspacemgt/"
WORKSPACES_HDR_PREFIX="include/rheia/workspacemgt/"
WORKSPACES_SRC_DIR=$RHEIA_DIR$WORKSPACES_SRC_PREFIX
WORKSPACES_HDR_DIR=$RHEIA_DIR$WORKSPACES_HDR_PREFIX

#editor directory stuff
EDITOR_SRC_PREFIX="src/rheia/editor/"
EDITOR_HDR_PREFIX="include/rheia/editor/"
EDITOR_SRC_DIR=$RHEIA_DIR$EDITOR_SRC_PREFIX
EDITOR_HDR_DIR=$RHEIA_DIR$EDITOR_HDR_PREFIX

#python directory stuff
PYTHON_SRC_PREFIX="src/rheia/python/"
PYTHON_HDR_PREFIX="include/rheia/python/"
PYTHON_SRC_DIR=$RHEIA_DIR$PYTHON_SRC_PREFIX
PYTHON_HDR_DIR=$RHEIA_DIR$PYTHON_HDR_PREFIX

#rheia directory stuff
RHEIA_SRC_PREFIX="src/rheia/"
RHEIA_HDR_PREFIX="include/rheia/"
RHEIA_SRC_DIR=$RHEIA_DIR$RHEIA_SRC_PREFIX
RHEIA_HDR_DIR=$RHEIA_DIR$RHEIA_HDR_PREFIX

#irrlicht jpeg stuff
IRRJPG_SRC_PREFIX="src/irrlicht/jpeglib/"
IRRJPG_HDR_PREFIX="src/irrlicht/jpeglib/"
IRRJPG_SRC_DIR=$RHEIA_DIR$IRRJPG_SRC_PREFIX
IRRJPG_HDR_DIR=$RHEIA_DIR$IRRJPG_HDR_PREFIX

#irrlicht png stuff
IRRPNG_SRC_PREFIX="src/irrlicht/libpng/"
IRRPNG_HDR_PREFIX="src/irrlicht/libpng/"
IRRPNG_SRC_DIR=$RHEIA_DIR$IRRPNG_SRC_PREFIX
IRRPNG_HDR_DIR=$RHEIA_DIR$IRRPNG_HDR_PREFIX

#irrlicht zlib stuff
IRRZLIB_SRC_PREFIX="src/irrlicht/zlib/"
IRRZLIB_HDR_PREFIX="src/irrlicht/zlib/"
IRRZLIB_SRC_DIR=$RHEIA_DIR$IRRZLIB_SRC_PREFIX
IRRZLIB_HDR_DIR=$RHEIA_DIR$IRRZLIB_HDR_PREFIX

#irrlicht macos stuff
IRRMACOS_SRC_PREFIX="src/irrlicht/MacOSX/"
IRRMACOS_HDR_PREFIX="src/irrlicht/MacOSX/"
IRRMACOS_SRC_DIR=$RHEIA_DIR$IRRMACOS_SRC_PREFIX
IRRMACOS_HDR_DIR=$RHEIA_DIR$IRRMACOS_HDR_PREFIX

#irrlicht stuff
IRRLICHT_SRC_PREFIX="src/irrlicht/"
IRRLICHT_HDR_PREFIX="include/irrlicht/"
IRRLICHT_SRC_DIR=$RHEIA_DIR$IRRLICHT_SRC_PREFIX
IRRLICHT_HDR_DIR=$RHEIA_DIR$IRRLICHT_HDR_PREFIX

#csirocsa stuff
CSIROCSA_SRC_PREFIX="src/csirocsa/"
CSIROCSA_HDR_PREFIX="include/csirocsa/"
CSIROCSA_SRC_DIR=$RHEIA_DIR$CSIROCSA_SRC_PREFIX
CSIROCSA_HDR_DIR=$RHEIA_DIR$CSIROCSA_HDR_PREFIX

#qsastime stuff
QSASTIME_SRC_PREFIX="src/qsastime/"
QSASTIME_HDR_PREFIX="include/qsastime/"
QSASTIME_SRC_DIR=$RHEIA_DIR$QSASTIME_SRC_PREFIX
QSASTIME_HDR_DIR=$RHEIA_DIR$QSASTIME_HDR_PREFIX

#wxwidgets plplot stuff
WXWIDGETS_SRC_PREFIX="src/wxwidgets/"
WXWIDGETS_HDR_PREFIX="include/wxwidgets/"
WXWIDGETS_SRC_DIR=$RHEIA_DIR$WXWIDGETS_SRC_PREFIX
WXWIDGETS_HDR_DIR=$RHEIA_DIR$WXWIDGETS_HDR_PREFIX

#plplot stuff
PLPLOT_SRC_PREFIX="src/plplot/"
PLPLOT_HDR_PREFIX="include/plplot/"
PLPLOT_SRC_DIR=$RHEIA_DIR$PLPLOT_SRC_PREFIX
PLPLOT_HDR_DIR=$RHEIA_DIR$PLPLOT_HDR_PREFIX

#wxplplot stuff
WXPLPLOT_SRC_PREFIX="src/wxplplot/"
WXPLPLOT_HDR_PREFIX="include/wxplplot/"
WXPLPLOT_SRC_DIR=$RHEIA_DIR$WXPLPLOT_SRC_PREFIX
WXPLPLOT_HDR_DIR=$RHEIA_DIR$WXPLPLOT_HDR_PREFIX

#wxplplot stuff
WEBCONNECT_SRC_PREFIX="webconnect/src/"
WEBCONNECT_HDR_PREFIX="webconnect/include/"
WEBCONNECT_SRC_DIR=$RHEIA_DIR$WEBCONNECT_SRC_PREFIX
WEBCONNECT_HDR_DIR=$RHEIA_DIR$WEBCONNECT_HDR_PREFIX


function ListAndSetFiles()
{
    	cd $1
	SRC=`ls $2`
	cd $CURRENT_DIR

	STR="<set var=\"$4\" hints=\"files\">"
	echo $STR >> $FILE

	for src in $SRC; do
		echo -e "\t" $3$src >> $FILE  
	done
	echo -e "</set>\n" >> $FILE
}

START="<?xml version=\"1.0\" ?>\n
<!-- Rheia Main Bakefile generated by foldink 16 April 2010 2:56:12 PM -->\n
<makefile>\n
\n
<!-- ======================================================================\n
\t\t\t\tFILES\n
\n
Files are listed in variables according to this scheme:\n
\n
\t\t+ each group has _SRC and _HDR variable, for sources and headers\n
\t\trespectively\n
\n
\t\t+ file groups are:\n
\n
\t\t\tRHEIA_UTILS\t\t\t\tRheia Framework Utils Library files\n
\t\t\tRHEIA_BASE\t\t\t\tRheia Framework Base Library files\n
\t\t\tRHEIA_LOGGERS\t\t\tRheia Framework Loggers Library files\n
\t\t\tRHEIA_PACKAGES\t\t\tRheia Framework Package Management Library files\n
\t\t\tRHEIA_WORKSPACES\t\tRheia Framework Workspace Management Library files\n
\t\t\tRHEIA_EDITOR\t\t\tRheia Framework Code Editor Library files\n
\t\t\tRHEIA_PYTHON\t\t\tRheia Framework Python Wrapping Library files\n
\t\t\tRHEIA\t\t\tRheia Demo Application Files\n
\n
\t\t+ one file may be listed in several groups\n
\n
====================================================================== -->\n
\n
\n
\n
<!-- ====================================================================== -->\n
<!-- \t\t\t\trheiautils -->\n
<!-- ====================================================================== -->\n"

echo -e $START > $FILE

###########################################################################################
# FILE LIST MANAGEMENT
#
# If you need to add a new component in rheia you shall modify the part bellow in 
# order to add your new component
###########################################################################################

######### UTILS SRC #############

ListAndSetFiles $UTILS_SRC_DIR "*.cpp" $UTILS_SRC_PREFIX "RHEIA_UTILS_SRC"

######### UTILS HDR #############

ListAndSetFiles $UTILS_HDR_DIR "*.h" $UTILS_HDR_PREFIX "RHEIA_UTILS_HDR"

STR="<!-- ====================================================================== -->\n
<!-- \t\t\t\trheiabase -->\n
<!-- ====================================================================== -->\n"
echo -e $STR >> $FILE

######### BASE SRC #############

ListAndSetFiles $BASE_SRC_DIR "*.cpp" $BASE_SRC_PREFIX "RHEIA_BASE_SRC"

######### BASE HDR #############

ListAndSetFiles $BASE_HDR_DIR "*.h" $BASE_HDR_PREFIX "RHEIA_BASE_HDR"

STR="<!-- ====================================================================== -->\n
<!-- \t\t\t\trheialoggers -->\n
<!-- ====================================================================== -->\n"
echo -e $STR >> $FILE

######### LOGGERS SRC #############

ListAndSetFiles $LOGGERS_SRC_DIR "*.cpp" $LOGGERS_SRC_PREFIX "RHEIA_LOGGERS_SRC"

######### LOGGERS HDR #############

ListAndSetFiles $LOGGERS_HDR_DIR "*.h" $LOGGERS_HDR_PREFIX "RHEIA_LOGGERS_HDR"

STR="<!-- ====================================================================== -->\n
<!-- \t\t\t\trheiapackagemgt -->\n
<!-- ====================================================================== -->\n"
echo -e $STR >> $FILE

######### PACKAGES SRC #############

ListAndSetFiles $PACKAGES_SRC_DIR "*.cpp" $PACKAGES_SRC_PREFIX "RHEIA_PACKAGES_SRC"

######### PACKAGES HDR #############

ListAndSetFiles $PACKAGES_HDR_DIR "*.h" $PACKAGES_HDR_PREFIX "RHEIA_PACKAGES_HDR"

STR="<!-- ====================================================================== -->\n
<!-- \t\t\t\trheiaworkspacemgt -->\n
<!-- ====================================================================== -->\n"
echo -e $STR >> $FILE

######### WORKSPACES SRC #############

ListAndSetFiles $WORKSPACES_SRC_DIR "*.cpp" $WORKSPACES_SRC_PREFIX "RHEIA_WORKSPACES_SRC"

######### WORKSPACES HDR #############

ListAndSetFiles $WORKSPACES_HDR_DIR "*.h" $WORKSPACES_HDR_PREFIX "RHEIA_WORKSPACES_HDR"

STR="<!-- ====================================================================== -->\n
<!-- \t\t\t\trheiaeditor -->\n
<!-- ====================================================================== -->\n"
echo -e $STR >> $FILE

######### EDITOR SRC #############

ListAndSetFiles $EDITOR_SRC_DIR "*.cpp" $EDITOR_SRC_PREFIX "RHEIA_EDITOR_SRC"

######### EDITOR HDR #############

ListAndSetFiles $EDITOR_HDR_DIR "*.h" $EDITOR_HDR_PREFIX "RHEIA_EDITOR_HDR"

STR="<!-- ====================================================================== -->\n
<!-- \t\t\t\trheiapython -->\n
<!-- ====================================================================== -->\n"
echo -e $STR >> $FILE

######### PYTHON SRC #############

ListAndSetFiles $PYTHON_SRC_DIR "*.cpp" $PYTHON_SRC_PREFIX "RHEIA_PYTHON_SRC"

######### PYTHON HDR #############

ListAndSetFiles $PYTHON_HDR_DIR "*.h" $PYTHON_HDR_PREFIX "RHEIA_PYTHON_HDR"

STR="<!-- ====================================================================== -->\n
<!-- \t\t\t\trheia demo app -->\n
<!-- ====================================================================== -->\n"
echo -e $STR >> $FILE

######### RHEIA SRC #############

ListAndSetFiles $RHEIA_SRC_DIR "*.cpp" $RHEIA_SRC_PREFIX "RHEIA_SRC"

######### RHEIA HDR #############

ListAndSetFiles $RHEIA_HDR_DIR "*.h" $RHEIA_HDR_PREFIX "RHEIA_HDR"

STR="<!-- ====================================================================== -->\n
<!-- \t\t\t\tirrlicht jpeg -->\n
<!-- ====================================================================== -->\n"
echo -e $STR >> $FILE

######### IRRJPG SRC #############

ListAndSetFiles $IRRJPG_SRC_DIR "*.c" $IRRJPG_SRC_PREFIX "RHEIA_IRRJPG_SRC"

######### IRRJPG HDR #############

ListAndSetFiles $IRRJPG_HDR_DIR "*.h" $IRRJPG_HDR_PREFIX "RHEIA_IRRJPG_HDR"


STR="<!-- ====================================================================== -->\n
<!-- \t\t\t\tirrlicht png -->\n
<!-- ====================================================================== -->\n"
echo -e $STR >> $FILE

######### IRRPNG SRC #############

ListAndSetFiles $IRRPNG_SRC_DIR "*.c" $IRRPNG_SRC_PREFIX "RHEIA_IRRPNG_SRC"

######### IRRPNG HDR #############

ListAndSetFiles $IRRPNG_HDR_DIR "*.h" $IRRPNG_HDR_PREFIX "RHEIA_IRRPNG_HDR"

STR="<!-- ====================================================================== -->\n
<!-- \t\t\t\tirrlicht zlib -->\n
<!-- ====================================================================== -->\n"
echo -e $STR >> $FILE

######### IRRZLIB SRC #############

ListAndSetFiles $IRRZLIB_SRC_DIR "*.c" $IRRZLIB_SRC_PREFIX "RHEIA_IRRZLIB_SRC"

######### IRRPNG HDR #############

ListAndSetFiles $IRRZLIB_HDR_DIR "*.h" $IRRZLIB_HDR_PREFIX "RHEIA_IRRZLIB_HDR"


STR="<!-- ====================================================================== -->\n
<!-- \t\t\t\tirrlicht macosx -->\n
<!-- ====================================================================== -->\n"
echo -e $STR >> $FILE

######### IRRMACOS SRC #############

ListAndSetFiles $IRRMACOS_SRC_DIR "*.mm" $IRRMACOS_SRC_PREFIX "RHEIA_IRRMACOS_SRC"

######### IRRMACOS HDR #############

ListAndSetFiles $IRRMACOS_HDR_DIR "*.h" $IRRMACOS_HDR_PREFIX "RHEIA_IRRMACOS_HDR"


STR="<!-- ====================================================================== -->\n
<!-- \t\t\t\tirrlicht -->\n
<!-- ====================================================================== -->\n"
echo -e $STR >> $FILE

######### IRRLICHT SRC #############

ListAndSetFiles $IRRLICHT_SRC_DIR "*.cpp" $IRRLICHT_SRC_PREFIX "RHEIA_IRRLICHT_SRC"

######### IRRLICHT HDR #############

ListAndSetFiles $IRRLICHT_HDR_DIR "*.h" $IRRLICHT_HDR_PREFIX "RHEIA_IRRLICHT_HDR"


#csirocsa stuff
STR="<!-- ====================================================================== -->\n
<!-- \t\t\t\tcsirocsa -->\n
<!-- ====================================================================== -->\n"
echo -e $STR >> $FILE

######### CSIROCSA SRC #############

ListAndSetFiles $CSIROCSA_SRC_DIR "*.c" $CSIROCSA_SRC_PREFIX "RHEIA_CSIROCSA_SRC"

######### CSIROCSA HDR #############

ListAndSetFiles $CSIROCSA_HDR_DIR "*.h" $CSIROCSA_HDR_PREFIX "RHEIA_CSIROCSA_HDR"

#qsastime stuff
STR="<!-- ====================================================================== -->\n
<!-- \t\t\t\tqsastime -->\n
<!-- ====================================================================== -->\n"
echo -e $STR >> $FILE

######### QSASTIME SRC #############

ListAndSetFiles $QSASTIME_SRC_DIR "*.c" $QSASTIME_SRC_PREFIX "RHEIA_QSASTIME_SRC"

######### QSASTIME HDR #############

ListAndSetFiles $QSASTIME_HDR_DIR "*.h" $QSASTIME_HDR_PREFIX "RHEIA_QSASTIME_HDR"

#wxwidgets plplot stuff
STR="<!-- ====================================================================== -->\n
<!-- \t\t\t\twxwidgets plplot driver -->\n
<!-- ====================================================================== -->\n"
echo -e $STR >> $FILE

######### WXWIDGETS SRC #############

ListAndSetFiles $WXWIDGETS_SRC_DIR "*.cpp" $WXWIDGETS_SRC_PREFIX "RHEIA_WXWIDGETS_SRC"

######### WXWIDGETS HDR #############

ListAndSetFiles $WXWIDGETS_HDR_DIR "*.h" $WXWIDGETS_HDR_PREFIX "RHEIA_WXWIDGETS_HDR"

#plplot stuff
STR="<!-- ====================================================================== -->\n
<!-- \t\t\t\tplplot library -->\n
<!-- ====================================================================== -->\n"
echo -e $STR >> $FILE

######### PLPLOT SRC #############

ListAndSetFiles $PLPLOT_SRC_DIR "*.c" $PLPLOT_SRC_PREFIX "RHEIA_PLPLOT_SRC"

######### PLPLOT HDR #############

ListAndSetFiles $PLPLOT_HDR_DIR "*.h" $PLPLOT_HDR_PREFIX "RHEIA_PLPLOT_HDR"

#wxplplot stuff
STR="<!-- ====================================================================== -->\n
<!-- \t\t\t\twxplplot library -->\n
<!-- ====================================================================== -->\n"
echo -e $STR >> $FILE

######### WXPLPLOT SRC #############

ListAndSetFiles $WXPLPLOT_SRC_DIR "*.cpp *.cc" $WXPLPLOT_SRC_PREFIX "RHEIA_WXPLPLOT_SRC"

######### PLPLOT HDR #############

ListAndSetFiles $WXPLPLOT_HDR_DIR "*.h" $WXPLPLOT_HDR_PREFIX "RHEIA_WXPLPLOT_HDR"

######### PLPLOT HDR #############

ListAndSetFiles $WEBCONNECT_SRC_DIR "*.cpp" $WEBCONNECT_SRC_PREFIX "RHEIA_WEBCONNECT_SRC"
ListAndSetFiles $WEBCONNECT_HDR_DIR "*.h" $WEBCONNECT_HDR_PREFIX "RHEIA_WEBCONNECT_HDR"

###########################################################################################
# END OF FILE LIST MANAGEMENT
###########################################################################################

###########################################################################################
# VARS FOR FILE GENERATION OF LIBRARIES AND EXECS
###########################################################################################

######### IRRLICHT INCLUDES ACCORDINGLY TO PLATFORMS ############
STR=" <set var=\"RHEIA_IRRLICHT_HEADERS_WIN32\" hints=\"files\"> \n
\t<if cond= \"PLATFORM_WIN32=='1'\">\n\t\t\$(RHEIA_IRRJPG_HDR)\n\t\t\$(RHEIA_IRRPNG_HDR)\n\t\t\$(RHEIA_IRRZLIB_HDR)\n\t</if>\n
 </set>\n\n"

echo -e $STR >> $FILE

STR=" <set var=\"RHEIA_IRRLICHT_HEADERS_MACOSX\" hints=\"files\"> \n
\t<if cond= \"PLATFORM_MACOSX=='1'\">\n\t\t\$(RHEIA_IRRJPG_HDR)\n\t\t\$(RHEIA_IRRPNG_HDR)\n\t\t\$(RHEIA_IRRZLIB_HDR)\n\t\t\$(RHEIA_IRRMACOS_HDR)\n\t</if>\n
 </set>\n\n"

echo -e $STR >> $FILE

STR=" <set var=\"RHEIA_IRRLICHT_HEADERS_OS2\" hints=\"files\"> \n
\t<if cond= \"PLATFORM_MACOSX=='1'\">\n\t\t\$(RHEIA_IRRJPG_HDR)\n\t\t\$(RHEIA_IRRPNG_HDR)\n\t\t\$(RHEIA_IRRZLIB_HDR)\n\t\t\$(RHEIA_IRRMACOS_HDR)\n\t</if>\n
 </set>\n\n"

echo -e $STR >> $FILE

STR=" <set var=\"ALL_IRRLICHT_HEADERS\" hints=\"files\"> \n
\t\$(RHEIA_IRRLICHT_HDR)\n
\t\$(RHEIA_IRRLICHT_HEADERS_WIN32)\n
\t\$(RHEIA_IRRLICHT_HEADERS_MACOSX)\n
\t\$(RHEIA_IRRLICHT_HEADERS_OS2)\n
 </set>\n\n"

echo -e $STR >> $FILE

######### IRRLICHT SRC ACCORDINGLY TO PLATFORMS ############

STR=" <set var=\"RHEIA_IRRLICHT_SOURCES_WIN32\" hints=\"files\"> \n
\t<if cond= \"PLATFORM_WIN32=='1'\">\n\t\t\$(RHEIA_IRRJPG_SRC)\n\t\t\$(RHEIA_IRRPNG_SRC)\n\t\t\$(RHEIA_IRRZLIB_SRC)\n\t</if>\n
 </set>\n\n"

echo -e $STR >> $FILE

STR=" <set var=\"RHEIA_IRRLICHT_SOURCES_MACOSX\" hints=\"files\"> \n
\t<if cond= \"PLATFORM_MACOSX=='1'\">\n\t\t\$(RHEIA_IRRJPG_SRC)\n\t\t\$(RHEIA_IRRPNG_SRC)\n\t\t\$(RHEIA_IRRZLIB_SRC)\n\t\t\$(RHEIA_IRRMACOS_SRC)\n\t</if>\n
 </set>\n\n"

echo -e $STR >> $FILE

STR=" <set var=\"RHEIA_IRRLICHT_SOURCES_OS2\" hints=\"files\"> \n
\t<if cond= \"PLATFORM_MACOSX=='1'\">\n\t\t\$(RHEIA_IRRJPG_SRC)\n\t\t\$(RHEIA_IRRPNG_SRC)\n\t\t\$(RHEIA_IRRZLIB_SRC)\n\t\t\$(RHEIA_IRRMACOS_SRC)\n\t</if>\n
 </set>\n\n"

echo -e $STR >> $FILE

STR=" <set var=\"ALL_IRRLICHT_SOURCES\" hints=\"files\"> \n
\t\$(RHEIA_IRRLICHT_SRC)\n
\t\$(RHEIA_IRRLICHT_SOURCES_WIN32)\n
\t\$(RHEIA_IRRLICHT_SOURCES_MACOSX)\n
\t\$(RHEIA_IRRLICHT_SOURCES_OS2)\n
 </set>\n\n"

echo -e $STR >> $FILE


######### PLPLOT INCLUDES ACCORDINGLY TO PLATFORMS ############
STR=" <set var=\"PLPLOT_HEADERS\" hints=\"files\"> \n
\t\$(RHEIA_CSIROCSA_HDR)\n
\t\$(RHEIA_QSASTIME_HDR)\n
\t\$(RHEIA_PLPLOT_HDR)\n
\t\$(RHEIA_WXWIDGETS_HDR)\n
 </set>\n\n"

echo -e $STR >> $FILE

######### PLPLOT SRC ACCORDINGLY TO PLATFORMS ############
STR=" <set var=\"PLPLOT_SOURCES\"  hints=\"files\"> \n
\t\$(RHEIA_CSIROCSA_SRC)\n
\t\$(RHEIA_QSASTIME_SRC)\n
\t\$(RHEIA_PLPLOT_SRC)\n
\t\$(RHEIA_WXWIDGETS_SRC)\n
 </set>\n\n"

echo -e $STR >> $FILE

######### WXPLPLOT INCLUDES ACCORDINGLY TO PLATFORMS ############
STR=" <set var=\"WXPLPLOT_HEADERS\"  hints=\"files\"> \n
\t\$(RHEIA_WXPLPLOT_HDR)\n
 </set>\n\n"

echo -e $STR >> $FILE

######### WXPLPLOT SRC ACCORDINGLY TO PLATFORMS ############
STR=" <set var=\"WXPLPLOT_SOURCES\"  hints=\"files\"> \n
\t\$(RHEIA_WXPLPLOT_SRC)\n
 </set>\n\n"

echo -e $STR >> $FILE

######### ALL PLPLOT AND WXPLPLOT INCLUDES ACCORDINGLY TO PLATFORMS ############
STR=" <set var=\"ALL_PLPLOT_HEADERS\"  hints=\"files\"> \n
\t\$(PLPLOT_HEADERS)\n
\t\$(WXPLPLOT_HEADERS)\n
 </set>\n\n"

echo -e $STR >> $FILE

######### ALL PLPLOT AND WXPLPLOT SRC ACCORDINGLY TO PLATFORMS ############
STR=" <set var=\"ALL_PLPLOT_SOURCES\"  hints=\"files\"> \n
\t\$(PLPLOT_SOURCES)\n
\t\$(WXPLPLOT_SOURCES)\n
 </set>\n\n"

echo -e $STR >> $FILE

######### WEBCONNECT INCLUDES ACCORDINGLY TO PLATFORMS ############
STR=" <set var=\"WEBCONNECT_HEADERS\"  hints=\"files\"> \n
\t\$(RHEIA_WEBCONNECT_HDR)\n
 </set>\n\n"

echo -e $STR >> $FILE

######### WEBCONNECT SRC ACCORDINGLY TO PLATFORMS ############
STR=" <set var=\"WEBCONNECT_SOURCES\"  hints=\"files\"> \n
\t\$(RHEIA_WEBCONNECT_SRC)\n
 </set>\n\n"

echo -e $STR >> $FILE


######### ADDITIONAL VARIABLES #############

STR=" <set var=\"ALL_RHEIA_HEADERS\" hints=\"files\"> \n
\t\$(RHEIA_UTILS_HDR)\n\t\$(RHEIA_BASE_HDR)\n\t\$(RHEIA_LOGGERS_HDR)\n\t\$(RHEIA_PACKAGES_HDR)\n\t\$(RHEIA_WORKSPACES_HDR)\n\t\$(RHEIA_EDITOR_HDR)\n\t\$(RHEIA_PYTHON_HDR)\n
 </set>\n\n"

echo -e $STR >> $FILE

STR=" <set var=\"ALL_RHEIA_SOURCES\" hints=\"files\"> \n
\t\$(RHEIA_UTILS_SRC)\n\t\$(RHEIA_BASE_SRC)\n\t\$(RHEIA_LOGGERS_SRC)\n\t\$(RHEIA_PACKAGES_SRC)\n\t\$(RHEIA_WORKSPACES_SRC)\n\t\$(RHEIA_EDITOR_SRC)\n\t\$(RHEIA_PYTHON_SRC)\n
 </set>\n\n"

echo -e $STR >> $FILE

######### SINGLE LIB RHEIA HEADERS #############

STR=" <set var=\"SINGLELIB_RHEIA_HEADERS_PLPLOT\" hints=\"files\"> \n
\t<if cond=\"USE_PLPLOT=='1'\">\$(ALL_PLPLOT_HEADERS)</if>\n
 </set>\n\n"

echo -e $STR >> $FILE

STR=" <set var=\"SINGLELIB_RHEIA_HEADERS_IRRLICHT\" hints=\"files\"> \n
\t<if cond=\"USE_IRRLICHT=='1'\">\$(ALL_IRRLICHT_HEADERS)</if>\n
 </set>\n\n"

echo -e $STR >> $FILE

STR=" <set var=\"SINGLELIB_RHEIA_HEADERS\" hints=\"files\"> \n
\t\$(SINGLELIB_RHEIA_HEADERS_IRRLICHT)\n
\t\$(SINGLELIB_RHEIA_HEADERS_PLPLOT)\n
\t\$(WEBCONNECT_HEADERS)\n
\t\$(ALL_RHEIA_HEADERS)
 </set>\n\n"

echo -e $STR >> $FILE

STR=" <set var=\"SINGLELIB_RHEIA_SOURCES_PLPLOT\" hints=\"files\"> \n
\t<if cond=\"USE_PLPLOT=='1'\">\$(ALL_PLPLOT_SOURCES)</if>\n
 </set>\n\n"

echo -e $STR >> $FILE

STR=" <set var=\"SINGLELIB_RHEIA_SOURCES_IRRLICHT\" hints=\"files\"> \n
\t<if cond=\"USE_IRRLICHT=='1'\">\$(ALL_IRRLICHT_SOURCES)</if>\n
 </set>\n\n"

echo -e $STR >> $FILE

STR=" <set var=\"SINGLELIB_RHEIA_SOURCES\" hints=\"files\"> \n
\t\$(SINGLELIB_RHEIA_SOURCES_IRRLICHT)\n
\t\$(SINGLELIB_RHEIA_SOURCES_PLPLOT)\n
\t\$(WEBCONNECT_SOURCES)\n
\t\$(ALL_RHEIA_SOURCES)
 </set>\n\n"

echo -e $STR >> $FILE

echo "</makefile>" >> $FILE

