/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
#ifndef RheiaSplashScreen_h_
#define RheiaSplashScreen_h_

#include <wx/bitmap.h>
#include <wx/dc.h>
#include <wx/timer.h>
#include <wx/frame.h>
#include <wx/splash.h>

#include "RheiaGlobals.h"
#include "RheiaBaseSettings.h"

/**
*   @class RheiaSplashScreen
*   @brief This is the main class for displaying a splash screen in the application
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 21-Nov-2008
*	@version 0.0.1
*/
class BASE_DLLEXPORT RheiaSplashScreen : public wxSplashScreen
{
  public:
    // A value of -1 for timeout makes it stay forever (you need to close it manually)
    RheiaSplashScreen(wxBitmap &label ,
                long flags = wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT,
                long time_out = 6000,
                wxWindow *parent = NULL,
                wxWindowID id = wxID_ANY,
                wxPoint pos = wxDefaultPosition,
                wxSize size = wxDefaultSize,
                long style = wxSIMPLE_BORDER|wxSTAY_ON_TOP );

    virtual ~RheiaSplashScreen() {};
};

#endif

