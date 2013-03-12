/**
 * Name        : Test
 * Version     : 
 * Vendor      : 
 * Description : 
 */

#include "Zij.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::System;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

Zij::Zij()
{
}

Zij::~Zij()
{
}

Application*
Zij::CreateInstance(void)
{
	// Create the instance through the constructor.
	return new Zij();
}

bool
Zij::OnAppInitializing(AppRegistry& appRegistry) {

	//Create context;
	//timeAndPlace = new TimeAndPlace();
	SkyCanvas::Initialize();

	// Create forms
	locationForm = new LocationForm();
	locationForm -> Initialize();

	skyBuilderForm = new SkyBuilderForm();
	skyBuilderForm -> Initialize();

	stellarForm = new StellarForm();
	stellarForm -> Initialize();

	skyForm = new SkyForm();
	skyForm -> Initialize();

	constellationForm = new ConstellationForm();
	constellationForm -> Initialize();

	// Add the form to the frame
	Frame *pFrame = GetAppFrame()->GetFrame();
	pFrame -> AddControl(*locationForm);
	pFrame -> AddControl(*skyBuilderForm);
	pFrame -> AddControl(*stellarForm);
	pFrame -> AddControl(*skyForm);
	pFrame -> AddControl(*constellationForm);

	pFrame->SetCurrentForm(*locationForm);

	locationForm -> Draw();
	locationForm -> Show();

	return true;

}

bool
Zij::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	// TODO:
	// Deallocate resources allocated by this application for termination.
	// The application's permanent data and context can be saved via appRegistry.
	return true;
}

void
Zij::OnUserEventReceivedN (RequestId requestId, Osp::Base::Collection::IList *pArgs) {
	AppLog("Event %d Received", requestId);
	Frame *pFrame = GetAppFrame()->GetFrame();
	switch (requestId) {
		case LocationForm::LOCATION_SET: {
			Osp::Base::Runtime::Thread::GetCurrentThread() -> Sleep(3000);
			pFrame->SetCurrentForm(*skyBuilderForm);
			skyBuilderForm -> RequestRedraw(true);
			skyBuilderForm -> Start();
			break;
		}
		case SkyBuilder::BUILD_PROGRESS_RANGE_SET: {
			Integer* arg1 = (Integer*)(pArgs -> GetAt(0));
			Integer* arg2 = (Integer*)(pArgs -> GetAt(1));
			skyBuilderForm -> SetRange(arg1 -> ToInt(), arg2 -> ToInt());
			delete pArgs;
			break;
		}
		case SkyBuilder::BUILD_PROGRESS_SET: {
			Integer* arg = (Integer*)(pArgs -> GetAt(0));
			skyBuilderForm -> SetProgress(arg -> ToInt());
			delete pArgs;
			break;
		}
		case SkyBuilder::BUILD_PROGRESS_DONE: {
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
			pFrame -> SetCurrentForm(*stellarForm);
			stellarForm -> Update();
			stellarForm -> RequestRedraw(true);
			break;
		}
		case StellarForm::CONSTELLATION_SELECTED: {
			AppLog("CONSTELLATION_SELECTED");
			String* constelName = SkyCanvas::GetSelectedConstellation();
			AppLog("Selected constellation name is %S", constelName);
			ConstellationBuilder::Build(constelName);
		}
		case ConstellationBuilder::CONSTELLATION_READY: {
				pFrame -> SetCurrentForm(*skyForm);
				skyForm -> Draw();
				skyForm -> Update();
				break;
		}
	}
}



