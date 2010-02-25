#ifdef RHEIA_USE_IRRLICHT

#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/progdlg.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <irrlicht.h>
#include "wxirrlicht.h"
#include "RheiaGlobals.h"

#ifdef LINUX
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <sstream>
//#include "wx/gtk/private.h"
#if wxCHECK_VERSION(2,9,0)
#include "wx/gtk/private/win_gtk.h"
#define GTK_PIZZA WX_PIZZA
#else
#include "wx/gtk/win_gtk.h"
#endif
#include <CIrrDeviceLinux.h>
#include <GL/gl.h>
#define GLX_GLXEXT_LEGACY 1
#include <GL/glx.h>
#endif

#include <wx/defs.h>

irrKeyMap wxIrrlicht::m_keys;

namespace{
REGISTER_KEY(WXK_BACK,irr::KEY_BACK);
REGISTER_KEY(WXK_TAB,irr::KEY_TAB);
REGISTER_KEY(WXK_RETURN,irr::KEY_RETURN);
REGISTER_KEY(WXK_ESCAPE,irr::KEY_ESCAPE);
REGISTER_KEY(WXK_SPACE,irr::KEY_SPACE);
REGISTER_KEY(WXK_DELETE,irr::KEY_DELETE);
REGISTER_KEY(WXK_LBUTTON,irr::KEY_LBUTTON);
REGISTER_KEY(WXK_RBUTTON,irr::KEY_RBUTTON);
REGISTER_KEY(WXK_CANCEL,irr::KEY_CANCEL);
REGISTER_KEY(WXK_MBUTTON,irr::KEY_MBUTTON);
REGISTER_KEY(WXK_CLEAR,irr::KEY_CLEAR);
REGISTER_KEY(WXK_SHIFT,irr::KEY_SHIFT);
REGISTER_KEY(WXK_CONTROL,irr::KEY_CONTROL);
REGISTER_KEY(WXK_MENU,irr::KEY_MENU);
REGISTER_KEY(WXK_PAUSE,irr::KEY_PAUSE);
REGISTER_KEY(WXK_CAPITAL,irr::KEY_CAPITAL);
REGISTER_KEY(WXK_END,irr::KEY_END);
REGISTER_KEY(WXK_HOME,irr::KEY_HOME);
REGISTER_KEY(WXK_LEFT,irr::KEY_LEFT);
REGISTER_KEY(WXK_UP,irr::KEY_UP);
REGISTER_KEY(WXK_RIGHT,irr::KEY_RIGHT);
REGISTER_KEY(WXK_DOWN,irr::KEY_DOWN);
REGISTER_KEY(WXK_SELECT,irr::KEY_SELECT);
REGISTER_KEY(WXK_PRINT,irr::KEY_PRINT);
REGISTER_KEY(WXK_EXECUTE,irr::KEY_EXECUT);
REGISTER_KEY(WXK_SNAPSHOT,irr::KEY_SNAPSHOT);
REGISTER_KEY(WXK_INSERT,irr::KEY_INSERT);
REGISTER_KEY(WXK_HELP,irr::KEY_HELP);
REGISTER_KEY(WXK_NUMPAD0,irr::KEY_NUMPAD0);
REGISTER_KEY(WXK_NUMPAD1,irr::KEY_NUMPAD1);
REGISTER_KEY(WXK_NUMPAD2,irr::KEY_NUMPAD2);
REGISTER_KEY(WXK_NUMPAD3,irr::KEY_NUMPAD3);
REGISTER_KEY(WXK_NUMPAD4,irr::KEY_NUMPAD4);
REGISTER_KEY(WXK_NUMPAD5,irr::KEY_NUMPAD5);
REGISTER_KEY(WXK_NUMPAD6,irr::KEY_NUMPAD6);
REGISTER_KEY(WXK_NUMPAD7,irr::KEY_NUMPAD7);
REGISTER_KEY(WXK_NUMPAD8,irr::KEY_NUMPAD8);
REGISTER_KEY(WXK_NUMPAD9,irr::KEY_NUMPAD9);
REGISTER_KEY(WXK_MULTIPLY,irr::KEY_MULTIPLY);
REGISTER_KEY(WXK_ADD,irr::KEY_ADD);
REGISTER_KEY(WXK_SEPARATOR,irr::KEY_SEPARATOR);
REGISTER_KEY(WXK_SUBTRACT,irr::KEY_SUBTRACT);
REGISTER_KEY(WXK_DECIMAL,irr::KEY_DECIMAL);
REGISTER_KEY(WXK_DIVIDE,irr::KEY_DIVIDE);
REGISTER_KEY(WXK_F1,irr::KEY_F1);
REGISTER_KEY(WXK_F2,irr::KEY_F2);
REGISTER_KEY(WXK_F3,irr::KEY_F3);
REGISTER_KEY(WXK_F4,irr::KEY_F4);
REGISTER_KEY(WXK_F5,irr::KEY_F5);
REGISTER_KEY(WXK_F6,irr::KEY_F6);
REGISTER_KEY(WXK_F7,irr::KEY_F7);
REGISTER_KEY(WXK_F8,irr::KEY_F8);
REGISTER_KEY(WXK_F9,irr::KEY_F9);
REGISTER_KEY(WXK_F10,irr::KEY_F10);
REGISTER_KEY(WXK_F11,irr::KEY_F11);
REGISTER_KEY(WXK_F12,irr::KEY_F12);
REGISTER_KEY(WXK_F13,irr::KEY_F13);
REGISTER_KEY(WXK_F14,irr::KEY_F14);
REGISTER_KEY(WXK_F15,irr::KEY_F15);
REGISTER_KEY(WXK_F16,irr::KEY_F16);
REGISTER_KEY(WXK_F17,irr::KEY_F17);
REGISTER_KEY(WXK_F18,irr::KEY_F18);
REGISTER_KEY(WXK_F19,irr::KEY_F19);
REGISTER_KEY(WXK_F20,irr::KEY_F20);
REGISTER_KEY(WXK_F21,irr::KEY_F21);
REGISTER_KEY(WXK_F22,irr::KEY_F22);
REGISTER_KEY(WXK_F23,irr::KEY_F23);
REGISTER_KEY(WXK_F24,irr::KEY_F24);
REGISTER_KEY(WXK_NUMLOCK,irr::KEY_NUMLOCK);
REGISTER_KEY(WXK_SCROLL,irr::KEY_SCROLL);
};

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace
{
    int ID_IRR_TIMER = wxNewId();
    int ID_TIMER_KEY = wxNewId();
    static bool rendering = false;
}

