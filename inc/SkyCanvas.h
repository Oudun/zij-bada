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

	private:
		Osp::Base::Collection::HashMapT<int, Osp::Graphics::Canvas*>* bufferedCanvases;

};

#endif /* SKYCANVAS_H_ */
