/*
 * Sky.h
 * Where all stars and other sky object placed.
 *  Created on: 21.02.2012
 *      Author: ddreval
 */

#ifndef SKY_H_
#define SKY_H_

#include <FLocations.h>
#include <FLocales.h>
#include "SkyObject.h"
#include "SkyCanvas.h"

class Sky {
public:
	Sky();
	Sky(Osp::Graphics::Canvas* canvas, SkyCanvas* skyCanvas);
	void paintBorders(void);
	virtual ~Sky();
	Osp::Graphics::Canvas* getCanvas(void);
    void draw();
    void zoomIn();
    void zoomOut();
    bool canZoomIn();
    bool canZoomOut();
    int getZoom() {return zoom;};
    Osp::Base::Collection::IList* getConst(void);

private:
//    void setSiderialHours(float siderialHours);
    Osp::Graphics::Canvas* canvas;
	static const int margin = 20;
	static const int min_zoom = 1;
	static const int max_zoom = 8;
	int zenithX;
	int zenithY;
	int radius;
	int originalRadius;
	float longitude;
	float latitude;
	float siderialHours;
	int zoom;
	bool busy;
	Osp::Graphics::Bitmap* bitmap;
	Osp::Base::Collection::IList* visibleConst;
	SkyCanvas* skyCanvas;
};

#endif /* SKY_H_ */