BEGIN_EVENT_TABLE(wxIrrlicht, wxPanel)
    EVT_TIMER(ID_IRR_TIMER, wxIrrlicht::OnTimer)
    EVT_SIZE(wxIrrlicht::OnSize)
    EVT_PAINT(wxIrrlicht::OnPaint)
    EVT_ERASE_BACKGROUND(wxIrrlicht::OnEraseBackground)
    EVT_LEFT_DOWN(wxIrrlicht::OnMouse)
    EVT_LEFT_UP(wxIrrlicht::OnMouse)
    EVT_LEFT_DCLICK(wxIrrlicht::OnMouse)
    EVT_MIDDLE_DOWN(wxIrrlicht::OnMouse)
    EVT_MIDDLE_UP(wxIrrlicht::OnMouse)
    EVT_MIDDLE_DCLICK(wxIrrlicht::OnMouse)
    EVT_RIGHT_DOWN(wxIrrlicht::OnMouse)
    EVT_RIGHT_UP(wxIrrlicht::OnMouse)
    EVT_RIGHT_DCLICK(wxIrrlicht::OnMouse)
    EVT_MOUSEWHEEL(wxIrrlicht::OnMouse)
    EVT_KEY_DOWN(wxIrrlicht::OnKey)
    EVT_KEY_UP(wxIrrlicht::OnKey)
END_EVENT_TABLE()

