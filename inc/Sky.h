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

class Sky {
public:
	Sky();
	Sky(Osp::Graphics::Canvas* canvas);
	void paintBorders(void);
	virtual ~Sky();

private:
	int zenithX;
	int zenithY;
	int radius;
	static const int margin = 20;
	Osp::Graphics::Canvas* canvas;
};

#endif /* SKY_H_ */
