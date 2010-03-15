/**
*   @file RheiaPersonalityManager.h
*
*   Revision : 15-January-2010
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.2
*/
#ifndef RheiaPersonalityManager_h_
#define RheiaPersonalityManager_h_

#include <RheiaBaseSettings.h>
#include <RheiaManager.h>

/**
*   @class RheiaPersonalityManager
*
*   @brief Manager class for getting the personality (i.e : different configuration files that might have been registred by the user)
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.2
*/
class BASE_DLLEXPORT RheiaPersonalityManager : public Singleton<RheiaPersonalityManager>
{
    /** give Singleton access to our private members */
    friend class Singleton<RheiaPersonalityManager>;
    /** give Manager access to our private members */
    friend class RheiaManager;

public:
    /************************************************************************************
    *   METHODS
    ************************************************************************************/
    /** Use this once, on program startup to set the working personality */
    void SetPersonality(const wxString& personality, bool createIfNotExist = false);

    /** Get the working personality string */
    const wxString GetPersonality();

    /** Get a list of all the known personalities */
    const wxArrayString GetPersonalitiesList();

private :
    /************************************************************************************
    *   PRIVATE MEMEBERS
    ************************************************************************************/
    static wxString pers;

    /************************************************************************************
    *   CONSTRUCTOR
    ************************************************************************************/
    RheiaPersonalityManager();
};

#endif
