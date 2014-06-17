
#ifndef _HELPFORM_H_
#define _HELPFORM_H_

#include <FBase.h>
#include <FUi.h>
#include <FApp.h>
#include "Constants.h"

class HelpForm :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener
{

// Construction
public:
	HelpForm(void);
	virtual ~HelpForm(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);
	void OnActionPerformed(const Osp::Ui::Control& source, int actionId);

};

#endif
