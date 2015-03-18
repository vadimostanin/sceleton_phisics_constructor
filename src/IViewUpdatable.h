/*
 * DrawingContentUpdatable.h
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#ifndef IVIEWUPDATABLE_H_
#define IVIEWUPDATABLE_H_

#include "Point.h"

class IViewUpdatable
{
public:
	virtual ~IViewUpdatable(){}

	virtual void update() = 0;
};


#endif /* IVIEWUPDATABLE_H_ */
