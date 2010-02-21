
#include <RheiaSplashScreen.h>

RheiaSplashScreen::RheiaSplashScreen(wxBitmap &label ,
                long flags,
                long time_out,
                wxWindow *parent,
                wxWindowID id,
                wxPoint pos,
                wxSize size,
                long style ) :
                wxSplashScreen( label , flags , time_out , parent , id , pos , size , style )
{

}

