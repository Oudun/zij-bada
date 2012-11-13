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
#include "FIo.h"

class SkyDbIterator : public SkyIterator {

public:
	SkyDbIterator();
	SkyDbIterator(float magnitude);
	virtual ~SkyDbIterator();

public:
	bool hasNext();
	SkyObject* getNext();

private:
	Osp::Io::DbEnumerator* dataSet;
};

#endif /* SKYDBITERATOR_H_ */
