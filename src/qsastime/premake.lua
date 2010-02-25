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
package.name = "qsastime"

-- Set this if you want a different name for your target than the package's name.
local targetName = "gmqsastime"
local version = "1.1.1"
local version_win = "1_1_1"

local CP = ""

if( macosx ) then
    CP="cp -r "
else
    CP="cp -ru "
end

-- Set the kind of package you want to create.
--		Options: exe | winexe | lib | dll
package.kind = "dll"

-- Set the files to include.
if ( not windows ) then
	package.files = { matchfiles( "*.cpp", "*.hpp", "*.cxx", "*.h", "*.cc", "*.hh" , "*.c" ), matchfiles( "../../include/qsastime/*.h" ) }
else
	package.files = { matchrecursive( "*.cpp", "*.hpp", "*.cxx", "*.h", "*.cc", "*.hh" , "*.c" ) , matchrecursive( "../../include/qsastime/*.h" ) }
end

-- Set the include paths.
package.includepaths = { "../../include/qsastime" }


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
		
		table.insert( package.defines, { "IRRLICHT_EXPORTS" , "_USRDLL" , "WIN32", "_WINDOWS" , "__WIN32__" , "HAVE_WIN32_THREADS" , "HAVE_COMPILER_TLS" , "_MBCS" , "__WXMSW__" , "_CRT_SECURE_DEPRECATE" , "_CRT_SECURE_NO_WARNINGS" , "_CRT_NONSTDC_NO_DEPRECATE" } )
		
		package.config["Release"].postbuildcommands = { "gmkdir -p ../../devel/Release/include/rheia" , "cp -ru ../../include/qsastime ../../devel/Release/include/rheia" }
		package.config["Debug"].postbuildcommands = { "gmkdir -p ../../devel/Debug/include/rheia" , "cp -ru ../../include/qsastime ../../devel/Debug/include/rheia" }
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
		
		table.insert( package.buildoptions, "/Dqsastime_EXPORTS" )
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
		
		package.config["Release"].postbuildcommands = { "gmkdir -p ../../devel/Release/include/rheia" , "cp -ru ../../include/qsastime ../../devel/Release/include/rheia" }
		package.config["Debug"].postbuildcommands = { "gmkdir -p ../../devel/Debug/include/rheia" , "cp -ru ../../include/qsastime ../../devel/Debug/include/rheia" }
		
		package.links = { "user32" , "gdi32" , "winspool" , "kernel32" , "comdlg32" , "advapi32" , "shell32" , "ole32" , "oleaut32" , "uuid" , "opengl32" , "winmm" }
	end
	
	package.config["Release"].target = targetName
	package.config["Release"].targetprefix = "lib"
	package.config["Release"].targetextension = "dll"
	package.config["Release"].libdir = "../../devel/Release/lib"
	package.config["Release"].bindir = "../../devel/Release/bin"

	package.config["Debug"].target = targetName .. "-dbg"
	package.config["Debug"].targetprefix = "lib"
	package.config["Debug"].targetextension = "dll"
	package.config["Debug"].libdir = "../../devel/Debug/lib"
	package.config["Debug"].bindir = "../../devel/Debug/bin"
	
	-- Set the Windows defines.
	table.insert( package.defines, { "WIN32", "_WINDOWS" } )
else
--******* LINUX SETUP *************
--*	Settings that are Linux specific.
--*********************************
		-- Set the build options.
	package.buildflags = { "extra-warnings" }
	package.config["Release"].buildflags = { "optimize-speed" }

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
		package.config["Release"].targetprefix = "lib"
		package.config["Release"].targetextension = "so." .. version
		package.config["Release"].libdir = "../../devel/Release/lib"
		package.config["Release"].bindir = "../../devel/Release/lib"

		package.config["Debug"].target = targetName .. "-dbg"
		package.config["Debug"].targetprefix = "lib"
		package.config["Debug"].targetextension = "so." .. version
		package.config["Debug"].libdir = "../../devel/Debug/lib"
		package.config["Debug"].bindir = "../../devel/Debug/lib"

		package.config["Release"].postbuildcommands = { "mkdir -p ../../devel/Release/include/rheia" , CP .. "../../include/qsastime ../../devel/Release/include/rheia" , "(cd ../../devel/Release/lib &amp;&amp; rm -rf " .. package.config["Release"].targetprefix .. package.config["Release"].target .. ".so)" , "(cd ../../devel/Release/lib &amp;&amp; ln -s " .. package.config["Release"].targetprefix .. package.config["Release"].target .. "." .. package.config["Release"].targetextension .. " " .. package.config["Release"].targetprefix .. package.config["Release"].target .. ".so)" }

		package.config["Debug"].postbuildcommands = { "mkdir -p ../../devel/Debug/include/rheia" , CP .. "../../include/qsastime ../../devel/Debug/include/rheia" , "(cd ../../devel/Debug/lib &amp;&amp; rm -rf " .. package.config["Debug"].targetprefix .. package.config["Debug"].target .. ".so)" , "(cd ../../devel/Debug/lib &amp;&amp; ln -s " .. package.config["Debug"].targetprefix .. package.config["Debug"].target .. "." .. package.config["Debug"].targetextension .. " " .. package.config["Debug"].targetprefix .. package.config["Debug"].target .. ".so)" }
	end

	table.insert( package.config["Debug"].defines, debug_macro )
	table.insert( package.config["Release"].defines, "NDEBUG" )

	-- Ignore resource files in Linux.
	table.insert( package.excludes, matchrecursive( "*.rc" ) )
end

