/*
 * StellarForm.cpp
 *
 *  Created on: 04.03.2013
 *      Author: ddreval
 */

#include "forms/ConstellationForm.h"

using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;
using namespace Osp::Base;
using namespace Osp::App;

ConstellationForm::ConstellationForm() {

}

ConstellationForm::~ConstellationForm() {
	// TODO Auto-generated destructor stub
}

bool
ConstellationForm::Initialize(void) {
	Construct(L"CONSTELLATION_FORM");
	return true;
}

result
ConstellationForm::OnInitializing(void) {

	Osp::App::AppResource* pAppResource = Osp::App::Application::GetInstance()->GetAppResource();
	Osp::Graphics::Bitmap* bitmapButtonPressed;
	bitmapButtonPressed = pAppResource -> GetBitmapN(L"ButtonPressed.png");

	__pConstelList = new List();
	__pConstelList -> Construct(
			Rectangle(0, 0, 240, 360),
			LIST_STYLE_NORMAL,
			LIST_ITEM_SINGLE_TEXT, 48, 48, 200, 0);
	__pConstelList -> AddItemEventListener(*this);
	__pConstelList -> SetBackgroundColor(COLOR_FORM_BKG);
	__pConstelList -> SetHighlightedItemBackgroundBitmap(*bitmapButtonPressed);
	__pConstelList -> SetItemTextColor(LIST_ITEM_TEXT1, COLOR_FORM_TEXT);
	__pConstelList -> SetItemTextColor(LIST_ITEM_TEXT2, COLOR_FORM_TEXT);
	AddControl(*__pConstelList);
	return E_SUCCESS;
}

void
ConstellationForm::Update(void) {
	__pConstelList ->RemoveAllItems();
	Osp::Base::Collection::IEnumerator* constNames = SkyCanvas::getConstellations()->GetEnumeratorN();
	String emptyString;
	__pConstelList -> AddItem(&emptyString, &emptyString, null, null, null);
	while (constNames -> MoveNext() == E_SUCCESS) {
		String* constNameAbbr = (String*) constNames -> GetCurrent();
		String constName;
		AppResource* appResource = Application::GetInstance()->GetAppResource();
		appResource->GetString(*constNameAbbr, constName);
		__pConstelList -> AddItem(&constName, &constName, null, null, null);
	}
}

void
ConstellationForm::OnItemStateChanged(const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status) {
	AppLog("Index = %d", index);
	AppLog("ItemId  = %d", itemId);
	SkyCanvas::SelectConstellation(index-1);
	Osp::App::Application::GetInstance() -> SendUserEvent(EVENT_CONSTELLATION_SELECTED, null);
}

