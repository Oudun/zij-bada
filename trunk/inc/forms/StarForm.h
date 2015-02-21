/*
 * StarForm.h
 *
 *  Created on: 08.02.2015
 *      Author: Denis
 */

#ifndef STARFORM_H_
#define STARFORM_H_

#include <FUi.h>
#include <FBase.h>
#include "SkyCanvas.h"

class StarForm :
	public Osp::Ui::Controls::Form,
 	public Osp::Ui::IItemEventListener {

 	public:
		StarForm();
		virtual ~StarForm();
		bool Initialize(void);
		virtual result OnInitializing(void);
		virtual void OnItemStateChanged(const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status);
		void Update(void);

 	private:
		String& GetGreek(String& greekTranslit);
		Osp::Ui::Controls::List* __pStarsList;

};

#endif /* STARFORM_H_ */
