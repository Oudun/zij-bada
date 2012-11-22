/*
 * SkyObject.cpp
 *
 *  Created on: 17.02.2012
 *      Author: ddreval
 */

#include "SkyObject.h"

using namespace Osp::Base;
using namespace Osp::Base::Utility;
using namespace Osp::Graphics;

SkyObject::SkyObject() {

}

SkyObject::~SkyObject() {

}

float
SkyObject::getRAH(void) {
	return RAH;
}

float
SkyObject::getDED(void) {
	return DED;
}

void
SkyObject::setMagnitude(float pMagnitude) {
	this -> magnitude = pMagnitude;
}

void
SkyObject::setSign(bool isNorthern) {
	sign = isNorthern;
}

void
SkyObject::setName(Osp::Base::String& aName) {
	name = aName;
}

Osp::Base::String&
SkyObject::getName(void) {
	return name;
}

bool
SkyObject::isNorthern(void) {
	return sign;
}

float
SkyObject::getMagnitude(void) {
	return magnitude;
}

void
SkyObject::draw(Sky* sky) {
	AppLog(">>SkyObject.Draw()");
	float lstDeg = 15*(sky -> getSiderialHours());
	float raDeg = RAH * 15; // 24 hours is 360 degrees, so 1 hour is 15 degrees
	float ha = lstDeg > raDeg ? lstDeg - raDeg : 360 + lstDeg - raDeg;
	double radInDegree = 0.0174532925;
	float decSigned = isNorthern() ? DED : -DED;
    double sinAlt =
        Math::Sin(radInDegree*decSigned)*Math::Sin(radInDegree*(sky->getLatitude()))
        +Math::Cos(radInDegree*decSigned)*Math::Cos(radInDegree*(sky->getLatitude()))*Math::Cos(radInDegree*(ha));
    double cosAlt =
        Math::Sqrt(1-sinAlt*sinAlt);
    double sinAz =
        -(Math::Sin(radInDegree*(ha))*Math::Cos(radInDegree*(decSigned)))/cosAlt;
    double cosAz =
        (Math::Sin(radInDegree*decSigned)-Math::Sin(radInDegree*(sky->getLatitude()))*sinAlt)/
            (Math::Cos(radInDegree*(sky->getLatitude()))*cosAlt);
    double R = sky->getRadius();
    double r = R * cosAlt;
    int top  = (int)((sky->getZenithY()) - r * cosAz);
    int left = (int)((sky->getZenithX()) - r * sinAz);
    int width = sky->getCanvas()->GetBounds().width;
    int height = sky->getCanvas()->GetBounds().height;
    int zoom = sky->getZoom();
    Osp::Graphics::Canvas* bufferedCanvas = sky->getBufferedCanvas(zoom);

    if (bufferedCanvas == null) {
    	bufferedCanvas = new Canvas();
    	Osp::Graphics::Rectangle* rect = new Osp::Graphics::Rectangle();
    	rect->SetBounds(0, 0 , width, height);
    	bufferedCanvas->Construct(*rect);
    	sky->setBufferedCanvas(bufferedCanvas, zoom);
    }
    int addition = zoom == 1 ? 0 : (zoom == 2) ? 1 : 2;
    Font pFont;
	pFont.Construct(FONT_STYLE_PLAIN, 12);
    bufferedCanvas->SetFont(pFont);
    bufferedCanvas->SetForegroundColor(Color::COLOR_GREY);

    Osp::Graphics::Color starColor;
    if (name.EndsWith("UMa")) {
    	starColor = Color::COLOR_YELLOW;
    } else if (name.EndsWith("Ori")) {
    	starColor = Color::COLOR_MAGENTA;
    } else if (name.EndsWith("Lyr")) {
    	starColor = Color::COLOR_GREEN;
    } else if (name.EndsWith("Cas")) {
    	starColor = Color::COLOR_MAGENTA;
    } else if (name.EndsWith("Peg")) {
    	starColor = Color::COLOR_CYAN;
    } else if (name.EndsWith("Ind")) {
        	starColor = Color::COLOR_RED;
    } else {
    	starColor = Color::COLOR_WHITE;
    }

    if (sinAlt > 0) {
    	if (left<0||top<0||left>width||top>height) {
    		return;
    	}
    	String* constName = new String(name);
    	if (sky->getConst()->Contains(*constName)) {
    		AppLog("!!!Constellation %S is in list %d", name.GetPointer(), sky->getConst()->GetCount());
    		delete constName;
    	} else {
    		AppLog("!!!Constellation %S is added to list %d", name.GetPointer(), name.GetPointer(), sky->getConst()->GetCount());
    		sky->getConst()->Add(*constName);
    	}
    	if (magnitude < 1) {
    		bufferedCanvas->FillEllipse(starColor, Rectangle(left,top,3+addition,3+addition));
			bufferedCanvas->DrawText(Point(left-8, top+8), name);
		} else if (magnitude < 2) {
			bufferedCanvas->FillEllipse(starColor, Rectangle(left,top,2+addition,2+addition));
		} else if (magnitude < 3) {
			bufferedCanvas->FillEllipse(starColor, Rectangle(left,top,1+addition,1+addition));
		} else if (magnitude < 4) {
			bufferedCanvas->FillEllipse(starColor, Rectangle(left,top,addition,addition));
		} else {
			bufferedCanvas->FillEllipse(starColor, Rectangle(left,top,-1+addition,-1+addition));
		}
    }
    Osp::Graphics::Rectangle rect = sky->getCanvas()->GetBounds();
    sky->getCanvas()->Copy(rect, *bufferedCanvas, rect);
    sky->getCanvas()->Show();

    AppLog("<<SkyObject.Draw() zoom=%d magnitude=%f", zoom, magnitude);

}

void SkyObject::setDED(float DED) {
    this->DED = DED;
}

void SkyObject::setRAH(float RAH) {
    this->RAH = RAH;
}



