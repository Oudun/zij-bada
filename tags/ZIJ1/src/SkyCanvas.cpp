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
	bufferedCanvases -> Add(1, canvas1);

	Canvas* canvas2 = new Canvas();
	canvas2 -> Construct(Rectangle(0, 0, 480, 800));
	bufferedCanvases -> Add(2, canvas2);

	Canvas* canvas4 = new Canvas();
	canvas4 -> Construct(Rectangle(0, 0, 960, 1600));
	bufferedCanvases -> Add(4, canvas4);

	Canvas* canvas8 = new Canvas();
	canvas8 -> Construct(Rectangle(0, 0, 1920, 3200));
	bufferedCanvases -> Add(8, canvas8);


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

void
SkyCanvas::SelectConstellation(Osp::Base::String* constellationName) {
	selectedConstellation = constellationName;
}

Osp::Base::Collection::IList*
SkyCanvas::getConstellations() {
	return constellationsVisible;
}

void
SkyCanvas::SetConstellations (Osp::Base::Collection::IList* aConstellationsVisible) {
//SkyCanvas::SetConstellations () {
	AppLog("SetConstellations");
	constellationsVisible = aConstellationsVisible;
}

