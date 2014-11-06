/*
 * TimeAndPlace.h
 *
 *  Created on: 24.11.2012
 *      Author: ddreval
 */

#ifndef TIMEANDPLACE_H_
#define TIMEANDPLACE_H_

#include <FBase.h>
#include <FBaseUtil.h>
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
		static Osp::Base::String* GetReadableLongitude(void);
		static Osp::Base::String* GetReadableLatitude(void);
		static float GetSiderialTime(void);
		static Osp::Base::DateTime* GetDateTime();
		static Osp::Base::String GetReadableTime();
		static Osp::Base::DateTime* GetStandardDateTime();
		static void SetSiderialTime(float longitude, float latitude, Osp::Base::DateTime* currTime);

	public:

		static float longitude;
		static float latitude;
		static float siderialTime;
		static Osp::Base::DateTime* dateTime;
		static Osp::Base::DateTime* localDateTime;

};




#endif /* TIMEANDPLACE_H_ */
