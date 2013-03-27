
#include "EarthMapForm.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;


EarthMapForm::EarthMapForm(void)
{
}

EarthMapForm::~EarthMapForm(void)
{
}

bool
EarthMapForm::Initialize()
{
	Form::Construct(L"EARTH_MAP_FORM");

	return true;
}

result
EarthMapForm::OnInitializing(void)
{
	result r = E_SUCCESS;

//	Osp::Graphics::Bitmap* map = new Bitmap();
//	map -> Construct()

	return r;
}

result
EarthMapForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}



void
EarthMapForm::OnTouchDoublePressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
EarthMapForm::OnTouchFocusIn(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
EarthMapForm::OnTouchFocusOut(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
EarthMapForm::OnTouchLongPressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
EarthMapForm::OnTouchMoved(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
EarthMapForm::OnTouchPressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}

void
EarthMapForm::OnTouchReleased(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{
	// TODO: Add your implementation codes here

}
