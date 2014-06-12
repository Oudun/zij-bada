
#ifndef _INFOFORM_H_
#define _INFOFORM_H_

#include <FBase.h>
#include <FUi.h>
#include "Constants.h"
#include <FApp.h>

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

// Implementation
protected:

// Generated call-back functions
public:

};

#endif
