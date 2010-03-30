--*****************************************************************************
--*	Author:		Nicolas Macherey <nm@graymat.fr>
--*	Date:		21/02/2010
--*	Version:	1.00-beta
--* Copyright (C) 2010 Nicolas Macherey
--*
--* This program is licensed under the terms of the Rheia User License Agreement
--* please refer to License.txt to see the exact terms and conditions.
--*
--*	NOTES:
--*		- use the '/' slash for all paths.
--*****************************************************************************

--******* Initial Setup ************
--*	Most of the setting are set here.
--**********************************
-- wxWidgets version

-- Set the name of your package.
package.name = "rheia"

local python_ver=""

if( macosx ) then
    python_ver="2.6"
elseif( OS == "windows" ) then
    python_ver="26"
else
    python_ver="2.5"
end

-- Set this if you want a different name for your target than the package's name.
local targetName = "rheia"
local version = "1.1.1"
local version_win = "1_1_1"

-- Set the kind of package you want to create.
--		Options: exe | winexe | lib | dll
package.kind = "winexe"

local CP = "";

if( macosx ) then
    CP="cp -r "
else
    CP="cp -ru "
end

-- Set the files to include.
if ( not windows ) then
	package.files = { matchfiles( "*.cpp", "*.hpp", "*.cxx", "*.h", "*.cc", "*.hh" , "*.c" ), matchfiles( "../../include/rheia/*.h" ) }
else
	package.files = { matchfiles( "*.cpp", "*.hpp", "*.cxx", "*.h", "*.cc", "*.hh" , "*.c" ) , matchfiles( "../../include/rheia/*.h" ) }
end

-- Set the include paths.
package.includepaths = { "../../include/rheia/python" , "../../include/rheia/editor" , "../../include/rheia" , "../../include/rheia/packagemgt" , "../../include/rheia/workspacemgt" , "$(WXPYTHON)/include" , "../../include/rheia/loggers" , "../../include/rheia/base" , "../../include/rheia/utils" , "../../include/irrlicht" , "../../src/irrlicht" , "../../webconnect/include" }

-- Set the packages dependancies. NOT implimented in the official Premake build for Code::Blocks
package.depends = { "csirocsa", "qsastime" , "plplot" , "irrlicht" , "rheiautils" , "rheiabase" , "rheialoggers" , "rheiapackagemgt" , "rheiaworkspacemgt" , "rheiapython" , "webconnect" , "rheiaeditor" }

-- Set the defines.
package.defines = { "HAVE_CONFIG_H" }

--------------------------- DO NOT EDIT BELOW ----------------------------------

--******* GENAERAL SETUP **********
--*	Settings that are not dependant
--*	on the operating system.
--*********************************

-- wxWidgets version
local wx_ver = ""
if( options["with-wx-28"] ) then
	if( windows ) then
		wx_ver = "28"
	else
		wx_ver = "2.8"
	end
else
	if( windows ) then
		wx_ver = "29"
	else
		wx_ver = "2.9"
	end
end

-- Common setup
package.language = "c++"

-- Set object output directory.
if ( options["unicode"] ) then
	package.config["Debug"].objdir = ".objsud"
	package.config["Release"].objdir = ".objsu"
else
	package.config["Debug"].objdir = ".objsd"
	package.config["Release"].objdir = ".objs"
end

-- Set debug flags
if ( options["disable-wx-debug"] and ( not windows ) ) then
	debug_option = "--debug=no"
	debug_macro = { "NDEBUG" }
else
	debug_option = "--debug=yes"
	debug_macro = { "DEBUG", "_DEBUG", "__WXDEBUG__" , "RHEIA_DEBUG" }
end
-- Set the default targetName if none is specified.

if ( string.len( targetName ) == 0 ) then
	targetName = package.name
end

package.config["Release"].target = targetName
package.config["Debug"].target = targetName.."-dbg"

table.insert( package.defines, "WXUSINGDLL" )
if ( options["unicode"] ) then
	table.insert( package.defines, { "UNICODE", "_UNICODE" } )
end
table.insert( package.defines, "__WX__" )
table.insert( package.config["Debug"].defines, debug_macro )
table.insert( package.config["Release"].defines, "NDEBUG" )

if( OS == "windows" ) then
	table.insert( package.config["Debug"].links , "libxml2-dbg" )
	table.insert( package.config["Release"].links , "libxml2" )
end

