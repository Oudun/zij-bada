/*
 * Projector.h
 *
 *  Created on: 27.11.2012
 *      Author: ddreval
 */

#ifndef PROJECTOR_H_
#define PROJECTOR_H_

#include <FGraphics.h>
#include "TimeAndPlace.h"

class Projector {

	public:
		Projector();
		virtual ~Projector();
		static Osp::Graphics::Point* GetProjection(
				float accentation,
				float declination,
				int sign,
				int width,
				int height);

};

#endif /* PROJECTOR_H_ */
