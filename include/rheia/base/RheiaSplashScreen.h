#ifndef RheiaSplashScreen_h_
#define RheiaSplashScreen_h_

#include <wx/bitmap.h>
#include <wx/dc.h>
#include <wx/timer.h>
#include <wx/frame.h>
#include <wx/splash.h>

/**
*   @class RheiaSplashScreen
*   @brief This is the main class for displaying a splash screen in the application
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 21-Nov-2008
*	@version 0.0.1
*/
class RheiaSplashScreen : public wxSplashScreen
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

