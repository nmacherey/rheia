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
package.name = "rheiacsirocsa"
-- Set this if you want a different name for your target than the package's name.
local targetName = "rheiacsirocsa"
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
package.files = { matchfiles( "../../src/csirocsa/*.cpp", "../../src/csirocsa/*.hpp", "../../src/csirocsa/*.cxx", "../../src/csirocsa/*.h", "../../src/csirocsa/*.cc", "../../src/csirocsa/*.hh" , "../../src/csirocsa/*.c" ), matchfiles( "../../include/csirocsa/*.h" ) }

-- Set the include paths.
package.includepaths = { "../../include/csirocsa" }

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
CreateCommonBuildOptions( package , options , {} )

-- Additional Preprocessor options especially for dynamic libraries options
table.insert( package.config["Release"].defines , { "csirocsa_EXPORTS"} )
table.insert( package.config["Debug"].defines , { "csirocsa_EXPORTS" } )

CreateCommonBuildOptions( package , options , {} )
CreateCompilerFlags( package , "Release" , "Debug" )
InsertStandardLibraries( package )
CreateRPathOptions( package , "Release" , "Debug")
