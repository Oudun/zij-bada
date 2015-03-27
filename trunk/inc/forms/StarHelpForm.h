
#ifndef _STARHELPFORM_H_
#define _STARHELPFORM_H_

#include <FBase.h>
#include <FUi.h>
#include <FApp.h>
#include "Constants.h"

class StarHelpForm :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener
{

// Construction
public:
	StarHelpForm(void);
	virtual ~StarHelpForm(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);
	void OnActionPerformed(const Osp::Ui::Control& source, int actionId);

// Implementation
protected:

// Generated call-back functions
public:

};

#endif
