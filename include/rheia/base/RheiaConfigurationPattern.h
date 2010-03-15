/**
*   @file RheiaConfigurationPattern.h
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	19-November-2009
*	@version 0.0.2
*/
#ifndef RheiaConfigurationPattern_h_
#define RheiaConfigurationPattern_h_

#include <RheiaBaseSettings.h>
#include <RheiaGlobals.h>
#include <RheiaManager.h>

#include <wx/string.h>
#include <set>
#include <map>

/* Rheia imports */
class RheiaConfigurationManager;
WX_DECLARE_STRING_HASH_MAP(RheiaConfigurationManager*, RheiaConfigurationManagerMap);

/* libxml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;
typedef struct _xmlXPathContext xmlXPathContext;

/**
*   @class RheiaConfigurationPattern
*
*   @brief This is the "Builder Design Pattern" class for helping RheiaConfiguration management
*
*   The Builder Pattern is a software design pattern. The intention is to abstract steps of
*   construction of objects so that different implementations of these steps can construct
*   different representations of objects.
*   Often, the Builder Pattern is used to build Products in accordance to the Composite pattern,
*   a structure pattern.
*
*   RheiaConfigurationPattern is the "Builder" class for RheiaConfigurationManager. it focuses
*   on constructing a RheiaConfigurationManager in a given context choosen by the developper.
*   The "Director" for this class is the most usefull manager in Rheia : RheiaManager.
*
*   You shall never have to use this class direclty, as it is a intermediate between the concrete
*   RheiaManager::Get()->GetConfigurationManager() and the RheiaConfigurationManager class.
*   This objects simply loads the rheia configuration file for the current personality and
*   provide Rheia developpers with different configuration groups that can be view as tables
*   in an information database. You can easily build any kind of configuration group you need
*   in the application.
*
*   If you are a Rheia core developper you might have to develop in this class for managing
*   special configuration options such as common configuration files or temporaries configuration
*   files. However if your are not this class may only interest you if you dont know the usefull
*   "Builder design Pattern".
*
*   If you follow the Wikipedia Link about "Design Patterns" you will find it in the list. The
*   Builder Pattern is represented as a set of objects as follow :
*
*   + Director : Here RheiaManager, which is responsible for managing the correct sequence of
*       object creation. It receives a Concrete Builder as a parameter and executes the necessary
*       operations on it.
*
*   + Concrete Builder : Here the global instance of RheiaConfigurationPattern.
*       Provide implementation for Builder. Construct and assemble parts to build the objects.
*
*   + Builder : Here RheiaConfigurationPattern class but not it's instance. Abstract interface for
*       creating objects (product).
*
*   + Product : Here RheiaConfgurationManager instances. The final object that will be created by
*       the Director using Builder.
*
*   You may notice here that this class is a simplified "Builder Pattern" has there is no real
*   differences between the "Concrete Builder" and the "Builder" itself.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	19-November-2009
*	@version 0.0.2
*/
class BASE_DLLEXPORT RheiaConfigurationPattern : public Singleton<RheiaConfigurationPattern>
{
    /************************************************************************************
    *   FRIENDS
    ************************************************************************************/
    /** Give our private members access to the configuration manager */
    friend class RheiaConfigurationManager;
    /** Give our private members access to the rheia manager */
    friend class RheiaManager;
    /** Give Singleton class access to our private members */
    friend class Singleton<RheiaConfigurationPattern>;

protected:
    /************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    ************************************************************************************/
    /**
    *   Basic constrcutor,
    *   As any other singleton in Rheia, you have to use RheiaConfigurationPattern::Get()
    *   to get the global instance for this class. However you should never have to
    *   use this unless you are a Rheia core Developper.
    */
    RheiaConfigurationPattern();

    /**
    *   Default destructor,
    *   As any other singleton in Rheia, you have to use RheiaConfigurationPattner::Free()
    *   to free the global instance of this manager. However, you should never have to
    *   use this unless you are a Rheie core Developper
    */
    ~RheiaConfigurationPattern();

    /************************************************************************************
    *   METHODS
    ************************************************************************************/
    /** method used to properly Save the confgiuration file manager */
    void Save();

    /** method used to change the configuration file to the one given in argument */
    void ChangeConfigurationTo(const wxString& file);

    /** Build a configuration manager for the given group name */
    RheiaConfigurationManager* Build(const wxString& group);

private :
    /************************************************************************************
    *   PRIVATE MEMBERS
    ************************************************************************************/
    RheiaConfigurationManagerMap m_groups; 			/*!< Namespaces maps, used for getting profiles informations */
    xmlDoc* m_doc;									/*!< User configuration document */
    xmlDoc *m_tempDoc;							    /*!< Temporary document used to store temporary info */

    /**
    *   As any configuration files can be used by different instance of the application
    *   We need here a critical section in order to avoid crashed due to simultaneous
    *   access to the configuration file.
    */
    wxCriticalSection m_criticalSection;

    /** path to the configuration file */
    wxString m_configFile;
};

#endif
