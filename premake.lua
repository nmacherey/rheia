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
	dopackage( "src/libxml2" )
end

if( not options["no-irrlicht"] ) then
	dopackage( "src/irrlicht" )
end

dopackage( "src/csirocsa" )
dopackage( "src/qsastime" )
--dopackage( "src/wxwidgets" )
dopackage( "src/plplot" )
dopackage( "src/wxplplot" )
dopackage( "webconnect/src" )
dopackage( "src/rheia/utils" )
dopackage( "src/rheia/base" )
dopackage( "src/rheia/loggers" )
dopackage( "src/rheia/packagemgt" )
dopackage( "src/rheia/workspacemgt" )
dopackage( "src/rheia/editor" )
dopackage( "src/rheia/python" )
dopackage( "src/rheia" )

-- Generate python bindings libraries
dopackage("python/utils")
dopackage("python/base")
dopackage("python/loggers")
dopackage("python/packagemgt")
dopackage("python/workspacemgt")

function CreateSymlink( pathToLink, symLink )
	os.execute( "ln -s -f -n " .. pathToLink .. " " .. symLink  )
end

