/*
 * SkyObject.cpp
 *
 *  Created on: 17.02.2012
 *      Author: ddreval
 */

#include "SkyObject.h"

using namespace Osp::Graphics;

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
	AppLog("Right Ascentation is %f", RAH);
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
	AppLog("Declination is %f", DED);
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
	Canvas* canvas = sky -> getCanvas();

//    double r = (R * p.getCosAlt());
//    int top = (int)(R - r * p.getCosAz());
//    int left = (int)(R + r *p.getSinAz());

//public static edu.astro.PositionTrig getObjectTrigPosition(float aRah, float aDec) {
//	float lstDeg = sky -> siderialHours;
//	float raDeg = RAH * 15;
//	float ha = (360 + lstDeg - raDeg)%360;
//    double sinAlt =
//        Math.sin(Math.toRadians(aDec))*Math.sin(Math.toRadians(latitude))
//        +Math.cos(Math.toRadians(aDec))*Math.cos(Math.toRadians(latitude))*Math.cos(Math.toRadians(ha));
//    double cosAlt =
//        Math.sqrt(1-sinAlt*sinAlt);
//    double sinAz =
//        -(Math.sin(Math.toRadians(ha))*Math.cos(Math.toRadians(aDec)))/cosAlt;
//    double cosAz =
//        (Math.sin(Math.toRadians(aDec))-Math.sin(Math.toRadians(latitude))*sinAlt)/
//            (Math.cos(Math.toRadians(latitude))*cosAlt);
//    PositionTrig positionTrig = new PositionTrig();
//    positionTrig.setCosAlt(cosAlt);
//    positionTrig.setSinAlt(sinAlt);
//    positionTrig.setCosAz(cosAz);
//    positionTrig.setSinAz(sinAz);
//    return positionTrig;
//}



}
