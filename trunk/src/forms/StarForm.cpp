/*
 * StarForm.cpp
 *
 *  Created on: 08.02.2015
 *      Author: Denis
 */

#include "forms/StarForm.h"

//static const Osp::Graphics::Color& COLOR_BRIGHT_STAR;
//static const Osp::Graphics::Color& COLOR_DIM_STAR;
//static const Osp::Graphics::Color& COLOR_SELECTED_STAR;

using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;
using namespace Osp::App;

StarForm::StarForm() {

}

StarForm::~StarForm() {
	// TODO Auto-generated destructor stub
}

bool
StarForm::Initialize(void) {
	Construct(L"STAR_FORM");
	return true;
}

result
StarForm::OnInitializing(void) {
	__pStarsList = new List();
	__pStarsList -> Construct(
			Rectangle(0, 0, 240, 360),
			LIST_STYLE_NORMAL,
			LIST_ITEM_SINGLE_TEXT, 48, 48, 200, 0);
	__pStarsList -> AddItemEventListener(*this);
	__pStarsList -> SetBackgroundColor(COLOR_FORM_BKG);
	__pStarsList -> SetItemTextColor(LIST_ITEM_TEXT1, COLOR_FORM_TEXT);
	__pStarsList -> SetItemTextColor(LIST_ITEM_TEXT2, COLOR_FORM_TEXT);
	AddControl(*__pStarsList);
	return E_SUCCESS;
}


//result
//StarForm::OnInitializing(void) {
//	__pStarsList = new List();
//	__pStarsList -> Construct(
//			Rectangle(0, 0, 240, 360),
//			LIST_STYLE_NORMAL,
//			LIST_ITEM_DOUBLE_IMAGE_TEXT_TEXT, 25, 15, 40, 200);
//	__pStarsList -> AddItemEventListener(*this);
//	__pStarsList -> SetBackgroundColor(COLOR_FORM_BKG);
////	__pStarsList -> SetItemTextColor(LIST_ITEM_TEXT1, COLOR_FORM_TEXT);
////	__pStarsList -> SetItemTextColor(LIST_ITEM_TEXT2, COLOR_FORM_TEXT);
//
//	__pStarsList -> SetItemTextColor(LIST_ITEM_TEXT1, Color::COLOR_YELLOW);
//	__pStarsList -> SetItemTextColor(LIST_ITEM_TEXT2, Color::COLOR_CYAN);
//
//	AddControl(*__pStarsList);
//	return E_SUCCESS;
//}




void
StarForm::Update(void) {
	__pStarsList ->RemoveAllItems();
	Osp::Base::Collection::IEnumerator* starNames = SkyCanvas::getStars()->GetEnumeratorN();
	String emptyString;
	__pStarsList -> AddItem(&emptyString, &emptyString, null, null, null);
	while (starNames -> MoveNext() == E_SUCCESS) {
		String starName;
		String* starNameAbbr = (String*) starNames -> GetCurrent();
		String constAcronym;
		String constName;
		String greekLetter;

		starNameAbbr -> SubString(0, 3, greekLetter);
		starNameAbbr -> SubString(4, constAcronym);

		AppResource* appResource = Application::GetInstance()->GetAppResource();
		appResource->GetString(*starNameAbbr, starName);
		appResource->GetString(constAcronym, constName);

		starName.Append(" (");
		starName.Append(GetGreek(greekLetter));
		starName.Append(" ");
		starName.Append(constName);
		starName.Append(")");

//		__pStarsList -> AddItem(&starName, &starName, null, null, null);
//		result	AddItem(
//				const Osp::Base::String* pText1,
//				const Osp::Base::String* pText2,
//				const Osp::Graphics::Bitmap* pBitmap1,
//				const Osp::Graphics::Bitmap* pBitmap2,
//				int itemId = LIST_ITEM_UNSPECIFIED_ID);

		Osp::Graphics::Bitmap* bitmapButtonPressed;
		Osp::App::AppResource* pAppResource = Osp::App::Application::GetInstance()->GetAppResource();
		bitmapButtonPressed = pAppResource -> GetBitmapN(L"ButtonPressed.png");

		__pStarsList -> AddItem(&starName, null, bitmapButtonPressed, bitmapButtonPressed, null);

	}
}

void
StarForm::OnItemStateChanged(const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status) {
	AppLog("StarForm::OnItemStateChanged(%d)", index);
	SkyCanvas::SelectStar(index-1);
	Osp::App::Application::GetInstance() -> SendUserEvent(EVENT_STAR_SELECTED, null);
}

String&
StarForm::GetGreek(String& greekTranslit) {
	if (greekTranslit.Equals(L"ALP", false)) {
		return STRING_ALPHA;
	} else if (greekTranslit.Equals(L"BET", false)) {
		return STRING_BETA;
	} else if (greekTranslit.Equals(L"GAM", false)) {
		return STRING_GAMMA;
	} else {
		return STRING_UNDEF;
	}
}


