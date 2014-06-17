
#include "forms/InfoForm.h"

using namespace Osp::Base;
using namespace Osp::Locales;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;


InfoForm::InfoForm(void)
{
}

InfoForm::~InfoForm(void)
{
}

bool
InfoForm::Initialize()
{
	Form::Construct(L"INFO_FORM");

	return true;
}

result
InfoForm::OnInitializing(void)
{
	result r = E_SUCCESS;
	SetBackgroundColor(COLOR_FORM_BKG);

	Osp::App::AppResource* pAppResource = Osp::App::Application::GetInstance()->GetAppResource();
	Osp::Graphics::Bitmap* bitmapButton;
	Osp::Graphics::Bitmap* bitmapButtonPressed;
	bitmapButton = pAppResource -> GetBitmapN(L"Button.png");
	bitmapButtonPressed = pAppResource -> GetBitmapN(L"ButtonPressed.png");

	Button* __buttonBack;
	__buttonBack = static_cast<Button *>(GetControl(L"IDC_BUTTON_BACK"));
	__buttonBack -> SetActionId(0);
	__buttonBack -> SetNormalBackgroundBitmap(*bitmapButton);
	__buttonBack -> SetPressedBackgroundBitmap(*bitmapButtonPressed);
	__buttonBack -> SetTextColor(COLOR_BUTTON_TEXT);
	__buttonBack -> AddActionEventListener(*this);
	__buttonBack -> SetText(Constants::GetString(STRING_BACK));

	__labelTime = static_cast<Label *>(GetControl(L"IDC_LABEL_MAP_TIME"));
	__labelTime -> SetBackgroundColor(COLOR_FORM_BKG);
	__labelTime -> SetTextColor(COLOR_FORM_TEXT);
	__labelTime -> SetText(Constants::GetString(STRING_SKY_TIME));

	__labelTimeValue = static_cast<Label *>(GetControl(L"IDC_LABEL_MAP_TIME_VALUE"));
	__labelTimeValue -> SetBackgroundColor(COLOR_FORM_BKG);
	__labelTimeValue -> SetTextColor(COLOR_FORM_TEXT);

	__labelCoordinates = static_cast<Label *>(GetControl(L"IDC_LABEL_COORDINATES"));
	__labelCoordinates -> SetBackgroundColor(COLOR_FORM_BKG);
	__labelCoordinates -> SetTextColor(COLOR_FORM_TEXT);
	__labelCoordinates -> SetText(Constants::GetString(STRING_SKY_COORDS));

	__labelCoordinatesValue = static_cast<Label *>(GetControl(L"IDC_LABEL_COORDINATES_VALUE"));
	__labelCoordinatesValue -> SetBackgroundColor(COLOR_FORM_BKG);
	__labelCoordinatesValue -> SetTextColor(COLOR_FORM_TEXT);
	__labelCoordinatesValue -> SetText(Constants::GetString(STRING_SKY_COORDS));

	return r;
}


result
InfoForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void
InfoForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId) {
	Osp::App::Application::GetInstance() -> SendUserEvent(EVENT_HELP_CLOSED, null);
}

result
InfoForm::OnDraw(void) {

	float time = TimeAndPlace::GetSiderialTime();
	AppLog("Siderial time is %f", time);
	DateTime* dateTime = TimeAndPlace::GetStandardDateTime();
//
//	String timeStr;
//	timeStr.Format(22, L"%d:%d:%d", dateTime->GetHour(), dateTime->GetMinute(), dateTime->GetSecond());
//	__labelTimeValue -> SetText(timeStr);

	String customizedPattern = L"HH:mm:ss zzzz";
	String readableDateTime;
	DateTimeFormatter* formatter = DateTimeFormatter::CreateDateFormatterN();
	formatter -> ApplyPattern(customizedPattern);
	formatter -> Format(*dateTime, readableDateTime);
	__labelTimeValue -> SetText(readableDateTime);

	// HH:mm:ss zzzz

//    pDateFormatter->Format(today, formattedString);
//
//    // Get time formatter
//    DateTimeFormatter* pTimeFormatter = DateTimeFormatter::CreateTimeFormatterN(locale, DATE_TIME_STYLE_DEFAULT);
//
//    // Format today with date formatter
//    pTimeFormatter->Format(today, formattedString);
//
//    // Customized pattern
//    String cutomizedPattern = L"EEE d MMM yy";
//    pDateFormatter->ApplyPattern(cutomizedPattern);



	String locationStr;
	locationStr.Format(22, L"%S\n%S",
			TimeAndPlace::GetReadableLongitude() -> GetPointer(),
			TimeAndPlace::GetReadableLatitude() -> GetPointer());
	__labelCoordinatesValue -> SetText(locationStr);

}
