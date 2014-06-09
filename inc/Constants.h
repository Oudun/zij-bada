/*
 * Constants.h
 *
 *  Created on: 03.06.2014
 *      Author: ddreval
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <FGraphics.h>

using Osp::Graphics::Color;

class Constants {
public:
	Constants();
	virtual ~Constants();
};

//static const Osp::Graphics::Color COLOR_SKY (0, 0, 0);
//static const Osp::Graphics::Color COLOR_BUTTON_BKG (0, 0, 0);
//static const Osp::Graphics::Color COLOR_BUTTON_TEXT (255, 255, 255);
//static const Osp::Graphics::Color COLOR_FORM_BKG(0, 255, 0);
//static const Osp::Graphics::Color COLOR_FORM_TEXT (255, 0, 0);
//static const Osp::Graphics::Color COLOR_CONSTEL_BORDER (255, 255, 0);
//static const Osp::Graphics::Color COLOR_BRIGHT_STAR (255, 255, 255);
//static const Osp::Graphics::Color COLOR_DIM_STAR (200, 200, 200);
//static const Osp::Graphics::Color COLOR_DIMMEST_STAR (128, 128, 128);

static const Osp::Graphics::Color COLOR_SKY(Color::COLOR_BLACK);
static const Osp::Graphics::Color COLOR_BUTTON_BKG(Color::COLOR_BLACK);
static const Osp::Graphics::Color COLOR_BUTTON_TEXT(Color::COLOR_WHITE);
static const Osp::Graphics::Color COLOR_FORM_BKG(Color::COLOR_BLUE);
static const Osp::Graphics::Color COLOR_FORM_TEXT(Color::COLOR_CYAN);
static const Osp::Graphics::Color COLOR_CONSTEL_BORDER(Color::COLOR_CYAN);
static const Osp::Graphics::Color COLOR_BRIGHT_STAR(Color::COLOR_WHITE);
static const Osp::Graphics::Color COLOR_DIM_STAR(Color::COLOR_GREY);
static const Osp::Graphics::Color COLOR_DIMMEST_STAR(Color::COLOR_GREY);


#endif /* CONSTANTS_H_ */
