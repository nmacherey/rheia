/**
*   @file RheiaEditorPropertyPanel.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 13-March-2010
*/

#include "RheiaEditorPropertyPanel.h"
#include "RheiaEditorLayout.h"

namespace
{
const wxString whiteSpaceChoices[] = {
				_("Invisible"),
				_("Always visible"),
				_("Visible after indentation"),
				_("Indentation only")
				};
				
const int nWhiteSpaceChoices = sizeof( whiteSpaceChoices ) / sizeof(wxString);

const wxString eolModeChoices[] = {
				_("Default"),
				_("Mac (CR)"),
				_("Windows (CRLF)"),
				_("Unix (LF)")
				};
				
const int nEolModeChoices = sizeof( eolModeChoices ) / sizeof(wxString);

const wxString foldOpenChoices[] = {
				_("Box minus"),
				_("Circle minus"),
				_("Mark minus"),
				_("Mark arrow down"),
				_("None")
				};
				
const int nFoldOpenChoices = sizeof( foldOpenChoices ) / sizeof(wxString);

const wxString foldClosingChoices[] = {
				_("Box plus"),
				_("Circle plus"),
				_("Mark plus"),
				_("Mark arrow"),
				_("None")
				};
				
const int nFoldClosingChoices = sizeof( foldClosingChoices ) / sizeof(wxString);

const wxString foldLinkChoices[] = {
				_("Vertical lines"),
				_("None")
				};
				
const int nFoldLinkChoices = sizeof( foldLinkChoices ) / sizeof(wxString);

const wxString foldTailChoices[] = {
				_("Low Corner Curves"),
				_("Low Corner"),
				_("Full Rectangle"),
				_("None")
				};
				
const int nFoldTailChoices = sizeof( foldTailChoices ) / sizeof(wxString);

};


// -----------------------------------------------------------------------
// wxSingleChoiceDialogAdapter (wxPGEditorDialogAdapter sample)
// -----------------------------------------------------------------------

class wxSingleChoiceDialogAdapter : public wxPGEditorDialogAdapter
{
public:

    wxSingleChoiceDialogAdapter( const wxPGChoices& choices )
        : wxPGEditorDialogAdapter(), m_choices(choices)
    {
    }

    virtual bool DoShowDialog( wxPropertyGrid* WXUNUSED(propGrid),
                               wxPGProperty* WXUNUSED(property) )
    {
		
        wxString s = ::wxGetSingleChoice(wxT("Select the value :"),
                                         wxT("Caption"),
                                         m_choices.GetLabels());
        if ( s.length() )
        {
            SetValue(s);
            return true;
        }

        return false;
    }

protected:
    const wxPGChoices&  m_choices;
};


class wxSingleChoiceProperty : public wxStringProperty
{
public:

    wxSingleChoiceProperty( const wxString& label,
						  const wxString choices[],
						  int nChoices,
                          const wxString& name = wxPG_LABEL,
                          const wxString& value = wxEmptyString)
        : wxStringProperty(label, name, value)
    {
		for( unsigned int i = 0; i < (unsigned int) nChoices ; ++ i)
			m_choices.Add(choices[i]);
    }

    // Set editor to have button
    virtual const wxPGEditor* DoGetEditorClass() const
    {
        return wxPGEditor_TextCtrlAndButton;
    }

    // Set what happens on button click
    virtual wxPGEditorDialogAdapter* GetEditorDialog() const
    {
        return new wxSingleChoiceDialogAdapter(m_choices);
    }

protected:
    wxPGChoices m_choices;
};


// -----------------------------------------------------------------------
// wxSizeProperty
// -----------------------------------------------------------------------

WX_PG_IMPLEMENT_PROPERTY_CLASS(wxSizeProperty,wxPGProperty,
                               wxSize,const wxSize&,TextCtrl)

wxSizeProperty::wxSizeProperty( const wxString& label, const wxString& name,
    const wxSize& value) : wxPGProperty(label,name)
{
    SetValueI(value);
    AddPrivateChild( new wxIntProperty(wxT("Width"),wxPG_LABEL,value.x) );
    AddPrivateChild( new wxIntProperty(wxT("Height"),wxPG_LABEL,value.y) );
}

