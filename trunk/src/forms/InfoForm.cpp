
#include "forms/InfoForm.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;


InfoForm::InfoForm(void)
{
}

InfoForm::~InfoForm(void)
{
}

bool
InfoForm::Initialize()
{
	Form::Construct(L"INFO_FORM");

	return true;
}

result
InfoForm::OnInitializing(void)
{
	result r = E_SUCCESS;
	SetBackgroundColor(COLOR_FORM_BKG);

	Osp::App::AppResource* pAppResource = Osp::App::Application::GetInstance()->GetAppResource();
	Osp::Graphics::Bitmap* bitmapEmpty;
	bitmapEmpty = pAppResource -> GetBitmapN(L"Empty.png");

	Button* __buttonBack;
	__buttonBack = static_cast<Button *>(GetControl(L"IDC_BUTTON_BACK"));
	__buttonBack -> SetActionId(0);
	__buttonBack -> SetNormalBackgroundBitmap(*bitmapEmpty);
	__buttonBack -> SetPressedBackgroundBitmap(*bitmapEmpty);
	__buttonBack -> SetTextColor(COLOR_BUTTON_TEXT);
	__buttonBack -> AddActionEventListener(*this);

	return r;
}


result
InfoForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void
InfoForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId) {
	Osp::App::Application::GetInstance() -> SendUserEvent(EVENT_HELP_CLOSED, null);
}
