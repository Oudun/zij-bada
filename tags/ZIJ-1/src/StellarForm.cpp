/*
 * StellarForm.cpp
 *
 *  Created on: 04.03.2013
 *      Author: ddreval
 */

#include "StellarForm.h"

using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;
using namespace Osp::Base;
using namespace Osp::App;

StellarForm::StellarForm(SkyCanvas* aSkyCanvas) {
	skyCanvas = aSkyCanvas;
}

StellarForm::~StellarForm() {
	// TODO Auto-generated destructor stub
}

bool
StellarForm::Initialize(void) {
	Construct(L"STELLAR_FORM");
	return true;
}

result
StellarForm::OnInitializing(void) {
//	pList1 = static_cast<Osp::Ui::Controls::List *>(GetControl("IDC_LIST1"));
//	if (pList1)	{
//		AppLog("Adding listener");
//		pList1->AddItemEventListener(*this);
//	} else {
//		AppLog("Can not add listener");
//	}
//	String str1(L"Hi");
//	String str2(L"Bye");
//	Osp::Base::String* constName = &str1;
//	AddControl (*pList1);
//	pList1 -> SetColumn1Width(100);
//	pList1 -> SetColumn1Width(100);
//	pList1 -> AddItem(&str1, &str2, null, null, null);
//	pList1 -> AddItem(constName, constName, null, null, null);
//	pList1 -> AddItem(constName, constName, null, null, null);
//	pList1 -> AddItem(constName, constName, null, null, null);
//	pList1 -> AddItem(constName, constName, null, null, null);
//	pList1 -> RefreshItem(2);
//	pList1 -> Show();


	pList1 = new List();
	pList1 -> Construct(
			Rectangle(0, 0, 240, 360),
			LIST_STYLE_NORMAL,
			LIST_ITEM_SINGLE_TEXT, 20, 20, 100, 100);
	pList1 -> AddItemEventListener(*this);
	AddControl(*pList1);

	return E_SUCCESS;
}

void
StellarForm::Update(void) {
	pList1 ->RemoveAllItems();
	Osp::Base::Collection::IEnumerator* constNames = SkyCanvas::getConstellations()->GetEnumeratorN();
	while (constNames -> MoveNext() == E_SUCCESS) {
		String* constNameAbbr = (String*) constNames -> GetCurrent();
		String constName;
		AppResource* appResource = Application::GetInstance()->GetAppResource();
		appResource->GetString(*constNameAbbr, constName);
		pList1 -> AddItem(&constName, &constName, null, null, null);
	}
	pList1 -> Draw();
	pList1 -> Show();
}

void
StellarForm::OnItemStateChanged(const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status) {

}
