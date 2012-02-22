/*
 * Sky.cpp
 *
 *  Created on: 21.02.2012
 *      Author: ddreval
 */

#include "../inc/Sky.h"

using namespace Osp::Base;
using namespace Osp::Base::Utility;
using namespace Osp::Graphics;

static Osp::Graphics::Color COLOR_CHOST = Osp::Graphics::Color(48,48,144);

Sky::Sky() {
	// TODO Auto-generated constructor stub

}

Sky::Sky(Osp::Graphics::Canvas* aCanvas) {
	canvas = aCanvas;
	Osp::Graphics::Rectangle rect1 = canvas->GetBounds();
	AppLog("Settng sky %d %d %d %d", rect1.x, rect1.y, rect1.width, rect1.height);
	radius = (Math::Min(rect1.width, rect1.height) - margin*2)/2;
	zenithX = rect1.x + margin + radius;
	zenithY = rect1.y + 2*margin + radius;
}

Sky::~Sky() {
	// TODO Auto-generated destructor stub
}

void
Sky::paintBorders(void) {
	canvas->SetLineWidth(1);
	canvas->SetForegroundColor(COLOR_CHOST);
//	canvas->DrawEllipse(Rectangle(margin, 2*margin, 2*radius, 2*radius));
	canvas->DrawEllipse(
			Rectangle(zenithX-radius, zenithY-radius, 2*radius, 2*radius));
	canvas->Show();
}

Osp::Graphics::Canvas*
Sky::getCanvas(void) {
	return canvas;
}

int Sky::getRadius() const
{
    return radius;
}

int Sky::getZenithX() const
{
    return zenithX;
}

int Sky::getZenithY() const
{
    return zenithY;
}

void Sky::setRadius(int radius)
{
    this->radius = radius;
}


