#include <RheiaXtraRes.h>
#include <wx/wx.h>

wxToolBarAddOnXmlHandler::wxToolBarAddOnXmlHandler()
: wxXmlResourceHandler(), m_isInside(FALSE), m_isAddon(false), m_toolbar(NULL)
{
    XRC_ADD_STYLE(wxTB_FLAT);
    XRC_ADD_STYLE(wxTB_DOCKABLE);
    XRC_ADD_STYLE(wxTB_VERTICAL);
    XRC_ADD_STYLE(wxTB_HORIZONTAL);
    XRC_ADD_STYLE(wxTB_3DBUTTONS);
    XRC_ADD_STYLE(wxTB_TEXT);
    XRC_ADD_STYLE(wxTB_NOICONS);
    XRC_ADD_STYLE(wxTB_NODIVIDER);
    XRC_ADD_STYLE(wxTB_NOALIGN);
}

wxBitmap wxToolBarAddOnXmlHandler::GetCenteredBitmap(const wxString& param,
    const wxArtClient& defaultArtClient, wxSize size)
{
    wxBitmap bitmap = GetBitmap(param, defaultArtClient, wxDefaultSize);
    if (!bitmap.Ok()) // == wxNullBitmap
        return bitmap;

    int bw = bitmap.GetWidth();
    int bh = bitmap.GetHeight();
    if (size == wxSize(bw, bh))
        return bitmap;

    wxImage image = bitmap.ConvertToImage();

    int w = size.GetWidth();
    int h = size.GetHeight();
    int x = (w - bw) / 2;
    int y = (h - bh) / 2;

    if (image.HasAlpha()) // Resize doesn't handle Alpha... :-(
    {
        const unsigned char *data = image.GetData();
        const unsigned char *alpha = image.GetAlpha();
        unsigned char *rgb = (unsigned char *) calloc(w * h, 3);
        unsigned char *a = (unsigned char *) calloc(w * h, 1);

        // copy Data/Alpha from smaller bitmap to larger bitmap
        for (int row = 0; row < bh; row++)
        {
            memcpy(rgb + ((row + y) * w + x) * 3, data + (row * bw) * 3, bw * 3);
            memcpy(a + ((row + y) * w + x), alpha + (row * bw), bw);
        }

        image = wxImage(w, h, rgb, a);
    }
    else
        image.Resize(size, wxPoint(x,y));

    return wxBitmap(image);
}

