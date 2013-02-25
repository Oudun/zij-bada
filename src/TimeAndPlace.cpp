/*
 * TimeAndPlace.cpp
 *
 *  Created on: 24.11.2012
 *      Author: ddreval
 */

#include "TimeAndPlace.h"

TimeAndPlace::TimeAndPlace() {
	AppLog("TimeAndPlace constructed");
}

TimeAndPlace::~TimeAndPlace() {
	AppLog("TimeAndPlace destroyed");
}

void
TimeAndPlace::SetLongitude(float pLongitude) {
	longitude = pLongitude;
}

void
TimeAndPlace::SetLatitude(float pLatitude) {
	latitude = pLatitude;
}

void
TimeAndPlace::SetSiderialTime(float pSiderialTime) {
	siderialTime = pSiderialTime;
}

float
TimeAndPlace::GetLongitude(void) {
	return longitude;
}

float
TimeAndPlace::GetLatitude(void) {
	return latitude;
}

float
TimeAndPlace::GetSiderialTime(void) {
	return siderialTime;
}
