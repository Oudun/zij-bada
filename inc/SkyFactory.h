/*
 * To provide access to sky object storage
 *
 *  Created on: Feb 22, 2012
 *      Author: Denis
 */

#ifndef SKYFACTORY_H_
#define SKYFACTORY_H_

#include "SkyIterator.h"

class SkyFactory {
public:
	SkyFactory();
	virtual ~SkyFactory();
	static SkyIterator* getStars(float magnitude);
};

#endif /* SKYFACTORY_H_ */
