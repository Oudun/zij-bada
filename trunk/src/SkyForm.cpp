#include "Zij.h"
#include "SkyObject.h"
#include "SkyFactory.h"
#include "SkyIterator.h"
#include "Sky.h"
#include "SkyForm.h"


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
using namespace Osp::Io;

SkyForm::SkyForm(void)
{
}

SkyForm::~SkyForm(void)
{
}

bool
SkyForm::Initialize()
{
	Construct(L"IDF_FORM1");
	return true;
}

result
SkyForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	__pButtonOk = static_cast<Button *>(GetControl(L"IDC_BUTTON_OK"));
	if (__pButtonOk != null)
	{
		__pButtonOk->SetActionId(ID_BUTTON_OK);
		__pButtonOk->AddActionEventListener(*this);
	}

	Button *pButton_gps = static_cast<Button *>(GetControl("IDC_BUTTON_GPS"));  
	if (pButton_gps)
	{
		pButton_gps->SetActionId(ID_BUTTON_GPS);
		pButton_gps->AddActionEventListener(*this);
	}

	__pLabel = static_cast<Label *>(GetControl("IDC_LABEL1"));
	__pLabel -> SetText("Initialized");
	__pLabel -> SetText("Again Initialized");

	Button *pButton1 = static_cast<Button *>(GetControl("IDC_BUTTON_STARS"));
	if (pButton1)
	{
		pButton1->SetActionId(103);
		pButton1->AddActionEventListener(*this);
	}

	Control* control = GetControl(L"IDF_SkyForm");
	sky = new Sky(control->GetCanvasN());

	return r;
}

result
SkyForm::OnTerminating(void)
{
	result r = E_SUCCESS;
	return r;
}

void
SkyForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
	switch(actionId)
	{
	case ID_BUTTON_OK:
		{
			sky->paintBorders();
			__pLabel->SetText("");
		}
		break;
	case ID_BUTTON_GPS:
		{
			locProvider.Construct(LOC_METHOD_HYBRID);
			locProvider.RequestLocationUpdates(*this, 5, true);
		}
		break;
	case ID_BUTTON_STARS:
		{
			sky->setLatitude(55.75578F);
			sky->setLongitude(37.8632F);
			AppLog("Local Siderial Hours is %f", sky->getSiderialHours());
			Log("Local Siderial Hours is ", sky->getSiderialHours());
			sky->draw();
		}
		break;
	default:
		break;
	}
}

void
SkyForm::OnLocationUpdated(Osp::Locations::Location& location) {
	AppLog("Location Updated\n");
	const QualifiedCoordinates* coordinates = location.GetQualifiedCoordinates();
	AppLog("Coordinates taken\n");
	String str;
	if (coordinates != 0) {
		double latd = coordinates->GetLatitude();
		AppLog("Latitude (double) taken\n");
		AppLog("Latitude (float) taken\n");
		Log("Latitude = ",(float)(coordinates->GetLatitude()));
		Log("Longitude = ",(float)(coordinates->GetLongitude()));
		sky->setLatitude(coordinates->GetLatitude());
		sky->setLongitude(coordinates->GetLongitude());
		AppLog("Local Siderial Hours is ", sky->getSiderialHours());
		//		Log("SLT = ", GetLocalSiderialTime((float)(coordinates->GetLongitude())));
		locProvider.CancelLocationUpdates();
	} else {
		LogSameLine("#");
	}
}

void
SkyForm::OnProviderStateChanged(Osp::Locations::LocProviderState newState) {
	AppLog("Location Provider state changed\n");
	Log("Location Provider state changed\n");
	if (newState == LOC_PROVIDER_AVAILABLE) {
		AppLog("The location provider is available");
		Log("The location provider is available");
	} else if (newState == LOC_PROVIDER_OUT_OF_SERVICE) {
		AppLog("The location provider is out of service");
		Log("The location provider is out of service");
	} else if (newState == LOC_PROVIDER_TEMPORARILY_UNAVAILABLE) {
		AppLog("The location provider is temporarily unavailable");
		Log("The location provider is temporarily unavailable");
	} else {
		AppLog("State unknown");
		Log("State unknown");
	}
}

float
SkyForm::GetLocalSiderialTime(float longitude) {
	TimeZone timeZone(60, L"Europe/London");
	DateTime* currTime = new DateTime();
	SystemTime::GetCurrentTime(*currTime);
	LogSameLine("currTime=");
	Log(currTime->ToString());
	calendar = Calendar::CreateInstanceN(timeZone, CALENDAR_GREGORIAN);
	calendar->SetTime(*currTime);
	float hrs = (calendar->GetTimeField(TIME_FIELD_HOUR_OF_DAY))-1;
	float minHrs = calendar->GetTimeField(TIME_FIELD_MINUTE)/60.0;
	float dayFract = (hrs + minHrs)/24.0;
	float dayNum = calendar->GetTimeField(TIME_FIELD_DAY_OF_YEAR);
	float year = calendar->GetTimeField(TIME_FIELD_YEAR);
	double daysSinceJ2000 = -1.5 + dayNum + (year-2000)*365 + (int)((year-2000)/4) + dayFract;
	double slt = 100.46 + 0.985647 * daysSinceJ2000 + longitude + 15*(hrs + minHrs);
	int sltInt = (int)(slt/360);
	float sltHrs = (slt-(360*sltInt))/15;
	Log("lstHours=",sltHrs);
	return sltHrs;
}

void
SkyForm::Log(const Osp::Base::String& aText, const float value) {
	String str;
	String text;
	text = aText;
	str = __pLabel->GetText();
	text.Append(value);
	str.Append(text);
	str.Append('\n');
	__pLabel->SetText(str);
	__pLabel->RequestRedraw();
}

void
SkyForm::Log(const Osp::Base::String& text) {
	String str;
	str = __pLabel->GetText();
	str.Append(text);
	str.Append('\n');
	__pLabel->SetText(str);
	__pLabel->RequestRedraw();
}

void
SkyForm::ClearLog(const Osp::Base::String& text) {
	__pLabel->SetText(text);
	__pLabel->RequestRedraw();
}

void
SkyForm::LogSameLine(const Osp::Base::String& text) {
	String str;
	str = __pLabel->GetText();
	str.Append(text);
	__pLabel->SetText(str);
	__pLabel->RequestRedraw();
}




