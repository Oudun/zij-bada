/*
 * ConstellationForm.cpp
 *
 *  Created on: 21.11.2012
 *      Author: ddreval
 */

#include "ConstellationForm.h"

using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Graphics;
using namespace Osp::Ui::Controls;

ConstellationForm::ConstellationForm() {
	__pConstList = new List();
	__pConstList -> Construct(
			Rectangle(0, 0, 300, 200),
			LIST_STYLE_NORMAL,
			LIST_ITEM_SINGLE_TEXT, 20, 20, 100, 100);
	AddControl(*__pConstList);
}

ConstellationForm::~ConstellationForm() {
	// TODO Auto-generated destructor stub
}

void
ConstellationForm::UpdateConstellationList(Osp::Base::Collection::IList* list) {
	AppLog("!!!Updating constellations list");
	__pConstList -> RemoveAllItems();
	IEnumerator* constEnum = list->GetEnumeratorN();
	while (constEnum->MoveNext()==E_SUCCESS) {
		String* constName = (String*)(constEnum->GetCurrent());
		__pConstList -> AddItem(constName, constName, null, null, null);
	}
	__pConstList->Draw();
	__pConstList->Show();
}
