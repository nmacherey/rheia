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
package.name = "libxml2"

-- Set this if you want a different name for your target than the package's name.
local targetName = "libxml2"
local version_win = "2"

-- Set the kind of package you want to create.
--		Options: exe | winexe | lib | dll
package.kind = "dll"

-- Set the files to include.
if ( OS == "windows" ) then
	addoption("cb-msvc8", "Compile with msvc8 options in codeblocks");
	package.files = { matchfiles( "../../include/*.h" ), matchrecursive( "*.cpp", "*.hpp", "*.cxx", "*.h", "*.cc", "*.hh" , "*.c"), matchrecursive( "../../include/libxml2/*.h", "../../include/libxml/*.h") }
	package.includepaths = { "../../include/libxml2" , "../../include" }
	-- Set the include paths.
	package.defines = { "WIN32" }


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
	package.config["Debug"].target = targetName

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
		
		table.insert( package.defines, { "WIN32", "_WINDOWS" , "__WIN32__" , "HAVE_WIN32_THREADS" , "HAVE_COMPILER_TLS" , "_MBCS" , "__WXMSW__" , "_CRT_SECURE_DEPRECATE" , "_CRT_SECURE_NO_WARNINGS" , "_CRT_NONSTDC_NO_DEPRECATE" } )
		
		package.config["Release"].postbuildcommands = { "gmkdir -p ../../devel/Release/include/rheia" , "cp -ru ../../include/libxml2 ../../devel/Release/include/rheia" }
		package.config["Debug"].postbuildcommands = { "gmkdir -p ../../devel/Debug/include/rheia" , "cp -ru ../../include/libxml2 ../../devel/Debug/include/rheia" }
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
		
		package.config["Release"].postbuildcommands = { "gmkdir -p ../../devel/Release/include/rheia" , "cp -ru ../../include/libxml2 ../../devel/Release/include/rheia" }
		package.config["Debug"].postbuildcommands = { "gmkdir -p ../../devel/Debug/include/rheia" , "cp -ru ../../include/libxml2 ../../devel/Debug/include/rheia" }
	end
	
	package.links = { "user32" , "wsock32" , "ws2_32" , "kernel32" }
	
	package.config["Release"].target = targetName
	package.config["Release"].targetprefix = ""
	package.config["Release"].targetextension = "dll"
	package.config["Release"].libdir = "../../devel/Release/lib"
	package.config["Release"].bindir = "../../devel/Release/bin"

	package.config["Debug"].target = targetName
	package.config["Debug"].targetprefix = ""
	package.config["Debug"].targetextension = "dll"
	package.config["Debug"].libdir = "../../devel/Debug/lib"
	package.config["Debug"].bindir = "../../devel/Debug/bin"
end
