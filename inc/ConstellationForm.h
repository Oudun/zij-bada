/*
 * ConstellationForm.h
 *
 *  Created on: 21.11.2012
 *      Author: ddreval
 */

#ifndef CONSTELLATIONFORM_H_
#define CONSTELLATIONFORM_H_

#include <FUi.h>

class ConstellationForm : public Osp::Ui::Controls::Form {

	public:
		ConstellationForm();
		virtual ~ConstellationForm();
		void UpdateConstellationList(Osp::Base::Collection::IList* list);

	private:
		Osp::Ui::Controls::List* __pConstList;

};

#endif /* CONSTELLATIONFORM_H_ */
