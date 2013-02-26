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

//int Sky::getRadius() const {
//	AppLog("Get Radius");
//    return radius;
//}
//
//int Sky::getZenithX() const {
//	AppLog("Get Zenith X");
//    return zenithX;
//}
//
//int Sky::getZenithY() const {
//	AppLog("Get Zenith Y");
//    return zenithY;
//}
//
//void Sky::setRadius(int radius) {
//	AppLog("Set Radius");
//    this->radius = radius;
//}
//
//float Sky::getLatitude() const {
//	AppLog("Get Latitude");
//    return latitude;
//}
//
//float Sky::getLongitude() const {
//	AppLog("Get Longitude");
//    return longitude;
//}
//
//void Sky::setLatitude(float latitude) {
//	AppLog("Set Latitude");
//    this->latitude = latitude;
//}
//
//void Sky::setLongitude(float longitude) {
//	AppLog("Set Longitude");
//    this->longitude = longitude;
//	TimeZone timeZone(60, L"Europe/London");
//	DateTime* currTime = new DateTime();
//	SystemTime::GetCurrentTime(*currTime);
//	Calendar* calendar = Calendar::CreateInstanceN(timeZone, CALENDAR_GREGORIAN);
//	calendar->SetTime(*currTime);
//	float hrs = (calendar->GetTimeField(TIME_FIELD_HOUR_OF_DAY))-1;
//	float minHrs = calendar->GetTimeField(TIME_FIELD_MINUTE)/60.0;
//	float dayFract = (hrs + minHrs)/24.0;
//	float dayNum = calendar->GetTimeField(TIME_FIELD_DAY_OF_YEAR);
//	float year = calendar->GetTimeField(TIME_FIELD_YEAR);
//	double daysSinceJ2000 = -1.5 + dayNum + (year-2000)*365 + (int)((year-2000)/4) + dayFract;
//	double slt = 100.46 + 0.985647 * daysSinceJ2000 + longitude + 15*(hrs + minHrs);
//	int sltInt = (int)(slt/360);
//	this -> siderialHours = (slt-(360*sltInt))/15;
//	AppLog("Local Siderial Time is %f hrs", siderialHours);
//	AppLog("Local Siderial Time is %f degrees", slt);
//}
//
//float
//Sky::getSiderialHours() const {
//	AppLog("Get siderial hours");
//    return siderialHours;
//}
//
//void
//Sky::setSiderialHours(float siderialHours) {
//	AppLog("Set siderial hours");
//    this->siderialHours = siderialHours;
//}

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
	Osp::Graphics::Canvas* bufferedCanvas = skyCanvas -> GetBufferedCanvas(zoom);	//Getting buffered canvas for given zoom
	Osp::Graphics::Point point(0, 0);									//Setting start point as top left
	canvas->Copy(point, *bufferedCanvas, rect);							//Copy buffered canvas into current
	canvas->Show();
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




