/*
 * SkyFileIterator.h
 *
 *  Created on: 02.05.2012
 *      Author: ddreval
 */

#ifndef SKYFILEITERATOR_H_
#define SKYFILEITERATOR_H_

#include "SkyIterator.h"
#include "SkyObject.h"

class SkyFileIterator : public SkyIterator {
	public:
		SkyFileIterator();
		SkyFileIterator(Osp::Base::String &path);
		virtual ~SkyFileIterator();
		bool hasNext();
		SkyObject* getNext();
	private:
		Osp::Io::File file;
		long fileSize;
		result r;
		SkyObject* nextObject;
		char buffer[1];
		Osp::Base::String substr1;
		Osp::Base::String substr2;
		Osp::Base::String substr3;
		Osp::Base::String line;
		int counter;

};

#endif /* SKYFILEITERATOR_H_ */
