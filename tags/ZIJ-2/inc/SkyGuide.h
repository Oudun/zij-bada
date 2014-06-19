#ifndef _TEST_H_
#define _TEST_H_

#include <FApp.h>
#include <FBase.h>
#include <FSystem.h>
#include <FUi.h>

#include "forms/SkyForm.h"
#include "forms/LocationForm.h"
#include "forms/EarthMapForm.h"
#include "forms/ConstellationForm.h"
#include "forms/AlterLocationForm.h"
#include "forms/SkyBuilderForm.h"
#include "forms/HelpForm.h"
#include "forms/InfoForm.h"

#include "TimeAndPlace.h"
#include "SkyBuilder.h"
#include "SkyCanvas.h"
#include "ConstellationBuilder.h"
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
		HelpForm* helpForm;
		InfoForm* infoForm;

		TimeAndPlace* timeAndPlace;
		SkyForm* skyForm;

};

#endif

