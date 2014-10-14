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

	IList* zoomedVertexes;
	zoomedVertexes = new ArrayList();

	Osp::Base::Collection::IEnumeratorT<SkyObject*>* e;

	e = vertexes -> GetEnumeratorN();
	while (e -> MoveNext() == E_SUCCESS) {
		SkyObject* vertex;
		e -> GetCurrent(vertex);
		Point* zoomedVertex = Projector::
				GetProjection(
						vertex->getRAH(),
						vertex->getDED(),
						vertex->isNorthern() ? 1 : 1,
						zoom*canvas->GetBounds().width,
						zoom*canvas->GetBounds().height);
		if (zoomedVertex != null) {
			int x = zoomedVertex -> x;
			int y = zoomedVertex -> y;
			zoomedVertex -> SetPosition(x - shiftX, y - shiftY);
			zoomedVertexes -> Add(*zoomedVertex);
		}
	}

	canvas -> SetForegroundColor(COLOR_CONSTEL_BORDER);
	canvas -> DrawPolygon(*zoomedVertexes);

}