wxSizeProperty::~wxSizeProperty() { }

void wxSizeProperty::RefreshChildren()
{
    if ( !GetChildCount() ) return;
    const wxSize& size = wxSizeRefFromVariant(m_value);
    Item(0)->SetValue( (long)size.x );
    Item(1)->SetValue( (long)size.y );
}

wxVariant wxSizeProperty::ChildChanged( wxVariant& thisValue,
                                        int childIndex,
                                        wxVariant& childValue ) const
{
    wxSize& size = wxSizeRefFromVariant(thisValue);
    int val = childValue.GetLong();
    switch ( childIndex )
    {
        case 0: size.x = val; break;
        case 1: size.y = val; break;
    }
    wxVariant newVariant;
    newVariant << size;
    return newVariant;
}

// -----------------------------------------------------------------------
// wxPointProperty
// -----------------------------------------------------------------------

WX_PG_IMPLEMENT_PROPERTY_CLASS(wxPointProperty,wxPGProperty,
                               wxPoint,const wxPoint&,TextCtrl)

wxPointProperty::wxPointProperty( const wxString& label, const wxString& name,
    const wxPoint& value) : wxPGProperty(label,name)
{
    SetValueI(value);
    AddPrivateChild( new wxIntProperty(wxT("X"),wxPG_LABEL,value.x) );
    AddPrivateChild( new wxIntProperty(wxT("Y"),wxPG_LABEL,value.y) );
}

wxPointProperty::~wxPointProperty() { }

void wxPointProperty::RefreshChildren()
{
    if ( !GetChildCount() ) return;
    const wxPoint& point = wxPointRefFromVariant(m_value);
    Item(0)->SetValue( (long)point.x );
    Item(1)->SetValue( (long)point.y );
}

wxVariant wxPointProperty::ChildChanged( wxVariant& thisValue,
                                         int childIndex,
                                         wxVariant& childValue ) const
{
    wxPoint& point = wxPointRefFromVariant(thisValue);
    int val = childValue.GetLong();
    switch ( childIndex )
    {
        case 0: point.x = val; break;
        case 1: point.y = val; break;
    }
    wxVariant newVariant;
    newVariant << point;
    return newVariant;
}


RheiaEditorPropertyPanel::RheiaEditorPropertyPanel(wxWindow* parent , RheiaEditorLayout* layout):
	wxPanel(parent, wxID_ANY),
	m_layout(layout)
{
	m_sizer = new wxBoxSizer(wxVERTICAL);
	m_PgId = wxNewId();
	
	int style = // default style
			wxPG_BOLD_MODIFIED |
			wxPG_SPLITTER_AUTO_CENTER |
			//wxPG_HIDE_MARGIN|wxPG_STATIC_SPLITTER |
			//wxPG_TOOLTIPS |
			//wxPG_HIDE_CATEGORIES |
			//wxPG_LIMITED_EDITING |
			//wxPG_TOOLBAR |
			wxPG_DESCRIPTION;

	int extraStyle = wxPG_EX_MODE_BUTTONS |
			 wxPG_EX_MULTIPLE_SELECTION;
			//| wxPG_EX_AUTO_UNSPECIFIED_VALUES
			//| wxPG_EX_GREY_LABEL_WHEN_DISABLED
			//| wxPG_EX_NATIVE_DOUBLE_BUFFERING
			//| wxPG_EX_HELP_AS_TOOLTIPS
			
	m_pPropGridManager = new wxPropertyGridManager(this,
                                  m_PgId, 
                                  wxDefaultPosition,
                                  wxSize(100, 100),
                                  style );
								  
	m_propGrid = m_pPropGridManager->GetGrid();
	m_pPropGridManager->SetExtraStyle(extraStyle);
	
	m_pPropGridManager->AddPage(_("Editor Settings"));
	
	m_pPropGridManager->SetValidationFailureBehavior( wxPG_VFB_BEEP | wxPG_VFB_MARK_CELL | wxPG_VFB_SHOW_MESSAGE );
    m_pPropGridManager->GetGrid()->SetVerticalSpacing( 2 );
	
	// Set somewhat different unspecified value appearance
    wxPGCell cell;
    cell.SetText(_("Unspecified"));
    cell.SetFgCol(*wxLIGHT_GREY);
    m_propGrid->SetUnspecifiedValueAppearance(cell);
	
	DoBuildGeneralProperties();
	DoBuildFoldingProperties();
	
	m_sizer->Add( m_pPropGridManager, 1, wxALL | wxEXPAND );
	SetSizer(m_sizer);
	
}

