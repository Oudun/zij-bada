/*
 * TimeAndPlace.h
 *
 *  Created on: 24.11.2012
 *      Author: ddreval
 */

#ifndef TIMEANDPLACE_H_
#define TIMEANDPLACE_H_

#include <FBase.h>
#include <FLocales.h>
#include <FLocations.h>

class TimeAndPlace {

	public:
		TimeAndPlace();
		virtual ~TimeAndPlace();
		static void SetLongitude(float longitude);
		static void SetLatitude(float latitude);
		static void SetSiderialTime(float siderialTime);
		static float GetLongitude(void);
		static float GetLatitude(void);
		static float GetSiderialTime(void);
		static void SetSiderialTime(float longitude, float latitude, Osp::Base::DateTime* currTime);

	private:

};

static float longitude = 0.0F;
static float latitude = 0.0F;
static float siderialTime = 0.0F;


#endif /* TIMEANDPLACE_H_ */
