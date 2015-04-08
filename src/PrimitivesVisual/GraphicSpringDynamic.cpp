/*
 * GraphicLinkDynamic.cpp
 *
 *  Created on: Apr 3, 2015
 *      Author: vostanin
 */

#include "GraphicSpringDynamic.h"

GraphicSpringDynamic::GraphicSpringDynamic( GeometrySpringDynamic * dynamicObject, Evas_Object * glview ) : GraphicSpring( dynamicObject, glview )
{
	m_DynamicSpring = dynamicObject;
}

GraphicSpringDynamic::~GraphicSpringDynamic()
{
}

void GraphicSpringDynamic::draw()
{
	m_DynamicSpring->update();

	GraphicSpring::draw();
}






















