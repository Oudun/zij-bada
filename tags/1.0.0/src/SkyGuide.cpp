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

	earthMapForm = new EarthMapForm();
	earthMapForm -> Initialize();

	AppLog("1");

	// Add the form to the frame
	Frame *pFrame = GetAppFrame()->GetFrame();
	AppLog("1a");
	pFrame -> AddControl(*locationForm);
	AppLog("1b");
	pFrame -> AddControl(*skyBuilderForm);
	AppLog("1c");
	pFrame -> AddControl(*constellationForm);
	AppLog("1d");
	pFrame -> AddControl(*skyForm);
	AppLog("1e");
	pFrame -> AddControl(*alterLocationForm);
	AppLog("1f");
	pFrame -> AddControl(*earthMapForm);
	AppLog("2");

	pFrame->SetCurrentForm(*locationForm);

	AppLog("3");

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
		case AlterLocationForm::USE_PREV_LOCATION: {
			double longitude, latitude;
			AppLog("Retrieving old coordinates");

			AppRegistry* appRegistry = Osp::App::AppRegistry::GetInstance();

			appRegistry -> Get("LAST_LONGITUDE", longitude);
			appRegistry -> Get("LAST_LATITUDE", latitude);

			AppLog("Reusing old coordinates longitude %f latitude %f", longitude, latitude);
			TimeAndPlace::SetSiderialTime(longitude, latitude, new DateTime());
			Osp::App::Application::GetInstance() -> SendUserEvent(LocationForm::LOCATION_SET, null);
			break;
		}
		case AlterLocationForm::USE_MAP_LOCATION: {
			AppLog("Showing earth map");
			pFrame -> SetCurrentForm(*earthMapForm);
			earthMapForm -> Draw();
			earthMapForm -> Update();
			break;
		}
//		case LocationForm::LOCATION_FAILED: {
//			AppLog("Auto location failed, choose alternate");
//			pFrame->SetCurrentForm(*alterLocationForm);
//			alterLocationForm -> RequestRedraw(true);
//			break;
//		}
	}
}



