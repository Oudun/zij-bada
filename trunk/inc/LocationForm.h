/*
 * LocationForm.h
 *
 *  Created on: 24.11.2012
 *      Author: ddreval
 */

#ifndef LOCATIONFORM_H_
#define LOCATIONFORM_H_

#include <FUi.h>
#include <FLocations.h>

#include "TimeAndPlace.h"

class LocationForm :
	public Osp::Ui::Controls::Form,
	public Osp::Locations::ILocationListener {

	public:
		LocationForm(TimeAndPlace* timeAndPlace);
		virtual ~LocationForm();
		virtual void OnLocationUpdated(Osp::Locations::Location& location);
		virtual void OnProviderStateChanged(Osp::Locations::LocProviderState newState);

	private:
		Osp::Locations::LocationProvider* locProvider;
		TimeAndPlace* timeAndPlace;

};

#endif /* LOCATIONFORM_H_ */
