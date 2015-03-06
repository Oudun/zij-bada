/*
 * PrecisePoint.h
 *
 *  Created on: 19.02.2015
 *      Author: Denis
 */

#ifndef PRECISEPOINT_H_
#define PRECISEPOINT_H_

#include <FGraphics.h>

class PrecisePoint {

	public:
		PrecisePoint();
		PrecisePoint(float x, float y);
		void SetPosition(float x, float y);
		Osp::Graphics::Point* GetPoint(void);

	public:
		float x;
		float y;


	virtual ~PrecisePoint();
};

#endif /* PRECISEPOINT_H_ */
