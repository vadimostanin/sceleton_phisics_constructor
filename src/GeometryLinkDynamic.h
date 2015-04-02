/*
 * GeometryLinkDynamic.h
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#ifndef GEOMETRYLINKDYNAMIC_H_
#define GEOMETRYLINKDYNAMIC_H_

#include "GeometryLink.h"
#include "IDynamicObject.h"

class GeometryLinkDynamic: public GeometryLink, public IDynamicObject {
public:
	GeometryLinkDynamic();
	virtual ~GeometryLinkDynamic();

	void update();
};

#endif /* GEOMETRYLINKDYNAMIC_H_ */
