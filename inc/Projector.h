/*
 * Projector.h
 *
 *  Created on: 27.11.2012
 *      Author: ddreval
 */

#ifndef PROJECTOR_H_
#define PROJECTOR_H_

#include <FGraphics.h>
#include <FBase.h>
#include "TimeAndPlace.h"
#include "PrecisePoint.h"

class Projector {

	public:
		Projector();
		virtual ~Projector();
		static PrecisePoint* GetProjection(
				float accentation,
				float declination,
				int sign,
				int width,
				int height);
		static void Zoom(
				PrecisePoint* source,
				PrecisePoint* result,
				int ratio);
		static Osp::Base::String** screenToConstMap;

};

#endif /* PROJECTOR_H_ */

