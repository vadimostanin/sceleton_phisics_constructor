/*
 * GraphicPointHighlighted.h
 *
 *  Created on: Mar 17, 2015
 *      Author: vostanin
 */

#ifndef GRAPHICPOINTHIGHLIGHTED_H_
#define GRAPHICPOINTHIGHLIGHTED_H_

#include "GraphicPoint.h"

class GraphicPointHighlighted : public GraphicPoint
{
public:
	GraphicPointHighlighted( IGeometryObject * geometryObject, Evas_Object * canvas );
	virtual ~GraphicPointHighlighted();
	GraphicPointHighlighted( IGeometryObject * geometryObject, Evas_Object * canvas, int x, int y );
	GraphicPointHighlighted( Evas_Object * canvas, const Point & point );
	GraphicPointHighlighted( const GraphicPoint & src );
	virtual void draw( Evas * canvas );
};

#endif /* GRAPHICPOINTHIGHLIGHTED_H_ */
