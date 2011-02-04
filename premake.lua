project.name = "rheia"

-- Configureations. All I am doing is reordering them so that
-- it defaults to a Release build.
project.configs = { "Release", "Debug" }

-- Package options
addoption( "unicode", "Use the Unicode character set" )
addoption( "with-wx-28", "Use wxWidgets 2.8 version" )

if ( not windows ) then
	addoption( "disable-wx-debug", "Compile against a wxWidgets library without debugging" )
	addoption("rpath", "Specify the rpath for the compiled binary")
end

addoption( "no-irrlicht", "Don't use irrlicht" )

-- Add packages here.
if ( windows ) then
	dopackage( "scripts/libxml2" )
end

if( not options["no-irrlicht"] ) then
	dopackage( "scripts/irrlicht" )
end

dopackage( "scripts/csirocsa" )
dopackage( "scripts/qsastime" )
--dopackage( "src/wxwidgets" )
dopackage( "scripts/plplot" )
dopackage( "scripts/wxplplot" )
dopackage( "scripts/webconnect" )
dopackage( "scripts/utils" )
dopackage( "scripts/base" )
dopackage( "scripts/loggers" )
dopackage( "scripts/packagemgt" )
dopackage( "scripts/workspacemgt" )
dopackage( "scripts/editor" )
dopackage( "scripts/python" )
dopackage( "scripts/rheia" )

-- Generate python bindings libraries
--dopackage("python/utils")
--dopackage("python/base")
--dopackage("python/loggers")
--dopackage("python/packagemgt")
--dopackage("python/workspacemgt")

function CreateSymlink( pathToLink, symLink )
	os.execute( "ln -s -f -n " .. pathToLink .. " " .. symLink  )
end

