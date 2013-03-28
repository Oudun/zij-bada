
#ifndef _ALTERLOCATIONFORM_H_
#define _ALTERLOCATIONFORM_H_

#include <FBase.h>
#include <FUi.h>
#include <FApp.h>
#include "TimeAndPlace.h"

class AlterLocationForm :
	public Osp::Ui::Controls::Form,
 	public Osp::Ui::IActionEventListener
{

// Construction
public:
	AlterLocationForm(void);
	virtual ~AlterLocationForm(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);

// Implementation
protected:
	static const int ID_BUTTON_QUIT = 0;
	static const int IDC_BUTTON_PREV_LOCATION = 1;
	static const int IDC_BUTTON_MAP_LOCATION = 2;

// Generated call-back functions
public:
	virtual void OnActionPerformed(const Osp::Ui::Control &source, int actionId);

public:
	static const int USE_PREV_LOCATION = 50;
	static const int USE_MAP_LOCATION = 51;

};

#endif
