
#include "forms/StarHelpForm.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::App;
using namespace Osp::Graphics;

StarHelpForm::StarHelpForm(void)
{
}

StarHelpForm::~StarHelpForm(void)
{
}

bool
StarHelpForm::Initialize()
{
	Form::Construct(L"STAR_HELP_FORM");
	return true;
}

result
StarHelpForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	SetBackgroundColor(COLOR_FORM_BKG);

	AppResource* pAppResource = Application::GetInstance()->GetAppResource();

	Bitmap* __bitmapSortByBrightness = pAppResource -> GetBitmapN(L"SortByBrightness.png");
	Bitmap* __bitmapSortByStarName = pAppResource -> GetBitmapN(L"SortByStarName.png");
	Bitmap* __bitmapSortByConstName = pAppResource -> GetBitmapN(L"SortByConstName.png");
	Bitmap* __bitmapButton = pAppResource -> GetBitmapN(L"Button.png");
	Bitmap* __bitmapButtonPressed = pAppResource -> GetBitmapN(L"ButtonPressed.png");

	Label* __labelSortByBrightness = static_cast<Label *>(GetControl(L"IDC_LABEL_BRIGHTNESS_ICON"));
	__labelSortByBrightness -> SetBackgroundBitmap(*__bitmapSortByBrightness);

	Label* __labelSortByName = static_cast<Label *>(GetControl(L"IDC_LABEL_NAME_ICON"));
	__labelSortByName -> SetBackgroundBitmap(*__bitmapSortByStarName);

	Label* __labelSortByConstName = static_cast<Label *>(GetControl(L"IDC_LABEL_CONST_NAME_ICON"));
	__labelSortByConstName -> SetBackgroundBitmap(*__bitmapSortByConstName);

	Label* __labelSortByBrightnessText = static_cast<Label *>(GetControl(L"IDC_LABEL_BRIGHTNESS_TEXT"));
	__labelSortByBrightnessText -> SetBackgroundColor(COLOR_FORM_BKG);
	__labelSortByBrightnessText -> SetTextColor(COLOR_FORM_TEXT);
	__labelSortByBrightnessText -> SetText(Constants::GetString(STRING_SORT_STAR_BRIGHTNESS));

	Label* __labelSortByNameText = static_cast<Label *>(GetControl(L"IDC_LABEL_NAME_TEXT"));
	__labelSortByNameText -> SetBackgroundColor(COLOR_FORM_BKG);
	__labelSortByNameText -> SetTextColor(COLOR_FORM_TEXT);
	__labelSortByNameText -> SetText(Constants::GetString(STRING_SORT_STAR_NAME));

	Label* __labelSortByConstNameText = static_cast<Label *>(GetControl(L"IDC_LABEL_CONST_NAME_TEXT"));
	__labelSortByConstNameText -> SetBackgroundColor(COLOR_FORM_BKG);
	__labelSortByConstNameText -> SetTextColor(COLOR_FORM_TEXT);
	__labelSortByConstNameText -> SetText(Constants::GetString(STRING_SORT_STAR_CONST_NAME));

	Button* __buttonBack;
	__buttonBack = static_cast<Button *>(GetControl(L"IDC_BUTTON_CLOSE"));
	__buttonBack -> SetActionId(0);
	__buttonBack -> SetNormalBackgroundBitmap(*__bitmapButton);
	__buttonBack -> SetPressedBackgroundBitmap(*__bitmapButtonPressed);
	__buttonBack -> SetTextColor(COLOR_BUTTON_TEXT);
	__buttonBack -> AddActionEventListener(*this);
	__buttonBack -> SetText(Constants::GetString(STRING_BACK));

	return r;

}

result
StarHelpForm::OnTerminating(void)
{
	result r = E_SUCCESS;
	return r;
}

void
StarHelpForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId) {
	Osp::App::Application::GetInstance() -> SendUserEvent(EVENT_STAR_HELP_CLOSED, null);
}

