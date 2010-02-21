#ifndef wxStreamedTextCtrl_h_
#define wxStreamedTextCtrl_h_

#include <wx/textctrl.h>
#include <wx/frame.h>

#include <RheiaUtilsSettings.h>
#include <iostream>

class wxWindow;
class wxString;
class wxPoint;
class wxSize;

#if !wxHAS_TEXT_WINDOW_STREAM

/*********************************************************************************************************//**
*	@class wxStreamedTextCtrl
*
*	@brief The wxStreamedTextCtrl class is made for enbling a text control to redirect a stream
*
*	This class has been taken from as well as the original wxWidgets one
*************************************************************************************************************/
class wxStreamedTextCtrl : public wxTextCtrl, public std::streambuf
{
public :
	wxStreamedTextCtrl( wxWindow *parent,
		wxWindowID id,
		const wxString& value = wxEmptyString,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0 ) : wxTextCtrl( parent , id , value , pos, size, style ){};

protected :
	int overflow(int i){
		AppendText((wxChar)i);
		// return something different from EOF
		return 0;
	};
};

/*********************************************************************************************************//**
*	@class wxStreamToTextRedirector
*
*	@brief The wxStreamToTextRedirector class is made for enabling the redirection of a stream to a textctrl
*
*	This class has been taken from as well as the original wxWidgets one
*************************************************************************************************************/
class wxStreamToTextRedirector
{
private:
    void Init(wxStreamedTextCtrl *text)
    {
        m_sbufOld = m_ostr.rdbuf();
        m_ostr.rdbuf(text);
    }

public:
    wxStreamToTextRedirector(wxStreamedTextCtrl *text , wxSTD ostream& _m_ostr )
        : m_ostr(_m_ostr)
    {
        Init(text);
    }

    wxStreamToTextRedirector(wxStreamedTextCtrl *text, wxSTD ostream *ostr)
        : m_ostr(*ostr)
    {
        Init(text);
    }

    ~wxStreamToTextRedirector()
    {
        m_ostr.rdbuf(m_sbufOld);
    }

private:
    // the stream we're redirecting
    wxSTD ostream&   m_ostr;

    // the old streambuf (before we changed it)
    wxSTD streambuf *m_sbufOld;
};
#endif

#endif
