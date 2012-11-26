#include "SkyForm.h"

using namespace Osp::Base;
using namespace Osp::Base::Utility;
using namespace Osp::Base::Runtime;
using namespace Osp::Base::Collection;
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
	Construct(L"SKY_FORM");
	return true;
}

result
SkyForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	__pButtonZoomIn = static_cast<Button *>(GetControl(L"IDC_BUTTON_ZOOM_IN"));
	if (__pButtonZoomIn != null)
	{
		__pButtonZoomIn->SetActionId(ID_BUTTON_ZOOM_IN);
		__pButtonZoomIn->AddActionEventListener(*this);
	}

	__pButtonZoomOut = static_cast<Button *>(GetControl(L"IDC_BUTTON_ZOOM_OUT"));
	if (__pButtonZoomOut != null)
	{
		__pButtonZoomOut->SetActionId(ID_BUTTON_ZOOM_OUT);
		__pButtonZoomOut->AddActionEventListener(*this);
	}

	__pButtonRefresh = static_cast<Button *>(GetControl(L"IDC_BUTTON_REFRESH"));
	if (__pButtonRefresh != null)
	{
		__pButtonRefresh->SetActionId(ID_BUTTON_REFRESH);
		__pButtonRefresh->AddActionEventListener(*this);
	}

	__pButtonConstellations = static_cast<Button *>(GetControl(L"IDC_BUTTON_CONSTELLATIONS"));
	if (__pButtonConstellations != null)
	{
		__pButtonConstellations->SetActionId(1);
		__pButtonConstellations->AddActionEventListener(*this);
		__pButtonConstellations->SetActionId(ID_BUTTON_CONSTELLATIONS);
		__pButtonConstellations->AddActionEventListener(*this);
	}

	//IDC_BUTTON_CONSTELLATIONS

	__pLabelLocation = static_cast<Label *>(GetControl(L"IDC_LABEL1"));
	__pLabelLocation ->SetText(L"Location");

	__pZoomLabel = static_cast<Label *>(GetControl("IDC_LABEL_ZOOM"));

	__pConstForm = new ConstellationForm(this);
	__pConstForm -> Construct(FORM_STYLE_NORMAL| FORM_STYLE_INDICATOR| FORM_STYLE_HEADER| FORM_STYLE_FOOTER);
	__pConstForm -> SetBackgroundColor(Color::COLOR_CYAN);

	Control* control = GetControl(L"SKY_FORM");
	sky = new Sky(control->GetCanvasN());
	AppLog("B");
	locProvider.Construct(LOC_METHOD_HYBRID);
	locProvider.RequestLocationUpdates(*this, 5, true);

	Button *pButton1 = static_cast<Button *>(GetControl("IDC_BUTTON1"));  
	if (pButton1)
	{
		pButton1->SetActionId(1);
		pButton1->AddActionEventListener(*this);
	}
	Button *pButton_refresh = static_cast<Button *>(GetControl("IDC_BUTTON_REFRESH"));  
	if (pButton_refresh)
	{
		pButton_refresh->SetActionId(3);
		pButton_refresh->AddActionEventListener(*this);
	}
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
	case ID_BUTTON_ZOOM_IN:
		{
			AppLog("Zoom in ?");
			String str = "X";
			str.Append(sky->getZoom());
			__pZoomLabel->SetText(str);
			if (sky->canZoomIn()) {
				String str = "X";
				str.Append(sky->getZoom());
				__pZoomLabel->SetText(str);
				sky->zoomIn();
				updateConstList(sky->getConst());
			}
		}
		break;
	case ID_BUTTON_ZOOM_OUT:
		{
			AppLog("Zoom out ?");
			if (sky->canZoomOut()) {
				String str = "X";
				str.Append(sky->getZoom());
				__pZoomLabel->SetText(str);
				sky->zoomOut();
				updateConstList(sky->getConst());
			}
		}
		break;
	case ID_BUTTON_REFRESH:
		{
			sky->draw();
			updateConstList(sky->getConst());
		}
		break;
	case ID_BUTTON_CONSTELLATIONS:
			{
				//AppLog("!!!ID_BUTTON_CONSTELLATIONS");
				Frame* frame = Application::GetInstance()->GetAppFrame()->GetFrame();
				if (!frame -> GetControls()->Contains(*__pConstForm)) {
					frame -> AddControl(*__pConstForm);
				}
				frame -> SetCurrentForm(*__pConstForm);
				__pConstForm -> RequestRedraw(true);
				__pConstForm -> Show();
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
	String str;
	if (coordinates != 0) {
		AppLog("Coordinates taken\n");
		String locationStr;
		locationStr.Format(21, L"%S %S",
				(DegreeToGrad(coordinates->GetLatitude(), "N", "S")->GetPointer()),
				(DegreeToGrad(coordinates->GetLongitude(), "E", "W")->GetPointer()));
		__pLabelLocation->SetText(locationStr.GetPointer());
		__pLabelLocation->Draw();
		sky->setLatitude(coordinates->GetLatitude());
		sky->setLongitude(coordinates->GetLongitude());
		locProvider.CancelLocationUpdates();
		sky->draw();
	} else {
		AppLog("#");
	}
}

void
SkyForm::OnProviderStateChanged(Osp::Locations::LocProviderState newState) {
	AppLog("Location Provider state changed\n");
	if (newState == LOC_PROVIDER_AVAILABLE) {
		AppLog("The location provider is available");
	} else if (newState == LOC_PROVIDER_OUT_OF_SERVICE) {
		AppLog("The location provider is out of service");
	} else if (newState == LOC_PROVIDER_TEMPORARILY_UNAVAILABLE) {
		AppLog("The location provider is temporarily unavailable");
	} else {
		AppLog("State unknown");
	}
}

float
SkyForm::GetLocalSiderialTime(float longitude) {
	TimeZone timeZone(60, L"Europe/London");
	DateTime* currTime = new DateTime();
	SystemTime::GetCurrentTime(*currTime);
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
	return sltHrs;
}

// Converts from decimal format -12,34456789 to N12°34'56
String*
SkyForm::DegreeToGrad(float angle, const char* posPrefix, const char* negPrefix) {
	const char* prefix = angle < 0 ? negPrefix : posPrefix;
	AppLog("orig: %f", angle);
	float latAbs = angle * 1000000;
	float deg = Math::Abs(Math::Floor(latAbs/1000000));
	AppLog("deg: %f", deg);
	float min = Math::Floor(((latAbs/1000000) - Math::Floor(latAbs/1000000))*60);
	AppLog("min: %f", min);
	float sec = Math::Floor(((((latAbs/1000000) - Math::Floor(latAbs/1000000))*60) - Math::Floor(((latAbs/1000000) - Math::Floor(latAbs/1000000))*60))*100000)*60/100000;
	AppLog("sec: %f", sec);
	String* result = new String();
	result->Format(10, L"%s%d°%d\'%d\"", prefix, (int)deg, (int)min, (int)sec);
	return result;
}

void
SkyForm::updateConstList(IList* list) {
	__pConstForm -> UpdateConstellationList(list);
}

void
SkyForm::OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList *pArgs) {
	AppLog("OnUserEventReceivedN");
	Frame* frame = Application::GetInstance()->GetAppFrame()->GetFrame();
	frame -> SetCurrentForm(*this);
	RequestRedraw(true);
	Show();
	sky->draw();
}



