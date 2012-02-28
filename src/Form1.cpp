#include "Form1.h"
#include "SkyObject.h"
#include "SkyFactory.h"
#include "SkyIterator.h"
#include "Sky.h"

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

Form1::Form1(void)
{
}

Form1::~Form1(void)
{
}

bool
Form1::Initialize()
{
	Construct(L"IDF_FORM1");
	return true;
}

result
Form1::OnInitializing(void)
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

	Control* control = GetControl(L"IDF_FORM1");
	sky = new Sky(control->GetCanvasN());

	return r;
}

result
Form1::OnTerminating(void)
{
	result r = E_SUCCESS;
	return r;
}

void
Form1::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
	switch(actionId)
	{
	case ID_BUTTON_OK:
		{
			sky->paintBorders();
			__pLabel->SetText("OK\n");
			__pLabel->RequestRedraw();
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
			sky->getCanvas()->FillEllipse(Color::COLOR_WHITE, Rectangle(100,200,1,1));
			sky->draw();
//			SkyIterator* stars;
//			stars = SkyFactory::getStars(1);
//			while(stars->hasNext()) {
//				stars->getNext()-> draw(sky);
//			}
//			stars = SkyFactory::getStars(2);
//			while(stars->hasNext()) {
//				stars->getNext()-> draw(sky);
//			}
//			AppLog("Iteration done");

//		    static final float VEGA_RAH = 18.615639F;
//		    static final float VEGA_DEC = 38.78361F;
//		    SkyObject* vega = new SkyObject();
//		    vega->setRAH(18.615639); //setting Vega righ ascenation
//		    vega->setDED(38.78361); // setting Vega declination
//		    vega->draw(sky);

		}
		break;
	default:
		break;
	}
}

void
Form1::OnLocationUpdated(Osp::Locations::Location& location) {
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
Form1::OnProviderStateChanged(Osp::Locations::LocProviderState newState) {
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
Form1::GetLocalSiderialTime(float longitude) {
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
Form1::Log(const Osp::Base::String& aText, const float value) {
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
Form1::Log(const Osp::Base::String& text) {
	String str;
	str = __pLabel->GetText();
	str.Append(text);
	str.Append('\n');
	__pLabel->SetText(str);
	__pLabel->RequestRedraw();
}

void
Form1::ClearLog(const Osp::Base::String& text) {
	__pLabel->SetText(text);
	__pLabel->RequestRedraw();
}

void
Form1::LogSameLine(const Osp::Base::String& text) {
	String str;
	str = __pLabel->GetText();
	str.Append(text);
	__pLabel->SetText(str);
	__pLabel->RequestRedraw();
}




