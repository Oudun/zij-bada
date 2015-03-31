#ifndef _FORM1_H_
#define _FORM1_H_

#include "Sky.h"
#include "SkyCanvas.h"
#include "ConstellationBuilder.h"
#include "StarBuilder.h"

class SkyForm :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener,
 	public Osp::Ui::ITouchEventListener

{

// Construction
public:
	SkyForm();
	virtual ~SkyForm(void);
	bool Initialize(void);
	static const int MAX_ZOOM = 4;
	static const int MIN_ZOOM = 1;

// Implementation
protected:
	static const int ID_BUTTON_OK = 101;
	static const int ID_BUTTON_GPS = 102;
	static const int ID_BUTTON_STARS = 103;
	static const int ID_BUTTON_ZOOM_IN = 1;
	static const int ID_BUTTON_ZOOM_OUT = 2;
	static const int ID_BUTTON_REFRESH = 3;
	static const int ID_BUTTON_CONSTELLATIONS = 4;
	static const int ID_BUTTON_HELP = 5;
	static const int ID_BUTTON_INFO = 6;

	Osp::Ui::Controls::Button *__pButtonZoomIn;
	Osp::Ui::Controls::Button *__pButtonZoomOut;
	Osp::Ui::Controls::Button *__pButtonConstellations;
	Osp::Ui::Controls::Button *__pButtonStars;
	Osp::Ui::Controls::Button *__pButtonHelp;
	Osp::Ui::Controls::Button *__pButtonInfo;
	Osp::Ui::Controls::Label* __pLabel;
	//Osp::Ui::Controls::Label* __pZoomLabel;
	Osp::Ui::Controls::Label* __pLabelLocation;

	Osp::Locations::LocationProvider locProvider;
	Osp::Locales::Calendar* calendar;
	Sky* sky;

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
	void Update(void);

private:
	Osp::Base::String* DegreeToGrad(float angle, const char* posPrefix, const char* negPrefix);
	void updateConstList(Osp::Base::Collection::IList* list);
	int destWidth;
	int destHeight;
	int zoom;
	float shiftX;
	float shiftY;

	Bitmap* bitmapZoomTwo;
	Bitmap* bitmapZoomFour;
	Bitmap* bitmapZoomEight;
	Bitmap* bitmapEmpty;
	Bitmap* bitmapInfo;
	Bitmap* bitmapInfoPressed;

	virtual void OnTouchDoublePressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchFocusIn(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchFocusOut(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchLongPressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchMoved(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchPressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchReleased(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);

};

#endif	//_FORM1_H_
