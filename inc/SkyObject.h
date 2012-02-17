/*
 * SkyObject.h
 *
 *  Created on: 17.02.2012
 *      Author: ddreval
 */

#ifndef SKYOBJECT_H_
#define SKYOBJECT_H_

#include <FBase.h>
#include <FGraphics.h>
#include <FMedia.h>
#include <FApp.h>
#include <FUi.h>
#include <FSystem.h>
#include <FLocations.h>
#include <FLocales.h>
#include <FIo.h>

class SkyObject
{

public:
	SkyObject();
	virtual ~SkyObject();
	void setRA(Osp::Base::String& raH, Osp::Base::String&  raM, Osp::Base::String&  raS);
	void test(void);

private:
	Osp::Base::String name;
	Osp::Base::String draperName;
	float RAH;
	float RAM;
	float RAS;
//    String name = str.substring(5, 14);
//    String draperName = str.substring(25, 31);
//    String rahStr = str.substring(75,77);
//    String ramStr = str.substring(77,79);
//    String rasStr = str.substring(79,83);
//    String dedStr = str.substring(84,86);
//    String demStr = str.substring(86,88);
//    String desStr = str.substring(88,90);
//    String sign = str.substring(83,84);

};

#endif /* SKYOBJECT_H_ */

