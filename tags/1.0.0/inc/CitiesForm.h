
#ifndef _CITIESFORM_H_
#define _CITIESFORM_H_

#include <FBase.h>
#include <FUi.h>



class CitiesForm :
	public Osp::Ui::Controls::Form
{

// Construction
public:
	CitiesForm(void);
	virtual ~CitiesForm(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);

// Implementation
protected:

// Generated call-back functions
public:

};

#endif
