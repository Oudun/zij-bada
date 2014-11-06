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

	AppLog("0");

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

	AppLog("1");

	// Add the form to the frame
	Frame *pFrame = GetAppFrame()->GetFrame();
	pFrame -> AddControl(*locationForm);
	pFrame -> AddControl(*skyBuilderForm);
	pFrame -> AddControl(*constellationForm);
	pFrame -> AddControl(*skyForm);
	pFrame -> AddControl(*alterLocationForm);
	pFrame -> AddControl(*helpForm);
	pFrame -> AddControl(*infoForm);
	pFrame -> SetCurrentForm(*locationForm);

	locationForm -> Draw();
	locationForm -> Show();

	AppLog("4");

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
	AppLog("Go Foreground");
	Frame *pFrame = GetAppFrame()->GetFrame();
	Form* form = pFrame -> GetCurrentForm();
	if (form == skyForm) {
		((SkyForm*)form) -> Update();
	}
}

void
SkyGuide::OnBackground(void){
	AppLog("Go Background");
}

void
SkyGuide::OnUserEventReceivedN (RequestId requestId, Osp::Base::Collection::IList *pArgs) {
	AppLog("Event %d Received", requestId);
	Frame *pFrame = GetAppFrame()->GetFrame();
	switch (requestId) {
		case LocationForm::LOCATION_SET: {
			AppLog("Getting location");
			Osp::Base::Runtime::Thread::GetCurrentThread() -> Sleep(3000);
			pFrame->SetCurrentForm(*skyBuilderForm);
			skyBuilderForm -> RequestRedraw(true);
			skyBuilderForm -> Start();
			break;
		}
		case SkyBuilder::BUILD_PROGRESS_RANGE_SET:
			AppLog("Setting sky build progress");{
			Integer* arg1 = (Integer*)(pArgs -> GetAt(0));
			Integer* arg2 = (Integer*)(pArgs -> GetAt(1));
			skyBuilderForm -> SetRange(arg1 -> ToInt(), arg2 -> ToInt());
			delete pArgs;
			break;
		}
		case SkyBuilder::BUILD_PROGRESS_SET: {
			AppLog("Updating sky build progress");
			Integer* arg = (Integer*)(pArgs -> GetAt(0));
			skyBuilderForm -> SetProgress(arg -> ToInt());
			delete pArgs;
			break;
		}
		case SkyBuilder::BUILD_PROGRESS_DONE: {
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
		case SkyForm::SELECT_CONSTELLATION: {
			AppLog("Showing list to select constellation");
			pFrame -> SetCurrentForm(*constellationForm);
			constellationForm -> Update();
			constellationForm -> RequestRedraw(true);
			break;
		}
		case ConstellationForm::CONSTELLATION_SELECTED: {
			AppLog("Constellation is selected, showing it on sky");

			pFrame -> SetCurrentForm(*skyForm);
			skyForm -> Draw();
			skyForm -> Update();
			break;
		}
		case EVENT_HELP_CLOSED: {
			pFrame -> SetCurrentForm(*skyForm);
			skyForm -> Draw();
			skyForm -> Update();
			break;
		}
		case EVENT_INFO_CLOSED: {
			pFrame -> SetCurrentForm(*skyForm);
			skyForm -> Draw();
			skyForm -> Update();
			break;
		}
		case AlterLocationForm::USE_PREV_LOCATION: {
			double longitude, latitude;
			AppLog("Retrieving old coordinates");

			AppRegistry* appRegistry = Osp::App::Application::GetInstance()->GetAppRegistry();
			//AppRegistry* appRegistry = Osp::App::AppRegistry::GetInstance(); for API 2.0 only

			appRegistry -> Get("LAST_LONGITUDE", longitude);
			appRegistry -> Get("LAST_LATITUDE", latitude);

			AppLog("Reusing old coordinates longitude %f latitude %f", longitude, latitude);
			TimeAndPlace::SetSiderialTime(longitude, latitude, new DateTime());
			Osp::App::Application::GetInstance() -> SendUserEvent(LocationForm::LOCATION_SET, null);
			break;
		}
		case SkyForm::SHOW_HELP: {
			AppLog("Showing help");
			pFrame -> SetCurrentForm(*helpForm);
			helpForm -> Draw();
			helpForm -> Show();
			break;
		}
		case SkyForm::SHOW_INFO: {
			AppLog("Showing info");
			pFrame -> SetCurrentForm(*infoForm);
			infoForm -> Draw();
			infoForm -> Show();
			break;
		}
		case LocationForm::LOCATION_FAILED: {
			AppLog("Auto location failed, choose alternate");
			pFrame->SetCurrentForm(*alterLocationForm);
			alterLocationForm -> RequestRedraw(true);
			break;
		}
	}
}



