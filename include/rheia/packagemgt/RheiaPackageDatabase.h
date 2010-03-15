/**
*   @file RheiaPackageDatabase.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 23-November-2009
*/
#ifndef _RheiaPackageDatabase_h_
#define _RheiaPackageDatabase_h_

#include <rheia/sdk/RheiaPMgtSettings.h>
#include <rheia/sdk/RheiaGlobals.h>
#include <rheia/sdk/RheiaManager.h>

#include <map>

/**
*   @class RheiaPackageDatabase
*
*   @brief Main manager class for managing installed RheiaPackages.
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 23-November-2009
*/
class PMGT_DLLEXPORT RheiaPackageDatabase : public Singleton<RheiaPackageDatabase>
{
    /** give RheiaManager our private members access */
    friend class RheiaManager;

    /** give Singleton our private members access */
    friend class Singleton<RheiaPackageDatabase>;

public :

private :
    /**************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    **************************************************************************************/
    /**
    *   Default constructor.
    *   As many other Manager in Rheia, you cannot build directly this class,
    *   use RheiaPackageDatabase::Get() to get the global instance of this class.
    *   Unless if you are a Rheia Developer you shall never have to deal with this
    *   class as it is a core function of Rheia. However if you manage to develop
    *   a plugin in order to accurate package management in Rheia this class shall
    *   provide you with all the methods you need.
    */
    RheiaPackageDatabase();

    /**
    *   Default destrcutor.
    *   You cannot call this destrcutor directly in your code, more over this may
    *   result in unexpected behaviour while the application is running. RheiaManager
    *   Is responsible for destroying this class via RheiaPackageDatabase::Free();
    */
    ~RheiaPackageDatabase();
};

#endif

