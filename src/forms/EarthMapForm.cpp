
#include "forms/EarthMapForm.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::App;
using namespace Osp::Graphics;

EarthMapForm::EarthMapForm(void)
{
}

EarthMapForm::~EarthMapForm(void)
{
}

bool
EarthMapForm::Initialize()
{
	Construct(L"EARTH_MAP_FORM");
	return true;
}

result
EarthMapForm::OnInitializing(void)
{
	result r = E_SUCCESS;
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
EarthMapForm::Update(void) {
	Control* control = GetControl(L"EARTH_MAP_FORM");
	Canvas* canvas;
	canvas = control -> GetCanvasN();

	Osp::App::AppResource* appResource = Osp::App::AppResource::GetInstance();
	Osp::Graphics::Bitmap* mapImage = appResource -> GetBitmapN("earth.png");

	Osp::Graphics::Point topLeft(0, 70);
	canvas -> DrawBitmap(topLeft, *mapImage);

//	canvas -> DrawLine(Osp::Graphics::Point(0, 0), Osp::Graphics::Point(100, 100));
	canvas -> Show();

}

void
EarthMapForm::OnTouchDoublePressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{


}

void
EarthMapForm::OnTouchFocusIn(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{


}

void
EarthMapForm::OnTouchFocusOut(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{


}

void
EarthMapForm::OnTouchLongPressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{


}

void
EarthMapForm::OnTouchMoved(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{


}

void
EarthMapForm::OnTouchPressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{


}

void
EarthMapForm::OnTouchReleased(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{


}
