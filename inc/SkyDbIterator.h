/*
 * SkyDbIterator.h
 *
 *  Created on: 24.10.2012
 *      Author: ddreval
 */

#ifndef SKYDBITERATOR_H_
#define SKYDBITERATOR_H_

#include "SkyIterator.h"
#include "SkyObject.h"

class SkyDbIterator : public SkyIterator {

public:
	SkyDbIterator();
	virtual ~SkyDbIterator();

public:
	virtual ~SkyFileIterator();
	bool hasNext();
	SkyObject* getNext();

};

#endif /* SKYDBITERATOR_H_ */
