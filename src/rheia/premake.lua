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
local wx_ver = ""
if( windows ) then
	wx_ver = "29"
else
	wx_ver = "2.9"
end

-- Set the name of your package.
package.name = "rheia"

-- Set this if you want a different name for your target than the package's name.
local targetName = "rheia"
local version = "1.1.1"
local version_win = "1_1_1"

-- Set the kind of package you want to create.
--		Options: exe | winexe | lib | dll
package.kind = "winexe"

-- Set the files to include.
if ( not windows ) then
	package.files = { matchfiles( "*.cpp", "*.hpp", "*.cxx", "*.h", "*.cc", "*.hh" , "*.c" ), matchfiles( "../../include/rheia/*.h" ) }
else
	package.files = { matchfiles( "*.cpp", "*.hpp", "*.cxx", "*.h", "*.cc", "*.hh" , "*.c" ) , matchfiles( "../../include/rheia/*.h" ) }
end

-- Set the include paths.
package.includepaths = { "../../include/rheia/python" , "../../include/rheia" , "../../include/rheia/packagemgt" , "../../include/rheia/workspacemgt" , "$(WXPYTHON)/include" , "/usr/include/python2.5" , "../../include/rheia/loggers" , "../../include/rheia/base" , "../../include/rheia/utils" , "../../include/irrlicht" , "../../src/irrlicht" }

-- Set the packages dependancies. NOT implimented in the official Premake build for Code::Blocks
package.depends = { "csirocsa", "qsastime" , "wxwidgets" , "plplot" , "irrlicht" , "rheiautils" , "rheiabase" , "rheialoggers" , "rheiapackagemgt" , "rheiaworkspacemgt" , "rheiapython" }

-- Set the defines.
package.defines = { "HAVE_CONFIG_H", "RHEIA_PYTHON_MAKINGDLL" , "RHEIA_USE_IRRLICHT" }

--------------------------- DO NOT EDIT BELOW ----------------------------------

--******* GENAERAL SETUP **********
--*	Settings that are not dependant
--*	on the operating system.
--*********************************
-- Package options
addoption( "unicode", "Use the Unicode character set" )
if ( not windows ) then
	addoption( "disable-wx-debug", "Compile against a wxWidgets library without debugging" )
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
	table.insert( package.config["Debug"].buildoptions, "-Ulinux" )
	table.insert( package.config["Debug"].buildoptions, "-Uunix" )
	table.insert( package.config["Debug"].buildoptions, "-fmessage-length=0" )
	table.insert( package.config["Debug"].buildoptions, "-Winvalid-pch" )
	table.insert( package.config["Debug"].buildoptions, "-fexceptions" )
	table.insert( package.config["Debug"].buildoptions, "-fPIC" )
	
	table.insert( package.config["Release"].buildoptions, "-fno-strict-aliasing" )
	table.insert( package.config["Release"].buildoptions, "-W" )
	table.insert( package.config["Release"].buildoptions, "-Ulinux" )
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
		table.insert( package.config["Debug"].linkoptions, "-Wl,-L../../devel/Debug/lib" )
	elseif ( not windows ) then
		addoption("rpath", "Specify the rpath for the compiled binary")
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
		table.insert( package.config["Release"].linkoptions, "-Wl,-L../../devel/Release/lib" )
	elseif ( not windows ) then
		addoption("rpath", "Specify the rpath for the compiled binary")
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

	-- Set the libraries it links to.
	package.config["Debug"].links = { "gmirrlicht-dbg", "gmcsirocsa-dbg", "gmqsastime-dbg", "gmplplot-dbg", "gmwxplplot-dbg" , "rheiautils-dbg" , "rheiabase-dbg" , "rheialoggers-dbg" , "rheiapackagemgt-dbg" , "rheiaworkspacemgt-dbg" , "rheiapython-dbg" ,"python2.5" }
	package.config["Release"].links = { "gmirrlicht", "gmcsirocsa", "gmqsastime", "gmplplot", "gmwxplplot" , "rheiautils" , "rheiabase" , "rheialoggers" , "rheiapackagemgt" , "rheiaworkspacemgt" , "rheiapython" , "python2.5" }

	package.config["Release"].postbuildcommands = { "mkdir -p ../../devel/Release/include/rheia" , "mkdir -p ../../devel/Release/share/rheia/images" , "mkdir -p ../../devel/Release/share/rheia/plugins", "mkdir -p ../../devel/Release/share/rheia/packages" , "mkdir -p ../../devel/Release/share/rheia/cache" , "mkdir -p ../../devel/Release/share/rheia/scripts" , "cp -ru ../../include/rheia/* ../../devel/Release/include/rheia" , "cp -ru ../../share/rheia/resource/images/settings ../../devel/Release/share/rheia/images" , "cp -ru ../../share/rheia/plplot ../../devel/Release/share/rheia" , "zip -j9 -r ../../devel/Release/share/rheia/resource.zip ../../share/rheia/resource" , "mkdir -p ../../../../devel/Release/include" , "mkdir -p ../../../../devel/Release/share" , "cp -ru ../../devel/Release/include/rheia ../../../../devel/Release/include" , "cp -ru ../../devel/Release/share/rheia ../../../../devel/Release/share" , "cp -ru ../../devel/Release/bin ../../../../devel/Release" , "cp -ru ../../devel/Release/lib ../../../../devel/Release" }

	package.config["Debug"].postbuildcommands = { "mkdir -p ../../devel/Debug/include/rheia" , "mkdir -p ../../devel/Debug/share/rheia-dbg/images" , "mkdir -p ../../devel/Debug/share/rheia-dbg/plugins", "mkdir -p ../../devel/Debug/share/rheia-dbg/packages" , "mkdir -p ../../devel/Debug/share/rheia-dbg/cache" , "mkdir -p ../../devel/Debug/share/rheia-dbg/scripts" , "cp -ru ../../include/rheia/* ../../devel/Debug/include/rheia" , "cp -ru ../../share/rheia/resource/images/settings ../../devel/Debug/share/rheia-dbg/images" , "cp -ru ../../share/rheia/plplot ../../devel/Debug/share/rheia-dbg" , "zip -j9 -r ../../devel/Debug/share/rheia-dbg/resource.zip ../../share/rheia/resource" , "mkdir -p ../../../../devel/Debug/include" , "mkdir -p ../../../../devel/Debug/share" , "cp -ru ../../devel/Debug/include/rheia ../../../../devel/Debug/include" , "cp -ru ../../devel/Debug/share/rheia-dbg ../../../../devel/Debug/share" , "cp -ru ../../devel/Debug/bin ../../../../devel/Debug" , "cp -ru ../../devel/Debug/lib ../../../../devel/Debug" }