wxIrrlicht::wxIrrlicht(wxWindow* parent, wxWindowID id, bool bs, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: wxPanel(parent, id, pos, size, style, name),
	m_pDevice(0),
    m_pDriver(0),
    m_pSceneManager(0),
    m_pGuiEnvironment(0),
    m_pCameraNode(0),
    m_Timer(this, ID_IRR_TIMER),
    m_pFPSText(0),
	m_showFPS(bs) {
	    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}//ctor

wxIrrlicht::~wxIrrlicht() {
    if( m_pDevice )
        m_pDevice->drop();
}//dtor

void wxIrrlicht::InitIrr(irr::SIrrlichtCreationParameters* init_params) {
    SIrrlichtCreationParameters params;
    params.DriverType = EDT_OPENGL;

    SIrrlichtCreationParameters* actual_params = init_params ? init_params : &params;
    dimension2d<unsigned int> irrSize(GetClientSize().GetX(), GetClientSize().GetY());
    actual_params->WindowSize = irrSize;

#ifdef LINUX
    params.DeviceType = EIDT_X11;
    params.Doublebuffer = 1;
    params.Stencilbuffer = 1;
    params.AntiAlias = 1;
    params.Stereobuffer = 0;
    /**
    *   Here is what I've changed from the previous versions....
    *   Unfortunately, under wxGTK a wxWindow have two GtkWidget's :
    *   - the first one is called m_widget and is a container basically a GtkScrolledWindow
    *   - the behaviour for the second one (m_wxwindow) is different accordingly to the wxControl used ,
    *       basically it's different fro a control which is able to contain other controls or not.
    *   Then the WindowId given to irrlicht createDeviceEx shall be the window id for this parameter
    *   This simple two lines have been very hard to find :-)
    */
//    Window win = GDK_WINDOW_XWINDOW(this->m_wxwindow->window);
#if wxCHECK_VERSION(2,9,0)
    wxPizza * pizza = WX_PIZZA(this->m_wxwindow);
    GtkWidget * widget = GTK_WIDGET(pizza);
    GdkWindow * window = widget->window;
#else
    GdkWindow *window = GTK_PIZZA(this->m_wxwindow)->bin_window;
#endif
    Window win = GDK_WINDOW_XWINDOW( window );
    actual_params->WindowId = (void*) win;
#else
    actual_params->WindowId = this->GetHandle();
#endif

    m_pDevice = createDeviceEx(*actual_params);

    if (!m_pDevice) {
        throw "Can't create Irrlicht device!";
	}//if

	m_pDriver = m_pDevice->getVideoDriver();
	m_pSceneManager = m_pDevice->getSceneManager();
	m_pGuiEnvironment = m_pDevice->getGUIEnvironment();

    OnCreateScene();

    m_pDriver->OnResize(irrSize);
}//InitIrr()

void wxIrrlicht::StartRendering(int milliseconds) {
    m_Timer.Start(milliseconds);
    //StartRenderingWindow(this);
    #ifdef LINUX
        if (!m_pDevice)
            return;
        Window win = ((CIrrDeviceLinux*) m_pDevice)->GetWindow();
        Display* display = GDK_DISPLAY();
        GLXContext Context = ((CIrrDeviceLinux*) m_pDevice)->GetContext();
        glXMakeContextCurrent(display, win, win, Context);
    #endif
}//StartRendering()

void wxIrrlicht::StopRendering(){
    m_Timer.Stop();
}//StopRendering()

void wxIrrlicht::OnMouseEnter(wxMouseEvent& event)
{
    StartRendering(20);
}

void wxIrrlicht::OnMouseLeave(wxMouseEvent& event)
{
    StopRendering();
}

void wxIrrlicht::Render() {
    if( !m_pDevice )
        return;

    if (rendering || !m_pDevice->run()) {
        return;
	}//if

    rendering = true;
    OnPreRender();
    OnRender();
    OnPostRender();
    rendering = false;
}//Render()

void wxIrrlicht::OnCreateScene() {
	if (m_showFPS) {
		m_pFPSText = m_pGuiEnvironment->addStaticText(L"FPS: 0", rect<s32>(1, 1, 50, 10), false);
		m_pFPSText->setOverrideColor(SColor(255,255,255,255));
	}//if
}//OnCreateScene()

void wxIrrlicht::OnRender() {
    m_pDriver->beginScene(true, true, SColor(0,0,0,0));
    m_pSceneManager->drawAll();
    m_pGuiEnvironment->drawAll();
    m_pDriver->endScene();
}//OnRender()

void wxIrrlicht::OnPostRender() {
    if (m_pFPSText && m_showFPS) {
        int fps = m_pDriver->getFPS();

        static int lastFPS = 0;
        if (lastFPS != fps) {
            core::stringw str = L"FPS: ";
            str += fps;

            m_pFPSText->setText(str.c_str());
            lastFPS = fps;
        }//if
    }//if
}//OnPostRender()

void wxIrrlicht::OnPaint(wxPaintEvent& event){
    wxPaintDC paint_dc(this);

    Render();
}//OnPaint()

void wxIrrlicht::OnSize(wxSizeEvent& event) {
    if (!m_pDriver) {
        return;
	}//if

    s32 w;
    s32 h;

    GetClientSize(&w, &h);
    dimension2d<unsigned int> siz(w, h);

    /**
    *   Here is the big stuff
    *   In order to make this working, I had to modify the CIrrLinuxDriver
    *   for getting the proper Window identifier which is different from
    *   the one givent in the InitIrr method
    *   Thanks to Davig Odin (DINDINX) for helping me in finding the right way for getting thi to work
    */
#ifdef LINUX
    Window win = ((CIrrDeviceLinux*) m_pDevice)->GetWindow();
    Display* display = GDK_DISPLAY();
    XMoveResizeWindow( display , win , 0, 0 , GetClientSize().GetWidth() , GetClientSize().GetHeight()  );
#endif

	m_pDriver->OnResize(siz);
	
#ifdef MACOSX
	m_pDriver->setViewPort( rect<s32>(0,0,GetClientSize().GetWidth(), GetClientSize().GetHeight()) );
    m_pDevice->setResizeAble(true);  //HACK..have to call to resize opengl context 
#endif

    if (m_pCameraNode) {
        m_pCameraNode->setAspectRatio((float)w / (float)h);
	}//if
}//OnSize

void wxIrrlicht::OnTimer(wxTimerEvent& event) {
    Render();
}

void wxIrrlicht::OnMouse(wxMouseEvent& event) {
    irr::SEvent sevt;

    sevt.EventType = irr::EET_MOUSE_INPUT_EVENT;

    if (event.IsButton()) {
        if (event.LeftDown())
            sevt.MouseInput.Event = irr::EMIE_LMOUSE_PRESSED_DOWN;
        else if (event.LeftUp())
            sevt.MouseInput.Event = irr::EMIE_LMOUSE_LEFT_UP;
        else if (event.MiddleDown())
            sevt.MouseInput.Event = irr::EMIE_MMOUSE_PRESSED_DOWN;
        else if (event.MiddleUp())
            sevt.MouseInput.Event = irr::EMIE_MMOUSE_LEFT_UP;
        else if (event.RightDown())
            sevt.MouseInput.Event = irr::EMIE_RMOUSE_PRESSED_DOWN;
        else if (event.RightUp())
            sevt.MouseInput.Event = irr::EMIE_RMOUSE_LEFT_UP;
    }//if

    else if (event.GetWheelRotation() != 0) {
        sevt.MouseInput.Wheel = (float)event.GetWheelRotation();
        sevt.MouseInput.Event = irr::EMIE_MOUSE_WHEEL;
    }//else if

    else if (event.Moving() || event.Dragging()) {
		sevt.MouseInput.Event = irr::EMIE_MOUSE_MOVED;
	}//else if

    sevt.MouseInput.X = event.GetX();
    sevt.MouseInput.Y = event.GetY();

    m_pDevice->postEventFromUser(sevt);

    if (!m_Timer.IsRunning()) {
        Render();
	}//if

    event.Skip();
}//OnMouse()

void wxIrrlicht::OnKey(wxKeyEvent& event) {
    irr::SEvent sevt;

    sevt.EventType = irr::EET_KEY_INPUT_EVENT;

    wxKeyCode m_key = (wxKeyCode) event.GetKeyCode();
    irrKeyMap::iterator it = m_keys.find(m_key);

    sevt.KeyInput.Key = it->second;
    sevt.KeyInput.PressedDown = event.GetEventType() == wxEVT_KEY_DOWN;

    sevt.KeyInput.Shift = event.ShiftDown();
    sevt.KeyInput.Control = event.CmdDown();
#if wxUSE_UNICODE
    sevt.KeyInput.Char = event.GetUnicodeKey();
#else
    sevt.KeyInput.Char = event.GetKeyCode();
#endif

    m_pDevice->postEventFromUser(sevt);

    if (!m_Timer.IsRunning()) {
        Render();
	}//if

    event.Skip();
}//OnKey()





/* CODE DUMP
	: wxWindow(parent, id, pos, size, style, name)

*/

#endif
