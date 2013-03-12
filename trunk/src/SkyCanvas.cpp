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

}

SkyCanvas::~SkyCanvas() {
	delete starLayers;
	delete constLayers;
}

void
SkyCanvas::Initialize() {

	starLayers = new Osp::Base::Collection::HashMapT<int, Osp::Graphics::Canvas*>();
	starLayers -> Construct();

	Canvas* canvas1 = new Canvas();
	canvas1 -> Construct(Rectangle(0, 0, 240, 400));
	starLayers -> Add(1, canvas1);

	Canvas* canvas2 = new Canvas();
	canvas2 -> Construct(Rectangle(0, 0, 480, 800));
	starLayers -> Add(2, canvas2);

	Canvas* canvas4 = new Canvas();
	canvas4 -> Construct(Rectangle(0, 0, 960, 1600));
	starLayers -> Add(4, canvas4);

	Canvas* canvas8 = new Canvas();
	canvas8 -> Construct(Rectangle(0, 0, 1920, 3200));
	starLayers -> Add(8, canvas8);

	// building constellation layers

	constLayers = new Osp::Base::Collection::HashMapT<int, Osp::Graphics::Canvas*>();
	constLayers -> Construct();

	Canvas* constellationCanvas1 = new Canvas();
	constellationCanvas1 -> Construct(Rectangle(0, 0, 240, 400));
	constLayers -> Add(1, constellationCanvas1);

	Canvas* constellationCanvas2 = new Canvas();
	constellationCanvas2 -> Construct(Rectangle(0, 0, 480, 800));
	constLayers -> Add(2, constellationCanvas2);

	Canvas* constellationCanvas4 = new Canvas();
	constellationCanvas4 -> Construct(Rectangle(0, 0, 960, 1600));
	constLayers -> Add(4, constellationCanvas4);

	Canvas* constellationCanvas8 = new Canvas();
	constellationCanvas8 -> Construct(Rectangle(0, 0, 1920, 3200));
	constLayers -> Add(8, constellationCanvas8);


}

Osp::Graphics::Canvas*
SkyCanvas::GetStarCanvas(int zoom) {
	Canvas* value;
	starLayers -> GetValue(zoom, value);
	return value;
}

Osp::Graphics::Canvas*
SkyCanvas::GetConstellationCanvas(int zoom) {
	Canvas* value;
	constLayers -> GetValue(zoom, value);
	return value;
}

void
SkyCanvas::SelectConstellation(int index) {
	selectedConstellationIndex = index;
	AppLog("selectedConstellationIndex = %d", selectedConstellationIndex);
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

Osp::Base::String*
SkyCanvas::GetSelectedConstellation(void) {
	if (selectedConstellationIndex == -1) {
		return null;
	} else {
		return (Osp::Base::String*)constellationsVisible->GetAt(selectedConstellationIndex);
	}
}



