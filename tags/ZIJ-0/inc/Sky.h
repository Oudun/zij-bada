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
	Osp::Graphics::Canvas* getBufferedCanvas(int zoom);
	void setBufferedCanvas(Osp::Graphics::Canvas* canvas, int zoom);
    int getRadius() const;
    int getZenithX() const;
    int getZenithY() const;
    void setRadius(int radius);
    float getLatitude() const;
    float getLongitude() const;
    void setLatitude(float latitude);
    void setLongitude(float longitude);
    float getSiderialHours() const;
    void draw();
    void zoomIn();
    void zoomOut();
    bool canZoomIn();
    bool canZoomOut();
    int getZoom() {return zoom;};

private:
    void setSiderialHours(float siderialHours);
    Osp::Graphics::Canvas* canvas;
	static const int margin = 20;
	static const int min_zoom = 1;
	static const int max_zoom = 2;
	int zenithX;
	int zenithY;
	int radius;
	int originalRadius;
	float longitude;
	float latitude;
	float siderialHours;
	int zoom;
	bool busy;
	Osp::Graphics::Canvas* bufferedCanvas;
	Osp::Graphics::Canvas* bufferedCanvas2;
	Osp::Graphics::Canvas* bufferedCanvas4;
	Osp::Graphics::Bitmap* bitmap;
};

#endif /* SKY_H_ */
