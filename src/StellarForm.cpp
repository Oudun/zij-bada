/*
 * StellarForm.cpp
 *
 *  Created on: 04.03.2013
 *      Author: ddreval
 */

#include "StellarForm.h"

using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;

StellarForm::StellarForm(SkyCanvas* aSkyCanvas) {
	skyCanvas = aSkyCanvas;
}

StellarForm::~StellarForm() {
	// TODO Auto-generated destructor stub
}

bool
StellarForm::Initialize(void) {
	Bitmap* bitmap;
	Construct(L"STELLAR_FORM");
	return true;
}

result
StellarForm::OnInitializing(void) {
	Button *pButton1 = static_cast<Button *>(GetControl("IDC_BUTTON1"));  
	if (pButton1)
	{
		pButton1->SetActionId(1);
		pButton1->AddActionEventListener(*this);
	}
	return E_SUCCESS;
}

void
StellarForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId) {
	AppLog("LocationForm::OnInitializing(void)");
}

void
StellarForm::DoIt(void) {
	Osp::Graphics::Canvas* canvas;
	Control* control = GetControl(L"STELLAR_FORM");
	canvas = control -> GetCanvasN();
	Osp::Graphics::Rectangle rect = canvas -> GetBounds();						//Getting size of current canvas
	Osp::Graphics::Canvas* bufferedCanvas = skyCanvas -> GetBufferedCanvas(1);	//Getting buffered canvas for given zoom
	Osp::Graphics::Point point(0, 0);											//Setting start point as top left
	canvas->Copy(point, *bufferedCanvas, rect);
	canvas -> Show();
}
