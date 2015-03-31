/*
 * PrecisePoint.cpp
 *
 *  Created on: 19.02.2015
 *      Author: Denis
 */

#include "PrecisePoint.h"

PrecisePoint::PrecisePoint() {

}

PrecisePoint::PrecisePoint(float argX, float argY) {
	x = argX;
	y = argY;
}


PrecisePoint::~PrecisePoint() {

}

void
PrecisePoint::SetPosition(float argX, float argY) {
	x = argX;
	y = argY;
}

Osp::Graphics::Point*
PrecisePoint::GetPoint(void) {
	return new Osp::Graphics::Point(x, y);
}

