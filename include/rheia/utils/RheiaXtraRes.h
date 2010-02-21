#ifndef RheiaXtraRes_h_
#define RheiaXtraRes_h_

#include <wx/wxprec.h>
#include <wx/xrc/xmlres.h>
#include <wx/toolbar.h>

#include <RheiaUtilsSettings.h>

class wxXmlResourceHandler;

/*********************************************************************************************************//**
*	@class wxToolBarAddOnXmlHandler
*
*	@brief The wxToolBarAddOnXmlHandler class is made for interpreting tool bar xrc nodes
*
*	This class has been taken from as well as the original wxWidgets one
*************************************************************************************************************/
class UTILS_DLLEXPORT wxToolBarAddOnXmlHandler : public wxXmlResourceHandler
{
    public:
        wxToolBarAddOnXmlHandler();
        virtual wxObject *DoCreateResource();
        virtual bool CanHandle(wxXmlNode *node);

    protected:
        bool m_isInside;
        bool m_isAddon;
        wxToolBar *m_toolbar;

        wxBitmap GetCenteredBitmap(const wxString& param = wxT("bitmap"),
            const wxArtClient& defaultArtClient = wxART_OTHER,
            wxSize size = wxDefaultSize);
};

#endif
