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
}

void
SkyCanvas::Initialize() {

	Color skyColor(Color::COLOR_GREEN);
	//skyColor.SetColorComponents(0, 0, 0, 125);

	starLayers = new Osp::Base::Collection::HashMapT<int, Osp::Graphics::Canvas*>();
	starLayers -> Construct();

	Canvas* canvas1 = new Canvas();
	canvas1 -> Construct(Rectangle(0, 0, 240, 400));
	canvas1 -> SetBackgroundColor(skyColor);
	starLayers -> Add(1, canvas1);

	Canvas* canvas2 = new Canvas();
	canvas2 -> SetBackgroundColor(skyColor);
	canvas2 -> Construct(Rectangle(0, 0, 480, 800));
	starLayers -> Add(2, canvas2);

	Canvas* canvas4 = new Canvas();
	canvas4 -> SetBackgroundColor(skyColor);
	canvas4 -> Construct(Rectangle(0, 0, 960, 1600));
	starLayers -> Add(4, canvas4);
//
//	Canvas* canvas8 = new Canvas();
//	canvas8 -> SetBackgroundColor(skyColor);
//	canvas8 -> Construct(Rectangle(0, 0, 1920, 3200));
//	starLayers -> Add(8, canvas8);

}

Osp::Graphics::Canvas*
SkyCanvas::GetStarCanvas(int zoom) {
	Canvas* value;
	starLayers -> GetValue(zoom, value);
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



