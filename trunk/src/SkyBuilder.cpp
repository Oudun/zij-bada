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

SkyBuilder::SkyBuilder() {

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
	while (skyIterator -> hasNext()) {
		SkyObject* skyObject = skyIterator -> getNext();
		counter++;
		skyObject -> Print();
		AppLog("Setting Progress value %d", counter);
		if (counter%100 == 0) {
			args -> RemoveAll(false);
			args -> Add(*(new Integer(counter)));
			Osp::App::Application::GetInstance() -> SendUserEvent(BUILD_PROGRESS_SET, args);
		}
	}
	return null;
}

//void
//SkyBuilder::BuildSky (void) {

//}
