/*
 * ConstellationForm.cpp
 *
 *  Created on: 21.11.2012
 *      Author: ddreval
 */

#include "ConstellationForm.h"

using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Graphics;
using namespace Osp::Ui::Controls;
using namespace Osp::App;

ConstellationForm::ConstellationForm() {

}

ConstellationForm::~ConstellationForm() {
	// TODO Auto-generated destructor stub
}

bool
ConstellationForm::Initialize(void) {
	list = new ArrayList();
	__pConstList = new List();
	__pConstList -> Construct(
			Rectangle(0, 0, 240, 360),
			LIST_STYLE_NORMAL,
			LIST_ITEM_SINGLE_TEXT, 20, 20, 100, 100);
	__pConstList -> AddItemEventListener(*this);
	AddControl(*__pConstList);
	return true;
}


void
ConstellationForm::UpdateConstellationList(Osp::Base::Collection::IList* pList) {
	list = pList;
	AppLog("!!!Updating constellations list");
//	__pConstList -> RemoveAllItems();
//	IEnumerator* constEnum = list->GetEnumeratorN();
//	while (constEnum->MoveNext()==E_SUCCESS) {
//		String* constName = (String*)(constEnum->GetCurrent());
//		__pConstList -> AddItem(constName, constName, null, null, null);
//	}
//	__pConstList->Draw();
//	__pConstList->Show();
}

void
ConstellationForm::OnItemStateChanged(const Osp::Ui::Control& source, int index, int itemId, Osp::Ui::ItemStatus status) {
	AppLog("Index is %d", index);
	AppLog("Id is %d", itemId);
	AppLog("Constellation list size is %d", list->GetCount());
	String* selectedConstellation = (String*)list->GetAt(index);
	AppLog("!!!Selected constellation is %S", selectedConstellation->GetPointer());
	AppLog("!!!Selected constellation is %S", selectedConstellation->GetPointer());
    String hello;
    AppResource* pAppResource = Application::GetInstance()->GetAppResource();
    if (pAppResource)
        pAppResource->GetString(*selectedConstellation, hello);
    AppLog("Name is %S", hello.GetPointer());
    IList* args = new ArrayList();
    args -> Add(*selectedConstellation);
    parent->SendUserEvent(1, args);
}

result
ConstellationForm::OnInitializing(void) {
	return E_SUCCESS;
}

//void
//ConstellationForm::OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList *pArgs) {
//	AppLog("Event Received");
//}
