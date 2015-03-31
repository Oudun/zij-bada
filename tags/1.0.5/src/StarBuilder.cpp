/*
 * StarBuilder.cpp
 *
 *  Created on: 12.02.2015
 *      Author: Denis
 */

#include "StarBuilder.h"
#include "Projector.h"

using namespace Osp::Graphics;
using namespace Osp::App;

StarBuilder::StarBuilder() {

}

StarBuilder::~StarBuilder() {

}

void
StarBuilder::DrawCanvas(Osp::Graphics::Canvas* canvas, int zoom, int shiftX, int shiftY) {
	String* fullStarName = SkyCanvas::GetSelectedStar();
	String greekLetter;
	String constAcronym;
	String starName;
	fullStarName->SubString(0, 3, greekLetter);
	fullStarName->SubString(4, 3, constAcronym);
	fullStarName->SubString(0, 7, starName);
	AppLog("Drawing %S %S", greekLetter.GetPointer(), constAcronym.GetPointer());
	SkyObject* namedStar = SkyFactory::getStar(&greekLetter, &constAcronym);
	if (namedStar !=null) {
		AppLog("Getting %S", namedStar->getName().GetPointer());

		PrecisePoint* zoomedVertex = Projector::
				GetProjection(
						namedStar->getRAH(),
						namedStar->getDED(),
						namedStar->isNorthern() ? 1 : 0,
						zoom*canvas->GetBounds().width,
						zoom*canvas->GetBounds().height);

		if (zoomedVertex != null) {
			int x = zoomedVertex -> x;
			int y = zoomedVertex -> y;
			int diameter = namedStar -> GetSizeOnCanvas();

			AppLog("??%S %S X:%d Y:%d", namedStar->getName().GetPointer(), namedStar->getConstellation().GetPointer(), x, y);

			zoomedVertex -> SetPosition(x - shiftX, y - shiftY);
			canvas -> SetForegroundColor(COLOR_SELECTED_STAR);
			canvas -> FillEllipse(COLOR_SELECTED_STAR, Rectangle(zoomedVertex->x, zoomedVertex->y, diameter, diameter));

			AppLog("%S %S X:%d Y:%d", namedStar->getName().GetPointer(), namedStar->getConstellation().GetPointer(), zoomedVertex->x, zoomedVertex->y);

			String starLongName;
			AppResource* appResource = Application::GetInstance()->GetAppResource();
			appResource->GetString(starName, starLongName);

			canvas -> DrawText(Point(zoomedVertex->x, zoomedVertex->y+5), starLongName.GetPointer());
		}
	} else {
		AppLog("No star %S in catalog", namedStar->getName().GetPointer());
	}
}

