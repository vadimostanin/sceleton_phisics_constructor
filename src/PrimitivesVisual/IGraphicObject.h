/*
 * IGraphicObject.h
 *
 *  Created on: Mar 17, 2015
 *      Author: vostanin
 */

#ifndef IGRAPHICOBJECT_H_
#define IGRAPHICOBJECT_H_

#include "IGeometryObject.h"
#include <Evas.h>

class IGraphicObject
{
public:
	virtual ~IGraphicObject(){}

	virtual IGeometryObject & getGeometryObject() = 0;

	virtual void draw() = 0;
};


#endif /* IGRAPHICOBJECT_H_ */
