/*
 * SkyFactory.cpp
 *
 *  Created on: Feb 22, 2012
 *      Author: Denis
 */

#include "SkyFactory.h"
#include "SkyIterator.h"

SkyFactory::SkyFactory() {
	// TODO Auto-generated constructor stub

}

SkyFactory::~SkyFactory() {
	// TODO Auto-generated destructor stub
}

SkyIterator*
SkyFactory::getStars(float magnitude)
{
	AppLog("Getting stars");
	Osp::Base::String fileName(L"/Home/catalog");
	return new SkyIterator(fileName);
}




