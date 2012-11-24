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

	private:
		float rightAccentation;
		float declination;
		float siderialTime;

};

#endif /* TIMEANDPLACE_H_ */
