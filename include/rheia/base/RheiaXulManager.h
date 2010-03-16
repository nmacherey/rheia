/**
* @file RheiaXulManager.h
* @author Nicolas Macherey (nm@graymat.fr)
* @version 1.0.1
* @date 2-March-2010
*/
#ifndef RheiaXulManager_h_
#define RheiaXulManager_h_

#include "RheiaBaseSettings.h"
#include "RheiaManager.h"
#include "RheiaGlobals.h"

/**
 * @class RheiaXulManager
 * @brief Main class for displaying a Start page in htlm format in your applications
 *
 * This class will create a wxWenConnect control based on xulrunner it's very usefull if
 * you need to display a web page content when starting the application.
 * 
 * @author Nicolas Macherey (nm@graymat.fr)
 * @version 1.0.1
 * @date 2-March-2010
 */
class BASE_DLLEXPORT RheiaXulManager : public Singleton<RheiaXulManager> 
{
	friend class RheiaManager;
	friend class Singleton<RheiaXulManager>;

public :

	/** Initialize xulrunner 
	 * @note that this must be called after adding plugin paths to xulrunner
	 */
	void Init(const wxString& path);
	
	/** Specify xulrunner for specific plugins it shall load 
	 * when starting
	 */
	void AddPluginPath( const wxString& path );
	
	/** Find the XulRunner dir located on your system */
	wxString FindXulRunner(const wxString& xulrunner_dirname);
	
	/** hcek if xulrunner is running or not */
	bool IsRunning() {return m_initialized;};
	
private :
	
	/** ctor */
	RheiaXulManager():m_initialized(false)
		{};
		
	/** dtor */
	~RheiaXulManager(){};
	
	/***************************************************************************
	 * PRIVATE MEMBERS
	 **************************************************************************/
	
	bool m_initialized;
};

#endif
