/*
 * DynamicObjectFactory.h
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#ifndef DYNAMICOBJECTFACTORY_H_
#define DYNAMICOBJECTFACTORY_H_

#include "IGeometryObject.h"
#include "IDynamicObject.h"
#include "IGraphicObject.h"
#include "GeometryObjectsTypes.h"
#include "GeometryPointDynamic.h"
#include <chipmunk/chipmunk.h>

class DynamicObjectFactory
{
public:
	DynamicObjectFactory();
	virtual ~DynamicObjectFactory();

	IDynamicObject * createDynamicObject( IGeometryObject * geometryObject );
	IGraphicObject * createGraphicObject( IDynamicObject * geometryObject, Evas_Object * canvas );

	void setCanvasWidth( unsigned int width );
	void setCanvasHeight( unsigned int height );
	unsigned int getCanvasWidth() const;
	unsigned int getCanvasHeight() const;

	void init();

	cpSpace * getSpace() const;

	static DynamicObjectFactory & getInstance();

private:

	void initSpace();
	void initCanvasBorders();

	cpSpace * m_Space;
	cpVect m_Gravity;

	cpShape * m_LeftBorder;
	cpShape * m_RightBorder;
	cpShape * m_TopBorder;
	cpShape * m_BottomBorder;

	unsigned int m_CanvasWidth;
	unsigned int m_CanvasHeight;

	bool m_Inited;
};

#endif /* DYNAMICOBJECTFACTORY_H_ */
