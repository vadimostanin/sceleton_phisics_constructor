/*
 * GraphicLinkDynamic.h
 *
 *  Created on: Apr 3, 2015
 *      Author: vostanin
 */

#ifndef GRAPHICSPRINGDYNAMIC_H_
#define GRAPHICSPRINGDYNAMIC_H_

#include "GraphicSpring.h"
#include "GeometrySpringDynamic.h"

class GraphicSpringDynamic: public GraphicSpring
{
public:
	GraphicSpringDynamic( GeometrySpringDynamic * dynamicObject, Evas_Object * glview );
	virtual ~GraphicSpringDynamic();

	void draw();

private:

	GeometrySpringDynamic * m_DynamicSpring;
};

#endif /* GRAPHICSPRINGDYNAMIC_H_ */
