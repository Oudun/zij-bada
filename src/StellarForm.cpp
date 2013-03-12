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

StellarForm::StellarForm() {

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
	__pConstelList = new List();
	__pConstelList -> Construct(
			Rectangle(0, 0, 240, 360),
			LIST_STYLE_NORMAL,
			LIST_ITEM_SINGLE_TEXT, 20, 20, 100, 100);
	__pConstelList -> AddItemEventListener(*this);
	AddControl(*__pConstelList);
	return E_SUCCESS;
}

void
StellarForm::Update(void) {
	__pConstelList ->RemoveAllItems();
	Osp::Base::Collection::IEnumerator* constNames = SkyCanvas::getConstellations()->GetEnumeratorN();
	while (constNames -> MoveNext() == E_SUCCESS) {
		String* constNameAbbr = (String*) constNames -> GetCurrent();
		String constName;
		AppResource* appResource = Application::GetInstance()->GetAppResource();
		appResource->GetString(*constNameAbbr, constName);
		__pConstelList -> AddItem(&constName, &constName, null, null, null);
	}
}

void
StellarForm::OnItemStateChanged(const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status) {
	AppLog("Index = %d", index);
	AppLog("ItemId  = %d", itemId);
	String* abbr = (String*)(SkyCanvas::getConstellations()->GetAt(index));
	AppLog("Selected constellation is %S", abbr -> GetPointer());
	SkyCanvas::SelectConstellation(index);
	Osp::App::Application::GetInstance() -> SendUserEvent(CONSTELLATION_SELECTED, null);
}

