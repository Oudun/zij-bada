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
ConstellationBuilder::Build(Osp::Base::String* name) {

	AppLog("Start building %S", name->GetPointer());
	constelDbIterator = new ConstellationDbIterator(name);

	SkyCanvas::GetConstellationCanvas(1) -> Clear();
	SkyCanvas::GetConstellationCanvas(2) -> Clear();
	SkyCanvas::GetConstellationCanvas(4) -> Clear();
	SkyCanvas::GetConstellationCanvas(8) -> Clear();

	IListT<SkyObject*>* vertexes;
	vertexes = constelDbIterator -> GetVertexes();

	delete constelDbIterator;

	Osp::App::Application::GetInstance() -> SendUserEvent(CONSTELLATION_READY, null);

}

void
ConstellationBuilder::Draw(IListT<SkyObject*>* vertexes) {
	Canvas* canvas;
	canvas = SkyCanvas::GetConstellationCanvas(1);
	DrawCanvas(vertexes, canvas);
}

void
ConstellationBuilder::DrawCanvas(IListT<SkyObject*>* vertexes, Canvas* canvas) {

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
						canvas->GetBounds().width,
						canvas->GetBounds().height);
		zoomedVertexes -> Add(*zoomedVertex);
	}

	canvas -> DrawPolygon(*zoomedVertexes);

}

