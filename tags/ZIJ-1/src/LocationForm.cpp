/*
 * To display progress of user location lookup and provide application
 * with current time and coordinates;
 *
 *  Created on: 24.11.2012
 *  Author: ddreval
 */

#include "LocationForm.h"

using namespace Osp::Base;
using namespace Osp::Base::Utility;
using namespace Osp::Locations;
using namespace Osp::Locales;
using namespace Osp::System;
using namespace Osp::Ui::Controls;

LocationForm::LocationForm() {
	maxAttempts = 1;
	attemptsCounter = 1;
	locProvider = new LocationProvider();
	locProvider -> Construct(LOC_METHOD_HYBRID);
	locProvider -> RequestLocationUpdates(*this, 5, true);
}

LocationForm::~LocationForm() {
	delete locProvider;
}

bool
LocationForm::Initialize() {
	Construct(L"LOCATION_FORM");
	return E_SUCCESS;
}

result
LocationForm::OnInitializing(void) {
	AppLog("LocationForm::OnInitializing(void)");
	__pActionLabel = static_cast<Label *>(GetControl("IDC_LABEL1"));
	__pActionAttemptLabel = static_cast<Label *>(GetControl("IDC_LABEL2"));
	__pGpsProviderStatusLabel = static_cast<Label *>(GetControl("IDC_LABEL3"));
	return E_SUCCESS;
}

result
LocationForm::OnTerminating(void) {
	AppLog("LocationForm::OnTerminating(void)");
	return E_SUCCESS;
}

void
LocationForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId) {
	AppLog("LocationForm::OnActionPerformed(void)");
}

void
LocationForm::OnLocationUpdated(Osp::Locations::Location& location) {
	AppLog("Location Updated\n");
	const QualifiedCoordinates* coordinates = location.GetQualifiedCoordinates();
//	String str;
	if (coordinates != 0) {
		AppLog("Coordinates taken\n");
		__pActionAttemptLabel -> SetText("Coordinates taken");
		__pActionAttemptLabel -> RequestRedraw(true);
		String locationStr;
		locationStr.Format(22, L"%S\n%S",
				(DegreeToGrad(coordinates->GetLatitude(), "N", "S")->GetPointer()),
				(DegreeToGrad(coordinates->GetLongitude(), "E", "W")->GetPointer()));
		__pGpsProviderStatusLabel->SetText(locationStr.GetPointer());
		__pGpsProviderStatusLabel -> RequestRedraw(true);
		locProvider -> CancelLocationUpdates();
		SetTimeAndPlace(coordinates->GetLatitude(), coordinates->GetLongitude(), new DateTime());
		Osp::App::Application::GetInstance() -> SendUserEvent(LOCATION_SET, null);
	} else if (attemptsCounter < maxAttempts){
		attemptsCounter++;
		Osp::Base::String str("Attempt #");
		str.Append(attemptsCounter);
		__pActionAttemptLabel -> SetText(str);
		__pActionAttemptLabel -> RequestRedraw(true);
	} else {
		SetTimeAndPlace(0, 0, new DateTime());
		attemptsCounter = 0;
		locProvider -> CancelLocationUpdates();
		Osp::App::Application::GetInstance() -> SendUserEvent(LOCATION_SET, null);
	}
}

void
LocationForm::OnProviderStateChanged(Osp::Locations::LocProviderState newState) {
	AppLog("Location Provider state changed\n");
	if (newState == LOC_PROVIDER_AVAILABLE) {
		__pGpsProviderStatusLabel -> SetText("The location provider is available");
		__pGpsProviderStatusLabel -> RequestRedraw(true);
		AppLog("The location provider is available");
	} else if (newState == LOC_PROVIDER_OUT_OF_SERVICE) {
		__pGpsProviderStatusLabel -> SetText("The location provider is out of service");
		__pGpsProviderStatusLabel -> RequestRedraw(true);
		AppLog("The location provider is out of service");
	} else if (newState == LOC_PROVIDER_TEMPORARILY_UNAVAILABLE) {
		__pGpsProviderStatusLabel -> SetText("The location provider is temporarily unavailable");
		__pGpsProviderStatusLabel -> RequestRedraw(true);
		AppLog("The location provider is temporarily unavailable");
	} else {
		__pGpsProviderStatusLabel -> SetText("State unknown");
		__pGpsProviderStatusLabel -> RequestRedraw(true);
		AppLog("State unknown");
	}
}

// Converts from decimal format -12,34456789 to N12°34'56
String*
LocationForm::DegreeToGrad(float angle, const char* posPrefix, const char* negPrefix) {
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

void
LocationForm::SetTimeAndPlace(float longitude, float latitude, DateTime* currTime) {
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
	TimeAndPlace::SetSiderialTime (sltHrs);
}

void
LocationForm::DoIt(void) {
//	Osp::Graphics::Canvas* canvas;
//	Control* control = GetControl(L"STELLAR_FORM");
//	canvas = control -> GetCanvasN();
////	canvas -> Clear();
////	canvas ->FillEllipse(Osp::Graphics::Color::COLOR_WHITE, Osp::Graphics::Rectangle(100, 100, 200, 200));
//	canvas -> Show();
}
