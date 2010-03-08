/**
*   @file RheiaMenuManager.h
*
*   Revision : 15-January-2010
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*   Revision : 8-February-2010
*       Nicolas Macherey (nm@graymat.fr)
*       Changes :   Added RheiaMenuFunctorManager and modifications of RheiaMenuManager to
*                   associated to a RheiaManagedFrame.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.2
*/
#ifndef RheiaMenuManager_h_
#define RheiaMenuManager_h_

#include <RheiaBaseSettings.h>
#include <RheiaManager.h>
#include <RheiaFunctor.h>
#include <RheiaManagedFrame.h>
#include <RheiaEventFrame.h>
#include <wx/event.h>
#include <vector>

class wxMenuBar;
class wxMenu;
class wxMenuItemId;

#ifndef SWIG
/**
*   @class RheiaMenuFunctorBase
*
*   @brief This base class define the menu functor in rheia used to register by the menu manager to rebuild
*   menus when the menu is built/rebuilt...
*
*   Any plugin, tool or object can register menu creation callbacks in the RheiaMenuManager. This allow the menu manager
*   to call this method when building or rebuilding Rheia's menu. The meu functor base is the base class used to store such
*   callbacks in the menu manager.
*   Unless you are a Rheia Developer you should never use this class directly for inheritence or derivation use the RheiaMenuFunctor
*   template class to register your callback in the menu manager.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/
class RheiaMenuFunctorBase : public RheiaFunctorBase
{
public:
    /************************************************************************************
    *   CONSTRUCTOR
    ************************************************************************************/
    /** default constructor */
    RheiaMenuFunctorBase( ) {}

    /** basic constructor */
    RheiaMenuFunctorBase( const RheiaMenuFunctorBase& rhs ) {}

    /************************************************************************************
    *   METHODS
    ************************************************************************************/
    /** Calling method */
    virtual void Call(wxMenuBar* menuBar) = 0;
};

/**
*   @class RheiaMenuFunctor
*
*   @brief Menu functor class.
*
*   This template method is used to register any menu callback on an instanciated object in Rheia. This is
*   the end template for generalizing functions pointers in non-static objects. You have to use it if you
*   want to keep a static menu in Rheia's menubar ...
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/
template<class ClassType> class RheiaMenuFunctor : public RheiaMenuFunctorBase
{
private:
    typedef void (ClassType::*Member)(wxMenuBar*);
    ClassType* This;
    Member member;
public:
    RheiaMenuFunctor(ClassType* this_, Member member_) : RheiaMenuFunctorBase() , This(this_), member(member_) {}
    RheiaMenuFunctor(const RheiaMenuFunctor<ClassType>& rhs) : RheiaMenuFunctorBase(rhs) , This(rhs.This), member(rhs.member) {}
    virtual void* GetThis()
    {
        return This;
    }
    virtual void Call(wxMenuBar* menuBar)
    {
        if (This) (This->*member)(menuBar);
    }
};

typedef std::vector< RheiaMenuFunctorBase* > RheiaMenuFunctorArray;

#endif

/**
*	@class RheiaMenuManager
*
*	@brief RheiaMenuManager is the class for providing plugins with the main menu bar information.
*
*	RheiaMenuManager is used at initialization time in Rheia, it means that once the application is runned,
*	The menubar and all its content is available in the object associated to the application.
*	The main frame is managing menu events, but this class is derived from an event handler, and by the way
*	when instanciated can handle events. This means that if we need to declare here special events generation
*	or callbacks this is possible in this class.
*
*   The menu manager can be used to Register a menu functor (Objects methods pointer generalization). Once registered
*   the functor will be called at each time the menu is Created/Recreated using RheiaMenuManager::ReceateMenuBar and
*   RheiaMenuManager::CreateMenuBar.
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	21-Nov-2008
*	@version 0.0.1
*/
class BASE_DLLEXPORT RheiaMenuManager : public wxEvtHandler, public RheiaMgr<RheiaManagedFrame,RheiaMenuManager>
{
    /** Give our private member access to RheiaMgr<RheiaManagedFrame,RheiaMenuManager> */
    friend class RheiaMgr<RheiaManagedFrame,RheiaMenuManager>;

