/*
 * StarBrightnessComparer.h
 *
 *  Created on: 03.03.2015
 *      Author: ddreval
 */

#ifndef STARBRIGHTNESSCOMPARER_H_
#define STARBRIGHTNESSCOMPARER_H_

#include <FBase.h>
#include <FApp.h>

class StarBrightnessComparer : public Osp::Base::Collection::IComparer {

	public:
		StarBrightnessComparer();
		virtual ~StarBrightnessComparer();
		virtual result Compare(const Osp::Base::Object&, const Osp::Base::Object&, int&) const;

};

#endif /* STARBRIGHTNESSCOMPARER_H_ */
