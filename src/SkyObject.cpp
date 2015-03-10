/*
 * SkyObject.cpp
 *
 *  Created on: 17.02.2012
 *      Author: ddreval
 */

#include "SkyObject.h"

using namespace Osp::Base;
using namespace Osp::Base::Utility;
using namespace Osp::Graphics;

SkyObject::SkyObject() {

}

SkyObject::~SkyObject() {

}

float
SkyObject::getRAH(void) {
	return RAH;
}

float
SkyObject::getDED(void) {
	return DED;
}

void
SkyObject::setMagnitude(float pMagnitude) {
	this -> magnitude = pMagnitude;
}

void
SkyObject::setSign(bool isNorthern) {
	sign = isNorthern;
}

void
SkyObject::setName(Osp::Base::String& aName) {
	name = aName;
}

Osp::Base::String&
SkyObject::getName(void) {
	return name;
}

void
SkyObject::setConstellation(Osp::Base::String& aConstellation) {
	constellation = aConstellation;
}

Osp::Base::String&
SkyObject::getConstellation(void) {
	return constellation;
}

bool
SkyObject::isNorthern(void) {
	return sign;
}

float
SkyObject::getMagnitude(void) {
	return magnitude;
}

void
SkyObject::setDED(float DED) {
    this->DED = DED;
}

void
SkyObject::setRAH(float RAH) {
    this->RAH = RAH;
}

void
SkyObject::Print(void) {
	if (name==null) {
		AppLog("NAME IS NULL");
	}
	AppLog("Object name=%S, magnitude=%f, ra=%f, de=%f, north=%d", name.GetPointer(), magnitude, RAH, DED, sign);
}

bool
SkyObject::Draw() {

	PrecisePoint* zoomedPoint = new PrecisePoint();

	Canvas* canvas;
	canvas = SkyCanvas::GetStarCanvas(1);

	PrecisePoint* point = Projector::
			GetProjection(RAH, DED, sign,
					canvas->GetBounds().width,
					canvas->GetBounds().height);

	if (point == null) {
		delete zoomedPoint;
		return false;
	}

	if(getConstellation() != null && !getConstellation().IsEmpty() && getConstellation().GetLength()>2) {
		int __gridX = (int)((point->x)/5);
		int __gridY = (int)((point->y)/5);
//		AppLog("MAP %d %d %S", 5 * __gridX, 5 * __gridY, getConstellation().GetPointer());
		if (Projector::screenToConstMap[__gridX][ __gridY] == null) {
			Projector::screenToConstMap[__gridX][ __gridY] = getConstellation();
//			AppLog("x:%d y:%d %S added", __gridX, __gridY, getConstellation().GetPointer());
		}
	}

	Projector::Zoom(point, zoomedPoint, 1);

	DrawCanvas(canvas, zoomedPoint);

	Projector::Zoom(point, zoomedPoint, 2);

	canvas = SkyCanvas::GetStarCanvas(2);
	DrawCanvas(canvas, zoomedPoint);

	Projector::Zoom(point, zoomedPoint, 4);

	canvas = SkyCanvas::GetStarCanvas(4);
	DrawCanvas(canvas, zoomedPoint);

	delete zoomedPoint;
	return true;

}

void
SkyObject::DrawCanvas(Canvas* canvas, PrecisePoint* point) {

	Color color = COLOR_BRIGHT_STAR;


	int diameter;

	if (magnitude < -1) {
		diameter = 8;
	} else if (magnitude < 0) {
		diameter = 6;
	} else if (magnitude < 1) {
		diameter = 4;
	} else if (magnitude < 2) {
		diameter = 3;
	} else if (magnitude < 3) {
		diameter = 2;
	} else if (magnitude < 4) {
		diameter = 1;
	} else if (magnitude < 5) {
		color = COLOR_DIM_STAR;
		diameter = 1;
	} else {
		color = COLOR_DIMMEST_STAR;
		diameter = 1;
	}

	canvas ->FillEllipse(color,
		Rectangle(point->x, point->y, diameter, diameter));

}

bool
SkyObject::DrawCanvas(Canvas* canvas) {

	return DrawCanvas(canvas, COLOR_BRIGHT_STAR, COLOR_DIM_STAR);

}

bool
SkyObject::DrawCanvas(Osp::Graphics::Canvas* canvas, const Color& brightColor, const Color& dimColor) {

	PrecisePoint* point = Projector::
			GetProjection(RAH, DED, sign,
					canvas->GetBounds().width,
					canvas->GetBounds().height);

	if (point == null) {
		return false;
	}

	Color color = brightColor;

	int diameter = (int)(7 - magnitude);

		if (magnitude < -1) {
			diameter = 8;
		} else if (magnitude < 0) {
			diameter = 6;
		} else if (magnitude < 1) {
			diameter = 5;
		} else if (magnitude < 2) {
			diameter = 4;
		} else if (magnitude < 3) {
			diameter = 3;
		} else if (magnitude < 4) {
			diameter = 2;
		} else if (magnitude < 5) {
			color = dimColor;
			diameter = 1;
		} else {
			color = dimColor;
			diameter = 1/2;
		}

		canvas ->FillEllipse(color,
			Rectangle(point->x, point->y, diameter, diameter));

		return true;

}

int
SkyObject::GetSizeOnCanvas(void) {

	int diameter = (int)(7 - magnitude);

	if (magnitude < -1) {
			diameter = 8;
		} else if (magnitude < 0) {
			diameter = 6;
		} else if (magnitude < 1) {
			diameter = 4;
		} else if (magnitude < 2) {
			diameter = 3;
		} else if (magnitude < 3) {
			diameter = 2;
		} else if (magnitude < 4) {
			diameter = 1;
		} else if (magnitude < 5) {
			diameter = 1;
		} else {
			diameter = 1;
		}

	return diameter;

}



