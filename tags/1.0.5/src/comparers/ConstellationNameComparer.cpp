/*
 * ConstellationNameComparer.cpp
 *
 *  Created on: 03.03.2015
 *      Author: ddreval
 */

#include "comparers/ConstellationNameComparer.h"

using namespace Osp::Base;
using namespace Osp::App;

ConstellationNameComparer::ConstellationNameComparer() {
	// TODO Auto-generated constructor stub

}

ConstellationNameComparer::~ConstellationNameComparer() {
	// TODO Auto-generated destructor stub
}

result
ConstellationNameComparer::Compare(const Osp::Base::Object& obj1, const Osp::Base::Object& obj2, int& cmp) const {

	String constAcronymOne;
	String constAcronymTwo;

	((String&)obj1).SubString(4, 3, constAcronymOne);
	((String&)obj2).SubString(4, 3, constAcronymTwo);

	AppLog("Comparing constellation names %S and %S", constAcronymOne.GetPointer(), constAcronymTwo.GetPointer());

	String constNameOne(L"");
	String constNameTwo(L"");

	AppResource* appResource = Osp::App::Application::GetInstance()->GetAppResource();

	appResource ->GetString(constAcronymOne, constNameOne);
	appResource ->GetString(constAcronymTwo, constNameTwo);

	cmp = Osp::Base::String::Compare(constNameOne, constNameTwo);

	AppLog("Comparing %S and %S with result %d", constNameOne.GetPointer(), constNameTwo.GetPointer(), cmp);

	return E_SUCCESS;
}
