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

	String sequence(L"");
	String* constellationName = SkyCanvas::GetSelectedConstellation();
	sequence.Append(*constellationName);
	constelDbIterator = new ConstellationDbIterator(constellationName);
	IListT<SkyObject*>* vertexes = constelDbIterator -> GetVertexes();

	IListT<SkyObject*>* vertexes2 = new ArrayListT<SkyObject*>();

	vertexes2 -> AddItems(*vertexes);
	SkyObject* firstStar;
	vertexes -> GetAt(0, firstStar);
	vertexes2 -> Add(firstStar);

	IList* zoomedVertexesStart;
	IList* zoomedVertexesEnd;
	zoomedVertexesStart = new ArrayList();
	zoomedVertexesEnd = new ArrayList();

	Osp::Base::Collection::IEnumeratorT<SkyObject*>* e;

	e = vertexes2 -> GetEnumeratorN();

	SkyObject* starAtStart;
	SkyObject* starAtEnd;
	SkyObject* starAtMiddle;
	int GRANULARITY = 4;

	e -> MoveNext();
	e -> GetCurrent(starAtStart);
	starAtMiddle = new SkyObject();

	bool __isVisible = false;
	bool __isTorn = false;

	while (e->MoveNext() == E_SUCCESS) {
		e -> GetCurrent(starAtEnd);

		AppLog("Iterating constellation stars RAH %f DED %f SIGN %d", starAtEnd->getRAH(), starAtEnd->getDED(), starAtEnd->isNorthern());

		if (((starAtEnd -> getRAH())-(starAtStart -> getRAH())) > 12) {
			starAtEnd -> setRAH(starAtEnd -> getRAH() - 24);
		} else if (((starAtEnd -> getRAH())-(starAtStart -> getRAH())) < -12) {
			starAtEnd -> setRAH(starAtEnd -> getRAH() + 24);
		}

		for (int i=0; i<GRANULARITY ; i++) {

			starAtMiddle -> setDED((i*(starAtEnd -> getDED()) + (GRANULARITY - i)*(starAtStart -> getDED()))/GRANULARITY);
			starAtMiddle -> setRAH((i*(starAtEnd -> getRAH()) + (GRANULARITY - i)*(starAtStart -> getRAH()))/GRANULARITY);
			//starAtMiddle -> setSign(starAtStart->isNorthern()); //todo - rewrite
			if (starAtStart->isNorthern()==starAtEnd->isNorthern()) {
				starAtMiddle -> setSign(starAtStart->isNorthern());
			} else {
				float f1 = starAtStart -> getDED() * (starAtStart->isNorthern()? 1.0 : -1.0);
				float f2 = starAtEnd -> getDED()* (starAtEnd->isNorthern()? 1.0 : -1.0);
				float f = (f1*((float)(GRANULARITY-i)) + f2*(float)i)/(float)GRANULARITY;
				AppLog("Start %f Middle %f End %f", f1, f, f2);
				starAtMiddle -> setSign(f > 0 ? 1 : 0);
			}

			//starAtMiddle -> setSign(starAtStart->isNorthern())

			//AppLog("Start DED %f RAH %f Middle #%d DED %f RAH %f      DIFF %f", starAtStart->getDED(), starAtStart->getRAH(),
			//		i, starAtMiddle ->getDED(), starAtMiddle -> getRAH(), starAtStart->getDED()-starAtMiddle->getDED());

			PrecisePoint* zoomedVertex = Projector::
					GetProjection(
							starAtMiddle -> getRAH(),
							starAtMiddle -> getDED(),
							starAtMiddle -> isNorthern() ? 1 : 0,
							zoom*canvas -> GetBounds().width,
							zoom*canvas -> GetBounds().height);
			if (zoomedVertex != null) {
				__isVisible = true;
				int x = zoomedVertex -> x;
				int y = zoomedVertex -> y;
				zoomedVertex -> SetPosition(x - shiftX, y - shiftY);
				if (!__isTorn) {
					zoomedVertexesEnd -> Add(*(zoomedVertex->GetPoint()));
				} else {
					zoomedVertexesStart -> Add(*(zoomedVertex->GetPoint()));
				}
				sequence.Append("+");
			} else {
				__isTorn = true;
				sequence.Append("-");
			}
		}

		starAtStart = starAtEnd;

	}

	AppLog("Constellation sequence %S", sequence.GetPointer());

	canvas -> SetForegroundColor(COLOR_CONSTEL_BORDER);
	zoomedVertexesStart -> AddItems(*zoomedVertexesEnd);
	DrawPolygons(canvas, zoomedVertexesStart, __isTorn);
	//DrawPolygons(canvas, zoomedVertexesEnd);

}

void
ConstellationBuilder::DrawPolygons(Canvas* canvas, IList* vertexes, bool isTorn) {
	if (vertexes == null || vertexes -> GetCount() == 0) {
		return;
	}
	AppLog("list has %d elements ", vertexes -> GetCount());
	IEnumerator* e = vertexes -> GetEnumeratorN();
	e ->MoveNext();
	Point* firstPoint = (Point*)(e ->GetCurrent());
	Point* startPoint = (Point*)(e ->GetCurrent());
	Point* nextPoint;
	while (e -> MoveNext() == E_SUCCESS) {
		nextPoint = (Point*)(e -> GetCurrent());
		canvas -> DrawLine(*startPoint, *nextPoint);
		startPoint = nextPoint;
	}
	if (!isTorn) {
		canvas -> DrawLine(*nextPoint, *firstPoint);
	}
}

