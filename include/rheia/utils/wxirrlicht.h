/* wxirrlicht.h -- A wxWidgets control that embeds the 'Irrlicht Engine'.

  Copyright (C) 2006 Yiannis Mandravellos <mandrav@codeblocks.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  ChangeLog
  ---------
    2 Sep 2006:
      * Original version released.
*/

/*
  2007/12/12
  	* changed version by loptr (devy@sourceforge.net)
*/

/*
  2009/29/10
  	* changed version by nicolas macherey (nm@graymat.fr)
  	* the original version for windows did not changed but for
  	* making it working in wxGTK it was a hudge problem
  	* The first thing to do is to modify the CIrrLinuxDevice in order to add the following method :
  	* Window GetWindow() {return window;};
  	* It will not work if you dont do this
  	* Then I've changed the OnSize event callback in order to properly resize the CIrrLinuxDevice::window
  	* using XResizeWindow method.
*/

#ifndef __WXIRRLICHT_H__
#define __WXIRRLICHT_H__

#ifdef RHEIA_USE_IRRLICHT

#ifdef WIN32
#include <windows.h>
#endif

#include <irrlicht.h>
#include <wx/wx.h>
#include <wx/panel.h>
#include <RheiaUtilsSettings.h>

#include <map>
#include <vector>

typedef std::map< wxKeyCode , irr::EKEY_CODE > irrKeyMap;

/**
*   @class wxIrrlicht
*   @brief wxWidget Control for integrating an irrlicht window in a wxPanel
*
*   @author Yiannis Mandravellos <mandrav@codeblocks.org>, loptr (devy@sourceforge.net), Nicolas Macherey (nm@graymat.fr)
*   @version 1.1.2
*   @date 29-October-2009
*/
class UTILS_DLLEXPORT wxIrrlicht : public wxPanel
{
public:
    /******************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    ******************************************************************************/
    /**
    *   Basic constructor
    *   @param parent The wxWindow parent for this control (@see wxWindow)
    *   @param id the window id for events callbacks (@see wxWindow)
    *   @param bs specify if the number of Frame Per Second hall be displayed on window top left
    *   @param pos window position (@see wxWindow)
    *   @param size window size (@see wxWindow)
    *   @param style window style (@see wxWindow)
    *   @param name window name (@see wxWindow)
    *
    *   @note That durin initialization the most important parameter to set is the WindowId in irrlicht, otherwise it will
    *   be loaded in an independent frame.
    */
    wxIrrlicht(wxWindow* parent, wxWindowID id, bool bs=true, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxPanelNameStr);

    /** default destructor */
    virtual ~wxIrrlicht();

    /******************************************************************************
    *   METHODS
    ******************************************************************************/
    /**
    *   Initialize the irrlicht environement with the given irrlicht parameters
    *   @param init_params the irrlicht initialization parameters (see irrlicht doc for more info)
    */
    void InitIrr( irr::SIrrlichtCreationParameters* init_params = 0 );

    /**
    *   Method used for starting the rendering task (main irrlicht loop)
    *   Call this method after wxIrrlicht::InitIrr()
    *   This starts the rendering time with a refresh for the given input milliseconds
    */
    void StartRendering(int milliseconds = 10);

    /**
    *   Stop the rendering task
    */
    void StopRendering();

    /**
    *   Render method used for irrlicht interactions
    *   This mainly call to m_pDevice->run() (see irrlicht documentation)
    */
    void Render();

    /**
    *   Overload this if you want to execute some specific actions
    *   when an irrlicht scene is created.
    */
    virtual void OnCreateScene();

    /**
    *   Overload this if you want to execute some specific actions
    *   before the rendring task
    */
    virtual void OnPreRender() {}

    /**
    *   Overload this if you want to change some specific actions
    *   when the rendring task is executed please remember to have
    *   a call to wxIrrlicht::OnRender()
    */
    virtual void OnRender();

    /**
    *   Overload this if you want to execute some specific actions
    *   after the rendering task
    */
    virtual void OnPostRender();

    /******************************************************************************
    *   ACCESSORS
    ******************************************************************************/
    /** get the device */
    irr::IrrlichtDevice* GetDevice() const
    {
        return m_pDevice;
    }

    /** get the video driver */
    irr::video::IVideoDriver* GetVideoDriver() const
    {
        return m_pDriver;
    }

    /** get the scene manager */
    irr::scene::ISceneManager* GetSceneManager() const
    {
        return m_pSceneManager;
    }

    /** get the camera */
    irr::scene::ICameraSceneNode* GetCameraNode() const
    {
        return m_pCameraNode;
    }

    /** get the gui environment in irrlicht */
    irr::gui::IGUIEnvironment* GetGuiEnvironment() const
    {
        return m_pGuiEnvironment;
    }

    static void wxToIrrlichtKeyRegistrant( wxKeyCode wxKey , irr::EKEY_CODE irrKey )
    {
        m_keys[wxKey] = irrKey;
    }

    static irrKeyMap m_keys;

protected:

    /******************************************************************************
    *   EVENT CALLBACKS
    ******************************************************************************/
    /** wxWindow OnPaint method */
    void OnPaint(wxPaintEvent& event);

    /**
    *   wxWindow OnSize method
    *   Here is the very important task in wxIrrlicht.
    *   Under wxGtk this method will have a call to XLib XResizeWindow(), in order
    *   to proper resize the window when the parent panel is resized.
    */
    void OnSize(wxSizeEvent& event);

    /** wxWindow OnEraseBackground method */
    void OnEraseBackground(wxEraseEvent& event) {}

    /** Callback used when the timer used for rendering is matching its update value */
    void OnTimer(wxTimerEvent& event);

    /** Callback used when the timer used for key ùmanagement is matching its update value */
    void OnTimerKey(wxTimerEvent& event);

    /** Mouse action event used for event management with irrlicht */
    void OnMouse(wxMouseEvent& event);

    /** Key action event used for event management with irrlicht */
    void OnKey(wxKeyEvent& event);

    /******************************************************************************
    *   PRIVATE VARIABLES
    ******************************************************************************/
    irr::IrrlichtDevice* m_pDevice;
    irr::video::IVideoDriver* m_pDriver;
    irr::scene::ISceneManager* m_pSceneManager;
    irr::gui::IGUIEnvironment* m_pGuiEnvironment;
    irr::scene::ICameraSceneNode* m_pCameraNode;
    wxTimer m_Timer;
    wxTimer m_TimerKey;
    irr::gui::IGUIStaticText* m_pFPSText;
    bool m_showFPS;

    void OnMouseEnter(wxMouseEvent& event);
    void OnMouseLeave(wxMouseEvent& event);

private:
#ifndef SWIG
    DECLARE_EVENT_TABLE();
#endif
};//wxIrrlicht

class irrKeyRegistrant
{
public :
    irrKeyRegistrant( wxKeyCode wxKey , irr::EKEY_CODE irrKey )
    {
        wxIrrlicht::wxToIrrlichtKeyRegistrant(wxKey,irrKey);
    }
};

#define REGISTER_KEY( wxKey , irrKey ) irrKeyRegistrant key##wxKey(wxKey,irrKey);

#endif

#endif

