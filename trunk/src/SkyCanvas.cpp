/*
 * SkyCanvas.cpp
 *
 *  Created on: 27.11.2012
 *      Author: ddreval
 */

#include "SkyCanvas.h"

using namespace Osp::Graphics;
using namespace Osp::Base::Collection;

SkyCanvas::SkyCanvas() {

	bufferedCanvases = new Osp::Base::Collection::HashMapT<int, Osp::Graphics::Canvas*>();
	bufferedCanvases -> Construct();

	Canvas* canvas1 = new Canvas();
	canvas1 -> Construct(Rectangle(0, 0, 240, 400));
	canvas1 -> FillEllipse(Color::COLOR_CYAN, Rectangle(50, 150, 16, 16));
	canvas1 -> Show();
	bufferedCanvases -> Add(1, canvas1);

	Canvas* canvas2 = new Canvas();
	canvas2 -> Construct(Rectangle(0, 0, 480, 800));
	bufferedCanvases -> Add(2, canvas2);

	Canvas* canvas4 = new Canvas();
	canvas4 -> Construct(Rectangle(0, 0, 960, 1600));
	bufferedCanvases -> Add(4, canvas4);

	Canvas* canvas = GetBufferedCanvas(1);
	canvas -> FillEllipse(Color::COLOR_VIOLET, Rectangle(150, 50, 16, 16));

}

SkyCanvas::~SkyCanvas() {
	delete bufferedCanvases;
}

Osp::Graphics::Canvas*
SkyCanvas::GetBufferedCanvas(int zoom) {
	Canvas* value;
	bufferedCanvases -> GetValue(zoom, value);
	return value;
}


void
SkyCanvas::SetBufferedCanvas(Osp::Graphics::Canvas* canvas, int zoom) {
	bufferedCanvases -> Add(zoom, canvas);
}
