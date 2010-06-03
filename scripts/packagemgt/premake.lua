--*****************************************************************************
--*	author:		nicolas macherey <nm@graymat.fr>
--*	date:		21/02/2010
--*	version:	1.00-beta
--* copyright (c) 2010 nicolas macherey
--*
--* this program is licensed under the terms of the rheia user license agreement
--* please refer to license.txt to see the exact terms and conditions.
--*
--*	notes:
--*		- use the '/' slash for all paths.
--*****************************************************************************

-- include the helper functions for all libraries
dofile ("../../share/premake_package_template.lua")

--******* initial setup ************
--* most of the setting are set here.
--**********************************
-- set the name of your package.
package.name = "rheiapackagemgt"
-- set this if you want a different name for your target than the package's name.
local targetName = "rheiapackagemgt"
-- common setup
package.language = "c++"
-- set the kind of package you want to create.
--		options: exe | winexe | lib | dll
package.kind = "dll"

-- Get the library version, this si mainly for uniformization
-- of all libraries so we are sure that they have the same
-- version number for all
local version,version_win = GetLibraryVersion()

-- Get the python library version
local python_ver = GetPythonLibraryVersion(options)

-- package files
package.files = { matchfiles( "../../src/rheia/packagemgt/*.cpp" , "../../src/rheia/packagemgt/*.h" ), matchfiles( "../../include/rheia/packagemgt/*.h" ) }

-- set the include paths.
package.includepaths = { "../../include/rheia/packagemgt" , "../../include/rheia/loggers" , "../../include/rheia/base" , "../../include/rheia/utils" , "../../webconnect/include" }

--******* genaeral setup **********
--*	settings that are not dependant
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

-- additional preprocessor options especially for dynamic libraries options
table.insert( package.config["Release"].defines , { "RHEIA_PMGT_MAKINGDLL" } )
table.insert( package.config["Debug"].defines , { "RHEIA_PMGT_MAKINGDLL" } )

-- add the related links for plplot
table.insert( package.links , { "rheiautils" , "rheiawebconnect" , "rheiabase" , "rheialoggers" } );

if( windows ) then
	table.insert( package.links , "libxml2" )
end

-- Make the global definitions for that package
CreateCommonBuildOptions( package , options , {} )
CreateCompilerFlags( package , "Release" , "Debug" )
InsertStandardLibraries( package )
InsertWxWidegtsDefines( package , "Release" , "Debug" , options )
InsertWxWidegtsLibs( package , "Release" , "Debug" , options )
CreateRPathOptions( package , "Release" , "Debug")
CreateXml2Defines( package , "Release" , "Debug" )
CreateXml2Flags( package , "Release" , "Debug" )


