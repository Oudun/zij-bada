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
#include "comparers/StarNameComparer.h"
#include "comparers/ConstellationNameComparer.h"
#include "comparers/StarBrightnessComparer.h"

class StarForm :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener,
 	public Osp::Ui::IItemEventListener {

 	public:
		StarForm();
		virtual ~StarForm();
		bool Initialize(void);
		virtual result OnInitializing(void);
		virtual void OnItemStateChanged(const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status);
		virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
		void Update(void);
		void Update(Osp::Base::Collection::IList* list);

 	private:
		String& GetGreek(String& greekTranslit);
		Osp::Ui::Controls::List* __pStarsList;

		Osp::Ui::Controls::Button* __buttonSortBrightness;
		Osp::Ui::Controls::Button* __buttonSortConstellation;
		Osp::Ui::Controls::Button* __buttonSortStarName;
		Osp::Ui::Controls::Button* __buttonStarHelp;

		static const int ID_BUTTON_SORT_BRIGHTNESS = 1;
		static const int ID_BUTTON_SORT_CONSTELLATION = 2;
		static const int ID_BUTTON_SORT_NAME = 3;
		static const int ID_BUTTON_HELP = 4;


	private:
		StarNameComparer* starNameComparer;
		ConstellationNameComparer* constellationNameComparer;
		StarBrightnessComparer* starBrightnessComparer;


};

#endif /* STARFORM_H_ */
