/*
 * ConstellationComparer.h
 *
 *  Created on: Mar 24, 2013
 *      Author: Denis
 */

#ifndef CONSTELLATIONCOMPARER_H_
#define CONSTELLATIONCOMPARER_H_

#include <FBase.h>
#include <FApp.h>

class ConstellationComparer :
	public Osp::Base::Collection::IComparer

{

	public:
		ConstellationComparer();
		virtual ~ConstellationComparer();
		virtual result Compare(const Osp::Base::Object&, const Osp::Base::Object&, int&) const;
//		virtual result Compare(const Osp::Base::Object&, const Osp::Base::Object&, int&) const;

};

#endif /* CONSTELLATIONCOMPARER_H_ */
