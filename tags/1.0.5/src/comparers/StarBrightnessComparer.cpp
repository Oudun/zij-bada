/*
 * StarBrightnessComparer.cpp
 *
 *  Created on: 03.03.2015
 *      Author: ddreval
 */

#include "comparers/StarBrightnessComparer.h"

using namespace Osp::Base;
using namespace Osp::App;

StarBrightnessComparer::StarBrightnessComparer() {
	// TODO Auto-generated constructor stub

}

StarBrightnessComparer::~StarBrightnessComparer() {
	// TODO Auto-generated destructor stub
}

result
StarBrightnessComparer::Compare(const Osp::Base::Object& obj1, const Osp::Base::Object& obj2, int& cmp) const {

	String starOne;
	String starTwo;

	float brightnessOne;
	float brightnessTwo;

	((String&)obj1).SubString(8, 5, starOne);
	((String&)obj2).SubString(8, 5, starTwo);

	Float::Parse(starOne, brightnessOne);
	Float::Parse(starTwo, brightnessTwo);

	cmp = Float::Compare(brightnessOne, brightnessTwo);

	AppLog("Comparing %f and %f with result %d", brightnessOne, brightnessTwo, cmp);

	return E_SUCCESS;

}
