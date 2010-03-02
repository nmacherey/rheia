project.name = "rheia"

-- Configureations. All I am doing is reordering them so that
-- it defaults to a Release build.
project.configs = { "Release", "Debug" }

-- Add packages here.
if ( windows ) then
	dopackage( "src/libxml2" )
end

dopackage( "src/irrlicht" )
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
dopackage( "src/rheia/python" )
dopackage( "src/rheia" )
dopackage( "src/tuto1" )
dopackage( "webconnect/testapp" )

function CreateSymlink( pathToLink, symLink )
	os.execute( "ln -s -f -n " .. pathToLink .. " " .. symLink  )
end