RheiaEditorPropertyPanel::~RheiaEditorPropertyPanel()
{
	 
}

void RheiaEditorPropertyPanel::DoBuildGeneralProperties()
{
	wxPGProperty* generalCat =  CreatePropertyCategory(NULL,_("General"),_("General Editor options"));
	
	/**************************************************************************************
	 * GUIDES
	 *************************************************************************************/
	wxPGProperty* guidesCat = CreatePropertyCategory(generalCat,_("Guides"),_("Edition guides general options"));
	
	CreatePropertyBool( guidesCat, _("Display line numbers"), _("Display line numbers in the left editor margin."),true);
	CreatePropertyBool( guidesCat, _("Highlight match braces"), _("Highlight matching braces when editing or selecting a brace in the editor.") ,true);
	CreatePropertyBool( guidesCat, _("Show indentation guides"), _("Show indentiation guide lines inside the editor to help you know how many levels of indentation you have.") ,true);
	CreatePropertyBool( guidesCat, _("Disable semicolon shift"), _("Disable semicolon shift.") ,false);
	CreatePropertyBool( guidesCat, _("Hide change marker margin"), _("Show/Hide the change marker margin that specifies you which lines have been changed since you have opened the file.") ,false);
	CreatePropertyChoice( guidesCat, _("White spaces visibility"), _("You can use this option if you want to show/hde white spaces in the editor.") , whiteSpaceChoices , nWhiteSpaceChoices, whiteSpaceChoices[0] );
	CreatePropertyChoice( guidesCat, _("End of line mode"), _("You can use this option if you want to use specific en of lines in the editor.") , eolModeChoices , nEolModeChoices, eolModeChoices[0] );
	
	/**************************************************************************************
	 * INDETATION
	 *************************************************************************************/
	wxPGProperty* indentCat = CreatePropertyCategory(generalCat,_("Indentation"),_("Indentation Options"));
	
	CreatePropertyBool( indentCat, _("Disable smart indentation"), _("If you disable this option, indentation will not automatically be done."),false);
	CreatePropertyBool( indentCat, _("Allow tabs to indent and un indent"), _("This option will allow you to use tab characters to indent and unindent when you are editing."),true);
	CreatePropertySpin( indentCat, _("Columns per indentation level"), _("Number of editor columns you want to use for each indentation level."),4,0,8,1);
	CreatePropertySpin( indentCat, _("Columns per tabs characters"), _("Number of editor columns you want to use for each tab character."),4,0,8,1);
	
	/**************************************************************************************
	 * CARET
	 *************************************************************************************/
	wxPGProperty* caretCat = CreatePropertyCategory(generalCat,_("Caret"),_("General options about the caret."));
	
	CreatePropertySpin( caretCat, _("Blink period"), _("Change the caret blink period."),300,100,1000,20);
	CreatePropertySpin( caretCat, _("Width"), _("Change the caret width in pixel."),1,1,5,1);
}

