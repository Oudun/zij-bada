/*
 * ConstellationDbIterator.h
 *
 *  Created on: 11.03.2013
 *      Author: ddreval
 */

#ifndef CONSTELLATIONDBITERATOR_H_
#define CONSTELLATIONDBITERATOR_H_

#include "SkyObject.h"
#include <FIo.h>

class ConstellationDbIterator {

	public:
		ConstellationDbIterator(Osp::Base::String* name);
		virtual ~ConstellationDbIterator();

	public:
		bool HasNext();
		SkyObject* GetNext();
		Osp::Base::Collection::IListT<SkyObject*>* GetVertexes (void);

	private:
		Osp::Io::DbEnumerator* dataSet;
		Osp::Io::Database* database;
		SkyObject* nextObject;
		int counter;
		Osp::Base::Collection::IListT<SkyObject&>* vertexes;
};


#endif /* CONSTELLATIONDBITERATOR_H_ */
