/**
*   @file RheiaPackagePolicy.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 23-November-2009
*/

/**
*   @page rheia_package_policy Rheia Package Policy
*
*   In Rheia package are managed quite similarly as debian/ubuntu packages. We have choosen to do this way in order to
*   manage packages dependecies in the right way.
*
*   For example you may have to write an environment plugin derived from RheiaEnvionmentPlugin which provides the application
*   with different kind of projects. All projects can be developed in the RheiaEnvironmentPugin's library. By doing this,
*   maintaining your environment can become a difficult task if you have to provide users with many different kind of projects
*   and if you have different development teams working on each kind of project. In order to allow a good organization of
*   such developments it might be interesting to let each projects be defined in different libraries (i.e : differnet packages)
*   that can then be assocaited to their parent environment by Rheia. This will enables organization and management facilities
*   of your development teams. Because some developers can be responsible for developing your models and different one can be
*   responsible for developing each set of functionalities specific to each kind of projects.
*
*   If you want to succeed in such tasks you will have to develop a "Factory Design Pattern" in order to allow any developer to
*   register their projects for your environment when the plugin/package library is loaded. Note that we provide you with good
*   models to fastly develop such patterns.
*
*   <h1> How packages are used </h1>
*
*   Rheia package information are provided via xml files. For each package you develop you have to write a control.xml file
*   based on the Rheia PackageControl.xsd. This file is like the debian package control file and has to be written properly
*   else your plugin will not be loaded by the application and all packages depending on it will not be loaded to.
*
*   The main purpose of the PackageControl.xsd file is to provide the application with the following information about the
*   package :
*
*       - Maintainer :
*           - name
*           - address
*           - zipcode
*           - town
*           - country
*           - phone
*           - fax
*           - email
*           - website
*
*       - Description :
*           - short description
*           - long description
*
*       - Architecture : either ia64 or ia32
*
*       - OS : Linux/Windows/MacOS
*
*       - Version : version are defined like MAJOR.MINOR.BUILD
*           - Major : major version number
*           - Minor : minor version number
*           - Build : build number or correction number
*
*       - Dependecies : name and version of the packages this package depends on
*           - Dependency : a dependency is defined by the dependent package name and its version
*
*       - Category : packages categories are libraries, resources, plugins and categoriess
*
*   <p>
*   When rheia starts it will locate all packages in the two defined Plugins directories (Global and Users) and load all their
*   associated control.xml files from their resources. Then Rheia will read and order the packages loading order accordingly
*   to all packages dependencies. The last step will be to load each package libraries in the right order so any packages will
*   be properly loaded and all their dependencies to.
*
*   A Rheia package can hav differnet purpose :
*       + Plugin : the package provide Rheia with additionnal functionalities
*       + Library : the package provide Rheia with new libraries that can be used in different plugins
*       + Resource : the package provide Rheia with additionnal files that will be available for any plugins in the application
*       + Multiple : the package provide Rheia with at least one of the preceeding category.
*
*   All packages are not managed the same in Rheia as Libraries have to be loaded first else the plugin Loading system will not
*   be able to open the plugin's dynamic library. Whereas resource packages files are simply checked when Rheia is started and
*   related files are moved to the right directory.
*   </p>
*/
