/*
 * Constants.h
 *
 *  Created on: 03.06.2014
 *      Author: ddreval
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <FGraphics.h>
#include <FBase.h>
#include <FApp.h>

using Osp::Graphics::Color;
using Osp::Base::String;

class Constants {
	public:
		Constants();
		virtual ~Constants();
	public:
		static String GetString(String& id);
		static String* GetStringPointer(String& id);
};

static String STRING_HELP("HELP");
static String STRING_BUILDING_SKY("BUILDING_SKY");
static String STRING_GETTING_LOCATION("GETTING_LOCATION");
static String STRING_BACK("BACK");
static String STRING_ATTEMPT_NO("ATTEMPT_NO");
static String STRING_COORDINATES_TAKEN("COORDINATES_TAKEN");
static String STRING_LOC_UNAVAIL("LOC_UNAVAIL");
static String STRING_LOC_OUT("LOC_OUT");
static String STRING_LOC_TEMP_UNAVAIL("LOC_TEMP_UNAVAIL");
static String STRING_LOC_STATE_UNKNOWN("LOC_STATE_UNKNOWN");
static String STRING_SKY_COORDS("SKY_COORDS");
static String STRING_SKY_TIME("SKY_TIME");

static const int EVENT_INFO_CLOSED = 80;
static const int EVENT_HELP_CLOSED = 81;

static const Osp::Graphics::Color COLOR_SKY(Color(0, 41, 50));
static const Osp::Graphics::Color COLOR_BUTTON_BKG(Color(0, 41, 50));
static const Osp::Graphics::Color COLOR_BUTTON_TEXT(Color::COLOR_WHITE);
static const Osp::Graphics::Color COLOR_FORM_BKG(Color(50, 100, 110));
static const Osp::Graphics::Color COLOR_FORM_TEXT(Color(150, 200, 200));
static const Osp::Graphics::Color COLOR_CONSTEL_BORDER(Color(89, 139, 152));
static const Osp::Graphics::Color COLOR_BRIGHT_STAR(Color(229, 250, 255));
static const Osp::Graphics::Color COLOR_DIM_STAR(Color(89, 139, 152));
static const Osp::Graphics::Color COLOR_DIMMEST_STAR(Color(50, 100, 110));
//static const Osp::Graphics::Color COLOR_TRANSPARENT(Color(255, 255, 255, 255));


#endif /* CONSTANTS_H_ */

