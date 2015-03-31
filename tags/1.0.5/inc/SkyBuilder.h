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
		SkyBuilder();
		virtual ~SkyBuilder();
		Object* Run(void);

	private:
		Projector* projector;

};

#endif /* SKYBUILDER_H_ */