end

table.insert( package.defines, "WXUSINGDLL" )
if ( options["unicode"] ) then
	table.insert( package.defines, { "UNICODE", "_UNICODE" } )
end
table.insert( package.defines, "__WX__" )
table.insert( package.config["Debug"].defines, debug_macro )
table.insert( package.config["Release"].defines, "NDEBUG" )

if ( OS == "windows" ) then
--******* WINDOWS SETUP ***********
--*	Settings that are Windows specific.
--*********************************
	-- Set wxWidgets include paths
	if ( target == "cb-gcc" ) then
		table.insert( package.includepaths, "$(#WX.include)" )
	else
		table.insert( package.includepaths, "$(WXWIN)/include" )
	end

	if ( options["unicode"] ) then
		if ( target == "cb-gcc" ) then
			table.insert( package.config["Debug"].includepaths, "$(#WX.lib)/gcc_dll/mswud" )
			table.insert( package.config["Release"].includepaths, "$(#WX.lib)/gcc_dll/mswu" )
		elseif ( target == "gnu" or target == "cl-gcc" ) then
			table.insert( package.config["Debug"].includepaths, "$(WXWIN)/lib/gcc_dll/mswud" )
			table.insert( package.config["Release"].includepaths, "$(WXWIN)/lib/gcc_dll/mswu" )
		else
			table.insert( package.config["Debug"].includepaths, "$(WXWIN)/lib/vc_dll/mswud" )
			table.insert( package.config["Release"].includepaths, "$(WXWIN)/lib/vc_dll/mswu" )
		end
	else
		if ( target == "cb-gcc" ) then
			table.insert( package.config["Debug"].includepaths, "$(#WX.lib)/gcc_dll/mswd" )
			table.insert( package.config["Release"].includepaths, "$(#WX.lib)/gcc_dll/msw" )
		elseif ( target == "gnu" or target == "cl-gcc" ) then
			table.insert( package.config["Debug"].includepaths, "$(WXWIN)/lib/gcc_dll/mswd" )
			table.insert( package.config["Release"].includepaths, "$(WXWIN)/lib/gcc_dll/msw" )
		else
			table.insert( package.config["Debug"].includepaths, "$(WXWIN)/lib/vc_dll/mswd" )
			table.insert( package.config["Release"].includepaths, "$(WXWIN)/lib/vc_dll/msw" )
		end
	end

	if ( target == "cb-gcc" ) then
		table.insert( package.libpaths, "$(#WX.lib)/gcc_dll" )
	elseif ( target == "gnu" or target == "cl-gcc" ) then
		table.insert( package.libpaths, "$(WXWIN)/lib/gcc_dll" )
	else
		table.insert( package.libpaths, "$(WXWIN)/lib/vc_dll" )
	end

	-- Set wxWidgets libraries to link.
	if ( options["unicode"] ) then
		table.insert( package.config["Release"].links, "wxmsw"..wx_ver.."u" )
		table.insert( package.config["Debug"].links, "wxmsw"..wx_ver.."ud" )
	else
		table.insert( package.config["Release"].links, "wxmsw"..wx_ver )
		table.insert( package.config["Debug"].links, "wxmsw"..wx_ver.."d" )
	end

	-- Set the Windows defines.
	table.insert( package.defines, { "__WXMSW__" , "WIN32", "_WINDOWS" } )
else
--******* LINUX SETUP *************
--*	Settings that are Linux specific.
--*********************************
	-- Ignore resource files in Linux.
	table.insert( package.excludes, matchrecursive( "*.rc" ) )
	table.insert( package.defines, { "LINUX" , "unix" } )

	-- Set wxWidgets build options.
	table.insert( package.config["Debug"].buildoptions, "`wx-config "..debug_option.." --cflags`" )
	table.insert( package.config["Debug"].buildoptions, "`xml2-config --cflags`" )

	table.insert( package.config["Release"].buildoptions, "`wx-config --cflags`" )
	table.insert( package.config["Release"].buildoptions, "`xml2-config --cflags`" )

	-- Set the wxWidgets link options.
	table.insert( package.config["Debug"].linkoptions, "`wx-config "..debug_option.." --static=no --libs all`" )
	table.insert( package.config["Debug"].linkoptions, "`xml2-config --libs`" )

	table.insert( package.config["Release"].linkoptions, "`wx-config --debug=no --static=no --libs all`" )
	table.insert( package.config["Release"].linkoptions, "`xml2-config --libs`" )
end

