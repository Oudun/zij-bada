/*
 * To display progress of user location lookup and provide application
 * with current time and coordinates;
 *
 *  Created on: 24.11.2012
 *  Author: ddreval
 */

#include "LocationForm.h"

using namespace Osp::Locations;

LocationForm::LocationForm(TimeAndPlace* pTimeAndPlace) {
//	timeAndPlace = pTimeAndPlace;
//	locProvider = new LocationProvider();
//	locProvider -> Construct(LOC_METHOD_HYBRID);
//	locProvider -> RequestLocationUpdates(*this, 5, true);
//	maxAttempts = 5;
//	attemptsCounter = 1;
}

LocationForm::~LocationForm() {
	// TODO Auto-generated destructor stub
}

bool
LocationForm::Initialize() {
	Construct(L"LOCATION_FORM");
	return E_SUCCESS;
}

result
LocationForm::OnInitializing(void) {
	AppLog("LocationForm::OnInitializing(void)");
	return E_SUCCESS;
}

result
LocationForm::OnTerminating(void) {
	AppLog("LocationForm::OnInitializing(void)");
	return E_SUCCESS;
}

void
LocationForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId) {
	AppLog("LocationForm::OnInitializing(void)");
}

void
LocationForm::OnLocationUpdated(Osp::Locations::Location& location) {
	AppLog("Location Updated\n");
	const QualifiedCoordinates* coordinates = location.GetQualifiedCoordinates();
//	String str;
	if (coordinates != 0) {
		AppLog("Coordinates taken\n");
//		String locationStr;
//		locationStr.Format(21, L"%S %S",
//				(DegreeToGrad(coordinates->GetLatitude(), "N", "S")->GetPointer()),
//				(DegreeToGrad(coordinates->GetLongitude(), "E", "W")->GetPointer()));
//		__pLabelLocation->SetText(locationStr.GetPointer());
//		__pLabelLocation->Draw();
//		sky->setLatitude(coordinates->GetLatitude());
//		sky->setLongitude(coordinates->GetLongitude());
//		locProvider.CancelLocationUpdates();
//		sky->draw();
	} else {
		AppLog("#");
		attemptsCounter++;
	}
}

void
LocationForm::OnProviderStateChanged(Osp::Locations::LocProviderState newState) {
	AppLog("Location Provider state changed\n");
	if (newState == LOC_PROVIDER_AVAILABLE) {
		AppLog("The location provider is available");
	} else if (newState == LOC_PROVIDER_OUT_OF_SERVICE) {
		AppLog("The location provider is out of service");
	} else if (newState == LOC_PROVIDER_TEMPORARILY_UNAVAILABLE) {
		AppLog("The location provider is temporarily unavailable");
	} else {
		AppLog("State unknown");
	}
}
