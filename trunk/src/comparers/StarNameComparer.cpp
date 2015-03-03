/*
 * StarNameComparer.cpp
 *
 *  Created on: 03.03.2015
 *      Author: ddreval
 */

#include "comparers/StarNameComparer.h"

using namespace Osp::Base;
using namespace Osp::App;

StarNameComparer::StarNameComparer() {
	// TODO Auto-generated constructor stub

}

StarNameComparer::~StarNameComparer() {
	// TODO Auto-generated destructor stub
}

result
StarNameComparer::Compare(const Osp::Base::Object& obj1, const Osp::Base::Object& obj2, int& cmp) const {

	String& constAcronymOne = (String&)obj1;
	String& constAcronymTwo = (String&)obj2;

	String constNameOne(L"");
	String constNameTwo(L"");

	AppResource* appResource = Osp::App::Application::GetInstance()->GetAppResource();

	appResource ->GetString(constAcronymOne, constNameOne);
	appResource ->GetString(constAcronymTwo, constNameTwo);

	cmp = Osp::Base::String::Compare(constNameOne, constNameTwo);

	AppLog("Comparing %S and %S with result %d", constNameOne.GetPointer(), constNameTwo.GetPointer(), cmp);

	return E_SUCCESS;
}