void RheiaEditorPropertyPanel::DoBuildFoldingProperties()
{
	wxPGProperty* foldingCat = CreatePropertyCategory(NULL,_("Folding"),_("Folding Options"));
	
	/**************************************************************************************
	 * FOLDING GENERAL PROPERTIES
	 *************************************************************************************/
	wxPGProperty* generalCat = CreatePropertyCategory(foldingCat,_("General Folding Options"),_("General Options about folding"));
	
	CreatePropertyBool( generalCat, _("Display Folding Margin"), _("Hide / Show the folding margin in editors."),true);
	CreatePropertyBool( generalCat, _("Underline folded lines"), _("Display a solid line under folded blocks."),true);
	CreatePropertyBool( generalCat, _("Enable preprocessor folding"), _("Allow folding of preprocessor definitions"),true);
	CreatePropertyBool( generalCat, _("Fold compact"), _("Enable compact folding."),true);
	CreatePropertyBool( generalCat, _("Fold comment"), _("Enable to fold comments."),true);
	CreatePropertyBool( generalCat, _("Fold at else"), _("Enable to fold at else statements."),true);
	
	/**************************************************************************************
	 * FOLDING SYMBOLS
	 *************************************************************************************/
	wxPGProperty* symbolsCat = CreatePropertyCategory(foldingCat,_("Folding Symbols"),_("Folding symbols options"));
	
	wxPGProperty* openFoldCat = CreatePropertyCategory(symbolsCat,_("Opened Folding Symbols"),_("Opened Folding symbols options"));
	CreatePropertyChoice(openFoldCat, _("Symbol for unfolded blocks"), _("This allow you to select the type of symbols you would like to have for opened code blocks") , foldOpenChoices , nFoldOpenChoices, foldOpenChoices[0] );
	CreatePropertyColour(openFoldCat,_("Unfolded blocks foreground colour"),_("This allow you to select the foreground color of unfolded code blocks"),wxColor(0xff, 0xff, 0xff));
	CreatePropertyColour(openFoldCat,_("Unfolded blocks background colour"),_("This allow you to select the background color of unfolded code blocks"),wxColor(0x80, 0x80, 0x80));
	
	wxPGProperty* closeFoldCat = CreatePropertyCategory(symbolsCat,_("Closed Folding Symbols"),_("Closed Folding symbols options"));
	CreatePropertyChoice(closeFoldCat, _("Symbol for folded blocks"), _("This allow you to select the type of symbols you would like to have for closed code blocks") , foldClosingChoices , nFoldClosingChoices, foldClosingChoices[0] );
	CreatePropertyColour(closeFoldCat,_("Folded blocks foreground colour"),_("This allow you to select the foreground color of folded code blocks"),wxColor(0xff, 0xff, 0xff));
	CreatePropertyColour(closeFoldCat,_("Folded blocks background colour"),_("This allow you to select the background color of folded code blocks"),wxColor(0x80, 0x80, 0x80));
	
	/**************************************************************************************
	 * FOLDING STYLES
	 *************************************************************************************/
	wxPGProperty* stylesCat = CreatePropertyCategory(foldingCat,_("Folding Styles"),_("Folding styles options"));
	
	wxPGProperty* linkFoldCat = CreatePropertyCategory(stylesCat,_("Folding Linkers"),_("Folding linker options"));
	CreatePropertyChoice(linkFoldCat, _("Linker style"), _("This allow you to select the type of links between different folders") , foldLinkChoices , nFoldLinkChoices, foldLinkChoices[0] );
	CreatePropertyColour(linkFoldCat,_("Linker foreground colour"),_("This allow you to select the foreground color of folder links"),wxColor(0xff, 0xff, 0xff));
	CreatePropertyColour(linkFoldCat,_("Linker background colour"),_("This allow you to select the background color of folder links"),wxColor(0x80, 0x80, 0x80));
	
	wxPGProperty* tailFoldCat = CreatePropertyCategory(stylesCat,_("Folding Tails"),_("Folding tail options"));
	CreatePropertyChoice(tailFoldCat, _("Tail style"), _("This allow you to select the type of tails between different folders") , foldTailChoices , nFoldTailChoices, foldTailChoices[0] );
	CreatePropertyColour(tailFoldCat,_("Tail foreground colour"),_("This allow you to select the foreground color of folder tails"),wxColor(0xff, 0xff, 0xff));
	CreatePropertyColour(tailFoldCat,_("Tail background colour"),_("This allow you to select the background color of folder tails"),wxColor(0x80, 0x80, 0x80));
}

