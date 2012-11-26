
#include "SkyBuilderForm.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;


SkyBuilderForm::SkyBuilderForm(TimeAndPlace* pTimeAndPlace) {
	timeAndPlace = pTimeAndPlace;
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
	result r = E_SUCCESS;
	__pStarsProgress = static_cast<Progress *>(GetControl("IDC_PROGRESS1"));
	r = skyBuilder -> Start();
	AppLog("");
	return r;
}

result
SkyBuilderForm::OnTerminating(void) {
	result r = E_SUCCESS;
	return r;
}

void
SkyBuilderForm::SetRange(int min, int max) {
	__pStarsProgress -> SetRange(min, max);
}

void
SkyBuilderForm::SetProgress(int value) {
	__pStarsProgress -> SetValue(value);
}




