/*
 * StellarForm.h
 *
 *  Created on: 04.03.2013
 *      Author: ddreval
 */

#ifndef STELLARFORM_H_
#define STELLARFORM_H_

#include <FUi.h>
#include <FBase.h>
#include <FGraphics.h>
#include "SkyCanvas.h"



class StellarForm  :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener{
public:
	StellarForm(SkyCanvas* skyCanvas);
	virtual ~StellarForm();
	bool Initialize(void);
	virtual result OnInitializing(void);
	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
	void DoIt(void);
private:
	Osp::Graphics::Canvas* canvas;
	SkyCanvas* skyCanvas;

};

#endif /* STELLARFORM_H_ */