table.insert( package.config["Debug"].links , "libgmcsirocsa-dbg" )
table.insert( package.config["Debug"].links , "libgmqsastime-dbg" )
table.insert( package.config["Debug"].links , "libgmplplot-dbg" )	
table.insert( package.config["Debug"].links , "libgmwxplplot-dbg" )
table.insert( package.config["Debug"].links , "librheiautils-dbg" )
table.insert( package.config["Debug"].links , "librheiabase-dbg" )
table.insert( package.config["Debug"].links , "librheialoggers-dbg" )
table.insert( package.config["Debug"].links , "librheiapython-dbg" )
table.insert( package.config["Debug"].links , "librheiapackagemgt-dbg" )
table.insert( package.config["Debug"].links , "librheiaworkspacemgt-dbg" )
table.insert( package.config["Debug"].links , "libwebconnect-dbg" )
table.insert( package.config["Debug"].links , "librheiaeditor-dbg" )

table.insert( package.config["Release"].links , "libgmcsirocsa" )
table.insert( package.config["Release"].links , "libgmqsastime" )
table.insert( package.config["Release"].links , "libgmplplot" )	
table.insert( package.config["Release"].links , "libgmwxplplot" )
table.insert( package.config["Release"].links , "librheiautils" )
table.insert( package.config["Release"].links , "librheiabase" )
table.insert( package.config["Release"].links , "librheialoggers" )
table.insert( package.config["Release"].links , "librheiapython" )
table.insert( package.config["Release"].links , "librheiapackagemgt" )
table.insert( package.config["Release"].links , "librheiaworkspacemgt" )
table.insert( package.config["Release"].links , "libwebconnect" )
table.insert( package.config["Release"].links , "librheiaeditor" )

if( not options["no-irrlicht"] ) then
	table.insert( package.defines, "RHEIA_USE_IRRLICHT" )
	table.insert( package.config["Debug"].links , "libgmirrlicht-dbg" )
	table.insert( package.config["Release"].links , "libgmirrlicht" )
end

if( not windows ) then
	table.insert( package.includepaths , "/usr/include/python" .. python_ver )
	table.insert( package.config["Debug"].links , "python" .. python_ver )
else
	table.insert( package.config["Debug"].includepaths , "../../pybinaries/Debug/Include" )
	table.insert( package.config["Release"].includepaths , "../../pybinaries/Release/Include" )
	table.insert( package.config["Debug"].links , "python" .. python_ver .. "_d" )
	table.insert( package.config["Debug"].links , "python" .. python_ver )
end

