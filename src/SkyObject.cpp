/*
 * SkyObject.cpp
 *
 *  Created on: 17.02.2012
 *      Author: ddreval
 */

#include "SkyObject.h"

SkyObject::SkyObject() {
	// TODO Auto-generated constructor stub

}

SkyObject::~SkyObject() {
	// TODO Auto-generated destructor stub
}

void
SkyObject::test(void) {
	AppLog("TEST");
}

void
setRA(Osp::Base::String& raH, Osp::Base::String&  raM, Osp::Base::String&  raS)
{
	float f;
	Osp::Base::Float::Parse(raM, f);
}
