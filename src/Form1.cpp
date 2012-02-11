#include "Form1.h"

//using namespace Osp::Base;
//using namespace Osp::Ui;
//using namespace Osp::Ui::Controls;

using namespace Osp::Base;
using namespace Osp::Base::Utility;
using namespace Osp::Base::Runtime;
using namespace Osp::Graphics;
using namespace Osp::Media;
using namespace Osp::Locales;
using namespace Osp::System;
using namespace Osp::App;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Locations;


Form1::Form1(void)
{
}

Form1::~Form1(void)
{
}

bool
Form1::Initialize()
{
	// Construct an XML form
	Construct(L"IDF_FORM1");

	return true;
}

result
Form1::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO: Add your initialization code here

	// Get a button via resource ID
	__pButtonOk = static_cast<Button *>(GetControl(L"IDC_BUTTON_OK"));
	if (__pButtonOk != null)
	{
		__pButtonOk->SetActionId(ID_BUTTON_OK);
		__pButtonOk->AddActionEventListener(*this);
	}

	Button *pButton_gps = static_cast<Button *>(GetControl("IDC_BUTTON_GPS"));  
	if (pButton_gps)
	{
		pButton_gps->SetActionId(1);
		pButton_gps->AddActionEventListener(*this);
	}
	Button *pButton1 = static_cast<Button *>(GetControl("IDC_BUTTON1"));  
	if (pButton1)
	{
		pButton1->SetActionId(102);
		pButton1->AddActionEventListener(*this);
	}
	return r;
}

result
Form1::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void
Form1::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
	switch(actionId)
	{
	case ID_BUTTON_OK:
		{
			AppLog("OK Button is clicked! \n");
			Canvas* __pCanvas;
			Control* control = GetControl(L"IDF_FORM1");
			__pCanvas = control->GetCanvasN();
			Point point1, point2;
			point1.x = 0;
			point1.y = 0;
			point2.x = 200;
			point2.y = 200;
			__pCanvas->SetLineWidth(1);
			__pCanvas->DrawLine(point1, point2);
			__pCanvas->SetForegroundColor(Color::COLOR_BLACK);
//			__pCanvas->Clear();
			__pCanvas->Show();
		}
		break;
	case ID_BUTTON_GPS:
		{
			AppLog("GPS Button is clicked! \n");
			locProvider.Construct(LOC_METHOD_HYBRID);
			AppLog("Location Provider! \n");
			locProvider.RequestLocationUpdates(*this, 5, true);
		}
		break;
	default:
		break;
	}
}

void
Form1::OnLocationUpdated(Osp::Locations::Location& location) {
	EditArea *pText = static_cast<EditArea *>(GetControl("IDC_EDITAREA1"));
	pText->SetText("Location Updated");
	pText->Show();
	AppLog("Location Updated\n");
	const QualifiedCoordinates* coordinates = location.GetQualifiedCoordinates();
	AppLog("Coordinates taken\n");
	String str;
	if (coordinates != 0) {
		double latd = coordinates->GetLatitude();
		AppLog("Latitude (double) taken\n");
		float latf = (float)latd;
		AppLog("Latitude (float) taken\n");
		AppLog("\nLatitude = %f", latf);
		AppLog("Longitude = %f", (float)(coordinates->GetLongitude()));
		AppLog("Altitude = %f", (float)(coordinates->GetAltitude()));
		locProvider.CancelLocationUpdates();
		str.Format(256, L"Latitude = %f\nLongitude = %f\nAltitude = %f",
				(float)(coordinates->GetLatitude()),
				(float)(coordinates->GetLongitude()),
				(float)(coordinates->GetAltitude()));
	} else {
		str = "*";
	}
	pText->AppendText(str);
	pText->Show();
}

void
Form1::OnProviderStateChanged(Osp::Locations::LocProviderState newState) {
	AppLog("Location Provider state changed\n");
	if (newState == LOC_PROVIDER_AVAILABLE) {
		AppLog("LOC_PROVIDER_AVAILABLE");
	} else if (newState == LOC_PROVIDER_OUT_OF_SERVICE) {
		AppLog("LOC_PROVIDER_AVAILABLE");
	} else if (newState == LOC_PROVIDER_TEMPORARILY_UNAVAILABLE) {
		AppLog("LOC_PROVIDER_TEMPORARILY_UNAVAILABLE");
	} else {
		AppLog("State unknown");
	}
}

float
Form1::GetLocalSIderialTime() {

	TimeZone timeZone(60, L"Europe/Moscow");
	calendar = Calendar::CreateInstanceN(timeZone, CALENDAR_GREGORIAN);

//    calendar.setTime(new Date());
//    calendar.add(Calendar.HOUR, -calendar.get(Calendar.ZONE_OFFSET)/3600000);
//    float hrs = calendar.get(Calendar.HOUR_OF_DAY);
//    float minHrs = calendar.get(Calendar.MINUTE)/60F;
//    float dayFract = (hrs + minHrs)/24F;
//    System.out.println(dayFract);
//    int dayNum = calendar.get(Calendar.DAY_OF_YEAR);
//    int year = calendar.get(Calendar.YEAR);
//    float daysSinceJ2000 = -1.5F + dayNum + (year-2000)*365 + (int)((year-2000)/4);
//    System.out.println(daysSinceJ2000);
//    daysSinceJ2000 += dayFract;
//    System.out.println(daysSinceJ2000);
//
//    float lst = 100.46F + 0.985647F * daysSinceJ2000 + longitude + 15*(hrs + minHrs);
//    lstDeg = lst%360;
//    System.out.println("LST = "+ lstDeg + " degrees");
//    System.out.println("LST = "+ (lstDeg/15) + " hours");

	return 0;

}



