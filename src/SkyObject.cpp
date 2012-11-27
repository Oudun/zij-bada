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
SkyObject::setDED(float DED) {
    this->DED = DED;
}

void
SkyObject::setRAH(float RAH) {
    this->RAH = RAH;
}

void
SkyObject::Print(void) {
	if (name==null) {
		AppLog("NAME IS NULL");
	}
	AppLog("Object name=%S, magnitude=%f, ra=%f, de=%f, north=%d", name.GetPointer(), magnitude, RAH, DED, sign);
}

void
SkyObject::Draw(SkyCanvas* skyCanvas) {
	result r = E_SUCCESS;
	AppLog("A");
	Canvas* canvas1 = skyCanvas -> GetBufferedCanvas(1);
	AppLog("B");
	if (canvas1 == null) {
		AppLog("C");
		canvas1 = new Canvas();
		AppLog("D");
		r = canvas1 -> Construct(Rectangle(0, 0, 240, 400));
		AppLog("Canvas construction result is %S", GetErrorMessage(r));
		canvas1 -> FillEllipse(Color::COLOR_GREEN, Rectangle(150, 150, 16, 16));
		canvas1 -> Show();
		AppLog("E");
		skyCanvas -> SetBufferedCanvas(canvas1, 1);
		AppLog("F");
	}
	AppLog("G");
	canvas1 -> FillEllipse(Color::COLOR_MAGENTA, Rectangle(100, 100, 16, 16));
	canvas1 -> Show();
	AppLog("H");
}



