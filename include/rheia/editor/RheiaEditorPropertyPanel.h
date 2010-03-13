/**
*   @file RheiaEditorPropertyPanel.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 13-March-2010
*/

#ifndef RheiaEditorPropertyPanel_h_
#define RheiaEditorPropertyPanel_h_

#include <map>

#include "RheiaEditorSettings.h"

#include <wx/wx.h>

#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/propgrid/manager.h>
#include <wx/propgrid/property.h>

/** imports */
class RheiaEditorLayout;

enum RheiaPropertyType
{
	rptCATEGORY = 1,
	rptFONT,
	rptCHOICE,
	rptSIZE,
	rptPOINT,
	rptBOOL,
	rptINT,
	rptSTRING,
	rptCOLOUR,
	rptIMAGE,
	rptFILE,
	rptDIR
};

/** 
 * @strcut RheiaPropertyInfo
 * @brief structure for regitering property information
 * @author Nicolas Macherey (nm@graymat.fr)
 * @version 0.0.1
 * @date 13-March-2010
 */
struct RheiaPropertyInfo
{
	RheiaPropertyInfo():parent(NULL),property(NULL){};
#ifndef SWIG
	RheiaPropertyInfo(const RheiaPropertyInfo& rhs):
		type(rhs.type),
		parent(rhs.parent),
		property(rhs.property),
		name(rhs.name){}
		
	RheiaPropertyInfo& operator=(const RheiaPropertyInfo& rhs)
	{
		type = rhs.type;
		parent = rhs.parent;
		property = rhs.property;
		name = rhs.name;
		
		return (*this);
	}
#endif
	RheiaPropertyType type;
	wxPGProperty* parent;
	wxPGProperty* property;
	wxString name;
};

/** define an array of properties */
typedef std::map<wxString,RheiaPropertyInfo> RheiaPropertyInfoArray;

/**
*   @class RheiaEditorPropertyPanel
*
*   @brief panel for enabling user editor configuration
* 
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 13-March-2010
*/
class EDITOR_DLLEXPORT RheiaEditorPropertyPanel : public wxPanel
{
public :
	/** ctor
	 * @param parent parented window
	 * @param layout RheiaEditorLayout to configure
	 */
	RheiaEditorPropertyPanel(wxWindow* parent , RheiaEditorLayout* layout);
	
	/** dtor */
	virtual ~RheiaEditorPropertyPanel();
	
	/** method for creating a category property 
	 * @param parent Parent property in which the property shall be created if NULL it will be added in the default page
	 * @param name property name
	 * @param help property help string
	 * @return thr created property, you do not need to store it as it is automatically stored in the RheiaPropertyInfoArray 
	 * for this panel. 
	 */
	wxPGProperty* CreatePropertyCategory( wxPGProperty* parent , const wxString& name, const wxString& help );
	
	/** method for creating a bool property 
	 * @param parent Parent property in which the property shall be created if NULL it will be added in the default page
	 * @param name property name
	 * @param help property help string
	 * @param value property default value
	 * @return thr created property, you do not need to store it as it is automatically stored in the RheiaPropertyInfoArray 
	 * for this panel. 
	 */
	wxPGProperty* CreatePropertyBool( wxPGProperty* parent , const wxString& name, const wxString& help , bool value = true );
	
	/** method for creating an Int property
	 * @param parent Parent property in which the property shall be created if NULL it will be added in the default page
	 * @param name property name
	 * @param help property help string
	 * @param value property default value
	 * @return thr created property, you do not need to store it as it is automatically stored in the RheiaPropertyInfoArray 
	 * for this panel. 
	 */
	wxPGProperty* CreatePropertyInt( wxPGProperty* parent , const wxString& name, const wxString& help , int value = 0);
	
	/** method for creating a Spin ctrl property
	 * @param parent Parent property in which the property shall be created if NULL it will be added in the default page
	 * @param name property name
	 * @param help property help string
	 * @param value property default value
	 * @param min property minimum value
	 * @param max property max value
	 * @param step property step
	 * @return thr created property, you do not need to store it as it is automatically stored in the RheiaPropertyInfoArray 
	 * for this panel. 
	 */
	wxPGProperty* CreatePropertySpin( wxPGProperty* parent , const wxString& name, const wxString& help , int value = 0, int min = 0, int max = 1 , int step = 1);
	
	/** method for creating a colour property
	 * @param parent Parent property in which the property shall be created if NULL it will be added in the default page
	 * @param name property name
	 * @param help property help string
	 * @param value property default value
	 * @return thr created property, you do not need to store it as it is automatically stored in the RheiaPropertyInfoArray 
	 * for this panel. 
	 */
	wxPGProperty* CreatePropertyColour( wxPGProperty* parent , const wxString& name, const wxString& help , wxColour value = *wxLIGHT_GREY );
	
	/** method for creating a font property
	 * @param parent Parent property in which the property shall be created if NULL it will be added in the default page
	 * @param name property name
	 * @param help property help string
	 * @param value property default value
	 * @return thr created property, you do not need to store it as it is automatically stored in the RheiaPropertyInfoArray 
	 * for this panel. 
	 */
	wxPGProperty* CreatePropertyFont( wxPGProperty* parent , const wxString& name, const wxString& help , wxFont value );
	
