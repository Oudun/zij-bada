/*
 * Sky.cpp
 *
 *  Created on: 21.02.2012
 *      Author: ddreval
 */

#include "Sky.h"
#include "SkyIterator.h"
#include "SkyFactory.h"

using namespace Osp::System;
using namespace Osp::App;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Locations;
using namespace Osp::Io;
using namespace Osp::Base;
using namespace Osp::Base::Utility;
using namespace Osp::Locales;
using namespace Osp::Graphics;

//static Osp::Graphics::Color COLOR_CHOST = Osp::Graphics::Color(48,48,144);
static Osp::Graphics::Color COLOR_CHOST = Osp::Graphics::Color(67,136,204);

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
			Rectangle(zenithX-radius, zenithY-radius, 2+2*radius, 2+2*radius));
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

float Sky::getLatitude() const
{
    return latitude;
}

float Sky::getLongitude() const
{
    return longitude;
}

void Sky::setLatitude(float latitude)
{
    this->latitude = latitude;
}

void Sky::setLongitude(float longitude)
{
    this->longitude = longitude;
	TimeZone timeZone(60, L"Europe/London");
	DateTime* currTime = new DateTime();
	SystemTime::GetCurrentTime(*currTime);
	Calendar* calendar = Calendar::CreateInstanceN(timeZone, CALENDAR_GREGORIAN);
	calendar->SetTime(*currTime);
	float hrs = (calendar->GetTimeField(TIME_FIELD_HOUR_OF_DAY))-1;
	float minHrs = calendar->GetTimeField(TIME_FIELD_MINUTE)/60.0;
	float dayFract = (hrs + minHrs)/24.0;
	float dayNum = calendar->GetTimeField(TIME_FIELD_DAY_OF_YEAR);
	float year = calendar->GetTimeField(TIME_FIELD_YEAR);
	double daysSinceJ2000 = -1.5 + dayNum + (year-2000)*365 + (int)((year-2000)/4) + dayFract;
	double slt = 100.46 + 0.985647 * daysSinceJ2000 + longitude + 15*(hrs + minHrs);
	int sltInt = (int)(slt/360);
	this -> siderialHours = (slt-(360*sltInt))/15;
	AppLog("Local Siderial Time is %f hrs", siderialHours);
	AppLog("Local Siderial Time is %f degrees", slt);
}

float
Sky::getSiderialHours() const
{
    return siderialHours;
}

void
Sky::setSiderialHours(float siderialHours)
{
    this->siderialHours = siderialHours;
}

void
Sky::draw(void)
{
	paintBorders();
	SkyIterator* stars;
	stars = SkyFactory::getStars(1);
	while(stars->hasNext()) {
		stars->getNext()-> draw(this);
	}
	stars = SkyFactory::getStars(2);
	while(stars->hasNext()) {
		stars->getNext()-> draw(this);
	}
	stars = SkyFactory::getStars(3);
	while(stars->hasNext()) {
		stars->getNext()-> draw(this);
	}
	stars = SkyFactory::getStars(4);
	while(stars->hasNext()) {
		stars->getNext()-> draw(this);
	}
}





