/**
*	@file RheiaFunctor.h
*
*   Revision : 4-January-2010
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/
#ifndef RheiaFunctor_h_
#define RheiaFunctor_h_

/**
*   @class RheiaFunctorBase
*
*   @brief Base abstract functor class. All functors must extend this interface.
*
*   A function object, also called a functor, functional, or functionoid, is a computer programming
*   construct allowing an object to be invoked or called like it was an ordinary function, usually with
*   the same syntax.
*
*   A typical use of a function object is in writing callback functions. A callback in procedural languages,
*   such as C, may be accomplished by using function pointers. However it can be difficult or awkward to pass
*   a state into or out of the callback function. This restriction also inhibits more dynamic behavior of the function.
*   A function object solves those problems since the function is really a façade for a full object, thus it
*   carries its own state.
*
*   In Rheia functors are used in order to allow any instanciated object to communicate whith each others using events.
*   The basic functor class is used to register callback methods you wrote in order to register, specific events
*   functions, menu functions or toolbar functions that needs to be called at any time the application needs it.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/
class RheiaFunctorBase
{
public:
    /************************************************************************************
    *   CONSTRUCTOR
    ************************************************************************************/
    /** Constructor */
    virtual ~RheiaFunctorBase() {}

    /************************************************************************************
    *   METHODS TO OVERLOAD
    ************************************************************************************/
    /**
    *   Any functor object must return the pointer to the object which is called
    *   by the functor callback. You have to overload this method in order to return
    *   the parent object when using the functor.
    */
    virtual void* GetThis() = 0;
};

/**
*   @class RheiaEventFunctorBase
*
*   @brief This base class define the events functor in rheia used to register any events  callbacks
*   in the application.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/
class RheiaEventFunctorBase : public RheiaFunctorBase
{
public:
    /************************************************************************************
    *   METHODS TO OVERLOAD
    ************************************************************************************/
    /**
    *   You have to overload this method in order to call the proper event method from
    *   the parent object.
    */
    virtual void Call(wxEvent& event) = 0;
};

/**
*   @class RheiaEventFunctor
*
*   @brief Event functor class.
*
*   This template method is used to register any event callback on an instanciated object in Rheia. This is
*   the end template for generalizing functions pointers in non-static objects.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/
template<class ClassType> class RheiaEventFunctor : public RheiaEventFunctorBase
{
private:
    /************************************************************************************
    *   DEFINES
    ************************************************************************************/
    /** Define a pointer to the callback method */
    typedef void (ClassType::*Member)(wxEvent&);

    /************************************************************************************
    *   PRIVATE MEMBERS
    ************************************************************************************/
    ClassType* This;
    Member member;

public:
    /************************************************************************************
    *   CONSTRUCTOR
    ************************************************************************************/
    /** Basic constructor */
    RheiaEventFunctor(ClassType* this_, Member member_) : This(this_), member(member_) {}

    /** Copy constructor */
    RheiaEventFunctor(const RheiaEventFunctor<ClassType>& rhs) : This(rhs.This), member(rhs.member) {}

    /************************************************************************************
    *   METHODS
    ************************************************************************************/
    /** Get the parent object pointer */
    virtual void* GetThis(){ return This;}

    /** Call the callback method registered in this template */
    virtual void Call(wxEvent& event) { if (This) (This->*member)(event); }
};

#endif
