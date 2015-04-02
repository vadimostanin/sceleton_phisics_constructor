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
	GraphicPointDynamic( IGeometryObject * geometryObject, Evas_Object * glview );
	virtual ~GraphicPointDynamic();

	void draw( Evas * canvas );

private:

	GeometryPointDynamic m_DynamicPoint;

};

#endif /* GRAPHICPOINTDYNAMIC_H_ */
