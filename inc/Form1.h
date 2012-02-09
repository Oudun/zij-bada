#ifndef _FORM1_H_
#define _FORM1_H_

//#include <FBase.h>
//#include <FUi.h>

#include <FBase.h>
#include <FGraphics.h>
#include <FMedia.h>
#include <FApp.h>
#include <FUi.h>
#include <FSystem.h>
#include <FLocations.h>


class Form1 :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener,
	public Osp::Locations::ILocationListener
{

// Construction
public:
	Form1(void);
	virtual ~Form1(void);
	bool Initialize(void);


// Implementation
protected:
	static const int ID_BUTTON_OK = 101;
	static const int ID_BUTTON_GPS = 1;
	Osp::Ui::Controls::Button *__pButtonOk;

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
	virtual void OnLocationUpdated(Osp::Locations::Location& location);
	virtual void OnProviderStateChanged(Osp::Locations::LocProviderState newState);
};

#endif	//_FORM1_H_
