/*
 * TimeAndPlace.cpp
 *
 *  Created on: 24.11.2012
 *      Author: ddreval
 */

#include "TimeAndPlace.h"

using namespace Osp::Base;
using namespace Osp::Locations;
using namespace Osp::Locales;
using namespace Osp::System;

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
void
TimeAndPlace::SetSiderialTime(float longitude, float latitude, DateTime* currTime) {
	AppLog("Trying to access TimeAndPlace");
	TimeAndPlace::SetLongitude(longitude);
	AppLog("Trying to access TimeAndPlace 1");
	TimeAndPlace::SetLatitude(latitude);
	AppLog("Trying to access TimeAndPlace 2");
	TimeZone timeZone(60, L"Europe/London");
	AppLog("TP1");
	SystemTime::GetCurrentTime(*currTime);
	AppLog("TP2");
	Calendar* calendar;
	AppLog("TP3");
	calendar = Calendar::CreateInstanceN(timeZone, CALENDAR_GREGORIAN);
	AppLog("TP4");
	calendar->SetTime(*currTime);
	AppLog("TP5");
	float hrs = (calendar->GetTimeField(TIME_FIELD_HOUR_OF_DAY))-1;
	AppLog("TP6");
	float minHrs = calendar->GetTimeField(TIME_FIELD_MINUTE)/60.0;
	AppLog("TP7");
	float dayFract = (hrs + minHrs)/24.0;
	AppLog("TP8");
	float dayNum = calendar->GetTimeField(TIME_FIELD_DAY_OF_YEAR);
	AppLog("TP9");
	float year = calendar->GetTimeField(TIME_FIELD_YEAR);
	AppLog("TP10");
	double daysSinceJ2000 = -1.5 + dayNum + (year-2000)*365 + (int)((year-2000)/4) + dayFract;
	AppLog("TP11");
	double slt = 100.46 + 0.985647 * daysSinceJ2000 + longitude + 15*(hrs + minHrs);
	AppLog("TP12");
	int sltInt = (int)(slt/360);
	AppLog("TP13");
	float sltHrs = (slt-(360*sltInt))/15;
	AppLog("TP14");
	SetSiderialTime (sltHrs);
	AppLog("TP15");
}
