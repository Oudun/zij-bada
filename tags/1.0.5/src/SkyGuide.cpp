/**
 * Name        : Test
 * Version     : 
 * Vendor      : 
 * Description : 
 */

#include "SkyGuide.h"


using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::System;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

SkyGuide::SkyGuide()
{
}

SkyGuide::~SkyGuide()
{
}

Application*
SkyGuide::CreateInstance(void)
{
	// Create the instance through the constructor.
	return new SkyGuide();
}

bool
SkyGuide::OnAppInitializing(AppRegistry& appRegistry) {

	AppLog("Initializing");

	SkyCanvas::Initialize();

	// Create forms
	locationForm = new LocationForm();
	locationForm -> Initialize();

	skyBuilderForm = new SkyBuilderForm();
	skyBuilderForm -> Initialize();

	constellationForm = new ConstellationForm();
	constellationForm -> Initialize();

	skyForm = new SkyForm();
	skyForm -> Initialize();

	alterLocationForm = new AlterLocationForm();
	alterLocationForm -> Initialize();

	helpForm = new HelpForm();
	helpForm -> Initialize();

	infoForm = new InfoForm();
	infoForm -> Initialize();

	starForm = new StarForm();
	starForm -> Initialize();

	starHelpForm = new StarHelpForm();
	starHelpForm -> Initialize();

	// Add the form to the frame
	Frame *pFrame = GetAppFrame()->GetFrame();
	pFrame -> AddControl(*locationForm);
	pFrame -> AddControl(*skyBuilderForm);
	pFrame -> AddControl(*constellationForm);
	pFrame -> AddControl(*skyForm);
	pFrame -> AddControl(*alterLocationForm);
	pFrame -> AddControl(*helpForm);
	pFrame -> AddControl(*infoForm);
	pFrame -> AddControl(*starForm);
	pFrame -> AddControl(*starHelpForm);

	pFrame -> SetCurrentForm(*locationForm);

	locationForm -> Draw();
	locationForm -> Show();

	return true;

}

bool
SkyGuide::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	// TODO:
	// Deallocate resources allocated by this application for termination.
	// The application's permanent data and context can be saved via appRegistry.
	return true;
}

void
SkyGuide::OnForeground(void) {
//	skyForm -> Draw();
	skyForm -> Update();
}

void
SkyGuide::OnUserEventReceivedN (RequestId requestId, Osp::Base::Collection::IList *pArgs) {

	AppLog("Event %d Received", requestId);
	Frame *pFrame = GetAppFrame()->GetFrame();
	switch (requestId) {
		case EVENT_LOCATION_SET: {//1
			AppLog("Getting location");
			Osp::Base::Runtime::Thread::GetCurrentThread() -> Sleep(3000);
			pFrame->SetCurrentForm(*skyBuilderForm);
			skyBuilderForm -> RequestRedraw(true);
			skyBuilderForm -> Start();
			break;
		}
		case EVENT_BUILD_PROGRESS_RANGE_SET://20
			AppLog("Setting sky build progress");{
			Integer* arg1 = (Integer*)(pArgs -> GetAt(0));
			Integer* arg2 = (Integer*)(pArgs -> GetAt(1));
			skyBuilderForm -> SetRange(arg1 -> ToInt(), arg2 -> ToInt());
			delete pArgs;
			break;
		}
		case EVENT_BUILD_PROGRESS_SET: {//21
			AppLog("Updating sky build progress");
			Integer* arg = (Integer*)(pArgs -> GetAt(0));
			skyBuilderForm -> SetProgress(arg -> ToInt());
			delete pArgs;
			break;
		}
		case EVENT_BUILD_PROGRESS_DONE: {//22
			AppLog("Showing sky");
			Integer* arg = (Integer*)(pArgs -> GetAt(0));
			skyBuilderForm -> SetProgress(arg -> ToInt());
			delete pArgs;
			Osp::Base::Runtime::Thread::GetCurrentThread() -> Sleep(1000);
			pFrame -> SetCurrentForm(*skyForm);
			skyForm -> Draw();
			skyForm -> Update();
			break;
		}
		case EVENT_SELECT_CONSTELLATION: {//30
			AppLog("Showing list to select constellation");
			pFrame -> SetCurrentForm(*constellationForm);
			constellationForm -> Update();
			constellationForm -> RequestRedraw(true);
			break;
		}
		case EVENT_CONSTELLATION_SELECTED: {//40
			AppLog("Constellation is selected, showing it on sky");
			pFrame -> SetCurrentForm(*skyForm);
			skyForm -> Draw();
			skyForm -> Update();
			break;
		}
		case EVENT_STAR_SELECTED: {//41
			AppLog("Star is selected, showing it on sky");
			pFrame -> SetCurrentForm(*skyForm);
			skyForm -> Draw();
			skyForm -> Update();
			break;
		}
		case EVENT_HELP_CLOSED: {//81
			pFrame -> SetCurrentForm(*skyForm);
			skyForm -> Draw();
			skyForm -> Update();
			break;
		}
		case EVENT_INFO_CLOSED: {//80
			pFrame -> SetCurrentForm(*skyForm);
			skyForm -> Draw();
			skyForm -> Update();
			break;
		}
		case EVENT_USE_PREV_LOCATION: {//50
			double longitude, latitude;
			AppLog("Retrieving old coordinates");

			AppRegistry* appRegistry = Osp::App::Application::GetInstance()->GetAppRegistry();
			//AppRegistry* appRegistry = Osp::App::AppRegistry::GetInstance(); for API 2.0 only

			appRegistry -> Get("LAST_LONGITUDE", longitude);
			appRegistry -> Get("LAST_LATITUDE", latitude);

			AppLog("Reusing old coordinates longitude %f latitude %f", longitude, latitude);
			TimeAndPlace::SetSiderialTime(longitude, latitude, new DateTime());
			Osp::App::Application::GetInstance() -> SendUserEvent(EVENT_LOCATION_SET, null);
			break;
		}
		case EVENT_SHOW_HELP: {//32
			AppLog("Showing help");
			pFrame -> SetCurrentForm(*helpForm);
			helpForm -> Draw();
			helpForm -> Show();
			break;
		}
		case EVENT_SHOW_INFO: {//31
			AppLog("Showing info");
			pFrame -> SetCurrentForm(*infoForm);
			infoForm -> Draw();
			infoForm -> Show();
			break;
		}
		case EVENT_LOCATION_FAILED: {//2
			AppLog("Auto location failed, choose alternate");
			pFrame->SetCurrentForm(*alterLocationForm);
			alterLocationForm -> RequestRedraw(true);
			break;
		}
		case EVENT_SHOW_STARS: {//33
			AppLog("Show named stars");
			pFrame->SetCurrentForm(*starForm);
			starForm -> Update();
			starForm -> RequestRedraw(true);
			break;
		}
		case EVENT_CONSTELLATION_TOUCHED: {
			AppLog("Constellation touched");
			String* arg = (String*)(pArgs -> GetAt(0));
			SkyCanvas::SelectConstellation(*arg);
			skyForm -> Draw();
			skyForm -> Update();
			break;
		}
		case EVENT_STAR_HELP: {
			AppLog("Star form help");
			pFrame->SetCurrentForm(*starHelpForm);
			starHelpForm -> RequestRedraw(true);
			break;
		}
		case EVENT_STAR_HELP_CLOSED: {
			AppLog("Close help and show named stars");
			pFrame->SetCurrentForm(*starForm);
			starForm -> Update();
			starForm -> RequestRedraw(true);
			break;
		}
	}
}




