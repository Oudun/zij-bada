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
		public void SetLongitude(float longitude);
		public void SetLatitude(float latitude);
		public void SetSiderialTime(float siderialTime);
		public float GetLongitude(void);
		public float GetLatitude(void);
		public float GetSiderialTime(void);

	private:
		float rightAccentation;
		float declination;
		float siderialTime;

};

#endif /* TIMEANDPLACE_H_ */
