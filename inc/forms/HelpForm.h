
#ifndef _HELPFORM_H_
#define _HELPFORM_H_

#include <FBase.h>
#include <FUi.h>
#include "Constants.h"

class HelpForm :
	public Osp::Ui::Controls::Form
{

// Construction
public:
	HelpForm(void);
	virtual ~HelpForm(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);

// Implementation
protected:

// Generated call-back functions
public:

};

#endif
