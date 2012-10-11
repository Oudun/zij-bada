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

#include "Sky.h"


class SkyObject
{

public:
	SkyObject();
	virtual ~SkyObject();

	// Setting right ascension using whole hour and minute and seconds with decimals as input
	void setRA(Osp::Base::String& raH, Osp::Base::String&  raM, Osp::Base::String&  raS);
	// Setting declination
	void setDE(Osp::Base::String& raH, Osp::Base::String&  raM, Osp::Base::String&  raS);
	// Sets name
	void setName(Osp::Base::String& name);
	// sets Draper name
	void setDraperName(Osp::Base::String& draperName);
	// Sets true if object in northern hemisphere
	void setSign(bool isNorthern);
	// Sets visual magnitude, i.e. brightness of object
	void setMagnitude(Osp::Base::String& magnitudeStr);

	// Returns right ascension in hours in decimal format
	float getRAH(void);
	// Returns declination in degrees in decimal format
	float getDED(void);
	// Returns name
	Osp::Base::String& getName(void);
	// Returns Draper name
	Osp::Base::String& getDraperName(void);
	// Returns true id object in Northern hemisphere
	bool isNorthern(void);
	// Returns visual magnitude (brightness). Lesser values have brighter stars
	float getMagnitude(void);
	// Draws object on canvas
	void draw(Sky* sky);
    void setDED(float DED);
    void setRAH(float RAH);
private:
    Osp::Base::String name;
    Osp::Base::String draperName;
    float RAH;
    float DED;
    float magnitude;
    bool sign;

};

#endif /* SKYOBJECT_H_ */

