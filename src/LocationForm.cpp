/*
 * LocationForm.cpp
 *
 *  Created on: 24.11.2012
 *      Author: ddreval
 */

#include "LocationForm.h"

using namespace Osp::Locations;

LocationForm::LocationForm(TimeAndPlace* pTimeAndPlace) {
	timeAndPlace = pTimeAndPlace;
	locProvider = new LocationProvider();
	locProvider -> Construct(LOC_METHOD_HYBRID);
	locProvider -> RequestLocationUpdates(*this, 5, true);
}

LocationForm::~LocationForm() {
	// TODO Auto-generated destructor stub
}

void
LocationForm::OnLocationUpdated(Osp::Locations::Location& location) {

}

void
LocationForm::OnProviderStateChanged(Osp::Locations::LocProviderState newState) {

}

