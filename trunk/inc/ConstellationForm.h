/*
 * ConstellationForm.h
 *
 *  Created on: 21.11.2012
 *      Author: ddreval
 */

#ifndef CONSTELLATIONFORM_H_
#define CONSTELLATIONFORM_H_

#include <FUi.h>
#include <FApp.h>

class ConstellationForm :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IItemEventListener {

	public:
		ConstellationForm();
		virtual ~ConstellationForm();
		void UpdateConstellationList(Osp::Base::Collection::IList* list);
		virtual void OnItemStateChanged(const Osp::Ui::Control& source, int index, int itemId, Osp::Ui::ItemStatus status);

	private:
		Osp::Ui::Controls::List* __pConstList;
		Osp::Base::Collection::IList* list;

};

#endif /* CONSTELLATIONFORM_H_ */
