/*
 * SkyCanvas.h
 *
 *  Created on: 27.11.2012
 *      Author: ddreval
 */

#ifndef SKYCANVAS_H_
#define SKYCANVAS_H_

#include <FBase.h>
#include <FGraphics.h>

class SkyCanvas {

	public:
		SkyCanvas();
		virtual ~SkyCanvas();
		static void Initialize(void);
		static Osp::Graphics::Canvas* GetStarCanvas(int zoom);
		static void SelectConstellation(int index);
		static Osp::Base::Collection::IList* getConstellations();
		static void SetConstellations (Osp::Base::Collection::IList* constellationsVisible);
		static Osp::Base::String* GetSelectedConstellation(void);

};

static Osp::Base::Collection::HashMapT<int, Osp::Graphics::Canvas*>* starLayers;
static Osp::Base::Collection::IList* constellationsVisible;
static int selectedConstellationIndex = -1;
static Osp::Graphics::Color DARK_GREY(128, 128, 128);


#endif /* SKYCANVAS_H_ */
