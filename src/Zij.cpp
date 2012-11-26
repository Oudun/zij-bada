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
	timeAndPlace = new TimeAndPlace();

	// Create forms
	locationForm = new LocationForm(timeAndPlace);
	locationForm -> Initialize();

	skyBuilderForm = new SkyBuilderForm(timeAndPlace);
	skyBuilderForm -> Initialize();

//	skyForm = new SkyForm();
//	skyForm -> Initialize();


	// Add the form to the frame
	Frame *pFrame = GetAppFrame()->GetFrame();
	pFrame -> AddControl(*locationForm);
	pFrame -> AddControl(*skyBuilderForm);
//	pFrame -> AddControl(*skyForm);

	// Set the current form
//	pFrame->SetCurrentForm(*skyForm);
	pFrame->SetCurrentForm(*locationForm);

	locationForm -> Draw();
	locationForm -> Show();

	// Draw and Show the form
//	skyForm->Draw();
//	skyForm->Show();

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
			pFrame->SetCurrentForm(*skyBuilderForm);
			skyBuilderForm -> RequestRedraw(true);
			break;
		}
		case SkyBuilder::BUILD_PROGRESS_RANGE_SET: {
			Integer* arg1 = (Integer*)(pArgs -> GetAt(1));
			Integer* arg2 = (Integer*)(pArgs -> GetAt(2));
			skyBuilderForm -> SetRange(arg1 -> ToInt(), arg2 -> ToInt());
			delete pArgs;
		}
		case SkyBuilder::BUILD_PROGRESS_SET: {
			Integer* arg = (Integer*)(pArgs -> GetAt(1));
			skyBuilderForm -> SetProgress(arg -> ToInt());
			delete pArgs;
		}
	}
}



