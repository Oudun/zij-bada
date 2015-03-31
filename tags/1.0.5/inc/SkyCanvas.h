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
#include "Constants.h"

class SkyCanvas {

	public:
		SkyCanvas();
		virtual ~SkyCanvas();
		static void Initialize(void);
		static Osp::Graphics::Canvas* GetStarCanvas(int zoom);

		static void SelectConstellation(int index);
		static void SelectConstellation(String& constName);
		static Osp::Base::Collection::IList* getConstellations();
		static Osp::Base::String* GetSelectedConstellation(void);
		static void SetConstellations (Osp::Base::Collection::IList* constellationsVisible);

		static void SelectStar(int index);
		static Osp::Base::Collection::IList* getStars();
		static Osp::Base::String* GetSelectedStar(void);
		static void SetStars(Osp::Base::Collection::IList* starsVisible);

		static Osp::Base::Collection::HashMapT<int, Osp::Graphics::Canvas*>* starLayers;
		static Osp::Base::Collection::IList* constellationsVisible;
		static Osp::Base::Collection::IList* starsVisible;
		static int selectedConstellationIndex;
		static int selectedStarIndex;

};

#endif /* SKYCANVAS_H_ */
