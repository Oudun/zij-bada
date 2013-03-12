/*
 * SkyFactory.cpp
 *
 *  Created on: Feb 22, 2012
 *      Author: Denis
 */

#include "SkyFactory.h"
#include "SkyDbIterator.h"

SkyFactory::SkyFactory() {
	// TODO Auto-generated constructor stub

}

SkyFactory::~SkyFactory() {
	// TODO Auto-generated destructor stub
}

SkyIterator*
SkyFactory::getStars(float magnitude) {
	AppLog("Getting stars with magnitude < %f", magnitude);
	SkyDbIterator* iterator = new SkyDbIterator(magnitude);
	return iterator;
}

SkyIterator*
SkyFactory::getStars() {
	return getStars(7);
}



