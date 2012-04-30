/*
 * SkyObject.cpp
 *
 *  Created on: 17.02.2012
 *      Author: ddreval
 */

#include "SkyObject.h"

using namespace Osp::Graphics;
using namespace Osp::Base::Utility;

SkyObject::SkyObject() {
	// TODO Auto-generated constructor stub

}

SkyObject::~SkyObject() {
	// TODO Auto-generated destructor stub
}

void
SkyObject::setRA(Osp::Base::String& raH, Osp::Base::String&  raM, Osp::Base::String&  raS)
{
	float f1, f2, f3;
	Osp::Base::Float::Parse(raH, f1);
	Osp::Base::Float::Parse(raM, f2);
	Osp::Base::Float::Parse(raS, f3);
	RAH = f1 + (f2/60) + (f3/3600);
//	AppLog("Right Ascentation is %f", RAH);
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
SkyObject::setDE(Osp::Base::String& deD, Osp::Base::String&  deM, Osp::Base::String&  deS)
{
	float f1, f2, f3;
	Osp::Base::Float::Parse(deD, f1);
	Osp::Base::Float::Parse(deM, f2);
	Osp::Base::Float::Parse(deS, f3);
	DED = f1 + (f2/60) + (f3/3600);
//	AppLog("Declination is %f", DED);
}

void
SkyObject::setMagnitude(Osp::Base::String& magnitudeStr) {
	float f;
	Osp::Base::Float::Parse(magnitudeStr, f);
	magnitude = f;
}

void
SkyObject::setSign(bool isNorthern) {
	sign = isNorthern;
}

void
SkyObject::setName(Osp::Base::String& aName) {
	name = aName;
}

void
SkyObject::setDraperName(Osp::Base::String& aDraperName) {
	draperName = aDraperName;
}

Osp::Base::String&
SkyObject::getName(void) {
	return name;
}

Osp::Base::String&
SkyObject::getDraperName(void) {
	return draperName;
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
    	result r = bufferedCanvas->Construct(*rect);
    	if(r == E_SUCCESS) {
    		AppLog("The method is successful.");
    	} else if (r == E_INVALID_ARG) {
    		AppLog("A specified input parameter is invalid.");
    	} else if (r == E_OUT_OF_RANGE) {
    		AppLog("The value of the argument is outside the valid range defined by the method.");
    	} else if (r == E_OUT_OF_MEMORY) {
    		AppLog("The memory is insufficient.");
    	} else if (r == E_INVALID_STATE) {
    		AppLog("This instance is in an invalid state.");
    	}
    	sky->setBufferedCanvas(bufferedCanvas, zoom);
    }
    if (sinAlt > 0) {
    	if (left<0||top<0||left>width||top>height) {
    		return;
    	}
//    	if (magnitude < 1) {
    		int size = (int)((8 * zoom) / (2 + magnitude));
    		if (size < 1) {
    			return;
    		}
    		bufferedCanvas->FillEllipse(Color::COLOR_WHITE, Rectangle(left,top,size,size));

    		//			Font pFont;
//			pFont.Construct(FONT_STYLE_PLAIN, 12);
//			bufferedCanvas->SetFont(pFont);
//			bufferedCanvas->DrawText(Point(left-8, top+8), name);

//		} else if (magnitude < 2) {
//			bufferedCanvas->FillEllipse(Color::COLOR_WHITE, Rectangle(left,top,4,4));
//		} else if (magnitude < 3) {
//			bufferedCanvas->FillEllipse(Color::COLOR_WHITE, Rectangle(left,top,2,2));
//		} else {
//			bufferedCanvas->FillEllipse(Color::COLOR_WHITE, Rectangle(left,top,1,1));
//		}
    }
    Osp::Graphics::Rectangle rect = sky->getCanvas()->GetBounds();
    sky->getCanvas()->Copy(rect, *bufferedCanvas, rect);
    sky->getCanvas()->Show();

//    PositionTrig positionTrig = new PositionTrig();
//    positionTrig.setCosAlt(cosAlt);
//    positionTrig.setSinAlt(sinAlt);
//    positionTrig.setCosAz(cosAz);
//    positionTrig.setSinAz(sinAz);
//    return positionTrig;
//}

}

void SkyObject::setDED(float DED)
{
    this->DED = DED;
}

void SkyObject::setRAH(float RAH)
{
    this->RAH = RAH;
}



