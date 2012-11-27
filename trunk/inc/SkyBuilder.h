/*
 * SkyBuilder.h
 *
 *  Created on: 26.11.2012
 *      Author: ddreval
 */

#ifndef SKYBUILDER_H_
#define SKYBUILDER_H_

#include <FBase.h>
#include <FUi.h>
#include "SkyCanvas.h"
#include "Projector.h"

class SkyBuilder : public Osp::Base::Runtime::Thread {

	public:
		SkyBuilder(TimeAndPlace* timeAndPlace, SkyCanvas* skyCanvas);
		virtual ~SkyBuilder();
//		void SetParent(Osp::Ui::Controls::Form* form);
		Object* Run(void);

	public:
		static const int BUILD_PROGRESS_RANGE_SET = 20;
		static const int BUILD_PROGRESS_SET = 21;
		static const int BUILD_PROGRESS_DONE = 22;

	private:
		SkyCanvas* skyCanvas;
		TimeAndPlace* timeAndPlace;
		Projector* projector;

};

#endif /* SKYBUILDER_H_ */
