/*
 * StarNameComparer.h
 *
 *  Created on: 03.03.2015
 *      Author: ddreval
 */

#ifndef STARNAMECOMPARER_H_
#define STARNAMECOMPARER_H_

#include <FBase.h>
#include <FApp.h>

class StarNameComparer :
	public Osp::Base::Collection::IComparer {
public:
	StarNameComparer();
	virtual ~StarNameComparer();
	virtual result Compare(const Osp::Base::Object&, const Osp::Base::Object&, int&) const;
};

#endif /* STARNAMECOMPARER_H_ */
