/**
 * Name        : Test
 * Version     : 
 * Vendor      : 
 * Description : 
 */


#include "Zij.h"
#include "SkyForm.h"

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
Zij::OnAppInitializing(AppRegistry& appRegistry)
{
	// TODO:
	// Initialize UI resources and application specific data.
	// The application's permanent data and context can be obtained from the appRegistry.
	//
	// If this method is successful, return true; otherwise, return false.
	// If this method returns false, the application will be terminated.

	// Uncomment the following statement to listen to the screen on/off events.
	//PowerManager::SetScreenEventListener(*this);

	// Create a form
	SkyForm *pSkyForm = new SkyForm();
	pSkyForm->Initialize();

	// Add the form to the frame
	Frame *pFrame = GetAppFrame()->GetFrame();
	pFrame->AddControl(*pSkyForm);

	// Set the current form
	pFrame->SetCurrentForm(*pSkyForm);

	// Draw and Show the form
	pSkyForm->Draw();
	pSkyForm->Show();

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



