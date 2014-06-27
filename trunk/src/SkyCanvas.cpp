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
SkyCanvas::Initialize(Rectangle rect) {

	int width = rect.width;
	int height = rect.height;

	starLayers = new Osp::Base::Collection::HashMapT<int, Osp::Graphics::Canvas*>();
	starLayers -> Construct();

	Font font;
	font.Construct(FONT_STYLE_BOLD, 14);

	Canvas* canvas1 = new Canvas();
	canvas1 -> Construct(Rectangle(0, 0, width, height));
	canvas1 -> SetBackgroundColor(COLOR_SKY);
	canvas1 -> SetForegroundColor(COLOR_FORM_TEXT);
	canvas1 -> FillRectangle(COLOR_SKY, Rectangle(0, 0, width, height));
	canvas1 -> SetFont(font);
	canvas1 -> DrawText(Point(width/2, (height-width)/2), "N");
	canvas1 -> DrawText(Point(width/2, (height+width)/2), "S");
	starLayers -> Add(1, canvas1);

	Canvas* canvas2 = new Canvas();
	canvas2 -> SetBackgroundColor(COLOR_SKY);
	canvas2 -> Construct(Rectangle(0, 0, 2 * width, 2 * height));
	canvas2 -> FillRectangle(COLOR_SKY, Rectangle(0, 0, 2 * width, 2 * height));
	starLayers -> Add(2, canvas2);

	Canvas* canvas4 = new Canvas();
	canvas4 -> SetBackgroundColor(COLOR_SKY);
	canvas4 -> Construct(Rectangle(0, 0, 4 * width, 4 * height));
	canvas4 -> FillRectangle(COLOR_SKY, Rectangle(0, 0, 4 * width, 4 * height));
	starLayers -> Add(4, canvas4);

//	Fails to initialize on real device :(
//	Canvas* canvas8 = new Canvas();
//	canvas8 -> SetBackgroundColor(COLOR_SKY);
//	canvas8 -> Construct(Rectangle(0, 0, 1920, 3200));
//	canvas8 -> FillRectangle(COLOR_SKY, Rectangle(0, 0, 1920, 3200));
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



