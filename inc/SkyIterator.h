/*
 * To iterate through sky objects
 *
 *  Created on: Feb 22, 2012
 *      Author: Denis
 */

#ifndef SKYITERATOR_H_
#define SKYITERATOR_H_

#include "SkyObject.h"

class SkyIterator {

public:
	SkyIterator();
	virtual ~SkyIterator();
	virtual bool hasNext();
	virtual SkyObject* getNext();
};

#endif /* SKYITERATOR_H_ */
