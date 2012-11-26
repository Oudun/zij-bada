/*
 * TimeAndPlace.h
 *
 *  Created on: 24.11.2012
 *      Author: ddreval
 */

#ifndef TIMEANDPLACE_H_
#define TIMEANDPLACE_H_

class TimeAndPlace {

	public:
		TimeAndPlace();
		virtual ~TimeAndPlace();
		void SetLongitude(float longitude);
		void SetLatitude(float latitude);
		void SetSiderialTime(float siderialTime);
		float GetLongitude(void);
		float GetLatitude(void);
		float GetSiderialTime(void);

	private:
		float longitude;
		float latitude;
		float siderialTime;

};

#endif /* TIMEANDPLACE_H_ */
