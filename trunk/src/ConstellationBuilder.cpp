/*
 * ConstellationBuilder.cpp
 *
 *  Created on: 11.03.2013
 *      Author: ddreval
 */

#include "ConstellationBuilder.h"
#include "SkyCanvas.h"
#include "Projector.h"
#include "SkyDbIterator.h"
#include "SkyObject.h"

ConstellationDbIterator* ConstellationBuilder::constelDbIterator;

using namespace Osp::Graphics;
using namespace Osp::Base;
using namespace Osp::Base::Collection;

ConstellationBuilder::ConstellationBuilder() {
	// TODO Auto-generated constructor stub

}

ConstellationBuilder::~ConstellationBuilder() {
	// TODO Auto-generated destructor stub
}

void
ConstellationBuilder::DrawCanvas(Canvas* canvas, int zoom, int shiftX, int shiftY) {

	String* constellationName = SkyCanvas::GetSelectedConstellation();
	constelDbIterator = new ConstellationDbIterator(constellationName);
	IListT<SkyObject*>* vertexes = constelDbIterator -> GetVertexes();

	IListT<SkyObject*>* vertexes2 = new ArrayListT<SkyObject*>();

	vertexes2 -> AddItems(*vertexes);
	SkyObject* firstStar;
	vertexes -> GetAt(0, firstStar);
	vertexes2 -> Add(firstStar);

	IList* zoomedVertexes;
	zoomedVertexes = new ArrayList();

	Osp::Base::Collection::IEnumeratorT<SkyObject*>* e;

	e = vertexes2 -> GetEnumeratorN();

	SkyObject* starAtStart;
	SkyObject* starAtEnd;
	SkyObject* starAtMiddle;
	int GRANULARITY = 16;

	e -> MoveNext();
	e -> GetCurrent(starAtStart);
	starAtMiddle = new SkyObject();

	while (e->MoveNext() == E_SUCCESS) {
		e -> GetCurrent(starAtEnd);

		if (((starAtEnd -> getRAH())-(starAtStart -> getRAH())) > 12) {
			AppLog("Big difference start %f end %f diff %f",
					starAtStart -> getRAH(),
					starAtEnd -> getRAH(),
					(starAtEnd -> getRAH()) - (starAtStart -> getRAH()));
			starAtEnd -> setRAH(starAtEnd -> getRAH() - 24);
			AppLog("End point reset to %f", starAtEnd -> getRAH());
		} else if (((starAtEnd -> getRAH())-(starAtStart -> getRAH())) < -12) {
			AppLog("Big difference start %f end %f diff %f",
					starAtStart -> getRAH(),
					starAtEnd -> getRAH(),
					(starAtEnd -> getRAH()) - (starAtStart -> getRAH()));
			starAtEnd -> setRAH(starAtEnd -> getRAH() + 24);
			AppLog("End point reset to %f", starAtEnd -> getRAH());
		}

		for (int i=0; i<GRANULARITY ; i++) {

			starAtMiddle -> setDED((i*(starAtEnd -> getDED()) + (GRANULARITY - i)*(starAtStart -> getDED()))/GRANULARITY);
			starAtMiddle -> setRAH((i*(starAtEnd -> getRAH()) + (GRANULARITY - i)*(starAtStart -> getRAH()))/GRANULARITY);
			starAtMiddle -> setSign(starAtStart->isNorthern()); //todo - rewrite

			AppLog("Start DED %f RAH %f Middle #%d DED %f RAH %f      DIFF %f", starAtStart->getDED(), starAtStart->getRAH(),
					i, starAtMiddle ->getDED(), starAtMiddle -> getRAH(), starAtStart->getDED()-starAtMiddle->getDED());

			PrecisePoint* zoomedVertex = Projector::
					GetProjection(
							starAtMiddle -> getRAH(),
							starAtMiddle -> getDED(),
							starAtMiddle -> isNorthern() ? 1 : 1,
							zoom*canvas -> GetBounds().width,
							zoom*canvas -> GetBounds().height);
			if (zoomedVertex != null) {
				int x = zoomedVertex -> x;
				int y = zoomedVertex -> y;
				zoomedVertex -> SetPosition(x - shiftX, y - shiftY);
				zoomedVertexes -> Add(*(zoomedVertex->GetPoint()));
			} else {

			}
		}

		starAtStart = starAtEnd;

	}

//
//	while (e -> MoveNext() == E_SUCCESS) {
//		SkyObject* vertex;
//		e -> GetCurrent(vertex);
//		PrecisePoint* zoomedVertex = Projector::
//				GetProjection(
//						vertex->getRAH(),
//						vertex->getDED(),
//						vertex->isNorthern() ? 1 : 1,
//						zoom*canvas->GetBounds().width,
//						zoom*canvas->GetBounds().height);
//		if (zoomedVertex != null) {
//			int x = zoomedVertex -> x;
//			int y = zoomedVertex -> y;
//			zoomedVertex -> SetPosition(x - shiftX, y - shiftY);
//			zoomedVertexes -> Add(*(zoomedVertex->GetPoint()));
//		}
//	}

	canvas -> SetForegroundColor(COLOR_CONSTEL_BORDER);
	canvas -> DrawPolygon(*zoomedVertexes);

}

