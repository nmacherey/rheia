#include <RheiaTreeItemData.h>

IMPLEMENT_DYNAMIC_CLASS(RheiaTreeItemData,wxObject)

//bool RheiaTreeItemData::OwnerCheck(wxTreeEvent& event,wxTreeCtrl *tree,wxEvtHandler *handler,bool strict)
//{
//    if(!tree)   // No tree to get data from - ignore event
//        return false;
//
//    RheiaTreeItemData* data =
//        (RheiaTreeItemData*)tree->GetItemData(event.GetItem());
//
//    if(!data)
//    {
//        if(!strict)
//            return true; // On doubt, allow event
//        else
//        {
//            event.Skip();
//            return false;
//        }
//    }
//    wxEvtHandler *h = data->GetOwner();
//    if((h && h!=handler) || (strict && !h))
//    {   // Tree Item belongs to another handler - skip
//        event.Skip();
//        return false;
//    }
//    return true;
//}
