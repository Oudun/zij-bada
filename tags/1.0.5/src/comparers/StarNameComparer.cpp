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

	String starNameAcronymOne;
	String starNameAcronymTwo;
	String starNameOne;
	String starNameTwo;

	((String&)obj1).SubString(0, 7, starNameAcronymOne);
	((String&)obj2).SubString(0, 7, starNameAcronymTwo);

	AppResource* appResource = Osp::App::Application::GetInstance()->GetAppResource();

	appResource ->GetString(starNameAcronymOne, starNameOne);
	appResource ->GetString(starNameAcronymTwo, starNameTwo);

	cmp = Osp::Base::String::Compare(starNameOne, starNameTwo);

	AppLog("Comparing %S and %S with result %d", starNameOne.GetPointer(), starNameTwo.GetPointer(), cmp);

	return E_SUCCESS;
}
