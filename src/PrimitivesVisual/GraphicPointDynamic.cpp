/*
 * GraphicPointDynamic.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: vostanin
 */

#include "GraphicPointDynamic.h"
#include <iostream>
using namespace std;

GraphicPointDynamic::GraphicPointDynamic( GeometryPointDynamic * dynamicObject, Evas_Object * glview ) : GraphicPoint( dynamicObject, glview )
{
	m_DynamicPoint = dynamicObject;
}

GraphicPointDynamic::~GraphicPointDynamic()
{
}

void GraphicPointDynamic::draw()
{
	m_DynamicPoint->update();

	GraphicPoint::draw();
}
























