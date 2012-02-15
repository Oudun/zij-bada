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
//		__pButtonOk->RequestRedraw();
//		Canvas* __pCanvas;
//		__pCanvas = __pButtonOk->GetCanvasN();
//		__pCanvas -> SetBackgroundColor(Color::COLOR_RED);
//		Rectangle rect = __pButtonOk->GetBounds();
//		__pCanvas -> Clear();
//		__pCanvas -> FillRectangle(Color::COLOR_WHITE, rect);
//		__pCanvas -> SetForegroundColor(Color::COLOR_CYAN);
//		__pCanvas -> DrawRectangle(rect);
//		__pCanvas -> Show();
//		__pButtonOk -> RequestRedraw();
	}

	Button *pButton_gps = static_cast<Button *>(GetControl("IDC_BUTTON_GPS"));  
	if (pButton_gps)
	{
		pButton_gps->SetActionId(102);
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
//			Color COLOR_CHOST = Color::COLOR_WHITE; //(48,48,144);
			Color COLOR_CHOST = Color(48,48,144);
//			Color COLOR_NIGHT = Color::COLOR_BLACK; //(24,24,72);
			__pCanvas = control->GetCanvasN();
			__pCanvas->SetLineWidth(1);
			__pCanvas->SetForegroundColor(COLOR_CHOST);
			int x, y, width, height, r;
			int margin = 20;
			Application::GetInstance()->GetAppFrame()->GetFrame()->GetBounds(x, y, width, height);
//			AppLog("x=%d",x);
//			AppLog("y=%d",y);
//			AppLog("width=%d",width);
//			AppLog("height=%d",height);
			r = (Math::Min(width, height) - margin*2)/2;
			Rectangle rect (margin, 2*margin, 2*r, 2*r);
//			//Rectangle rect (0,0,20,20);
			__pCanvas->DrawEllipse(rect);
			__pCanvas->Show();
//			Canvas* __pButtonCanvas;
//			__pButtonCanvas = source.GetCanvasN();
//			AppLog("source.GetBounds().x=%d", source.GetBounds().x);
//			AppLog("source.GetBounds().y=%d", source.GetBounds().y);
//			AppLog("source.GetBounds().height=%d", source.GetBounds().height);
//			AppLog("source.GetBounds().width=%d", source.GetBounds().width);
//			Rectangle buttonRect = source.GetBounds();
//			buttonRect.SetPosition(0,0);
//			__pButtonCanvas->FillRectangle(COLOR_NIGHT, buttonRect);
//			__pButtonCanvas->DrawRectangle(buttonRect);
			__pLabel->SetText("OK\n");
			__pLabel->RequestRedraw();
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
	case ID_BUTTON_STARS:
		{
			AppLog("STARS Button is clicked! \n");
			IterateStars();
		}
		break;
	default:
		break;
	}
}

void
Form1::OnLocationUpdated(Osp::Locations::Location& location) {
	//EditArea *pText = static_cast<EditArea *>(GetControl("IDC_EDITAREA1"));
	AppLog("Location Updated\n");
	const QualifiedCoordinates* coordinates = location.GetQualifiedCoordinates();
	AppLog("Coordinates taken\n");
	AppLog("Label\n");
	String str;
	if (coordinates != 0) {
		double latd = coordinates->GetLatitude();
		AppLog("Latitude (double) taken\n");
		AppLog("Latitude (float) taken\n");
		Log("Latitude = ",(float)(coordinates->GetLatitude()));
		Log("Longitude = ",(float)(coordinates->GetLongitude()));
		Log("SLT = ", GetLocalSiderialTime((float)(coordinates->GetLongitude())));
		locProvider.CancelLocationUpdates();
	} else {
		//float lst = GetLocalSiderialTime((float)(55.75578));
		LogSameLine("#");
	}
}

void
Form1::OnProviderStateChanged(Osp::Locations::LocProviderState newState) {
	AppLog("Location Provider state changed\n");
	Log("Location Provider state changed\n");
	if (newState == LOC_PROVIDER_AVAILABLE) {
		AppLog("LOC_PROVIDER_AVAILABLE");
		Log("LOC_PROVIDER_AVAILABLE");
	} else if (newState == LOC_PROVIDER_OUT_OF_SERVICE) {
		AppLog("LOC_PROVIDER_AVAILABLE");
		Log("LOC_PROVIDER_AVAILABLE");
	} else if (newState == LOC_PROVIDER_TEMPORARILY_UNAVAILABLE) {
		AppLog("LOC_PROVIDER_TEMPORARILY_UNAVAILABLE");
		Log("LOC_PROVIDER_TEMPORARILY_UNAVAILABLE");
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
//	currTime->SetValue(2012,2,13,15,5,33);
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

void
Form1::IterateStars (void) {

	String fileName(L"/Home/catalog");
	File file;
	result r = file.Construct(fileName, L"r+");
	char buffer[1];
	String* line = new String();
	r = E_SUCCESS;
	do {
		file.Read(buffer, 1);
		if(buffer[0]!='\n') {
			line->Append(buffer[0]);
		} else {
			ClearLog(*line);
			AppLog("%s",line);
			line->Clear();
		}
		r = GetLastResult();
	} while (!IsFailed(r));


}


