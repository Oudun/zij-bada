
#ifndef _SKYBUILDERFORM_H_
#define _SKYBUILDERFORM_H_

#include <FBase.h>
#include <FUi.h>

#include "TimeAndPlace.h"
#include "SkyBuilder.h"
#include "SkyCanvas.h"

class SkyBuilderForm :
	public Osp::Ui::Controls::Form
{

// Construction
public:
	SkyBuilderForm();
	virtual ~SkyBuilderForm(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);
	virtual result OnDraw(void);
	void SetRange(int min, int max);
	void SetProgress(int value);
	void Start(void);

private:
	Osp::Ui::Controls::Progress* __pStarsProgress;
	Osp::Ui::Controls::Label* __label;
	SkyBuilder* skyBuilder;

};

#endif
