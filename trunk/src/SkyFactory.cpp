/*
 * SkyFactory.cpp
 *
 *  Created on: Feb 22, 2012
 *      Author: Denis
 */

#include "SkyFactory.h"
#include "SkyFileIterator.h"
#include "SkyMemoryIterator.h"

SkyFactory::SkyFactory() {
	// TODO Auto-generated constructor stub

}

SkyFactory::~SkyFactory() {
	// TODO Auto-generated destructor stub
}

SkyIterator*
SkyFactory::getStars(float magnitude)
{
	AppLog("Getting stars with magnitude < %f", magnitude);
	Osp::Base::String fileName(L"/Home/catalogue-");
	fileName.Append(magnitude);
	SkyFileIterator* iterator = new SkyFileIterator(fileName);
	return iterator;
//	return new SkyMemoryIterator();
}