if ( OS == "windows" ) then
--******* WINDOWS SETUP ***********
--*	Settings that are Windows specific.
--*********************************
	if ( (not options["cb-msvc8"]) and (string.find( target or "", ".*-gcc" ) or target == "gnu") ) then
		-- Set the build options.
		package.buildflags = { "extra-warnings" }
		package.config["Release"].buildflags = { "optimize-speed" }
	
		table.insert( package.config["Debug"].buildoptions, "-O0" )
		table.insert( package.config["Debug"].buildoptions, "-g" )
		table.insert( package.config["Debug"].buildoptions, "-fno-strict-aliasing" )
		table.insert( package.config["Debug"].buildoptions, "-W" )
		table.insert( package.config["Debug"].buildoptions, "-fmessage-length=0" )
		table.insert( package.config["Debug"].buildoptions, "-Winvalid-pch" )
		table.insert( package.config["Debug"].buildoptions, "-fexceptions" )
		table.insert( package.config["Debug"].buildoptions, "-fPIC" )

		table.insert( package.config["Release"].buildoptions, "-fno-strict-aliasing" )
		table.insert( package.config["Release"].buildoptions, "-W" )
		table.insert( package.config["Release"].buildoptions, "-fmessage-length=0" )
		table.insert( package.config["Release"].buildoptions, "-Winvalid-pch" )
		table.insert( package.config["Release"].buildoptions, "-fexceptions" )
		table.insert( package.config["Release"].buildoptions, "-fPIC" )
		table.insert( package.config["Release"].buildoptions, "-O1" )
		table.insert( package.config["Release"].buildoptions, "-O2" )
		table.insert( package.config["Release"].buildoptions, "-O3" )
		table.insert( package.config["Release"].buildoptions, "-fexpensive-optimizations" )
		
		table.insert( package.config["Debug"].defines, debug_macro )
		table.insert( package.config["Release"].defines, "NDEBUG" )
		
		table.insert( package.defines, { "_USRDLL" , "WIN32", "_WINDOWS" , "__WIN32__" , "HAVE_WIN32_THREADS" , "HAVE_COMPILER_TLS" , "_MBCS" , "__WXMSW__" , "_CRT_SECURE_DEPRECATE" , "_CRT_SECURE_NO_WARNINGS" , "_CRT_NONSTDC_NO_DEPRECATE" } )
		
		package.config["Release"].postbuildcommands = { "gmkdir -p ../../devel/Release/include/rheia" , "gmkdir -p ../../devel/Release/bin/share/rheia/images" , "gmkdir -p ../../devel/Release/bin/share/rheia/plugins", "gmkdir -p ../../devel/Release/bin/share/rheia/packages" , "gmkdir -p ../../devel/Release/bin/share/rheia/cache" , "gmkdir -p ../../devel/Release/bin/share/rheia/scripts" , CP .. "../../xulrunner ../../devel/Release/bin" , CP .. "../../share/rheia/webresource/* ../../devel/Release/bin/share/rheia/" , CP .. "../../include/rheia/* ../../devel/Release/include/rheia" , CP .. "../../share/rheia/resource/images/settings ../../devel/Release/bin/share/rheia/images" , CP .. "../../share/rheia/plplot ../../devel/Release/bin/share/rheia" , "zip -j9 -r ../../devel/Release/bin/share/rheia/resource.zip ../../share/rheia/resource" , "gmkdir -p ../../../../devel/Release/include" , "gmkdir -p ../../../../devel/Release/bin/share" , CP .. "../../devel/Release/include/rheia ../../../../devel/Release/include" , CP .. "../../devel/Release/bin/share/rheia ../../../../devel/Release/bin/share" , CP .. "../../devel/Release/bin ../../../../devel/Release" , CP .. "../../devel/Release/lib ../../../../devel/Release" }
	    package.config["Debug"].postbuildcommands = { "gmkdir -p ../../devel/Debug/include/rheia" , "gmkdir -p ../../devel/Debug/bin/share/rheia-dbg/images" , "gmkdir -p ../../devel/Debug/bin/share/rheia-dbg/plugins", "gmkdir -p ../../devel/Debug/bin/share/rheia-dbg/packages" , "gmkdir -p ../../devel/Debug/bin/share/rheia-dbg/cache" , "gmkdir -p ../../devel/Debug/bin/share/rheia-dbg/scripts" , CP .. "../../xulrunner ../../devel/Debug/bin" , CP .. "../../share/rheia/webresource/* ../../devel/Debug/bin/share/rheia-dbg/" , CP .. "../../include/rheia/* ../../devel/Debug/include/rheia" , CP .. "../../share/rheia/resource/images/settings ../../devel/Debug/bin/share/rheia-dbg/images" , CP .. "../../share/rheia/plplot ../../devel/Debug/bin/share/rheia-dbg" , "zip -j9 -r ../../devel/Debug/bin/share/rheia-dbg/resource.zip ../../share/rheia/resource" , "gmkdir -p ../../../../devel/Debug/include" , "gmkdir -p ../../../../devel/Debug/bin/share" , CP .. "../../devel/Debug/include/rheia ../../../../devel/Debug/include" , CP .. "../../devel/Debug/bin/share/rheia-dbg ../../../../devel/Debug/bin/share" , CP .. "../../devel/Debug/bin ../../../../devel/Debug" , CP .. "../../devel/Debug/lib ../../../../devel/Debug" }
	else
		table.insert( package.config["Release"].buildoptions, "/Zi" )
		table.insert( package.config["Release"].buildoptions, "/Zc:wchar_t" )
		table.insert( package.config["Release"].buildoptions, "/W3" )
		table.insert( package.config["Release"].buildoptions, "/Ox" )
		table.insert( package.config["Release"].buildoptions, "/GF" )
		table.insert( package.config["Release"].buildoptions, "/EHs" )
		--table.insert( package.config["Release"].buildoptions, "/TP" )
		table.insert( package.config["Release"].buildoptions, "/MD" )
		table.insert( package.config["Release"].buildoptions, "/DNDEBUG" )
		
		table.insert( package.config["Debug"].buildoptions, "/Zi" )
		table.insert( package.config["Debug"].buildoptions, "/Zc:wchar_t" )
		table.insert( package.config["Debug"].buildoptions, "/W3" )
		table.insert( package.config["Debug"].buildoptions, "/GF" )
		table.insert( package.config["Debug"].buildoptions, "/EHs" )
		--table.insert( package.config["Debug"].buildoptions, "/TP" )
		table.insert( package.config["Debug"].buildoptions, "/MDd" )
		table.insert( package.config["Debug"].buildoptions, "/DDEBUG" )
		table.insert( package.config["Debug"].buildoptions, "/D_DEBUG" )
		
		table.insert( package.buildoptions, "/D_USRDLL" )
		table.insert( package.buildoptions, "/DUSINGDLL" )
		table.insert( package.buildoptions, "/DHAVE_CONFIG_H" )
		table.insert( package.buildoptions, "/DWIN32" )
		table.insert( package.buildoptions, "/D_WINDOWS")
		table.insert( package.buildoptions, "/D__WIN32__")
		table.insert( package.buildoptions, "/DHAVE_WIN32_THREADS")
		table.insert( package.buildoptions, "/DHAVE_COMPILER_TLS")
		table.insert( package.buildoptions, "/D_MBCS")
		table.insert( package.buildoptions, "/D__WXMSW__")
		table.insert( package.buildoptions, "/D_CRT_SECURE_DEPRECATE")
		table.insert( package.buildoptions, "/D_CRT_SECURE_NO_WARNINGS")
		table.insert( package.buildoptions, "/D_CRT_NONSTDC_NO_DEPRECATE")
		
		package.config["Release"].postbuildcommands = { "gmkdir -p ../../devel/Release/include/rheia" , "gmkdir -p ../../devel/Release/bin/share/rheia/images" , "gmkdir -p ../../devel/Release/bin/share/rheia/plugins", "gmkdir -p ../../devel/Release/bin/share/rheia/packages" , "gmkdir -p ../../devel/Release/bin/share/rheia/cache" , "gmkdir -p ../../devel/Release/bin/share/rheia/scripts" , CP .. "../../xulrunner ../../devel/Release/bin" , CP .. "../../share/rheia/webresource/* ../../devel/Release/bin/share/rheia/" , CP .. "../../include/rheia/* ../../devel/Release/include/rheia" , CP .. "../../share/rheia/resource/images/settings ../../devel/Release/bin/share/rheia/images" , CP .. "../../share/rheia/plplot ../../devel/Release/bin/share/rheia" , "zip -j9 -r ../../devel/Release/bin/share/rheia/resource.zip ../../share/rheia/resource" , "gmkdir -p ../../../../devel/Release/include" , "gmkdir -p ../../../../devel/Release/bin/share" , CP .. "../../devel/Release/include/rheia ../../../../devel/Release/include" , CP .. "../../devel/Release/bin/share/rheia ../../../../devel/Release/bin/share" , CP .. "../../devel/Release/bin ../../../../devel/Release" , CP .. "../../devel/Release/lib ../../../../devel/Release" }
	    package.config["Debug"].postbuildcommands = { "gmkdir -p ../../devel/Debug/include/rheia" , "gmkdir -p ../../devel/Debug/bin/share/rheia-dbg/images" , "gmkdir -p ../../devel/Debug/bin/share/rheia-dbg/plugins", "gmkdir -p ../../devel/Debug/bin/share/rheia-dbg/packages" , "gmkdir -p ../../devel/Debug/bin/share/rheia-dbg/cache" , "gmkdir -p ../../devel/Debug/bin/share/rheia-dbg/scripts"  , CP .. "../../xulrunner ../../devel/Debug/bin" , CP .. "../../share/rheia/webresource/* ../../devel/Debug/bin/share/rheia-dbg/" , CP .. "../../include/rheia/* ../../devel/Debug/include/rheia" , CP .. "../../share/rheia/resource/images/settings ../../devel/Debug/bin/share/rheia-dbg/images" , CP .. "../../share/rheia/plplot ../../devel/Debug/bin/share/rheia-dbg" , "zip -j9 -r ../../devel/Debug/bin/share/rheia-dbg/resource.zip ../../share/rheia/resource" , "gmkdir -p ../../../../devel/Debug/include" , "gmkdir -p ../../../../devel/Debug/bin/share" , CP .. "../../devel/Debug/include/rheia ../../../../devel/Debug/include" , CP .. "../../devel/Debug/bin/share/rheia-dbg ../../../../devel/Debug/bin/share" , CP .. "../../devel/Debug/bin ../../../../devel/Debug" , CP .. "../../devel/Debug/lib ../../../../devel/Debug" }
		
		package.links = { "user32" , "gdi32" , "winspool" , "kernel32" , "comdlg32" , "advapi32" , "shell32" , "ole32" , "oleaut32" , "uuid" , "opengl32" , "winmm" }
	end
	
	package.config["Release"].target = targetName
	package.config["Release"].libdir = "../../devel/Release/lib"
	package.config["Release"].bindir = "../../devel/Release/bin"
	package.config["Release"].libpaths = { "../../devel/Release/lib" }

	package.config["Debug"].target = targetName .. "-dbg"
	package.config["Debug"].libdir = "../../devel/Debug/lib"
	package.config["Debug"].bindir = "../../devel/Debug/bin"
	package.config["Debug"].libpaths = { "../../devel/Release/lib" }
	
	-- Set wxWidgets include paths
	if ( target == "cb-gcc" ) then
		table.insert( package.includepaths, "$(#WX.include)" )
	else
		table.insert( package.includepaths, "$(WXWIN)/include" )
	end

	if ( options["unicode"] ) then
		if ( target == "cb-gcc" ) then
			table.insert( package.config["Debug"].includepaths, "$(#WX.lib)/gcc_dll/mswud" )
			table.insert( package.config["Release"].includepaths, "$(#WX.lib)/gcc_dll/mswuh" )
		elseif ( target == "gnu" or target == "cl-gcc" ) then
			table.insert( package.config["Debug"].includepaths, "$(WXWIN)/lib/gcc_dll/mswud" )
			table.insert( package.config["Release"].includepaths, "$(WXWIN)/lib/gcc_dll/mswuh" )
		else
			table.insert( package.config["Debug"].includepaths, "$(WXWIN)/lib/vc_dll/mswud" )
			table.insert( package.config["Release"].includepaths, "$(WXWIN)/lib/vc_dll/mswuh" )
		end
	else
		if ( target == "cb-gcc" ) then
			table.insert( package.config["Debug"].includepaths, "$(#WX.lib)/gcc_dll/mswd" )
			table.insert( package.config["Release"].includepaths, "$(#WX.lib)/gcc_dll/mswh" )
		elseif ( target == "gnu" or target == "cl-gcc" ) then
			table.insert( package.config["Debug"].includepaths, "$(WXWIN)/lib/gcc_dll/mswd" )
			table.insert( package.config["Release"].includepaths, "$(WXWIN)/lib/gcc_dll/mswh" )
		else
			table.insert( package.config["Debug"].includepaths, "$(WXWIN)/lib/vc_dll/mswd" )
			table.insert( package.config["Release"].includepaths, "$(WXWIN)/lib/vc_dll/mswh" )
		end
	end

	if ( target == "cb-gcc" ) then
		table.insert( package.libpaths, "$(#WX.lib)/gcc_dll" )
	elseif ( target == "gnu" or target == "cl-gcc" ) then
		table.insert( package.libpaths, "$(WXWIN)/lib/gcc_dll" )
	else
		table.insert( package.libpaths, "$(WXWIN)/lib/vc_dll" )
	end
	
	table.insert( package.config["Release"].libpaths, "../../pybinaries/Release/libs" )
	table.insert( package.config["Debug"].libpaths, "../../pybinaries/Debug/libs" )
	table.insert( package.config["Debug"].libpaths, "../../pybinaries/Release/libs" )

	-- Set wxWidgets libraries to link.
	if ( options["unicode"] ) then
		table.insert( package.config["Release"].links, "wxmsw".. wx_ver .. "uh_richtext" )
		table.insert( package.config["Release"].links, "wxmsw".. wx_ver .. "uh_xrc" )
		table.insert( package.config["Release"].links, "wxmsw".. wx_ver .. "uh_aui" )
		table.insert( package.config["Release"].links, "wxmsw".. wx_ver .. "uh_media" )
		table.insert( package.config["Release"].links, "wxbase".. wx_ver .. "uh_net" )
		table.insert( package.config["Release"].links, "wxbase".. wx_ver .. "uh_xml" )
		table.insert( package.config["Release"].links, "wxmsw".. wx_ver .. "uh_adv" )
		table.insert( package.config["Release"].links, "wxmsw".. wx_ver .. "uh_html" )
		table.insert( package.config["Release"].links, "wxmsw".. wx_ver .. "uh_core" )
		table.insert( package.config["Release"].links, "wxbase".. wx_ver .. "uh" )
		table.insert( package.config["Release"].links, "wxpngh" )
		table.insert( package.config["Release"].links, "wxjpegh" )
		table.insert( package.config["Release"].links, "wxtiffh" )
		table.insert( package.config["Release"].links, "wxregexuh" )
		table.insert( package.config["Release"].links, "wxzlibh" )
		table.insert( package.config["Release"].links, "wxexpath" )
		
		table.insert( package.config["Debug"].links, "wxmsw".. wx_ver .. "ud_richtext" )
		table.insert( package.config["Debug"].links, "wxmsw".. wx_ver .. "ud_xrc" )
		table.insert( package.config["Debug"].links, "wxmsw".. wx_ver .. "ud_aui" )
		table.insert( package.config["Debug"].links, "wxmsw".. wx_ver .. "ud_media" )
		table.insert( package.config["Debug"].links, "wxbase".. wx_ver .. "ud_net" )
		table.insert( package.config["Debug"].links, "wxbase".. wx_ver .. "ud_xml" )
		table.insert( package.config["Debug"].links, "wxmsw".. wx_ver .. "ud_adv" )
		table.insert( package.config["Debug"].links, "wxmsw".. wx_ver .. "ud_html" )
		table.insert( package.config["Debug"].links, "wxmsw".. wx_ver .. "ud_core" )
		table.insert( package.config["Debug"].links, "wxbase".. wx_ver .. "ud" )
		table.insert( package.config["Debug"].links, "wxpngd" )
		table.insert( package.config["Debug"].links, "wxjpegd" )
		table.insert( package.config["Debug"].links, "wxtiffd" )
		table.insert( package.config["Debug"].links, "wxregexud" )
		table.insert( package.config["Debug"].links, "wxzlibd" )
		table.insert( package.config["Debug"].links, "wxexpatd" )
	else
		table.insert( package.config["Release"].links, "wxmsw".. wx_ver .. "h_richtext" )
		table.insert( package.config["Release"].links, "wxmsw".. wx_ver .. "h_xrc" )
		table.insert( package.config["Release"].links, "wxmsw".. wx_ver .. "h_aui" )
		table.insert( package.config["Release"].links, "wxmsw".. wx_ver .. "h_media" )
		table.insert( package.config["Release"].links, "wxbase".. wx_ver .. "h_net" )
		table.insert( package.config["Release"].links, "wxbase".. wx_ver .. "h_xml" )
		table.insert( package.config["Release"].links, "wxmsw".. wx_ver .. "h_adv" )
		table.insert( package.config["Release"].links, "wxmsw".. wx_ver .. "h_html" )
		table.insert( package.config["Release"].links, "wxmsw".. wx_ver .. "h_core" )
		table.insert( package.config["Release"].links, "wxbase".. wx_ver .."h" )
		table.insert( package.config["Release"].links, "wxpngh" )
		table.insert( package.config["Release"].links, "wxjpegh" )
		table.insert( package.config["Release"].links, "wxtiffh" )
		table.insert( package.config["Release"].links, "wxregexh" )
		table.insert( package.config["Release"].links, "wxzlibh" )
		table.insert( package.config["Release"].links, "wxexpath" )
		
		table.insert( package.config["Debug"].links, "wxmsw".. wx_ver .. "d_richtext" )
		table.insert( package.config["Debug"].links, "wxmsw".. wx_ver .. "d_xrc" )
		table.insert( package.config["Debug"].links, "wxmsw".. wx_ver .. "d_aui" )
		table.insert( package.config["Debug"].links, "wxmsw".. wx_ver .. "d_media" )
		table.insert( package.config["Debug"].links, "wxbase".. wx_ver .. "d_net" )
		table.insert( package.config["Debug"].links, "wxbase".. wx_ver .. "d_xml" )
		table.insert( package.config["Debug"].links, "wxmsw".. wx_ver .. "d_adv" )
		table.insert( package.config["Debug"].links, "wxmsw".. wx_ver .. "d_html" )
		table.insert( package.config["Debug"].links, "wxmsw".. wx_ver .. "d_core" )
		table.insert( package.config["Debug"].links, "wxbase".. wx_ver .. "d" )
		table.insert( package.config["Debug"].links, "wxpngd" )
		table.insert( package.config["Debug"].links, "wxjpegd" )
		table.insert( package.config["Debug"].links, "wxtiffd" )
		table.insert( package.config["Debug"].links, "wxregexd" )
		table.insert( package.config["Debug"].links, "wxzlibd" )
		table.insert( package.config["Debug"].links, "wxexpatd" )
	end
	-- Set the Windows defines.
	table.insert( package.defines, { "__WXMSW__" , "WIN32", "_WINDOWS" } )
