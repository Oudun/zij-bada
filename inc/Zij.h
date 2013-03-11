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
#include "StellarForm.h"
#include "ConstellationForm.h"

/**
 * [Test] application must inherit from Application class
 * which provides basic features necessary to define an application.
 */
class Zij : public Osp::App::Application {

	public:
		Zij();
		~Zij();
		static Osp::App::Application* CreateInstance(void);
		bool OnAppInitializing(Osp::App::AppRegistry& appRegistry);
		bool OnAppTerminating(Osp::App::AppRegistry& appRegistry, bool forcedTermination = false);
		virtual void OnUserEventReceivedN (RequestId requestId, Osp::Base::Collection::IList *pArgs);

	private:
		TimeAndPlace* timeAndPlace;
		LocationForm* locationForm;
		SkyBuilderForm* skyBuilderForm;
		SkyForm* skyForm;
		SkyCanvas* skyCanvas;
		StellarForm* stellarForm;
		ConstellationForm* constellationForm;
};

#endif
