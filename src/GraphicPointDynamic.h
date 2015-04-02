/*
 * GraphicPointDynamic.h
 *
 *  Created on: Apr 2, 2015
 *      Author: vostanin
 */

#ifndef GRAPHICPOINTDYNAMIC_H_
#define GRAPHICPOINTDYNAMIC_H_

#include "GraphicPoint.h"
#include "GeometryPointDynamic.h"

class GraphicPointDynamic: public GraphicPoint
{
public:
	GraphicPointDynamic( GeometryPointDynamic * dynamicObject, Evas_Object * glview );
	virtual ~GraphicPointDynamic();

	void draw();

private:

	GeometryPointDynamic * m_DynamicPoint;

};

#endif /* GRAPHICPOINTDYNAMIC_H_ */