else
--******* LINUX SETUP *************
--*	Settings that are Linux specific.
--*********************************
		-- Set the build options.
	package.buildflags = { "extra-warnings" }
	package.config["Release"].buildflags = { "optimize-speed" }

	if ( options["unicode"] ) then
		table.insert( package.buildflags, "unicode" )
	end

	if ( string.find( target or "", ".*-gcc" ) or target == "gnu" ) then
		table.insert( package.config["Debug"].buildoptions, "-O0" )
		table.insert( package.config["Debug"].buildoptions, "-g" )
		table.insert( package.config["Debug"].buildoptions, "-fno-strict-aliasing" )
		table.insert( package.config["Debug"].buildoptions, "-W" )
		if( not macosx ) then
	        table.insert( package.config["Debug"].buildoptions, "-Ulinux" )
	    end
		table.insert( package.config["Debug"].buildoptions, "-Uunix" )
		table.insert( package.config["Debug"].buildoptions, "-fmessage-length=0" )
		table.insert( package.config["Debug"].buildoptions, "-Winvalid-pch" )
		table.insert( package.config["Debug"].buildoptions, "-fexceptions" )
		table.insert( package.config["Debug"].buildoptions, "-fPIC" )

		table.insert( package.config["Release"].buildoptions, "-fno-strict-aliasing" )
		table.insert( package.config["Release"].buildoptions, "-W" )
		if( not macosx ) then
	        table.insert( package.config["Release"].buildoptions, "-Ulinux" )
	    end
		table.insert( package.config["Release"].buildoptions, "-Uunix" )
		table.insert( package.config["Release"].buildoptions, "-fmessage-length=0" )
		table.insert( package.config["Release"].buildoptions, "-Winvalid-pch" )
		table.insert( package.config["Release"].buildoptions, "-fexceptions" )
		table.insert( package.config["Release"].buildoptions, "-fPIC" )
		table.insert( package.config["Release"].buildoptions, "-O1" )
		table.insert( package.config["Release"].buildoptions, "-O2" )
		table.insert( package.config["Release"].buildoptions, "-O3" )
		table.insert( package.config["Release"].buildoptions, "-fexpensive-optimizations" )

		package.config["Release"].target = targetName
		package.config["Release"].libdir = "../../devel/Release/lib"
		package.config["Release"].bindir = "../../devel/Release/bin"
		package.config["Release"].libpaths = { "../../devel/Release/lib" }

		package.config["Debug"].target = targetName .. "-dbg"
		package.config["Debug"].libdir = "../../devel/Debug/lib"
		package.config["Debug"].bindir = "../../devel/Debug/bin"
		package.config["Debug"].libpaths = { "../../devel/Debug/lib" }

		if ( macosx ) then
			table.insert( package.config["Debug"].linkoptions, "-Wl,-L../lib" )
		elseif ( not windows ) then
			if ( options["rpath"] ) then
				-- need to upgrade premake before this works
				-- table.insert( package.linkoptions, "-Wl,-rpath," .. options[rpath] )
				table.insert( package.config["Debug"].linkoptions, "-Wl,-rpath,/usr/lib" )
			else
				if ( target == "cb-gcc" ) then
					table.insert( package.config["Debug"].linkoptions, "-Wl,-rpath,$``ORIGIN/../lib" )
				else
					table.insert( package.config["Debug"].linkoptions, "-Wl,-rpath,$$``ORIGIN/../lib" )
				end
			end
		end

		if ( macosx ) then
			table.insert( package.config["Release"].linkoptions, "-Wl,-L../lib" )
		elseif ( not windows ) then
			if ( options["rpath"] ) then
				-- need to upgrade premake before this works
				-- table.insert( package.linkoptions, "-Wl,-rpath," .. options[rpath] )
				table.insert( package.config["Release"].linkoptions, "-Wl,-rpath,/usr/lib" )
			else
				if ( target == "cb-gcc" ) then
					table.insert( package.config["Release"].linkoptions, "-Wl,-rpath,$``ORIGIN/../lib" )
				else
					table.insert( package.config["Release"].linkoptions, "-Wl,-rpath,$$``ORIGIN/../lib" )
				end
			end
		end

	    if( not macosx ) then
	        package.config["Release"].postbuildcommands = { "mkdir -p ../../devel/Release/include/rheia" , "mkdir -p ../../devel/Release/share/rheia/images" , "mkdir -p ../../devel/Release/share/rheia/plugins", "mkdir -p ../../devel/Release/share/rheia/packages" , "mkdir -p ../../devel/Release/share/rheia/cache" , "mkdir -p ../../devel/Release/share/rheia/scripts" , CP .. "../../include/rheia/* ../../devel/Release/include/rheia" , CP .. "../../share/rheia/resource/images/settings ../../devel/Release/share/rheia/images" , CP .. "../../share/rheia/webresource/* ../../devel/Release/share/rheia/" , CP .. "../../share/rheia/plplot ../../devel/Release/share/rheia" , "zip -j9 -r ../../devel/Release/share/rheia/resource.zip ../../share/rheia/resource" , "mkdir -p ../../../../devel/Release/include" , "mkdir -p ../../../../devel/Release/share" , CP .. "../../devel/Release/include/rheia ../../../../devel/Release/include" , CP .. "../../devel/Release/share/rheia ../../../../devel/Release/share" , CP .. "../../devel/Release/bin ../../../../devel/Release" , CP .. "../../devel/Release/lib ../../../../devel/Release" }
	        package.config["Debug"].postbuildcommands = { "mkdir -p ../../devel/Debug/include/rheia" , "mkdir -p ../../devel/Debug/share/rheia-dbg/images" , "mkdir -p ../../devel/Debug/share/rheia-dbg/plugins", "mkdir -p ../../devel/Debug/share/rheia-dbg/packages" , "mkdir -p ../../devel/Debug/share/rheia-dbg/cache" , "mkdir -p ../../devel/Debug/share/rheia-dbg/scripts" , CP .. "../../include/rheia/* ../../devel/Debug/include/rheia" , CP .. "../../share/rheia/resource/images/settings ../../devel/Debug/share/rheia-dbg/images" , CP .. "../../share/rheia/webresource/* ../../devel/Debug/share/rheia-dbg/" , CP .. "../../share/rheia/plplot ../../devel/Debug/share/rheia-dbg" , "zip -j9 -r ../../devel/Debug/share/rheia-dbg/resource.zip ../../share/rheia/resource" , "mkdir -p ../../../../devel/Debug/include" , "mkdir -p ../../../../devel/Debug/share" , CP .. "../../devel/Debug/include/rheia ../../../../devel/Debug/include" , CP .. "../../devel/Debug/share/rheia-dbg ../../../../devel/Debug/share" , CP .. "../../devel/Debug/bin ../../../../devel/Debug" , CP .. "../../devel/Debug/lib ../../../../devel/Debug" }
	    else
	        package.config["Release"].postbuildcommands = { "mkdir -p ../../devel/Release/include/rheia" , "mkdir -p ../../devel/Release/share/rheia/images" , "mkdir -p ../../devel/Release/share/rheia/plugins", "mkdir -p ../../devel/Release/share/rheia/packages" , "mkdir -p ../../devel/Release/share/rheia/cache" , "mkdir -p ../../devel/Release/share/rheia/scripts" , CP .. "../../include/rheia/* ../../devel/Release/include/rheia" , CP .. "../../share/rheia/resource/images/settings ../../devel/Release/share/rheia/images" , CP .. "../../share/rheia/webresource/* ../../devel/Release/share/rheia/" , CP .. "../../share/rheia/plplot ../../devel/Release/share/rheia" , "zip -j9 -r ../../devel/Release/share/rheia/resource.zip ../../share/rheia/resource" , "mkdir -p ../../../../devel/Release/include" , "mkdir -p ../../../../devel/Release/share" , CP .. "../../devel/Release/include/rheia ../../../../devel/Release/include" , CP .. "../../devel/Release/share/rheia ../../../../devel/Release/share" , CP .. "../../devel/Release/bin ../../../../devel/Release" , CP .. "../../devel/Release/lib ../../../../devel/Release" , "(cd ../../macosx/postinstall &amp;&amp; sh postbuild.sh)"}
	        package.config["Debug"].postbuildcommands = { "mkdir -p ../../devel/Debug/include/rheia" , "mkdir -p ../../devel/Debug/share/rheia-dbg/images" , "mkdir -p ../../devel/Debug/share/rheia-dbg/plugins", "mkdir -p ../../devel/Debug/share/rheia-dbg/packages" , "mkdir -p ../../devel/Debug/share/rheia-dbg/cache" , "mkdir -p ../../devel/Debug/share/rheia-dbg/scripts" , CP .. "../../include/rheia/* ../../devel/Debug/include/rheia" , CP .. "../../share/rheia/resource/images/settings ../../devel/Debug/share/rheia-dbg/images" , CP .. "../../share/rheia/webresource/* ../../devel/Debug/share/rheia-dbg/" , CP .. "../../share/rheia/plplot ../../devel/Debug/share/rheia-dbg" , "zip -j9 -r ../../devel/Debug/share/rheia-dbg/resource.zip ../../share/rheia/resource" , "mkdir -p ../../../../devel/Debug/include" , "mkdir -p ../../../../devel/Debug/share" , CP .. "../../devel/Debug/include/rheia ../../../../devel/Debug/include" , CP .. "../../devel/Debug/share/rheia-dbg ../../../../devel/Debug/share" , CP .. "../../devel/Debug/bin ../../../../devel/Debug" , CP .. "../../devel/Debug/lib ../../../../devel/Debug" ,"(cd ../../macosx/postinstall &amp;&amp; sh postbuildd.sh)" }
	    end
	end

	-- Ignore resource files in Linux.
	table.insert( package.excludes, matchrecursive( "*.rc" ) )
	if( not macosx ) then
        table.insert( package.defines, { "LINUX" , "unix" } )
    else
        table.insert( package.defines, { "MACOSX" , "unix" } )
    end

	-- Set wxWidgets build options.
	table.insert( package.config["Debug"].buildoptions, "`wx-config "..debug_option.." --cflags`" )
	table.insert( package.config["Debug"].buildoptions, "`xml2-config --cflags`" )

	table.insert( package.config["Release"].buildoptions, "`wx-config --cflags`" )
	table.insert( package.config["Release"].buildoptions, "`xml2-config --cflags`" )

	if( wx_ver == "2.9" ) then
		-- Set the wxWidgets link options.
		table.insert( package.config["Debug"].linkoptions, "`wx-config "..debug_option.." --static=no --libs all`" )
		table.insert( package.config["Debug"].linkoptions, "`xml2-config --libs`" )

		table.insert( package.config["Release"].linkoptions, "`wx-config --debug=no --static=no --libs all`" )
		table.insert( package.config["Release"].linkoptions, "`xml2-config --libs`" )
	else
		-- Set the wxWidgets link options.
		table.insert( package.config["Debug"].linkoptions, "`wx-config "..debug_option.." --libs`" )
		table.insert( package.config["Debug"].linkoptions, "`xml2-config --libs`" )

		table.insert( package.config["Release"].linkoptions, "`wx-config --debug=no --libs`" )
		table.insert( package.config["Release"].linkoptions, "`xml2-config --libs`" )
	end
end
