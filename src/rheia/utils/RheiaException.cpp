#include <RheiaException.h>
#include <RheiaGlobals.h>

#include <wx/log.h> // for wxSafeShowMessage()
#include <wx/intl.h>
#include <iostream>


RheiaException::RheiaException(const wxString& msg, const wxString& file, int line)
  : Message(msg),
    File(file),
    Line(line)
{}

RheiaException::~RheiaException()
{}


void RheiaException::ShowErrorMessage(bool safe)
{
    wxString gccvers;
#ifdef __GNUC__
    gccvers.Printf(_T("gcc %d.%d.%d"), __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#endif

    wxString title = _("Exception");
    wxString err;
    err.Printf(_("An exception has been raised!\n\n"
                 "The application encountered an error at %s, on line %d.\n"
                 "The error message is:\n\n%s\n\n"
                 "Rheia Version revision %d (%s, "
                 "build: %s %s)"),
               File.c_str(), Line, Message.c_str(),
               1123, gccvers.c_str(),
               wxT(__DATE__), wxT(__TIME__));

	if( safe )
		std::cerr <<  rcU2C( title )  << " : " << rcU2C( err ) << std::endl;
	else
		wxMessageBox( err , wxT("Rheia exception catched !") , wxICON_ERROR );
}
