/*
 * TimeAndPlace.cpp
 *
 *  Created on: 24.11.2012
 *      Author: ddreval
 */

#include "TimeAndPlace.h"

float TimeAndPlace::longitude = 0.0F;
float TimeAndPlace::latitude = 0.0F;
float TimeAndPlace::siderialTime = 0.0F;
Osp::Base::DateTime* TimeAndPlace::dateTime;
Osp::Base::DateTime* TimeAndPlace::localDateTime;

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

	AppLog("Getting siderial time for longitude %f latitude %f", longitude, latitude);
	TimeAndPlace::SetLongitude(longitude);
	TimeAndPlace::SetLatitude(latitude);

	LocaleManager localeManager;
	localeManager.Construct();
	Locale locale = localeManager.GetSystemLocale();
	TimeZone timeZone = localeManager.GetSystemTimeZone();

	AppLog("Locale code %S", (locale.GetLanguageCodeString().GetPointer()));
	AppLog("TimeZone ID is %S", (timeZone.GetId()).GetPointer());
	AppLog("TimeZone offset is %d", (timeZone.GetRawOffset()));

	SystemTime::GetCurrentTime(*currTime);
	AppLog("TP2");
	dateTime = currTime;
	AppLog("TP2a");
	//localDateTime = &(timeZone.UtcTimeToStandardTime(*currTime));
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
	AppLog("TP11 daysSinceJ2000 %f", (float)daysSinceJ2000);
	// Calculating local siderial time in degrees
	// To get siderial time in hours it should be divided by 15
	double slt = 100.46 + 0.985647 * daysSinceJ2000 + longitude + 15*(hrs + minHrs);
	AppLog("TP12 LST is %f", (float)(slt/15));
	int sltInt = (int)(slt/360);
	AppLog("TP13");
	float sltHrs = (slt-(360*sltInt))/15;
	AppLog("TP14");
	SetSiderialTime (sltHrs);
	AppLog("TP15");

	int yearInt = calendar -> GetTimeField(TIME_FIELD_YEAR);
	int monthInt = calendar -> GetTimeField(TIME_FIELD_MONTH);
	int dayInt = calendar -> GetTimeField(TIME_FIELD_DAY_OF_MONTH);
	int hourInt = calendar -> GetTimeField(TIME_FIELD_HOUR_OF_DAY);
	int minuteInt = calendar -> GetTimeField(TIME_FIELD_MINUTE);
	int secondInt = calendar -> GetTimeField(TIME_FIELD_SECOND);
	double UT = ((float)hourInt * 3600 + (float)minuteInt * 60 + (float)secondInt) / 3600;
	UT = UT - (timeZone.GetRawOffset())/60.0;

	AppLog("UT (%d, %d, %d) = %f",
			hourInt, minuteInt, secondInt, UT);

	AppLog("JulianDay for year %d month %d day %d time %f is %d", yearInt, monthInt, dayInt, UT, (int)(1000000*GetJulianDay(yearInt, monthInt, dayInt, UT)));

	GetSiderialTime(GetJulianDay(yearInt, monthInt, dayInt, UT), longitude);
	//GetSiderialTime(GetJulianDay(yearInt, monthInt, dayInt, UT), 0.1);
	//GetSiderialTime(GetJulianDay(yearInt, monthInt, dayInt, UT), 13.41);//13.41 - Berlin longitude


}

String*
TimeAndPlace::GetReadableLongitude(void) {

	float angle = longitude;
	const char* prefix = angle < 0 ? "S" : "N";
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
	const char* prefix = angle < 0 ? "W" : "E";
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

double
TimeAndPlace::GetJulianDay(int year, int month, int day, float UT) {

	if (year < 1900) {
		 year = year + 1900;
	}

	if (month <= 2) {
		month = month + 12;
		year = year - 1;
	}

	double d = (float)Math::Floor(365.25 * (year + 4716)) + (float)Math::Floor(30.6001 * (month + 1)) + (float)day - (float)13 - (float)1524.5 + ((float)UT)/24.0;

	return d;

}


double
TimeAndPlace::GetSiderialTime(double jd, double longitude) {
	AppLog("Calculating siderial time for julian day %f %e %g longitude %f", jd, jd, jd, longitude);
	double t_eph, ut, MJD0, MJD, GMST, LMST, localSiderial;
	MJD = jd - 2400000.5;
	MJD0 = Math::Floor(MJD);
	ut = (MJD - MJD0) * 24.0;
	t_eph  = (MJD0-51544.5)/36525.0;
	GMST =  6.697374558 + 1.0027379093*ut + (8640184.812866 + (0.093104 - 0.0000062*t_eph)*t_eph)*t_eph/3600.0;
	localSiderial = GMST + longitude/15.0;
	LMST =  24.0 * Fraction((localSiderial)/24.0);

	 int h = Math::Floor(LMST);
	 int min = Math::Floor(60.0*Fraction(LMST));
	 int secs = Math::Round(60.0*(60.0*Fraction(LMST)-min));



	AppLog("Raw siderial time is %f", GMST);
	AppLog("Raw local siderial time is %f", LMST);
    AppLog("Local siderial time is %d hours %d minutes %d seconds", h, min, secs);


	return LMST;
}

double
TimeAndPlace::Fraction(double value) {
	value = value - Math::Floor(value);
	if (value < 0) {
		 value = value + 1.0;
	 }
	 return value;
}


//function GM_Sidereal_Time (jd) {
//		var t_eph, ut, MJD0, MJD;
//
//		MJD = jd - 2400000.5;
//		MJD0 = Math.floor(MJD);
//		ut = (MJD - MJD0)*24.0;
//		t_eph  = (MJD0-51544.5)/36525.0;
//		return  6.697374558 + 1.0027379093*ut + (8640184.812866 + (0.093104 - 0.0000062*t_eph)*t_eph)*t_eph/3600.0;
//	}
//
//function LM_Sidereal_Time (jd, longitude) {
//		var GMST = GM_Sidereal_Time(jd);
//		var LMST =  24.0*frac((GMST + longitude/15.0)/24.0);
//  return HoursMinutesSeconds(LMST);
//	}

