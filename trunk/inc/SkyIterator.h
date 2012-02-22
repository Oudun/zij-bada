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
	SkyIterator(Osp::Base::String &path);
	virtual ~SkyIterator();
	bool hasNext();
	SkyObject* getNext();

private:
	Osp::Io::File file;
	char buffer[1];
	Osp::Base::String substr1;
	Osp::Base::String substr2;
	Osp::Base::String substr3;
	Osp::Base::String line;
	result r;
	SkyObject* nextObject;
};

#endif /* SKYITERATOR_H_ */
