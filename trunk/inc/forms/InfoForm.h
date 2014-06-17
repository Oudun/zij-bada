
#ifndef _INFOFORM_H_
#define _INFOFORM_H_

#include <FBase.h>
#include <FUi.h>
#include <FApp.h>
#include "Constants.h"
#include "TimeAndPlace.h"

class InfoForm :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener
{

// Construction
public:
	InfoForm(void);
	virtual ~InfoForm(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);
	void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
	result OnDraw(void);

private:
	Osp::Ui::Controls::Label* __labelTime;
	Osp::Ui::Controls::Label* __labelTimeValue;
	Osp::Ui::Controls::Label* __labelCoordinates;
	Osp::Ui::Controls::Label* __labelCoordinatesValue;

};

#endif