wxPGProperty* RheiaEditorPropertyPanel::CreatePropertyCategory( wxPGProperty* parent , const wxString& name, const wxString& help )
{
	RheiaPropertyInfoArray::iterator it = m_properties.find(name);
	if( it != m_properties.end() )
		return NULL;
	
	wxPropertyGridPage* pg = m_pPropGridManager->GetPage(_("Editor Settings"));
	if( pg == NULL )
		return NULL;
	
	wxPGProperty* ret = NULL;
	
	ret = new wxPropertyCategory(name,wxPG_LABEL);
	
	if( parent != NULL )
		parent->AppendChild(ret);
	else
		pg->Append(ret);
		
	pg->SetPropertyHelpString(name,help);
	
	RheiaPropertyInfo info;
	info.parent = parent;
	info.property = ret;
	info.name = name;
	info.type = rptCATEGORY;
	
	m_properties[name] = info;
	
	return ret;
}

wxPGProperty* RheiaEditorPropertyPanel::CreatePropertyBool( wxPGProperty* parent , const wxString& name, const wxString& help , bool value )
{
	RheiaPropertyInfoArray::iterator it = m_properties.find(name);
	if( it != m_properties.end() )
		return NULL;
	
	wxPropertyGridPage* pg = m_pPropGridManager->GetPage(_("Editor Settings"));
	if( pg == NULL )
		return NULL;
	
	wxPGProperty* ret = NULL;
	
	ret = new wxBoolProperty(name,wxPG_LABEL,value);
	
	if( parent != NULL )
		parent->AppendChild(ret);
	else
		pg->Append(ret);
		
	pg->SetPropertyHelpString(name,help);
	
	RheiaPropertyInfo info;
	info.parent = parent;
	info.property = ret;
	info.name = name;
	info.type = rptBOOL;
	
	m_properties[name] = info;
	
	return ret;
}

wxPGProperty* RheiaEditorPropertyPanel::CreatePropertyInt( wxPGProperty* parent , const wxString& name, const wxString& help , int value)
{
	RheiaPropertyInfoArray::iterator it = m_properties.find(name);
	if( it != m_properties.end() )
		return NULL;
	
	wxPropertyGridPage* pg = m_pPropGridManager->GetPage(_("Editor Settings"));
	if( pg == NULL )
		return NULL;
	
	wxPGProperty* ret = NULL;
	
	ret = new wxIntProperty(name,wxPG_LABEL,value);
	
	if( parent != NULL )
		parent->AppendChild(ret);
	else
		pg->Append(ret);
		
	pg->SetPropertyHelpString(name,help);
	
	RheiaPropertyInfo info;
	info.parent = parent;
	info.property = ret;
	info.name = name;
	info.type = rptINT;
	
	m_properties[name] = info;
	
	return ret;
}

wxPGProperty* RheiaEditorPropertyPanel::CreatePropertySpin( wxPGProperty* parent , const wxString& name, const wxString& help , int value, int min, int max , int step)
{
	wxPropertyGridPage* pg = m_pPropGridManager->GetPage(_("Editor Settings"));
	if( pg == NULL )
		return NULL;
		
	wxPGProperty* ret = CreatePropertyInt( parent , name , help , value );
	if( ret == NULL )
		return NULL;
		
	pg->SetPropertyEditor(name, wxPGEditor_SpinCtrl );
    pg->SetPropertyAttribute(name, wxPG_ATTR_MIN, (long)min );  // Use constants instead of string
    pg->SetPropertyAttribute(name, wxPG_ATTR_MAX, (long)max );   // for reduced binary size.
    pg->SetPropertyAttribute(name, wxT("Step"), (long)step );
    pg->SetPropertyAttribute(name, wxT("MotionSpin"), true );
	
	return ret;
}

