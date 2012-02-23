/*
 * Sky.h
 * Where all stars and other sky object placed.
 *  Created on: 21.02.2012
 *      Author: ddreval
 */

#ifndef SKY_H_
#define SKY_H_

#include <FBase.h>
#include <FGraphics.h>
#include <FSystem.h>
#include <FApp.h>
#include <FLocations.h>
#include <FLocales.h>
#include <FGraphics.h>

class Sky {
public:
	Sky();
	Sky(Osp::Graphics::Canvas* canvas);
	void paintBorders(void);
	virtual ~Sky();
	Osp::Graphics::Canvas* getCanvas(void);
    int getRadius() const;
    int getZenithX() const;
    int getZenithY() const;
    void setRadius(int radius);
    float getLatitude() const;
    float getLongitude() const;
    void setLatitude(float latitude);
    void setLongitude(float longitude);
    float getSiderialHours() const;
    void setSiderialHours(float siderialHours);

private:
	Osp::Graphics::Canvas* canvas;
	static const int margin = 20;
	int zenithX;
	int zenithY;
	int radius;
	float longitude;
	float latitude;
	float siderialHours;
};

#endif /* SKY_H_ */
