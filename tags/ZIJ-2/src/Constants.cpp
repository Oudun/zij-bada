/*
 * Constants.cpp
 *
 *  Created on: 03.06.2014
 *      Author: ddreval
 */

#include "Constants.h"

Constants::Constants() {
	// TODO Auto-generated constructor stub

}

Constants::~Constants() {
	// TODO Auto-generated destructor stub
}

String
Constants::GetString(String& id) {
	String localResult;
	Osp::App::AppResource* appResource = Osp::App::Application::GetInstance()->GetAppResource();
	appResource -> GetString(id, localResult);
	return localResult;
}

String*
Constants::GetStringPointer(String& id) {
	String* localResult = new String();
	Osp::App::AppResource* appResource = Osp::App::Application::GetInstance()->GetAppResource();
	appResource -> GetString(id, *localResult);
	return localResult;
}
