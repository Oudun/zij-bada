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
		Osp::Graphics::Canvas* GetBufferedCanvas(int zoom);
		void SetBufferedCanvas(Osp::Graphics::Canvas* canvas, int zoom);
		static void SelectConstellation(Osp::Base::String* constellationName);
		static Osp::Base::Collection::IList* getConstellations();
		static void SetConstellations (Osp::Base::Collection::IList* constellationsVisible);
//		static void SetConstellations(void);

	private:
		Osp::Base::Collection::HashMapT<int, Osp::Graphics::Canvas*>* bufferedCanvases;

};

static Osp::Base::Collection::IList* constellationsVisible;
static Osp::Base::String* selectedConstellation;


#endif /* SKYCANVAS_H_ */
