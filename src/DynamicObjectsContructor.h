/*
 * DynamicObjectsContructor.h
 *
 *  Created on: 5 апр. 2015
 *      Author: vadim
 */

#ifndef DYNAMICOBJECTSCONTRUCTOR_H_
#define DYNAMICOBJECTSCONTRUCTOR_H_

#include "IGeometryObject.h"
#include "IDynamicObject.h"
#include <vector>

class DynamicObjectsContructor
{
public:
	DynamicObjectsContructor( int CanvasWidth, int CanvasHeight );
	virtual ~DynamicObjectsContructor();

	void convert( vector<IGeometryObject *> & geometryObjects, vector<IDynamicObject *> & dynamicObjects );
	void convertSmart( vector<IGeometryObject *> & geometryObjects, vector<IDynamicObject *> & dynamicObjects );

	void setCanvasWidth( int width );
	void setCanvasHeight( int height );

private:

	 int m_CanvasWidth;
	 int m_CanvasHeight;
};

#endif /* DYNAMICOBJECTSCONTRUCTOR_H_ */