	/** method for creating a size property
	 * @param parent Parent property in which the property shall be created if NULL it will be added in the default page
	 * @param name property name
	 * @param help property help string
	 * @param value property default value
	 * @return thr created property, you do not need to store it as it is automatically stored in the RheiaPropertyInfoArray 
	 * for this panel. 
	 */
	wxPGProperty* CreatePropertySize( wxPGProperty* parent , const wxString& name, const wxString& help , wxSize value = wxDefaultSize );
	
	/** method for creating a point property
	 * @param parent Parent property in which the property shall be created if NULL it will be added in the default page
	 * @param name property name
	 * @param help property help string
	 * @param value property default value
	 * @return thr created property, you do not need to store it as it is automatically stored in the RheiaPropertyInfoArray 
	 * for this panel. 
	 */
	wxPGProperty* CreatePropertyPoint( wxPGProperty* parent , const wxString& name, const wxString& help , wxPoint value = wxDefaultPosition );
	
	/** method for creating a string property
	 * @param parent Parent property in which the property shall be created if NULL it will be added in the default page
	 * @param name property name
	 * @param help property help string
	 * @param value property default value
	 * @return thr created property, you do not need to store it as it is automatically stored in the RheiaPropertyInfoArray 
	 * for this panel. 
	 */
	wxPGProperty* CreatePropertyString( wxPGProperty* parent , const wxString& name, const wxString& help , const wxString& value = wxEmptyString );
	
	/** method for creating a single choice string property
	 * @param parent Parent property in which the property shall be created if NULL it will be added in the default page
	 * @param name property name
	 * @param help property help string
	 * @param choices choices for the property
	 * @param nChoices number of choices in the array
	 * @param value property default value
	 * @return thr created property, you do not need to store it as it is automatically stored in the RheiaPropertyInfoArray 
	 * for this panel. 
	 */
	wxPGProperty* CreatePropertyChoice( wxPGProperty* parent , const wxString& name, const wxString& help , const wxString choices[] , int nChoices , const wxString& value );
	
	/** method for creating an image file property
	 * @param parent Parent property in which the property shall be created if NULL it will be added in the default page
	 * @param name property name
	 * @param help property help string
	 * @param value property default value
	 * @return thr created property, you do not need to store it as it is automatically stored in the RheiaPropertyInfoArray 
	 * for this panel. 
	 */
	wxPGProperty* CreatePropertyImageFile( wxPGProperty* parent , const wxString& name, const wxString& help , const wxString& value = wxEmptyString );
	
	/** method for creating a file property
	 * @param parent Parent property in which the property shall be created if NULL it will be added in the default page
	 * @param name property name
	 * @param help property help string
	 * @param value property default value
	 * @return thr created property, you do not need to store it as it is automatically stored in the RheiaPropertyInfoArray 
	 * for this panel. 
	 */
	wxPGProperty* CreatePropertyFile( wxPGProperty* parent , const wxString& name, const wxString& help , const wxString& value = wxEmptyString );
	
	/** method for creating a dir property
	 * @param parent Parent property in which the property shall be created if NULL it will be added in the default page
	 * @param name property name
	 * @param help property help string
	 * @param value property default value
	 * @return thr created property, you do not need to store it as it is automatically stored in the RheiaPropertyInfoArray 
	 * for this panel. 
	 */
	wxPGProperty* CreatePropertyDir( wxPGProperty* parent , const wxString& name, const wxString& help , const wxString& value = wxEmptyString );
	
private:

	/** Build the general properties parent and categories */
	void DoBuildGeneralProperties();
	
	/** Build the folding properties parent and categories */
	void DoBuildFoldingProperties();

	RheiaEditorLayout* m_layout;
	wxPropertyGridManager*  m_pPropGridManager;
    wxPropertyGrid*     m_propGrid;
	RheiaPropertyInfoArray m_properties;
	
	int m_PgId;
	wxSizer* m_sizer;
};


/*******************************************************
 * WX SAMPLE PROPERTIES
********************************************************/
// -----------------------------------------------------------------------

class wxSizeProperty : public wxPGProperty
{
    WX_PG_DECLARE_PROPERTY_CLASS(wxSizeProperty)
public:

    wxSizeProperty( const wxString& label = wxPG_LABEL, const wxString& name = wxPG_LABEL,
                    const wxSize& value = wxSize() );
    virtual ~wxSizeProperty();

    virtual wxVariant ChildChanged( wxVariant& thisValue,
                                    int childIndex,
                                    wxVariant& childValue ) const;
    virtual void RefreshChildren();

protected:

    // I stands for internal
    void SetValueI( const wxSize& value )
    {
        m_value = WXVARIANT(value);
    }
};

// -----------------------------------------------------------------------

class wxPointProperty : public wxPGProperty
{
    WX_PG_DECLARE_PROPERTY_CLASS(wxPointProperty)
public:

    wxPointProperty( const wxString& label = wxPG_LABEL, const wxString& name = wxPG_LABEL,
                     const wxPoint& value = wxPoint() );
    virtual ~wxPointProperty();

    virtual wxVariant ChildChanged( wxVariant& thisValue,
                                    int childIndex,
                                    wxVariant& childValue ) const;
    virtual void RefreshChildren();

protected:

    // I stands for internal
    void SetValueI( const wxPoint& value )
    {
        m_value = WXVARIANT(value);
    }
};

#endif
