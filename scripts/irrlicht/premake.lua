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

-- Include the helper functions for all libraries
dofile ("../../share/premake_package_template.lua")

--******* Initial Setup ************
--* Most of the setting are set here.
--**********************************
-- Set the name of your package.
package.name = "rheiairrlicht"
-- Set this if you want a different name for your target than the package's name.
local targetName = "rheiairrlicht"
-- Common setup
package.language = "c++"
-- Set the kind of package you want to create.
--		Options: exe | winexe | lib | dll
package.kind = "dll"

-- Get the library version, this si mainly for uniformization
-- of all libraries so we are sure that they have the same
-- version number for all
local version,version_win = GetLibraryVersion()

-- Get the python library version
local python_ver = GetPythonLibraryVersion(options)

-- Set the files to include.
if ( windows ) then
	package.files = { matchrecursive( "../../src/irrlicht/*.cpp", "../../src/irrlicht/*.hpp", "../../src/irrlicht/*.cxx", "../../src/irrlicht/*.h", "../../src/irrlicht/*.cc", "../../src/irrlicht/*.hh" , "../../src/irrlicht/*.c" ), matchrecursive( "../../include/irrlicht/*.cpp", "../../include/irrlicht/*.hpp", "../../include/irrlicht/*.cxx", "../../include/irrlicht/*.h", "../../include/irrlicht/*.cc", "../../include/irrlicht/*.hh" ) }
elseif ( macosx ) then
	package.files = { matchrecursive( "../../src/irrlicht/*.cpp", "../../src/irrlicht/*.c", "../../src/irrlicht/*.hpp", "../../src/irrlicht/*.cxx", "../../src/irrlicht/*.h", "../../src/irrlicht/*.cc", "../../src/irrlicht/*.hh" ), matchfiles( "MacOSX/*.cpp", "MacOSX/*.hpp", "MacOSX/*.cxx", "MacOSX/*.h", "MacOSX/*.cc", "MacOSX/*.hh" , "MacOSX/*.mm" )  , matchrecursive( "../../include/irrlicht/*.cpp", "../../include/irrlicht/*.hpp", "../../include/irrlicht/*.cxx", "../../include/irrlicht/*.h", "../../include/irrlicht/*.cc", "../../include/irrlicht/*.hh" ) }
else
	package.files = { matchfiles( "../../src/irrlicht/*.cpp", "../../src/irrlicht/*.hpp", "../../src/irrlicht/*.cxx", "../../src/irrlicht/*.h", "../../src/irrlicht/*.cc", "../../src/irrlicht/*.hh" ), matchfiles( "../../include/irrlicht/*.cpp", "../../include/irrlicht/*.hpp", "../../include/irrlicht/*.cxx", "../../include/irrlicht/*.h", "../../include/irrlicht/*.cc", "../../include/irrlicht/*.hh" ) }
end

-- Set the include paths.
package.excludes = matchfiles("../../src/irrlicht/jpeglib/ansi2knr.c", "../../src/irrlicht/jpeglib/cdjpeg.c" , "../../src/irrlicht/jpeglib/cjpeg.c" , "../../src/irrlicht/jpeglib/ckconfig.c" , "../../src/irrlicht/jpeglib/djpeg.c" , "../../src/irrlicht/jpeglib/example.c" , "../../src/irrlicht/jpeglib/jmemansi.c" , "../../src/irrlicht/jpeglib/jmemdos.c" , "../../src/irrlicht/jpeglib/jmemmac.c" , "../../src/irrlicht/jpeglib/jmemname.c" , "../../src/irrlicht/jpeglib/jpegtran.c" , "../../src/irrlicht/jpeglib/Tcdjpeg.c" , "../../src/irrlicht/jpeglib/wrjpgcom.c" , "../../src/irrlicht/jpeglib/rdjpgcom.c" );


for i,file in ipairs( package.excludes ) do
        print( file );	
	for j,f in ipairs(package.files) do
		local found = false
		for k,fl in ipairs(f) do

			if ( file == fl ) then
				print( "removing file " .. package.files[j][k] )
				table.remove( package.files[j] , k )
				print( package.files[j][k] )
				found = true
				break
			end
		end
		if( found ) then 
			break
		end
	end
end


if ( windows ) then
	package.includepaths = { "../../include/irrlicht" , "../../src/irrlicht/jpeglib" , "../../src/irrlicht/libpng" , "../../src/irrlicht/zlib" , "../../src/irrlicht/MacOSX" }
	package.defines = { "" }
elseif ( macosx ) then
	package.includepaths = { "../../include/irrlicht" , "../../src/irrlicht/jpeglib" , "../../src/irrlicht/libpng" , "../../src/irrlicht/zlib" , "../../src/irrlicht/MacOSX" }
	table.insert( package.linkoptions, "-framework OpenGL" )
	table.insert( package.linkoptions, "-framework CoreFoundation" )
	table.insert( package.linkoptions, "-framework Carbon" )
	table.insert( package.linkoptions, "-framework Cocoa" )
	table.insert( package.linkoptions, "-framework IOKit" )
	table.insert( package.linkoptions, "-framework Carbon" )
	package.defines = { "MACOSX" }
else
	package.includepaths = { "../../include/irrlicht" }
	-- Set the libraries it links to.
	package.links = { "GL", "GLU", "glut", "Xxf86vm", "jpeg" , "z" , "png" }
	package.defines = { "LINUX" }
end

--******* GENAERAL SETUP **********
--*	Settings that are not dependant
--*	on the operating system.
--*********************************

-- Set up all object dirs for putting objects at the right place
SetUpObjectDirectories( package , options ,  "Release" , "Debug" )

-- Set the default targetName if none is specified.
if ( string.len( targetName ) == 0 ) then
	targetName = package.name
end

package.config["Release"].target = targetName
package.config["Debug"].target = targetName .. ""

-- Set up default paths and names
SetUpDefaultPaths( package , "Release" , "Debug" )
CreateTargetDefinitionsLibrary( package , targetName , "Release" , "Debug" )

-- Append postbuild steps
CreateLibraryPostBuildStepFor( package , "Release" )
CreateLibraryPostBuildStepFor( package , "Debug" )

-- Make the global definitions for that package
CreateCommonBuildOptionsIrr( package , options , {} )

-- Additional Preprocessor options especially for dynamic libraries options
table.insert( package.config["Release"].defines , { "IRRLICHT_EXPORTS"} )
table.insert( package.config["Debug"].defines , { "IRRLICHT_EXPORTS" } )

CreateCompilerFlags( package , "Release" , "Debug" )
InsertStandardLibraries( package )
CreateRPathOptions( package , "Release" , "Debug")
