/*
 * StarForm.cpp
 *
 *  Created on: 08.02.2015
 *      Author: Denis
 */

#include "forms/StarForm.h"

using namespace Osp::Base::Collection;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;
using namespace Osp::App;

StarForm::StarForm() {
	starNameComparer = new StarNameComparer();
	constellationNameComparer = new ConstellationNameComparer();
	starBrightnessComparer = new StarBrightnessComparer();
}

StarForm::~StarForm() {
	delete starNameComparer;
	delete constellationNameComparer;
	delete starBrightnessComparer;
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
			Rectangle(0, 0, 240, 340),
			LIST_STYLE_NORMAL,
			LIST_ITEM_SINGLE_TEXT, 48, 48, 200, 0);
	__pStarsList -> AddItemEventListener(*this);
	__pStarsList -> SetBackgroundColor(COLOR_FORM_BKG);
	__pStarsList -> SetItemTextColor(LIST_ITEM_TEXT1, COLOR_FORM_TEXT);
	__pStarsList -> SetItemTextColor(LIST_ITEM_TEXT2, COLOR_FORM_TEXT);
	AddControl(*__pStarsList);

//	__pButtonZoomIn = static_cast<Button *>(GetControl(L"IDC_BUTTON_ZOOM_IN"));
//	__pButtonZoomIn -> SetNormalBackgroundBitmap(*bitmapZoomIn);
//	__pButtonZoomIn -> SetPressedBackgroundBitmap(*bitmapZoomInPressed);
//	__pButtonZoomIn -> SetActionId(ID_BUTTON_ZOOM_IN);
//	__pButtonZoomIn -> AddActionEventListener(*this);

	__buttonSortBrightness = static_cast<Button *>(GetControl(L"IDC_BUTTON_SORT_BRIGHTNESS"));
	__buttonSortBrightness -> SetActionId(ID_BUTTON_SORT_BRIGHTNESS);
	__buttonSortBrightness -> AddActionEventListener(*this);

	__buttonSortConstellation = static_cast<Button *>(GetControl(L"IDC_BUTTON_SORT_CONSTELLATION"));
	__buttonSortConstellation -> SetActionId(ID_BUTTON_SORT_CONSTELLATION);
	__buttonSortConstellation -> AddActionEventListener(*this);

	__buttonSortStarName = static_cast<Button *>(GetControl(L"IDC_BUTTON_SORT_NAME"));
	__buttonSortStarName -> SetActionId(ID_BUTTON_SORT_NAME);
	__buttonSortStarName -> AddActionEventListener(*this);

	return E_SUCCESS;

}

void
StarForm::Update(Osp::Base::Collection::IList* starsList) {
	__pStarsList ->RemoveAllItems();
	Osp::Base::Collection::IEnumerator* starNames = starsList ->GetEnumeratorN();
	String emptyString;
	__pStarsList -> AddItem(&emptyString, &emptyString, null, null, null);
	while (starNames -> MoveNext() == E_SUCCESS) {
		String starName;
		String* starNameAbbr = (String*) starNames -> GetCurrent();
		String constAcronym;
		String constName;
		String starConstAcronym;
		String greekLetter;

		starNameAbbr -> SubString(0, 3, greekLetter);
		starNameAbbr -> SubString(4, 3, constAcronym);
		starNameAbbr -> SubString(0, 7, starConstAcronym);

		AppResource* appResource = Application::GetInstance()->GetAppResource();
		appResource->GetString(starConstAcronym, starName);
		appResource->GetString(constAcronym, constName);

		AppLog("Constellation for %S is %S", constAcronym.GetPointer(), constName.GetPointer());
		AppLog("Star for %S is %S", starConstAcronym.GetPointer(), starName.GetPointer());

		starName.Append(" (");
		starName.Append(GetGreek(greekLetter));
		starName.Append(" ");
		starName.Append(constName);
		starName.Append(")");

		Osp::Graphics::Bitmap* bitmapButtonPressed;
		Osp::App::AppResource* pAppResource = Osp::App::Application::GetInstance()->GetAppResource();
		bitmapButtonPressed = pAppResource -> GetBitmapN(L"ButtonPressed.png");

		__pStarsList -> AddItem(&starName, null, bitmapButtonPressed, bitmapButtonPressed, null);

	}
}

void
StarForm::Update(void) {
	Update(SkyCanvas::getStars());
}

void
StarForm::OnItemStateChanged(const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status) {
	AppLog("StarForm::OnItemStateChanged(%d)", index);
	SkyCanvas::SelectStar(index-1);
	Osp::App::Application::GetInstance() -> SendUserEvent(EVENT_STAR_SELECTED, null);
}

void
StarForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId) {
	switch (actionId) {
		case ID_BUTTON_SORT_BRIGHTNESS: {
			AppLog("ID_BUTTON_SORT_BRIGHTNESS pressed");
			ArrayList* stars = (ArrayList*)SkyCanvas::getStars();
			stars -> Sort(*starBrightnessComparer);
			Update(stars);
			RequestRedraw(true);
			break;
		}
		case ID_BUTTON_SORT_CONSTELLATION: {
			AppLog("ID_BUTTON_SORT_CONSTELLATION pressed");
			ArrayList* stars = (ArrayList*)SkyCanvas::getStars();
			stars -> Sort(*constellationNameComparer);
			Update(stars);
			RequestRedraw(true);
			break;
		}
		case ID_BUTTON_SORT_NAME: {
			AppLog("ID_BUTTON_SORT_NAME pressed");
			ArrayList* stars = (ArrayList*)SkyCanvas::getStars();
			stars -> Sort(*starNameComparer);
			Update(stars);
			RequestRedraw(true);
			break;
		}
	}
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


