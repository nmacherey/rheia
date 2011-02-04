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

-- Set the name of your package.
package.name = "rheia"
-- Set this if you want a different name for your target than the package's name.
local targetName = "rheia"
package.kind = "winexe"
-- Common setup
package.language = "c++"

-- Set the files to include.
package.files = { matchfiles( "../../src/rheia/*.cpp" ), matchfiles( "../../include/rheia/*.h" ) }

-- Set the include paths.
package.includepaths = { "../../include/rheia" , "../../include/rheia/python" , "../../include/rheia/editor" , "../../include/rheia/loggers" , "../../include/rheia/base" , "../../include/rheia/utils" , "../../include/rheia/packagemgt" , "../../include/rheia/workspacemgt" }

AppendAdditionalIncludes( package )

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
package.config["Debug"].target = targetName

SetUpDefaultLibs( package , "Release" , "Debug" )

if( not options["no-irrlicht"] ) then
	table.insert( package.defines, "RHEIA_USE_IRRLICHT" )
	table.insert( package.links , "rheiairrlicht" )
end

-- Insert the wxShapeFramework library
table.insert( package.links , {"rheiacsirocsa" , "rheiaqsastime" , "rheiaplplot" , "rheiawxplplot" , "rheiawebconnect" } )
table.insert( package.links , {"rheiautils" , "rheiabase" , "rheialoggers" , "rheiapackagemgt" , "rheiaworkspacemgt" , "rheiaeditor" , "rheiapython" } )
if( windows ) then
	table.insert( package.links , "libxml2" )
end

SetUpDefaultPaths( package , "Release" , "Debug" )
CreateTargetDefinitionsExe( package , targetName , "Release" , "Debug" )

CreateExePostBuildStepFor( package , "Release" )
CreateExePostBuildStepFor( package , "Debug" )

-- Make the global definitions for that package
CreateCommonBuildOptions( package , options , {} )
CreateCompilerFlags( package , "Release" , "Debug" )
InsertStandardLibraries( package )
InsertWxWidegtsDefines( package , "Release" , "Debug" , options )
InsertWxWidegtsLibs( package , "Release" , "Debug" , options )
CreateRPathOptions( package , "Release" , "Debug")
CreateXml2Defines( package , "Release" , "Debug" )
CreateXml2Flags( package , "Release" , "Debug" )
