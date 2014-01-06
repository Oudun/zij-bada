
#include "AlterLocationForm.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;


AlterLocationForm::AlterLocationForm(void)
{
}

AlterLocationForm::~AlterLocationForm(void)
{
}

bool
AlterLocationForm::Initialize()
{
	Form::Construct(L"ALTER_LOCATION_FORM");

	return true;
}

result
AlterLocationForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO: Add your initialization code here

	Button *pButton3 = static_cast<Button *>(GetControl("IDC_BUTTON3"));  
	if (pButton3)
	{
		pButton3->SetActionId(0);
		pButton3->AddActionEventListener(*this);
	}

	Osp::App::AppRegistry* appRegistry = Osp::App::Application::GetInstance()->GetAppRegistry();//Osp::App::AppRegistry::GetInstance();

	Button *pButton_prev_location = static_cast<Button *>(GetControl("IDC_BUTTON_PREV_LOCATION"));  
	if (pButton_prev_location)
	{
		pButton_prev_location->SetActionId(1);
		pButton_prev_location->AddActionEventListener(*this);
	}

	double latitude, longitude;
	result rLon = appRegistry -> Get("LAST_LONGITUDE", longitude);
	AppLog("Error %S", GetErrorMessage(rLon));
	AppLog("Longitude is %f", longitude);
	result rLat = appRegistry -> Get("LAST_LATITUDE", latitude);
	AppLog("Latitude is %f", latitude);

	if (rLat != E_SUCCESS || rLon != E_SUCCESS) {
		pButton_prev_location -> SetShowState(false);
		//pButton_prev_location -> Draw();
	}

	Button *pButton1 = static_cast<Button *>(GetControl("IDC_BUTTON1"));  
	if (pButton1)
	{
		pButton1->SetActionId(2);
		pButton1->AddActionEventListener(*this);
	}
	Button *pButton_map_location = static_cast<Button *>(GetControl("IDC_BUTTON_MAP_LOCATION"));  
	if (pButton_map_location)
	{
		pButton_map_location->SetActionId(2);
		pButton_map_location->AddActionEventListener(*this);
	}
	return r;
}

result
AlterLocationForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}



void
AlterLocationForm::OnActionPerformed(const Osp::Ui::Control &source, int actionId)
{
	switch (actionId) {
		case IDC_BUTTON_MAP_LOCATION : {
			Osp::App::Application::GetInstance() -> SendUserEvent(USE_MAP_LOCATION, null);
			break;
		}
		case IDC_BUTTON_PREV_LOCATION : {
			Osp::App::Application::GetInstance() -> SendUserEvent(USE_PREV_LOCATION, null);
			break;
		}
		case ID_BUTTON_QUIT : {
			Osp::App::Application::GetInstance() -> Terminate();
			break;
		}
		default:
			break;
	}

}
