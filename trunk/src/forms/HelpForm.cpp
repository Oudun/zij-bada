
#include "forms/HelpForm.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;


HelpForm::HelpForm(void)
{
}

HelpForm::~HelpForm(void)
{
}

bool
HelpForm::Initialize()
{
	Form::Construct(L"HELP_FORM");

	return true;
}

result
HelpForm::OnInitializing(void)
{
	result r = E_SUCCESS;
	SetBackgroundColor(COLOR_FORM_BKG);

	Osp::App::AppResource* pAppResource = Osp::App::Application::GetInstance()->GetAppResource();
	Osp::Graphics::Bitmap* bitmapButton;
	Osp::Graphics::Bitmap* bitmapButtonPressed;
	bitmapButton = pAppResource -> GetBitmapN(L"Button.png");
	bitmapButtonPressed = pAppResource -> GetBitmapN(L"ButtonPressed.png");

	Button* __buttonBack;
	__buttonBack = static_cast<Button *>(GetControl(L"IDC_BUTTON_BACK"));
	__buttonBack -> SetActionId(0);
	__buttonBack -> SetNormalBackgroundBitmap(*bitmapButton);
	__buttonBack -> SetPressedBackgroundBitmap(*bitmapButtonPressed);
	__buttonBack -> SetTextColor(COLOR_BUTTON_TEXT);
	__buttonBack -> AddActionEventListener(*this);
	__buttonBack -> SetText(Constants::GetString(STRING_BACK));

	Label* __label = static_cast<Label *>(GetControl(L"IDC_LABEL"));
	__label -> SetBackgroundColor(COLOR_FORM_BKG);
	__label -> SetTextColor(COLOR_FORM_TEXT);
	__label -> SetText(Constants::GetString(STRING_HELP));

	return r;

}

result
HelpForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void
HelpForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId) {
	Osp::App::Application::GetInstance() -> SendUserEvent(EVENT_HELP_CLOSED, null);
}