wxPGProperty* RheiaEditorPropertyPanel::CreatePropertyColour( wxPGProperty* parent , const wxString& name, const wxString& help , wxColour value )
{
	RheiaPropertyInfoArray::iterator it = m_properties.find(name);
	if( it != m_properties.end() )
		return NULL;
	
	wxPropertyGridPage* pg = m_pPropGridManager->GetPage(_("Editor Settings"));
	if( pg == NULL )
		return NULL;
	
	wxPGProperty* ret = NULL;
	
	ret = new wxColourProperty(name,wxPG_LABEL,value);
	
	if( parent != NULL )
		parent->AppendChild(ret);
	else
		pg->Append(ret);
		
	pg->SetPropertyHelpString(name,help);
	
	RheiaPropertyInfo info;
	info.parent = parent;
	info.property = ret;
	info.name = name;
	info.type = rptCOLOUR;
	
	m_properties[name] = info;
	
	return ret;
}

wxPGProperty* RheiaEditorPropertyPanel::CreatePropertyFont( wxPGProperty* parent , const wxString& name, const wxString& help , wxFont value )
{
	RheiaPropertyInfoArray::iterator it = m_properties.find(name);
	if( it != m_properties.end() )
		return NULL;
	
	wxPropertyGridPage* pg = m_pPropGridManager->GetPage(_("Editor Settings"));
	if( pg == NULL )
		return NULL;
	
	wxPGProperty* ret = NULL;
	
	ret = new wxFontProperty(name,wxPG_LABEL,value);
	
	if( parent != NULL )
		parent->AppendChild(ret);
	else
		pg->Append(ret);
		
	pg->SetPropertyHelpString(name,help);
	
	RheiaPropertyInfo info;
	info.parent = parent;
	info.property = ret;
	info.name = name;
	info.type = rptFONT;
	
	m_properties[name] = info;
	
	return ret;
}

wxPGProperty* RheiaEditorPropertyPanel::CreatePropertySize( wxPGProperty* parent , const wxString& name, const wxString& help , wxSize value )
{
	RheiaPropertyInfoArray::iterator it = m_properties.find(name);
	if( it != m_properties.end() )
		return NULL;
	
	wxPropertyGridPage* pg = m_pPropGridManager->GetPage(_("Editor Settings"));
	if( pg == NULL )
		return NULL;
	
	wxPGProperty* ret = NULL;
	
	ret = new wxSizeProperty(name,wxPG_LABEL,value);
	
	if( parent != NULL )
		parent->AppendChild(ret);
	else
		pg->Append(ret);
		
	pg->SetPropertyHelpString(name,help);
	
	RheiaPropertyInfo info;
	info.parent = parent;
	info.property = ret;
	info.name = name;
	info.type = rptSIZE;
	
	m_properties[name] = info;
	
	return ret;
}

wxPGProperty* RheiaEditorPropertyPanel::CreatePropertyPoint( wxPGProperty* parent , const wxString& name, const wxString& help , wxPoint value )
{
	RheiaPropertyInfoArray::iterator it = m_properties.find(name);
	if( it != m_properties.end() )
		return NULL;
	
	wxPropertyGridPage* pg = m_pPropGridManager->GetPage(_("Editor Settings"));
	if( pg == NULL )
		return NULL;
	
	wxPGProperty* ret = NULL;
	
	ret = new wxPointProperty(name,wxPG_LABEL,value);
	
	if( parent != NULL )
		parent->AppendChild(ret);
	else
		pg->Append(ret);
		
	pg->SetPropertyHelpString(name,help);
	
	RheiaPropertyInfo info;
	info.parent = parent;
	info.property = ret;
	info.name = name;
	info.type = rptPOINT;
	
	m_properties[name] = info;
	
	return ret;
}

wxPGProperty* RheiaEditorPropertyPanel::CreatePropertyString( wxPGProperty* parent , const wxString& name, const wxString& help , const wxString& value )
{
	RheiaPropertyInfoArray::iterator it = m_properties.find(name);
	if( it != m_properties.end() )
		return NULL;
	
	wxPropertyGridPage* pg = m_pPropGridManager->GetPage(_("Editor Settings"));
	if( pg == NULL )
		return NULL;
	
	wxPGProperty* ret = NULL;
	
	ret = new wxStringProperty(name,wxPG_LABEL,value);
	
	if( parent != NULL )
		parent->AppendChild(ret);
	else
		pg->Append(ret);
		
	pg->SetPropertyHelpString(name,help);
	
	RheiaPropertyInfo info;
	info.parent = parent;
	info.property = ret;
	info.name = name;
	info.type = rptSTRING;
	
	m_properties[name] = info;
	
	return ret;
}

