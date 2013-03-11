/*
 * SkyBuilder.cpp
 *
 *  Created on: 26.11.2012
 *      Author: ddreval
 */

#include "SkyBuilder.h"
#include "SkyFactory.h"
#include "SkyIterator.h"

using namespace Osp::Base;
using namespace Osp::Base::Collection;

SkyBuilder::SkyBuilder(SkyCanvas* aSkyCanvas) {
	skyCanvas = aSkyCanvas;
	projector = new Projector();
}

SkyBuilder::~SkyBuilder() {

}

Osp::Base::Object*
SkyBuilder::Run() {
	SkyIterator* skyIterator = SkyFactory::getStars();
	ArrayList* args = new ArrayList();
	args -> Add(*(new Integer(0)));
	args -> Add(*(new Integer(skyIterator -> GetSize())));
	Osp::App::Application::GetInstance() -> SendUserEvent(BUILD_PROGRESS_RANGE_SET, args);
	AppLog("Setting progress range from 0 to %d", skyIterator -> GetSize());
	int counter = 0;
	bool isVisible = false;
	Osp::Base::Collection::IList* list;
	list = new Osp::Base::Collection::ArrayList();
	while (skyIterator -> hasNext()) {
		SkyObject* skyObject = skyIterator -> getNext();
		isVisible = skyObject -> Draw(skyCanvas);
		String constName = skyObject->getConstellation();
		if (isVisible && !list -> Contains(constName)&&constName.GetLength()>0) {
			String* str = new String(constName);
			list -> Add(*str);
		}
		counter++;
		if (counter%100 == 0) {
			args = new ArrayList();
			args -> Add(*(new Integer(counter)));
			Osp::App::Application::GetInstance() -> SendUserEvent(BUILD_PROGRESS_SET, args);
		}
	}
	args = new ArrayList();
	args -> Add(*(new Integer(skyIterator -> GetSize())));
	IEnumerator* e = list->GetEnumeratorN();
	while (e->MoveNext()==E_SUCCESS) {
		AppLog("List have %S", ((String*)e->GetCurrent())->GetPointer());
	}

	SkyCanvas::SetConstellations(list);
	Osp::App::Application::GetInstance() -> SendUserEvent(BUILD_PROGRESS_DONE, args);
	return null;
}
