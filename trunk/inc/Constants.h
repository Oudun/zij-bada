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
static String STRING_SORT_STAR_BRIGHTNESS("SORT_STAR_BRIGHTNESS");
static String STRING_SORT_STAR_NAME("SORT_STAR_NAME");
static String STRING_SORT_STAR_CONST_NAME("SORT_STAR_CONST_NAME");

static String STRING_ALPHA("α");
static String STRING_BETA("β");
static String STRING_GAMMA("γ");
static String STRING_UNDEF("?");

static const int EVENT_LOCATION_SET = 1;
static const int EVENT_LOCATION_FAILED = 2;
static const int EVENT_BUILD_PROGRESS_RANGE_SET = 20;
static const int EVENT_BUILD_PROGRESS_SET = 21;
static const int EVENT_BUILD_PROGRESS_DONE = 22;
static const int EVENT_SELECT_CONSTELLATION = 30;
static const int EVENT_SHOW_HELP = 32;
static const int EVENT_SHOW_INFO = 31;
static const int EVENT_SHOW_STARS = 33;
static const int EVENT_CONSTELLATION_SELECTED = 40;
static const int EVENT_STAR_SELECTED = 41;
static const int EVENT_CONSTELLATION_TOUCHED = 42;
static const int EVENT_USE_PREV_LOCATION = 50;
static const int EVENT_USE_MAP_LOCATION = 51;
static const int EVENT_INFO_CLOSED = 80;
static const int EVENT_HELP_CLOSED = 81;
static const int EVENT_STAR_HELP = 90;
static const int EVENT_STAR_HELP_CLOSED = 91;


static const Osp::Graphics::Color COLOR_SKY(Color(0, 41, 50));
static const Osp::Graphics::Color COLOR_BUTTON_BKG(Color(0, 41, 50));
static const Osp::Graphics::Color COLOR_BUTTON_TEXT(Color::COLOR_WHITE);
static const Osp::Graphics::Color COLOR_FORM_BKG(Color(50, 100, 110));
static const Osp::Graphics::Color COLOR_FORM_TEXT(Color(150, 200, 200));
static const Osp::Graphics::Color COLOR_CONSTEL_BORDER(Color(89, 139, 152));
static const Osp::Graphics::Color COLOR_DIMMEST_STAR(Color(50, 100, 110));
static const Osp::Graphics::Color& COLOR_BRIGHT_STAR(Color(229, 250, 255));
static const Osp::Graphics::Color& COLOR_DIM_STAR(Color(89, 139, 152));
static const Osp::Graphics::Color& COLOR_SELECTED_STAR(Color(255, 165, 85));


//static const Osp::Graphics::Color COLOR_TRANSPARENT(Color(255, 255, 255, 255));


#endif /* CONSTANTS_H_ */

