/*
 * ConstellationBuilder.h
 *
 *  Created on: 11.03.2013
 *      Author: ddreval
 */

#ifndef CONSTELLATIONBUILDER_H_
#define CONSTELLATIONBUILDER_H_

#include "ConstellationDbIterator.h"
#include <FBase.h>

using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Graphics;

class ConstellationBuilder {

	public:
		ConstellationBuilder();
		virtual ~ConstellationBuilder();
		static void Build(Osp::Base::String* name);

		static const int CONSTELLATION_READY = 50;

	private:
		static void Draw(IListT<SkyObject*>* vertexes);
		static void DrawCanvas(IListT<SkyObject*>* vertexes, Canvas* canvas);


};

static ConstellationDbIterator* constelDbIterator;

#endif /* CONSTELLATIONBUILDER_H_ */