    /** Give our private member access to RheiaManager */
    friend class RheiaManager;
public :
    /**********************************************************************************************************
    *	METHODS
    **********************************************************************************************************/
    /*! Get the Main menu bar */
    wxMenuBar *GetMainMenuBar()
    {
        return MainMenuBar;
    };

private :
    /**********************************************************************************************************
    *	CONSTRUCTORS
    **********************************************************************************************************/
    /*! Default constructor */
    RheiaMenuManager( RheiaManagedFrame* parent );

    /*! Default destructor */
    ~RheiaMenuManager();

    /**********************************************************************************************************
    *	METHODS
    **********************************************************************************************************/
    /** This method when called recreates the menubar for Rheia's Main frame. */
    void RecreateMenuBar();

    /** This method when called creates the menubar for Rheia's Main frame. */
    void CreateMenuBar();

    /** Register events in the menu manager */
    void RegisterEvents();

    /** Get the parent window */
    RheiaManagedFrame* GetParent() {return m_parent;};

    /** Send event */
    void SendEvent( const wxEventType& type );

    /**********************************************************************************************************
    *	CALLBACKS
    **********************************************************************************************************/
    /** Callback used when a menu function is added in RheiaMenuFunctorManager */
    void OnMenuCallbackAdded( wxCommandEvent& event );

    /** Callback used when a menu function is removed from RheiaMenuFunctorManager */
    void OnMenuCallbackRemoved( wxCommandEvent& event );

    /** On frame closing */
    void OnFrameClosing(RheiaFrameEvent& event);

    /**********************************************************************************************************
    *	PRIVATE VARIABLES
    **********************************************************************************************************/
    wxMenuBar *MainMenuBar;										/*!< Pointer to the main frame's menu bar */
    RheiaManagedFrame* m_parent;
};

#ifndef SWIG
/**
*	@class RheiaMenuFunctorManager
*
*	@brief RheiaMenuFunctorManager is the class for providing plugins with the main menu bar information.
*
*	RheiaMenuManager is used for registering menu callbacks for creation and deletion in the ManagedFrame's menu...
*   This is tipically the kind of Manager which are global to the application... So you never have to associate
*   a RheiaManagedFrame to it... You can access the global instance of this manager by calling RheiaMenuFunctorManager::Get()
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	21-Nov-2008
*	@version 0.0.1
*/
class BASE_DLLEXPORT RheiaMenuFunctorManager : public wxEvtHandler, public Mgr<RheiaMenuFunctorManager>
{
    /** Give our private member access to Mgr */
    friend class Mgr<RheiaMenuFunctorManager>;
    /** Give our private member access to RheiaManager */
    friend class RheiaManager;
public :
    /**********************************************************************************************************
    *	METHODS
    **********************************************************************************************************/
    /** Register a menu function in the manager */
    void RegisterMenuFunction( RheiaMenuFunctorBase* func );

    /** Unregister menu function from the manager */
    void UnregisterMenufunction( RheiaMenuFunctorBase* func );

    /** Get the array of functors */
    const RheiaMenuFunctorArray& GetFunctors() const {return m_funcs;};

private :
    /**********************************************************************************************************
    *	CONSTRUCTORS
    **********************************************************************************************************/
    /*! Default constructor */
    RheiaMenuFunctorManager();

    /*! Default destructor */
    ~RheiaMenuFunctorManager();
    /**********************************************************************************************************
    *	METHODS
    **********************************************************************************************************/
    /** send an event to the events manager to notify that menu has changed */
    void SendEvent( const wxEventType& type );

    /**********************************************************************************************************
    *	PRIVATE VARIABLES
    **********************************************************************************************************/
    RheiaMenuFunctorArray m_funcs;
};
#endif

#endif
