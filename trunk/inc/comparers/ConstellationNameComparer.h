/*
 * ConstellationNameComparer.h
 *
 *  Created on: 03.03.2015
 *      Author: ddreval
 */

#ifndef CONSTELLATIONNAMECOMPARER_H_
#define CONSTELLATIONNAMECOMPARER_H_

#include <FBase.h>
#include <FApp.h>

class ConstellationNameComparer :
	public Osp::Base::Collection::IComparer {

	public:
			ConstellationNameComparer();
			virtual ~ConstellationNameComparer();
			virtual result Compare(const Osp::Base::Object&, const Osp::Base::Object&, int&) const;

};

#endif /* CONSTELLATIONNAMECOMPARER_H_ */
