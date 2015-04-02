/*
 * GraphicPointDynamic.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: vostanin
 */

#include "GraphicPointDynamic.h"

GraphicPointDynamic::GraphicPointDynamic( GeometryPointDynamic * geometryObject, Evas_Object * glview ) : GraphicPoint( geometryObject, glview )
{
	m_DynamicPoint = geometryObject;
}

GraphicPointDynamic::~GraphicPointDynamic()
{
}

void GraphicPointDynamic::draw()
{
	m_DynamicPoint->update();

	GraphicPoint::draw();
}
























