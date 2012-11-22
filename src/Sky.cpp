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
	// TODO Auto-generated constructor stub

}

Sky::Sky(Osp::Graphics::Canvas* aCanvas) {
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
	// TODO Auto-generated destructor stub
}

void
Sky::paintBorders(void) {
	canvas->SetLineWidth(1);
	canvas->SetForegroundColor(COLOR_CHOST);
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

/**
 * If sky instance is cached for given zoom value, use this
 * If not - get current stars set and draw them, display and place result to cache
 */
void
Sky::draw(void)
{
	AppLog(">>Sky::draw with zoom %d", zoom);
	busy = true;
	canvas->Clear();
	if (getBufferedCanvas(zoom)!=null) {
		Osp::Graphics::Rectangle rect = getCanvas()->GetBounds();			//Getting size of current canvas
		Osp::Graphics::Canvas* bufferedCanvas = getBufferedCanvas(zoom);	//Getting buffered canvas for given zoom
		Osp::Graphics::Point point(0, 0);									//Setting start point as top left
		canvas->Copy(point, *bufferedCanvas, rect);							//Copy buffered canvas into current
	    canvas->Show();
	    busy = false;
	} else {
		paintBorders();
		SkyIterator* stars;
		stars = SkyFactory::getStars(3);
		while(stars->hasNext()) {
			//stars->getNext()-> draw(this);
			draw(stars->getNext());
		}
		if (zoom > 1) {
			stars = SkyFactory::getStars(4);
			while(stars->hasNext()) {
				//stars->getNext()-> draw(this);
				draw(stars->getNext());
			}
		}
		if (zoom > 2) {
			stars = SkyFactory::getStars(6);
			while(stars->hasNext()) {
				//stars->getNext()-> draw(this);
				draw(stars->getNext());
			}
		}
		busy = false;
		AppLog("<<Sky::draw with zoom %d", zoom);
	}
}

void
Sky::draw(SkyObject* skyObject) {
	AppLog(">>SkyObject.Draw()");
	float lstDeg = 15*(getSiderialHours());
	float raDeg = skyObject->getRAH() * 15; // 24 hours is 360 degrees, so 1 hour is 15 degrees
	float ha = lstDeg > raDeg ? lstDeg - raDeg : 360 + lstDeg - raDeg;
	double radInDegree = 0.0174532925;
	float decSigned = skyObject->isNorthern() ? skyObject->getDED(): -(skyObject->getDED());
    double sinAlt =
        Math::Sin(radInDegree*decSigned)*Math::Sin(radInDegree*(getLatitude()))
        +Math::Cos(radInDegree*decSigned)*Math::Cos(radInDegree*(getLatitude()))*Math::Cos(radInDegree*(ha));
    double cosAlt =
        Math::Sqrt(1-sinAlt*sinAlt);
    double sinAz =
        -(Math::Sin(radInDegree*(ha))*Math::Cos(radInDegree*(decSigned)))/cosAlt;
    double cosAz =
        (Math::Sin(radInDegree*decSigned)-Math::Sin(radInDegree*(getLatitude()))*sinAlt)/
            (Math::Cos(radInDegree*(getLatitude()))*cosAlt);
    double R = getRadius();
    double r = R * cosAlt;
    int top  = (int)((getZenithY()) - r * cosAz);
    int left = (int)((getZenithX()) - r * sinAz);
    int width = getCanvas()->GetBounds().width;
    int height = getCanvas()->GetBounds().height;
    int zoom = getZoom();
    Osp::Graphics::Canvas* bufferedCanvas = getBufferedCanvas(zoom);

    if (bufferedCanvas == null) {
    	bufferedCanvas = new Canvas();
    	Osp::Graphics::Rectangle* rect = new Osp::Graphics::Rectangle();
    	rect->SetBounds(0, 0 , width, height);
    	bufferedCanvas->Construct(*rect);
    	setBufferedCanvas(bufferedCanvas, zoom);
    }
    int addition = zoom == 1 ? 0 : (zoom == 2) ? 1 : 2;
    Font pFont;
	pFont.Construct(FONT_STYLE_PLAIN, 12);
    bufferedCanvas->SetFont(pFont);
    bufferedCanvas->SetForegroundColor(Color::COLOR_GREY);

    Osp::Graphics::Color starColor;
    if (skyObject->getName().EndsWith("UMa")) {
    	starColor = Color::COLOR_YELLOW;
    } else if (skyObject->getName().EndsWith("Ori")) {
    	starColor = Color::COLOR_MAGENTA;
    } else if (skyObject->getName().EndsWith("Lyr")) {
    	starColor = Color::COLOR_GREEN;
    } else if (skyObject->getName().EndsWith("Cas")) {
    	starColor = Color::COLOR_MAGENTA;
    } else if (skyObject->getName().EndsWith("Peg")) {
    	starColor = Color::COLOR_CYAN;
    } else if (skyObject->getName().EndsWith("Ind")) {
        	starColor = Color::COLOR_RED;
    } else {
    	starColor = Color::COLOR_WHITE;
    }

    if (sinAlt > 0) {
    	if (left<0||top<0||left>width||top>height) {
    		return;
    	}
    	String* constName = new String(skyObject->getName());
    	if (getConst()->Contains(*constName)) {
    		AppLog("!!!Constellation %S is in list %d", skyObject->getName().GetPointer(), getConst()->GetCount());
    		delete constName;
    	} else {
    		AppLog("!!!Constellation %S is added to list %d", skyObject->getName().GetPointer(), skyObject->getName().GetPointer(), getConst()->GetCount());
    		getConst()->Add(*constName);
    	}
    	if (skyObject->getMagnitude() < 1) {
    		bufferedCanvas->FillEllipse(starColor, Rectangle(left,top,3+addition,3+addition));
			bufferedCanvas->DrawText(Point(left-8, top+8), skyObject->getName());
		} else if (skyObject->getMagnitude() < 2) {
			bufferedCanvas->FillEllipse(starColor, Rectangle(left,top,2+addition,2+addition));
		} else if (skyObject->getMagnitude() < 3) {
			bufferedCanvas->FillEllipse(starColor, Rectangle(left,top,1+addition,1+addition));
		} else if (skyObject->getMagnitude() < 4) {
			bufferedCanvas->FillEllipse(starColor, Rectangle(left,top,addition,addition));
		} else {
			bufferedCanvas->FillEllipse(starColor, Rectangle(left,top,-1+addition,-1+addition));
		}
    }
    Osp::Graphics::Rectangle rect = getCanvas()->GetBounds();
    getCanvas()->Copy(rect, *bufferedCanvas, rect);
    getCanvas()->Show();

    AppLog("<<SkyObject.Draw() zoom=%d magnitude=%f", zoom, skyObject->getMagnitude());
}


void
Sky::zoomIn() {
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
	return zoom < max_zoom;
}

bool
Sky::canZoomOut() {
	return zoom > min_zoom;
}

Osp::Graphics::Canvas*
Sky::getBufferedCanvas(int zoom) {
	switch(zoom) {
		case 1:
		{
			return bufferedCanvas;
		}
		case 2:
		{
			return bufferedCanvas2;
		}
		case 4:
		{
			return bufferedCanvas4;
		}
	}
}

void
Sky::setBufferedCanvas(Osp::Graphics::Canvas* aCanvas, int zoom) {
	switch(zoom) {
		case 1:
		{
			bufferedCanvas = aCanvas;
		}
		break;
		case 2:
		{
			bufferedCanvas2 = aCanvas;
		}
		break;
		case 4:
		{
			bufferedCanvas4 = aCanvas;
		}
		break;
	}
}

Osp::Base::Collection::IList*
Sky::getConst(void) {
	return visibleConst;
}




