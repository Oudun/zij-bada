/*
 * Projector.cpp
 *
 *  Created on: 27.11.2012
 *      Author: ddreval
 */

#include "Projector.h"

using namespace Osp::Base::Utility;
using namespace Osp::Graphics;

Projector::Projector() {
}

Projector::~Projector() {
	// TODO Auto-generated destructor stub
}

Osp::Graphics::Point*
Projector::GetProjection(float accentation, float declination, int sign, int width, int height) {
	float lstDeg = 15*(TimeAndPlace::GetSiderialTime());
	float raDeg = accentation * 15; // 24 hours is 360 degrees, so 1 hour is 15 degrees
	float ha = lstDeg > raDeg ? lstDeg - raDeg : 360 + lstDeg - raDeg;
	double radInDegree = 0.0174532925;
	float decSigned = sign ? declination : -declination;
    double sinAlt =
        Math::Sin(radInDegree*decSigned)*Math::Sin(radInDegree*(TimeAndPlace::GetLatitude()))
        +Math::Cos(radInDegree*decSigned)*Math::Cos(radInDegree*(TimeAndPlace::GetLatitude()))*Math::Cos(radInDegree*(ha));

    // show only stars higher than 30 degrees above ground
    if (sinAlt < 0.5) {
    	return null;
    }
    double cosAlt =
        Math::Sqrt(1-sinAlt*sinAlt);
    double sinAz =
        -(Math::Sin(radInDegree*(ha))*Math::Cos(radInDegree*(decSigned)))/cosAlt;
    double cosAz =
        (Math::Sin(radInDegree*decSigned)-Math::Sin(radInDegree*(TimeAndPlace::GetLatitude()))*sinAlt)/
            (Math::Cos(radInDegree*(TimeAndPlace::GetLatitude()))*cosAlt);
    double R = Math::Floor(width/2);
    double r = R * cosAlt;
    int top  = (int)((Math::Floor(height/2)) - r * cosAz);
    int left = (int)((Math::Floor(width/2)) - r * sinAz);
    return new Point(left, top);
}

Osp::Graphics::Point*
Projector::Zoom(
		Osp::Graphics::Point* source,
		Osp::Graphics::Point* result,
		int ratio) {
	result -> SetPosition(ratio * source->x, ratio * source->y);
}
