
#include "CitiesForm.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;


CitiesForm::CitiesForm(void)
{
}

CitiesForm::~CitiesForm(void)
{
}

bool
CitiesForm::Initialize()
{
	Form::Construct(L"CITIES_FORM");

	return true;
}

result
CitiesForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO: Add your initialization code here

	return r;
}

result
CitiesForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}


