#ifndef _TEST_H_
#define _TEST_H_

#include <FApp.h>
#include <FBase.h>
#include <FSystem.h>
#include <FUi.h>

#include "TimeAndPlace.h"
#include "LocationForm.h"
#include "SkyForm.h"
#include "SkyBuilderForm.h"
#include "SkyBuilder.h"
#include "SkyCanvas.h"
#include "ConstellationForm.h"
#include "ConstellationBuilder.h"
#include "AlterLocationForm.h"
#include "EarthMapForm.h"
//#include "Shared.h"


/**
 * [Test] application must inherit from Application class
 * which provides basic features necessary to define an application.
 */
class SkyGuide : public Osp::App::Application {

	public:
		SkyGuide();
		~SkyGuide();
		static Osp::App::Application* CreateInstance(void);
		bool OnAppInitializing(Osp::App::AppRegistry& appRegistry);
		bool OnAppTerminating(Osp::App::AppRegistry& appRegistry, bool forcedTermination = false);
		virtual void OnUserEventReceivedN (RequestId requestId, Osp::Base::Collection::IList *pArgs);

	private:
		LocationForm* locationForm;
		SkyBuilderForm* skyBuilderForm;
		ConstellationForm* constellationForm;
		AlterLocationForm* alterLocationForm;
		EarthMapForm* earthMapForm;

		TimeAndPlace* timeAndPlace;
		SkyForm* skyForm;

};

#endif
