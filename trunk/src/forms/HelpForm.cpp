
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

	// TODO: Add your initialization code here

	return r;
}

result
HelpForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}


