
#ifndef _SKYBUILDERFORM_H_
#define _SKYBUILDERFORM_H_

#include <FBase.h>
#include <FUi.h>

#include "TimeAndPlace.h"
#include "SkyBuilder.h"

class SkyBuilderForm :
	public Osp::Ui::Controls::Form
{

// Construction
public:
	SkyBuilderForm(TimeAndPlace* timeAndPlace);
	virtual ~SkyBuilderForm(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);
	void SetRange(int min, int max);
	void SetProgress(int value);

private:
	TimeAndPlace* timeAndPlace;
	Osp::Ui::Controls::Progress* __pStarsProgress;
	SkyBuilder* skyBuilder;

};

#endif