wxPGProperty* RheiaEditorPropertyPanel::CreatePropertyChoice( wxPGProperty* parent , const wxString& name, const wxString& help , const wxString choices[] , int nChoices , const wxString& value )
{
	RheiaPropertyInfoArray::iterator it = m_properties.find(name);
	if( it != m_properties.end() )
		return NULL;
	
	wxPropertyGridPage* pg = m_pPropGridManager->GetPage(_("Editor Settings"));
	if( pg == NULL )
		return NULL;
	
	wxPGProperty* ret = NULL;
	
	ret = new wxSingleChoiceProperty(name,choices,nChoices,wxPG_LABEL,value);
	
	if( parent != NULL )
		parent->AppendChild(ret);
	else
		pg->Append(ret);
		
	pg->SetPropertyHelpString(name,help);
	
	RheiaPropertyInfo info;
	info.parent = parent;
	info.property = ret;
	info.name = name;
	info.type = rptCHOICE;
	
	m_properties[name] = info;
	
	return ret;
}

wxPGProperty* RheiaEditorPropertyPanel::CreatePropertyImageFile( wxPGProperty* parent , const wxString& name, const wxString& help , const wxString& value )
{
	RheiaPropertyInfoArray::iterator it = m_properties.find(name);
	if( it != m_properties.end() )
		return NULL;
	
	wxPropertyGridPage* pg = m_pPropGridManager->GetPage(_("Editor Settings"));
	if( pg == NULL )
		return NULL;
	
	wxPGProperty* ret = NULL;
	
	ret = new wxImageFileProperty(name,wxPG_LABEL,value);
	
	if( parent != NULL )
		parent->AppendChild(ret);
	else
		pg->Append(ret);
		
	pg->SetPropertyHelpString(name,help);
	
	RheiaPropertyInfo info;
	info.parent = parent;
	info.property = ret;
	info.name = name;
	info.type = rptIMAGE;
	
	m_properties[name] = info;
	
	return ret;
}

wxPGProperty* RheiaEditorPropertyPanel::CreatePropertyFile( wxPGProperty* parent , const wxString& name, const wxString& help , const wxString& value )
{
	RheiaPropertyInfoArray::iterator it = m_properties.find(name);
	if( it != m_properties.end() )
		return NULL;
	
	wxPropertyGridPage* pg = m_pPropGridManager->GetPage(_("Editor Settings"));
	if( pg == NULL )
		return NULL;
	
	wxPGProperty* ret = NULL;
	
	ret = new wxFileProperty(name,wxPG_LABEL,value);
	
	if( parent != NULL )
		parent->AppendChild(ret);
	else
		pg->Append(ret);
		
	pg->SetPropertyHelpString(name,help);
	
	RheiaPropertyInfo info;
	info.parent = parent;
	info.property = ret;
	info.name = name;
	info.type = rptFILE;
	
	m_properties[name] = info;
	
	return ret;
}

wxPGProperty* RheiaEditorPropertyPanel::CreatePropertyDir( wxPGProperty* parent , const wxString& name, const wxString& help , const wxString& value )
{
	RheiaPropertyInfoArray::iterator it = m_properties.find(name);
	if( it != m_properties.end() )
		return NULL;
	
	wxPropertyGridPage* pg = m_pPropGridManager->GetPage(_("Editor Settings"));
	if( pg == NULL )
		return NULL;
	
	wxPGProperty* ret = NULL;
	
	ret = new wxDirProperty(name,wxPG_LABEL,value);
	
	if( parent != NULL )
		parent->AppendChild(ret);
	else
		pg->Append(ret);
		
	pg->SetPropertyHelpString(name,help);
	
	RheiaPropertyInfo info;
	info.parent = parent;
	info.property = ret;
	info.name = name;
	info.type = rptDIR;
	
	m_properties[name] = info;
	
	return ret;
}