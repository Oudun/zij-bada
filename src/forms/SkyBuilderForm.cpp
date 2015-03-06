
#include "forms/SkyBuilderForm.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;
using namespace Osp::App;

SkyBuilderForm::SkyBuilderForm() {
	skyBuilder = new SkyBuilder();
	skyBuilder -> Construct();
}

SkyBuilderForm::~SkyBuilderForm(void) {

}

bool
SkyBuilderForm::Initialize() {
	Form::Construct(L"SKY_BUILDER_FORM");
	return true;
}

result
SkyBuilderForm::OnInitializing(void) {

	AppLog("Initializing Sky Builder Form");

	result r = E_SUCCESS;

	SetBackgroundColor(COLOR_FORM_BKG);

	__pStarsProgress = static_cast<Progress *>(GetControl("IDC_PROGRESS1"));
	__label = static_cast<Label *>(GetControl("IDC_LABEL1"));
	__label -> SetBackgroundColor(COLOR_FORM_BKG);
	__label -> SetTextColor(COLOR_FORM_TEXT);
	__label -> SetText(Constants::GetString(STRING_BUILDING_SKY));

	AppLog("Initializing Sky Builder Form - done");

	return r;
}

void
SkyBuilderForm::Start(void) {
	skyBuilder -> Start();
}

result
SkyBuilderForm::OnTerminating(void) {
	result r = E_SUCCESS;
	return r;
}

void
SkyBuilderForm::SetRange(int min, int max) {
	__pStarsProgress -> SetRange(min, max);
	__pStarsProgress -> SetValue(min);
	__pStarsProgress -> RequestRedraw(true);
}

void
SkyBuilderForm::SetProgress(int value) {
	int max;
	int min;
	__pStarsProgress -> GetRange(min, max);
	__pStarsProgress -> SetValue(value);
	__pStarsProgress -> RequestRedraw(true);

}


result
SkyBuilderForm::OnDraw(void) {
	AppResource* pAppResource = Application::GetInstance()->GetAppResource();
	Bitmap* bitmapBackground = pAppResource -> GetBitmapN(L"FormBackground.png");
	Canvas* canvas = GetCanvasN();
	result r = canvas -> DrawBitmap(GetBounds(), *bitmapBackground);
	return r;
}


