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
	skyForm = new SkyForm();
	skyForm -> Initialize();
	locationForm = new LocationForm(timeAndPlace);

	// Add the form to the frame
	Frame *pFrame = GetAppFrame()->GetFrame();
	pFrame->AddControl(*skyForm);

	// Set the current form
	pFrame->SetCurrentForm(*skyForm);

	// Draw and Show the form
	skyForm->Draw();
	skyForm->Show();

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



