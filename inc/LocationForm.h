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
	public Osp::Locations::ILocationListener,
	public Osp::Ui::IActionEventListener {

	public:
		LocationForm(TimeAndPlace* timeAndPlace);
		virtual ~LocationForm();
		bool Initialize(void);

		virtual result OnInitializing(void);
		virtual result OnTerminating(void);
		virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);

		virtual void OnLocationUpdated(Osp::Locations::Location& location);
		virtual void OnProviderStateChanged(Osp::Locations::LocProviderState newState);

		Osp::Base::String* DegreeToGrad(float angle, const char* posPrefix, const char* negPrefix);
		void SetTimeAndPlace(float longitude, float latitude);

	private:
		Osp::Ui::Controls::Label* __pActionLabel;
		Osp::Ui::Controls::Label* __pActionAttemptLabel;
		Osp::Ui::Controls::Label* __pGpsProviderStatusLabel;
		Osp::Locations::LocationProvider* locProvider;
		TimeAndPlace* timeAndPlace;
		int maxAttempts;
		int attemptsCounter;

};

#endif /* LOCATIONFORM_H_ */
