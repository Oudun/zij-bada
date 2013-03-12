
#include "SkyBuilderForm.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;


SkyBuilderForm::SkyBuilderForm(SkyCanvas* pSkyCanvas) {
	skyBuilder = new SkyBuilder(pSkyCanvas);
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
	result r = E_SUCCESS;
	__pStarsProgress = static_cast<Progress *>(GetControl("IDC_PROGRESS1"));
	__pStarsProgress -> SetBarColor(Osp::Graphics::Color::COLOR_VIOLET);
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
//	AppLog("Real min = %d, max=%d", min, max);
	__pStarsProgress -> SetValue(value);
	__pStarsProgress -> RequestRedraw(true);
}




