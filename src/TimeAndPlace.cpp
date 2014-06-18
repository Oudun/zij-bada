/*
 * TimeAndPlace.cpp
 *
 *  Created on: 24.11.2012
 *      Author: ddreval
 */

#include "TimeAndPlace.h"

using namespace Osp::Base;
using namespace Osp::Base::Utility;
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

DateTime*
TimeAndPlace::GetDateTime(void) {
	return dateTime;
}

DateTime*
TimeAndPlace::GetStandardDateTime(void) {

	LocaleManager localeManager;
	localeManager.Construct();
	Locale locale = localeManager.GetSystemLocale();
	TimeZone timeZone = localeManager.GetSystemTimeZone();

	AppLog("GMT Time Zone id is %S", timeZone.GetGmtTimeZone().GetId().GetPointer());
	AppLog("Time Zone is %S", timeZone.GetId().GetPointer());
	AppLog("Time Zone offset is %d", timeZone.GetRawOffset());
	AppLog("Time Zone DST is %d", timeZone.GetDstSavings());

	result r;

	String customizedPattern = L"HH:mm:ss zzz";
	String readableDateTime;
	DateTimeFormatter* formatter = DateTimeFormatter::CreateDateFormatterN();
	r = formatter -> ApplyPattern(customizedPattern);
	AppLog("formatter -> ApplyPattern(customizedPattern) result is %s", GetErrorMessage(r));

	DateTime standardOffsetDateTime = timeZone.UtcTimeToStandardTime(*dateTime, timeZone.GetRawOffset());
	r = formatter -> Format(standardOffsetDateTime, readableDateTime);
	AppLog("Standard Local Time is %S", readableDateTime.GetPointer());
	readableDateTime.Clear();

	DateTime standardDateTime = timeZone.UtcTimeToStandardTime(*dateTime);
	r = formatter -> Format(standardDateTime, readableDateTime);
	AppLog("Standard Time is %S", readableDateTime.GetPointer());
	readableDateTime.Clear();

	DateTime wallDateTime = timeZone.UtcTimeToWallTime(*dateTime);
	r = formatter -> Format(wallDateTime, readableDateTime);
	AppLog("Wall Time is %S", readableDateTime.GetPointer());
	readableDateTime.Clear();

	r = formatter -> Format(*dateTime, readableDateTime);
	AppLog("UTC Time is %S", readableDateTime.GetPointer());
	readableDateTime.Clear();

//	Calendar* calendar = Calendar::CreateInstanceN(timeZone, CALENDAR_GREGORIAN);
//	DateTime localTime1 = calendar -> GetTime();
//	r = formatter -> Format(localTime1, readableDateTime);
//	AppLog("Local Time is %S", readableDateTime.GetPointer());

	return localDateTime;
}

String
TimeAndPlace::GetReadableTime(void) {

	LocaleManager localeManager;
	localeManager.Construct();
	Locale locale = localeManager.GetSystemLocale();
	TimeZone timeZone = localeManager.GetSystemTimeZone();

	AppLog("GMT Time Zone id is %S", timeZone.GetGmtTimeZone().GetId().GetPointer());
	AppLog("Time Zone is %S", timeZone.GetId().GetPointer());
	AppLog("Time Zone offset is %d", timeZone.GetRawOffset());
	AppLog("Time Zone DST is %d", timeZone.GetDstSavings());

	String customizedPattern = L"HH:mm:ss";
	String readableDateTime;
	DateTimeFormatter* formatter = DateTimeFormatter::CreateDateFormatterN();
	formatter -> ApplyPattern(customizedPattern);

	DateTime standardOffsetDateTime = timeZone.UtcTimeToStandardTime(*dateTime, timeZone.GetRawOffset());
	formatter -> Format(standardOffsetDateTime, readableDateTime);
	AppLog("Standard Local Time is %S", readableDateTime.GetPointer());

	readableDateTime.Append("\n");
	readableDateTime.Append(timeZone.GetId());

	return readableDateTime;
}

void
TimeAndPlace::SetSiderialTime(float longitude, float latitude, DateTime* currTime) {
	AppLog("Trying to access TimeAndPlace");
	TimeAndPlace::SetLongitude(longitude);
	AppLog("Trying to access TimeAndPlace 1");
	TimeAndPlace::SetLatitude(latitude);
	AppLog("Trying to access TimeAndPlace 2");
	//TimeZone timeZone(60, L"Europe/London");

	LocaleManager localeManager;
	localeManager.Construct();
	Locale locale = localeManager.GetSystemLocale();
	TimeZone timeZone = localeManager.GetSystemTimeZone();

	AppLog("Locale code %S", (locale.GetLanguageCodeString().GetPointer()));
	AppLog("TimeZone ID is %S", (timeZone.GetId()).GetPointer());

//	TimeZone timeZone(TimeZone::GetGmtTimeZone());
	AppLog("TP1");
	SystemTime::GetCurrentTime(*currTime);
	AppLog("TP2");
	dateTime = currTime;
	AppLog("TP2a");
	localDateTime = &(timeZone.UtcTimeToStandardTime(*currTime));
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

String*
TimeAndPlace::GetReadableLongitude(void) {

	float angle = longitude;
	char* posPrefix = "N";
	char* negPrefix = "S";

	const char* prefix = angle < 0 ? negPrefix : posPrefix;
	float latAbs = angle * 1000000;
	float deg = Math::Abs(Math::Floor(latAbs/1000000));
	float min = Math::Floor(((latAbs/1000000)
			- Math::Floor(latAbs/1000000))*60);
	float sec = Math::Floor(((((latAbs/1000000)
			- Math::Floor(latAbs/1000000))*60)
			- Math::Floor(((latAbs/1000000)
			- Math::Floor(latAbs/1000000))*60))*100000)*60/100000;
	String* result = new String();
	result->Format(11, L"%s%d°%d\'%d\"", prefix, (int)deg, (int)min, (int)sec);
	return result;

}

String*
TimeAndPlace::GetReadableLatitude(void) {

	float angle = latitude;
	char* posPrefix = "E";
	char* negPrefix = "W";

	const char* prefix = angle < 0 ? negPrefix : posPrefix;
	float latAbs = angle * 1000000;
	float deg = Math::Abs(Math::Floor(latAbs/1000000));
	float min = Math::Floor(((latAbs/1000000)
			- Math::Floor(latAbs/1000000))*60);
	float sec = Math::Floor(((((latAbs/1000000)
			- Math::Floor(latAbs/1000000))*60)
			- Math::Floor(((latAbs/1000000)
			- Math::Floor(latAbs/1000000))*60))*100000)*60/100000;
	String* result = new String();
	result->Format(11, L"%s%d°%d\'%d\"", prefix, (int)deg, (int)min, (int)sec);
	return result;

}

