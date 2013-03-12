/*
 * Sky.cpp
 *
 *  Created on: 21.02.2012
 *      Author: ddreval
 */

#include "Sky.h"
#include "SkyFactory.h"

using namespace Osp::System;
using namespace Osp::App;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Locations;
using namespace Osp::Io;
using namespace Osp::Base;
using namespace Osp::Base::Utility;
using namespace Osp::Base::Collection;
using namespace Osp::Locales;
using namespace Osp::Graphics;

//static Osp::Graphics::Color COLOR_CHOST = Osp::Graphics::Color(48,48,144);
static Osp::Graphics::Color COLOR_CHOST = Osp::Graphics::Color(67,136,204);

Sky::Sky() {
	AppLog("Sky default constructor");
}

Sky::Sky(Osp::Graphics::Canvas* aCanvas, SkyCanvas* aSkyCanvas) {
	AppLog("Sky Created");
	skyCanvas = aSkyCanvas;
	canvas = aCanvas;
	bitmap = new Bitmap();
	Osp::Graphics::Rectangle rect1 = canvas->GetBounds();
	zoom = 1;
	busy = false;
	AppLog("Setting sky %d %d %d %d %d", rect1.x, rect1.y, rect1.width, rect1.height, zoom);
	originalRadius = (Math::Min(rect1.width, rect1.height) - margin*2)/2;
	radius = zoom * originalRadius;
	zenithX = rect1.width/2; //rect1.x + margin + radius;
	zenithY = rect1.height/2; //rect1.y + 2*margin + radius;
	visibleConst = new ArrayList();
}

Sky::~Sky() {
	AppLog("Sky destroyer");
	// TODO Auto-generated destructor stub
}

void
Sky::paintBorders(void) {
	AppLog("Sky Borders");
	canvas->SetLineWidth(1);
	canvas->SetForegroundColor(COLOR_CHOST);
	canvas->DrawEllipse(
			Rectangle(zenithX-radius, zenithY-radius, 2+2*radius, 2+2*radius));
	canvas->Show();
}

Osp::Graphics::Canvas*
Sky::getCanvas(void) {
	AppLog("getting canvas");
	return canvas;
}

/**
 * If sky instance is cached for given zoom value, use this
 * If not - get current stars set and draw them, display and place result to cache
 */
void
Sky::draw(void) {
	AppLog(">>Sky::draw with zoom %d", zoom);
	busy = true;
	canvas->Clear();
	AppLog("Canvas for zoom %d is buffered", zoom);
	Osp::Graphics::Rectangle rect = getCanvas()->GetBounds();			//Getting size of current canvas
	AppLog("1");
	Osp::Graphics::Canvas* bufferedCanvas = skyCanvas -> GetBufferedCanvas(zoom);	//Getting buffered canvas for given zoom
	AppLog("2");
	Osp::Graphics::Point point(0, 0);									//Setting start point as top left
	AppLog("3");
	canvas->Copy(point, *bufferedCanvas, rect);							//Copy buffered canvas into current
	AppLog("4");
	result r;
	r = canvas->Show();
	AppLog("Canvas show result is %S", GetErrorMessage(r));
	AppLog("5");
	busy = false;
}

void
Sky::zoomIn() {
	AppLog("Zooming in");
	if (!busy) {
		zoom *= 2;
		radius = zoom * originalRadius;
		AppLog("Zoom In %d", zoom);
		draw();
	} else {
		AppLog("busy");
	}
}

void
Sky::zoomOut() {
	AppLog("Zooming out");
	if (!busy) {
		zoom = (int)(zoom/2);
		radius = zoom * originalRadius;
		AppLog("Zoom In %d", zoom);
		draw();
	} else {
		AppLog("busy");
	}
}

bool
Sky::canZoomIn() {
	AppLog("can Zooming in");
	return zoom < max_zoom;
}

bool
Sky::canZoomOut() {
	AppLog("can Zooming out");
	return zoom > min_zoom;
}

Osp::Base::Collection::IList*
Sky::getConst(void) {
	AppLog("List const");
	return visibleConst;
}




