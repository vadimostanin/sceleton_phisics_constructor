/*
 * IGraphicObject.h
 *
 *  Created on: Mar 17, 2015
 *      Author: vostanin
 */

#ifndef IGRAPHICOBJECT_H_
#define IGRAPHICOBJECT_H_

#include <Evas.h>

class IGraphicObject
{
public:
	virtual ~IGraphicObject(){}

	virtual void draw( Evas * canvas ) = 0;
};


#endif /* IGRAPHICOBJECT_H_ */
