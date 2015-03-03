/*
 * StarBuilder.h
 *
 *  Created on: 12.02.2015
 *      Author: Denis
 */

#ifndef STARBUILDER_H_
#define STARBUILDER_H_

#include "SkyCanvas.h"
#include "SkyObject.h"
#include "SkyFactory.h"

class StarBuilder {

	public:
		StarBuilder();
		virtual ~StarBuilder();
		static void DrawCanvas(Osp::Graphics::Canvas* canvas, int zoom, int shiftX, int shiftY);

};

#endif /* STARBUILDER_H_ */
