/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 * It has just been renamed accordingly to the application's name
 */
#ifndef RheiaInfoWindow_h_
#define RheiaInfoWindow_h_

#include <wx/event.h>
#include <wx/timer.h>
#include <wx/string.h>
#include <wx/dialog.h>

#include <RheiaUtilsSettings.h>

//#if wxUSE_POPUPWIN
//    #include <wx/popupwin.h>
//    typedef wxPopupWindow wxInfoWindowBase;
//#else
    typedef wxDialog wxInfoWindowBase;
//#endif

#undef new
#include <list>
#include <algorithm>

class Stacker
{
    std::list<int> widths;

    public:

    int StackMe(int mySize)
    {
        mySize += 3;
        int pos = 0;

        if(!widths.empty())
            pos = *(std::max_element(widths.begin(), widths.end()));

        widths.push_back(pos + mySize);
        return pos + mySize;
    };

    void ReleaseMe(int myPos)
    {
        std::list<int>::iterator it = std::find(widths.begin(), widths.end(), myPos);
        if(it != widths.end())
            widths.erase(it);
    };
};


class UTILS_DLLEXPORT InfoWindow : public wxInfoWindowBase
{
    wxTimer *m_timer;
    int left;
    int top;
    int hMin;
    int pos;
    unsigned int status;
    unsigned int m_delay;
    unsigned int ks;
    std::list<wxString>::iterator my_message_iterator;
    static Stacker stacker;
    static int screenWidth;
    static int screenHeight;
    static std::list<wxString> active_messages; // if a new message is in this, don't display it (already is displayed). Check Display()

    InfoWindow(const wxString& title, const wxString& message, unsigned int delay, unsigned int hysteresis);
    virtual ~InfoWindow();
    void OnTimer(wxTimerEvent& e);
    void OnMove(wxMouseEvent& e);
    void OnClick(wxMouseEvent& e);
    DECLARE_EVENT_TABLE()

    public:

    static void Display(const wxString& title, const wxString& message, unsigned int delay = 5000, unsigned int hysteresis = 1);
};






#endif
