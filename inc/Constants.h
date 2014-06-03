/*
 * Constants.h
 *
 *  Created on: 03.06.2014
 *      Author: ddreval
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <FGraphics.h>

class Constants {
public:
	Constants();
	virtual ~Constants();
};

static const Osp::Graphics::Color COLOR_SKY (0, 255, 0);
static const Osp::Graphics::Color COLOR_BUTTON_BKG;
static const Osp::Graphics::Color COLOR_BUTTON_TEXT;
static const Osp::Graphics::Color COLOR_FORM_BKG;
static const Osp::Graphics::Color COLOR_FORM_TEXT;
static const Osp::Graphics::Color COLOR_CONSTEL_BORDER (255, 255, 0);
static const Osp::Graphics::Color COLOR_BRIGHT_STAR (255, 255, 255);
static const Osp::Graphics::Color COLOR_DIM_STAR (200, 200, 200);
static const Osp::Graphics::Color COLOR_DIMMEST_STAR (128, 128, 128);

#endif /* CONSTANTS_H_ */
