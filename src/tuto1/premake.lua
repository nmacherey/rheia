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

-- Set the name of your package.
package.name = "pyedt"

-- Set this if you want a different name for your target than the package's name.
local targetName = "pyedt"
local version = "1.1.1"
local version_win = "1_1_1"

local CP = ""

if( macosx ) then
    CP="cp -r "
else
    CP="cp -ru "
end

local python_ver

if( macosx ) then
    python_ver="2.6"
else
    python_ver="2.5"
end

-- Set the kind of package you want to create.
--		Options: exe | winexe | lib | dll
package.kind = "winexe"

-- Set the files to include.
if ( not windows ) then
	package.files = { matchfiles( "*.cpp", "*.hpp", "*.cxx", "*.h", "*.cc", "*.hh" , "*.c" ), matchfiles( "../../include/tuto1/*.h" ) }
else
	package.files = { matchfiles( "*.cpp", "*.hpp", "*.cxx", "*.h", "*.cc", "*.hh" , "*.c" ) , matchfiles( "../../include/tuto1/*.h" ) }
end

-- Set the include paths.
package.includepaths = { "../../include/rheia/python" , "../../include/tuto1" , "../../include/rheia" , "../../include/rheia/packagemgt" , "../../include/rheia/workspacemgt" , "$(WXPYTHON)/include" , "/usr/include/python" .. python_ver , "../../include/rheia/loggers" , "../../include/rheia/base" , "../../include/rheia/utils" , "../../include/irrlicht" , "../../src/irrlicht" }

-- Set the packages dependancies. NOT implimented in the official Premake build for Code::Blocks
package.depends = { "csirocsa", "qsastime" , "plplot" , "irrlicht" , "rheiautils" , "rheiabase" , "rheialoggers" , "rheiapackagemgt" , "rheiaworkspacemgt" , "rheiapython" , "rheia" }

-- Set the defines.
package.defines = { "HAVE_CONFIG_H" , "RHEIA_USE_IRRLICHT" }

--------------------------- DO NOT EDIT BELOW ----------------------------------

--******* GENAERAL SETUP **********
--*	Settings that are not dependant
--*	on the operating system.
--*********************************
-- Package options
addoption( "unicode", "Use the Unicode character set" )
addoption( "with-wx-28", "Use the Unicode character set" )

if ( not windows ) then
	addoption( "disable-wx-debug", "Compile against a wxWidgets library without debugging" )
end

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
		table.insert( package.config["Release"].linkoptions, "-Wl,-L../lib" )
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
	package.config["Debug"].links = { "gmirrlicht-dbg", "gmcsirocsa-dbg", "gmqsastime-dbg", "gmplplot-dbg", "gmwxplplot-dbg" , "rheiautils-dbg" , "rheiabase-dbg" , "rheialoggers-dbg" , "rheiapackagemgt-dbg" , "rheiaworkspacemgt-dbg" , "rheiapython-dbg" ,"python" .. python_ver }
	package.config["Release"].links = { "gmirrlicht", "gmcsirocsa", "gmqsastime", "gmplplot", "gmwxplplot" , "rheiautils" , "rheiabase" , "rheialoggers" , "rheiapackagemgt" , "rheiaworkspacemgt" , "rheiapython" , "python" .. python_ver }

    if( not macosx ) then
        package.config["Release"].postbuildcommands = { "mkdir -p ../../devel/Release/include/pyedt" , "mkdir -p ../../devel/Release/lib" , "mkdir -p ../../devel/Release/share/pyedt/images", CP .. "../../include/tuto1/* ../../devel/Release/include/pyedt" , CP .. "../../share/rheia/resource/images/settings ../../devel/Release/share/pyedt/images" , "zip -j9 -r ../../devel/Release/share/pyedt/resource.zip ../../share/rheia/resource" }
        package.config["Debug"].postbuildcommands = { "mkdir -p ../../devel/Debug/include/pyedt" , "mkdir -p ../../devel/Debug/lib" , "mkdir -p ../../devel/Debug/share/pyedt-dbg/images", CP .. "../../include/tuto1/* ../../devel/Debug/include/pyedt" , CP .. "../../share/rheia/resource/images/settings ../../devel/Debug/share/pyedt-dbg/images" , "zip -j9 -r ../../devel/Debug/share/pyedt-dbg/resource.zip ../../share/rheia/resource" }
    else
        package.config["Release"].postbuildcommands = { "mkdir -p ../../devel/Release/include/pyedt" , "mkdir -p ../../devel/Release/lib" , "mkdir -p ../../devel/Release/share/pyedt/images", CP .. "../../include/tuto1/* ../../devel/Release/include/pyedt" , CP .. "../../share/rheia/resource/images/settings ../../devel/Release/share/pyedt/images" , "zip -j9 -r ../../devel/Release/share/pyedt/resource.zip ../../share/rheia/resource" , "(cd ../../macosx/postinstall &amp;&amp; sh pyedt_postbuild.sh)"}
        package.config["Debug"].postbuildcommands = { "mkdir -p ../../devel/Debug/include/pyedt" , "mkdir -p ../../devel/Debug/lib" , "mkdir -p ../../devel/Debug/share/pyedt-dbg/images", CP .. "../../include/tuto1/* ../../devel/Debug/include/pyedt" , CP .. "../../share/rheia/resource/images/settings ../../devel/Debug/share/pyedt-dbg/images" , "zip -j9 -r ../../devel/Debug/share/pyedt-dbg/resource.zip ../../share/rheia/resource","(cd ../../macosx/postinstall &amp;&amp; sh pyedt_postbuildd.sh)" }
    end

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
		table.insert( package.config["Debug"].links, "wx_gtk2u_stc-2.8" )
		table.insert( package.config["Debug"].linkoptions, "`xml2-config --libs`" )

		table.insert( package.config["Release"].linkoptions, "`wx-config --debug=no --libs`" )
		table.insert( package.config["Release"].linkoptions, "`xml2-config --libs`" )
		table.insert( package.config["Release"].links, "wx_gtk2u_stc-2.8" )
	end
end