wxObject *wxToolBarAddOnXmlHandler::DoCreateResource()
{
    wxToolBar* toolbar=NULL;
    if (m_class == _T("tool"))
    {
        wxCHECK_MSG(m_toolbar, NULL, _("Incorrect syntax of XRC resource: tool not within a toolbar!"));

        wxSize bitmapSize = m_toolbar->GetToolBitmapSize();

        if (GetPosition() != wxDefaultPosition)
        {
            m_toolbar->AddTool(GetID(),
                               GetCenteredBitmap(_T("bitmap"), wxART_TOOLBAR, bitmapSize),
                               GetCenteredBitmap(_T("bitmap2"), wxART_TOOLBAR, bitmapSize),
                               GetBool(_T("toggle")),
                               GetPosition().x,
                               GetPosition().y,
                               NULL,
                               GetText(_T("tooltip")),
                               GetText(_T("longhelp")));
           if (GetBool(_T("disabled")))
           {
               m_toolbar->Realize();
               m_toolbar->EnableTool(GetID(),false);
           }
        }
        else
        {
            wxItemKind kind = wxITEM_NORMAL;
            if (GetBool(_T("radio")))
                kind = wxITEM_RADIO;
            if (GetBool(_T("toggle")))
            {
                wxASSERT_MSG( kind == wxITEM_NORMAL,
                              _("can't have both toggleable and radion button at once") );
                kind = wxITEM_CHECK;
            }
            m_toolbar->AddTool(GetID(),
                               GetText(_T("label")),
                               GetCenteredBitmap(_T("bitmap"), wxART_TOOLBAR, bitmapSize),
                               GetCenteredBitmap(_T("bitmap2"), wxART_TOOLBAR, bitmapSize),
                               kind,
                               GetText(_T("tooltip")),
                               GetText(_T("longhelp")));
           if (GetBool(_T("disabled")))
           {
               m_toolbar->Realize();
               m_toolbar->EnableTool(GetID(),false);
           }
        }
        return m_toolbar; // must return non-NULL
    }

    else if (m_class == _T("separator"))
    {
        wxCHECK_MSG(m_toolbar, NULL, _("Incorrect syntax of XRC resource: separator not within a toolbar!"));
        m_toolbar->AddSeparator();
        return m_toolbar; // must return non-NULL
    }

    else /*<object class="wxToolBar">*/
    {
        m_isAddon=(m_class == _T("wxToolBarAddOn"));
        if(m_isAddon)
        { // special case: Only add items to toolbar
          toolbar=(wxToolBar*)m_instance;
          // XRC_MAKE_INSTANCE(toolbar, wxToolBar);
        }
        else
        {
            int style = GetStyle(_T("style"), wxNO_BORDER | wxTB_HORIZONTAL);
            #ifdef __WXMSW__
            if (!(style & wxNO_BORDER)) style |= wxNO_BORDER;
            #endif

            XRC_MAKE_INSTANCE(toolbar, wxToolBar)

            toolbar->Create(m_parentAsWindow,
                             GetID(),
                             GetPosition(),
                             GetSize(),
                             style,
                             GetName());
            wxSize bmpsize = GetSize(_T("bitmapsize"));
            if (!(bmpsize == wxDefaultSize))
                toolbar->SetToolBitmapSize(bmpsize);
            wxSize margins = GetSize(_T("margins"));
            if (!(margins == wxDefaultSize))
                toolbar->SetMargins(margins.x, margins.y);
            long packing = GetLong(_T("packing"), -1);
            if (packing != -1)
                toolbar->SetToolPacking(packing);
            long separation = GetLong(_T("separation"), -1);
            if (separation != -1)
                toolbar->SetToolSeparation(separation);
        }

        wxXmlNode *children_node = GetParamNode(_T("object"));
        if (!children_node)
           children_node = GetParamNode(_T("object_ref"));

        if (children_node == NULL) return toolbar;

        m_isInside = TRUE;
        m_toolbar = toolbar;

        wxXmlNode *n = children_node;

        while (n)
        {
            if ((n->GetType() == wxXML_ELEMENT_NODE) &&
                (n->GetName() == _T("object") || n->GetName() == _T("object_ref")))
            {
                wxObject *created = CreateResFromNode(n, toolbar, NULL);
                wxControl *control = wxDynamicCast(created, wxControl);
                if (!IsOfClass(n, _T("tool")) &&
                    !IsOfClass(n, _T("separator")) &&
                    control != NULL &&
                    control != toolbar)
                {
                    wxLogDebug(_T("control=%p, parent=%p, toolbar=%p"), control, control->GetParent(), toolbar);
                    toolbar->AddControl(control);
                }
            }
            n = n->GetNext();
        }

        toolbar->Realize();

        m_isInside = FALSE;
        m_toolbar = NULL;

        if(!m_isAddon)
        {
            if (m_parentAsWindow && !GetBool(_T("dontattachtoframe")))
            {
                wxFrame *parentFrame = wxDynamicCast(m_parent, wxFrame);
                if (parentFrame)
                    parentFrame->SetToolBar(toolbar);
            }
        }
        m_isAddon=false;
        return toolbar;
    }
}

bool wxToolBarAddOnXmlHandler::CanHandle(wxXmlNode *node)
{
// NOTE (mandrav#1#): wxXmlResourceHandler::IsOfClass() doesn't work in unicode (2.6.2)
// Don't ask why. It does this and doesn't work for our custom handler:
//    return node->GetPropVal(wxT("class"), wxEmptyString) == classname;
//
// This works though:
//    return node->GetPropVal(wxT("class"), wxEmptyString).Matches(classname);
//
// Don't ask me why... >:-|

    bool istbar = node->GetPropVal(wxT("class"), wxEmptyString).Matches(_T("wxToolBarAddOn"));
    bool istool = node->GetPropVal(wxT("class"), wxEmptyString).Matches(_T("tool"));
    bool issep = node->GetPropVal(wxT("class"), wxEmptyString).Matches(_T("separator"));

    return ((!m_isInside && istbar) ||
            (m_isInside && istool) ||
            (m_isInside && issep));
}
