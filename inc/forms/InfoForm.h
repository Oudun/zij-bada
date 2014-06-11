
#ifndef _INFOFORM_H_
#define _INFOFORM_H_

#include <FBase.h>
#include <FUi.h>
#include "Constants.h"

class InfoForm :
	public Osp::Ui::Controls::Form
{

// Construction
public:
	InfoForm(void);
	virtual ~InfoForm(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);

// Implementation
protected:

// Generated call-back functions
public:

};

#endif
