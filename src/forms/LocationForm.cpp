/*
 * To display progress of user location lookup and provide application
 * with current time and coordinates;
 *
 *  Created on: 24.11.2012
 *  Author: ddreval
 */

#include "forms/LocationForm.h"

using namespace Osp::Base;
using namespace Osp::Base::Utility;
using namespace Osp::Locations;
using namespace Osp::Locales;
using namespace Osp::System;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;
using namespace Osp::App;


LocationForm::LocationForm() {
	maxAttempts = 16;
	attemptsCounter = 1;
	locProvider = new LocationProvider();
	AppLog("1");
	result r = E_SUCCESS;
	r = locProvider -> Construct(LOC_METHOD_HYBRID);
	if (r != E_SUCCESS) {
		Osp::App::Application::GetInstance() -> SendUserEvent(EVENT_LOCATION_FAILED, null);
	}
	r = locProvider -> RequestLocationUpdates(*this, 15, true);
	if (r != E_SUCCESS) {
		Osp::App::Application::GetInstance() -> SendUserEvent(EVENT_LOCATION_FAILED, null);
	}
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

	SetBackgroundColor(COLOR_FORM_BKG);

	__pActionLabel -> SetBackgroundColor(COLOR_FORM_BKG);
	__pActionLabel -> SetTextColor(COLOR_FORM_TEXT);
	__pActionLabel -> SetText(Constants::GetString(STRING_GETTING_LOCATION));

	__pActionAttemptLabel -> SetBackgroundColor(COLOR_FORM_BKG);
	__pActionAttemptLabel -> SetTextColor(COLOR_FORM_TEXT);

	__pGpsProviderStatusLabel -> SetBackgroundColor(COLOR_FORM_BKG);
	__pGpsProviderStatusLabel -> SetTextColor(COLOR_FORM_TEXT);

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

	//just for testing:
//	QualifiedCoordinates* coordinates = new QualifiedCoordinates();
//	coordinates -> SetLatitude(55.0);
//	coordinates -> SetLongitude(37.0);

	if (coordinates != 0) {
		AppLog("Coordinates taken lon %f lat %f \n", coordinates->GetLongitude(), coordinates->GetLatitude());
		__pActionAttemptLabel -> SetText(Constants::GetString(STRING_COORDINATES_TAKEN));
		__pActionAttemptLabel -> RequestRedraw(true);
		String locationStr;
		locationStr.Format(22, L"%S\n%S",
				(DegreeToGrad(coordinates->GetLatitude(), "N", "S")->GetPointer()),
				(DegreeToGrad(coordinates->GetLongitude(), "E", "W")->GetPointer()));
		__pGpsProviderStatusLabel->SetText(locationStr.GetPointer());
		__pGpsProviderStatusLabel -> RequestRedraw(true);
		locProvider -> CancelLocationUpdates();

		TimeAndPlace::SetSiderialTime(coordinates->GetLongitude(), coordinates->GetLatitude(), new DateTime());

		Osp::App::AppRegistry* appRegistry = Osp::App::Application::GetInstance()->GetAppRegistry();
		result r = E_SUCCESS;
		r = appRegistry -> Set("LAST_LONGITUDE", coordinates->GetLongitude());
		if (r == E_KEY_NOT_FOUND) {
			appRegistry -> Add("LAST_LONGITUDE", coordinates->GetLongitude());
		}
		r = appRegistry -> Set("LAST_LATITUDE", coordinates ->GetLatitude());
		if (r == E_KEY_NOT_FOUND) {
			appRegistry -> Add("LAST_LATITUDE", coordinates->GetLatitude());
		}
		appRegistry -> Save();
		Osp::App::Application::GetInstance() -> SendUserEvent(EVENT_LOCATION_SET, null);

	} else if (attemptsCounter < maxAttempts){
		attemptsCounter++;
		Osp::Base::String str(Constants::GetString(STRING_ATTEMPT_NO));
		str.Append(attemptsCounter);
		__pActionAttemptLabel -> SetText(str);
		__pActionAttemptLabel -> RequestRedraw(true);

	} else {
		attemptsCounter = 0;
		locProvider -> CancelLocationUpdates();
		Osp::App::Application::GetInstance() -> SendUserEvent(EVENT_LOCATION_FAILED, null);
	}
}

void
LocationForm::OnProviderStateChanged(Osp::Locations::LocProviderState newState) {

	AppLog("4");
	AppLog("Location Provider state changed\n");
	if (newState == LOC_PROVIDER_AVAILABLE) {
		__pGpsProviderStatusLabel -> SetText(Constants::GetString(STRING_LOC_UNAVAIL));
		__pGpsProviderStatusLabel -> RequestRedraw(true);
		AppLog("The location provider is available");
	} else if (newState == LOC_PROVIDER_OUT_OF_SERVICE) {
		__pGpsProviderStatusLabel -> SetText(Constants::GetString(STRING_LOC_OUT));
		__pGpsProviderStatusLabel -> RequestRedraw(true);
		AppLog("The location provider is out of service");
	} else if (newState == LOC_PROVIDER_TEMPORARILY_UNAVAILABLE) {
		__pGpsProviderStatusLabel -> SetText(Constants::GetString(STRING_LOC_TEMP_UNAVAIL));
		__pGpsProviderStatusLabel -> RequestRedraw(true);
		AppLog("The location provider is temporarily unavailable");
	} else {
		__pGpsProviderStatusLabel -> SetText(Constants::GetString(STRING_LOC_STATE_UNKNOWN));
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

result
LocationForm::OnDraw(void) {
	AppResource* pAppResource = Application::GetInstance()->GetAppResource();
	Bitmap* bitmapBackground = pAppResource -> GetBitmapN(L"FormBackground.png");
	Canvas* canvas = GetCanvasN();
	result r = canvas -> DrawBitmap(GetBounds(), *bitmapBackground);
	return r;
}
