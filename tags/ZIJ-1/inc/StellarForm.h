/*
 * StellarForm.h
 *
 *  Created on: 04.03.2013
 *      Author: ddreval
 */

#ifndef STELLARFORM_H_
#define STELLARFORM_H_

#include <FApp.h>
#include <FUi.h>
#include <FBase.h>
#include <FGraphics.h>
#include "SkyCanvas.h"



class StellarForm  :
	public Osp::Ui::Controls::Form,
 	public Osp::Ui::IItemEventListener{
public:
	StellarForm(SkyCanvas* skyCanvas);
	virtual ~StellarForm();
	bool Initialize(void);
	virtual result OnInitializing(void);
	void Update(void);
	virtual void OnItemStateChanged(const Osp::Ui::Control &source, int index, int itemId, Osp::Ui::ItemStatus status);

private:
	Osp::Graphics::Canvas* canvas;
	SkyCanvas* skyCanvas;
	Osp::Ui::Controls::List* pList1;

};

#endif /* STELLARFORM_H_ */
