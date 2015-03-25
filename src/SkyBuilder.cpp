/*
 * SkyBuilder.cpp
 *
 *  Created on: 26.11.2012
 *      Author: ddreval
 */

#include "SkyBuilder.h"
#include "SkyFactory.h"
#include "SkyIterator.h"
#include "comparers/ConstellationComparer.h"

using namespace Osp::Base;
using namespace Osp::Base::Collection;

SkyBuilder::SkyBuilder() {
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
	Osp::App::Application::GetInstance() -> SendUserEvent(EVENT_BUILD_PROGRESS_RANGE_SET, args);
	int counter = 0;
	bool isVisible = false;
	Osp::Base::Collection::ArrayList* __constellationsList;
	Osp::Base::Collection::ArrayList* __starsList;
	ConstellationComparer* comparer = new ConstellationComparer();
	__constellationsList = new Osp::Base::Collection::ArrayList();
	__starsList = new Osp::Base::Collection::ArrayList();
	while (skyIterator -> hasNext()) {
		SkyObject* skyObject = skyIterator -> getNext();
		isVisible = skyObject -> Draw();
		String constName = skyObject->getConstellation();
		constName.Trim();
		if (isVisible && (!__constellationsList -> Contains(constName)) && constName.GetLength()>0) {
			String* str = new String(constName);
			__constellationsList -> Add(*str);
		}
		String skyObjectName = skyObject->getName();
		if(isVisible && skyObjectName!=null && (skyObjectName.Equals("ALP", false)||skyObjectName.Equals("BET", false)||skyObjectName.Equals("GAM", false))) {
			String starGreekLetter = skyObject -> getName();
			starGreekLetter.ToUpper();

			String* fullStarKey = new String();
			fullStarKey->Format(14, L"%S_%S_%f",
					starGreekLetter.GetPointer(),
					skyObject->getConstellation().GetPointer(),
					skyObject->getMagnitude());

			String* starKey = new String();
			starKey->Format(8, L"%S_%S",
								starGreekLetter.GetPointer(),
								skyObject->getConstellation().GetPointer());

			String starName;
			Osp::App::AppResource* appResource = Osp::App::Application::GetInstance()->GetAppResource();
			appResource->GetString(*starKey, starName);
			if(starName != null) {
			__starsList -> Add(*fullStarKey);
			}
		}
		counter++;
		if (counter%500 == 0) {
			args = new ArrayList();
			args -> Add(*(new Integer(counter)));
			Osp::App::Application::GetInstance() -> SendUserEvent(EVENT_BUILD_PROGRESS_SET, args);
		}
	}
	args = new ArrayList();
	args -> Add(*(new Integer(skyIterator -> GetSize())));
	IEnumerator* e = __constellationsList->GetEnumeratorN();
	__constellationsList -> Sort(*comparer);
	SkyCanvas::SetConstellations(__constellationsList);
	SkyCanvas::SetStars(__starsList);
	delete comparer;
	Osp::App::Application::GetInstance() -> SendUserEvent(EVENT_BUILD_PROGRESS_DONE, args);
	return null;
}
