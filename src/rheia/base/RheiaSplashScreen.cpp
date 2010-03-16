/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/

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

