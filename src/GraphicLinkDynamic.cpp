/*
 * GraphicLinkDynamic.cpp
 *
 *  Created on: Apr 3, 2015
 *      Author: vostanin
 */

#include "GraphicLinkDynamic.h"

GraphicLinkDynamic::GraphicLinkDynamic( GeometryLinkDynamic * dynamicObject, Evas_Object * glview ) : GraphicLink( dynamicObject, glview )
{
	m_DynamicLink = dynamicObject;
}

GraphicLinkDynamic::~GraphicLinkDynamic()
{
}

void GraphicLinkDynamic::draw()
{
	m_DynamicLink->update();

	GraphicLink::draw();
}






















