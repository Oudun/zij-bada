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
	SystemTime::GetCurrentTime(*currTime);
	Calendar* calendar;
	calendar = Calendar::CreateInstanceN(timeZone, CALENDAR_GREGORIAN);
	calendar->SetTime(*currTime);
	float hrs = (calendar->GetTimeField(TIME_FIELD_HOUR_OF_DAY))-1;
	float minHrs = calendar->GetTimeField(TIME_FIELD_MINUTE)/60.0;
	float dayFract = (hrs + minHrs)/24.0;
	float dayNum = calendar->GetTimeField(TIME_FIELD_DAY_OF_YEAR);
	float year = calendar->GetTimeField(TIME_FIELD_YEAR);
	double daysSinceJ2000 = -1.5 + dayNum + (year-2000)*365 + (int)((year-2000)/4) + dayFract;
	double slt = 100.46 + 0.985647 * daysSinceJ2000 + longitude + 15*(hrs + minHrs);
	int sltInt = (int)(slt/360);
	float sltHrs = (slt-(360*sltInt))/15;
	SetSiderialTime (sltHrs);
}
