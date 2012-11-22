#ifndef _FORM1_H_
#define _FORM1_H_

#include "Sky.h"
#include "ConstellationForm.h"

class SkyForm :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener,
	public Osp::Locations::ILocationListener
{

// Construction
public:
	SkyForm(void);
	virtual ~SkyForm(void);
	bool Initialize(void);

// Implementation
protected:
	static const int ID_BUTTON_OK = 101;
	static const int ID_BUTTON_GPS = 102;
	static const int ID_BUTTON_STARS = 103;
	static const int ID_BUTTON_ZOOM_IN = 1;
	static const int ID_BUTTON_ZOOM_OUT = 2;
	static const int ID_BUTTON_REFRESH = 3;
	static const int ID_BUTTON_CONSTELLATIONS = 4;

	Osp::Ui::Controls::Button *__pButtonOk;
	Osp::Ui::Controls::Button *__pButtonZoomIn;
	Osp::Ui::Controls::Button *__pButtonZoomOut;
	Osp::Ui::Controls::Button *__pButtonRefresh;
	Osp::Ui::Controls::Button *__pButtonConstellations;
	Osp::Ui::Controls::Label* __pLabel;
	Osp::Ui::Controls::Label* __pZoomLabel;
	Osp::Ui::Controls::Label* __pLabelLocation;
	ConstellationForm* __pConstForm;

	Osp::Locations::LocationProvider locProvider;
	Osp::Locales::Calendar* calendar;
	Sky* sky;

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
	virtual void OnLocationUpdated(Osp::Locations::Location& location);
	virtual void OnProviderStateChanged(Osp::Locations::LocProviderState newState);

private:
	float GetLocalSiderialTime(float aLon);
	Osp::Base::String* DegreeToGrad(float angle, const char* posPrefix, const char* negPrefix);
	void updateConstList(Osp::Base::Collection::IList* list);
};

#endif	//_FORM1_H_
