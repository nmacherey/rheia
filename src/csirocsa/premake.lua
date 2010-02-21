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
package.name = "csirocsa"

-- Set this if you want a different name for your target than the package's name.
local targetName = "gmcsirocsa"
local version = "1.1.1"
local version_win = "1_1_1"

-- Set the kind of package you want to create.
--		Options: exe | winexe | lib | dll
package.kind = "dll"

-- Set the files to include.
if ( not windows ) then
	package.files = { matchfiles( "*.cpp", "*.hpp", "*.cxx", "*.h", "*.cc", "*.hh" , "*.c" ), matchfiles( "../../include/csirocsa/*.h" ) }
else
	package.files = { matchrecursive( "*.cpp", "*.hpp", "*.cxx", "*.h", "*.cc", "*.hh" , "*.c" ) , matchrecursive( "../../include/csirocsa/*.h" ) }
end

-- Set the include paths.
package.includepaths = { "../../include/csirocsa" }


-- Set the libraries it links to.
--package.links = { "GL", "GLU", "glut", "Xxf86vm", "jpeg" , "z" , "png" }

if ( windows ) then
	package.defines = { "" }
else
	package.defines = { "LINUX" }
end


--------------------------- DO NOT EDIT BELOW ----------------------------------

--******* GENAERAL SETUP **********
--*	Settings that are not dependant
--*	on the operating system.
--*********************************
-- Common setup
package.language = "c"

-- Set object output directory.
package.config["Debug"].objdir = ".objsd"
package.config["Release"].objdir = ".objs"

debug_macro = { "DEBUG", "_DEBUG" }
-- Set the default targetName if none is specified.

if ( string.len( targetName ) == 0 ) then
	targetName = package.name
end

package.config["Release"].target = targetName
package.config["Debug"].target = targetName.."-dbg"

-- Set the build options.
package.buildflags = { "extra-warnings" }
package.config["Release"].buildflags = { "optimize-speed" }

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
	package.config["Release"].targetprefix = "lib"
	package.config["Release"].targetextension = "so." .. version
	package.config["Release"].libdir = "../../devel/Release/lib"
	package.config["Release"].bindir = "../../devel/Release/lib"
	
	package.config["Debug"].target = targetName .. "-dbg"
	package.config["Debug"].targetprefix = "lib"
	package.config["Debug"].targetextension = "so." .. version
	package.config["Debug"].libdir = "../../devel/Debug/lib"
	package.config["Debug"].bindir = "../../devel/Debug/lib"

	package.config["Release"].postbuildcommands = { "mkdir -p ../../devel/Release/include/rheia" , "cp -ru ../../include/csirocsa ../../devel/Release/include/rheia" , "(cd ../../devel/Release/lib &amp;&amp; rm -rf " .. package.config["Release"].targetprefix .. package.config["Release"].target .. ".so)" , "(cd ../../devel/Release/lib &amp;&amp; ln -s " .. package.config["Release"].targetprefix .. package.config["Release"].target .. "." .. package.config["Release"].targetextension .. " " .. package.config["Release"].targetprefix .. package.config["Release"].target .. ".so)" }

	package.config["Debug"].postbuildcommands = { "mkdir -p ../../devel/Debug/include/rheia" , "cp -ru ../../include/csirocsa ../../devel/Debug/include/rheia" , "(cd ../../devel/Debug/lib &amp;&amp; rm -rf " .. package.config["Debug"].targetprefix .. package.config["Debug"].target .. ".so)" , "(cd ../../devel/Debug/lib &amp;&amp; ln -s " .. package.config["Debug"].targetprefix .. package.config["Debug"].target .. "." .. package.config["Debug"].targetextension .. " " .. package.config["Debug"].targetprefix .. package.config["Debug"].target .. ".so)" }
end

table.insert( package.config["Debug"].defines, debug_macro )
table.insert( package.config["Release"].defines, "NDEBUG" )

if ( OS == "windows" ) then
--******* WINDOWS SETUP ***********
--*	Settings that are Windows specific.
--*********************************

	-- Set the Windows defines.
	table.insert( package.defines, { "WIN32", "_WINDOWS" } )
else
--******* LINUX SETUP *************
--*	Settings that are Linux specific.
--*********************************
	-- Ignore resource files in Linux.
	table.insert( package.excludes, matchrecursive( "*.rc" ) )
end

