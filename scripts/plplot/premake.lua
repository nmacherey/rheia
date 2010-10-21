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
package.name = "rheiaplplot"
-- Set this if you want a different name for your target than the package's name.
local targetName = "rheiaplplot"
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

package.files = { matchfiles( "../../src/wxwidgets/*.cpp", "../../src/wxwidgets/*.hpp", "../../src/wxwidgets/*.cxx", "../../src/wxwidgets/*.h", "../../src/wxwidgets/*.cc", "../../src/wxwidgets/*.hh" , "../../src/wxwidgets/*.c" ) , matchfiles( "../../src/plplot/*.cpp", "../../src/plplot/*.hpp", "../../src/plplot/*.cxx", "../../src/plplot/*.h", "../../src/plplot/*.cc", "../../src/plplot/*.hh" , "../../src/plplot/*.c" ), matchfiles( "../../include/plplot/*.h" ) }


-- Set the include paths.
package.includepaths = { "../../include/plplot" , "../../include/wxwidgets" , "../../include/csirocsa" , "../../include/qsastime" }

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
table.insert( package.config["Release"].defines , { "plplotd_EXPORTS" , "wxwidgets_EXPORTS" } )
table.insert( package.config["Debug"].defines , { "plplotd_EXPORTS" , "wxwidgets_EXPORTS" } )

-- Add the related links for plplot
table.insert( package.links , { "rheiacsirocsa" , "rheiaqsastime" } );

-- Make the global definitions for that package
CreateCommonBuildOptions( package , options , {} )
CreateCompilerFlags( package , "Release" , "Debug" )
InsertStandardLibraries( package )
InsertWxWidegtsDefines( package , "Release" , "Debug" , options )
InsertWxWidegtsLibs( package , "Release" , "Debug" , options )
CreateRPathOptions( package , "Release" , "Debug")
CreateXml2Defines( package , "Release" , "Debug" )
CreateXml2Flags( package , "Release" , "Debug" )
