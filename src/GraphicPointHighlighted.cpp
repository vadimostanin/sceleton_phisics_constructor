/*
 * GraphicPointHighlighted.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: vostanin
 */

#include "GraphicPointHighlighted.h"

GraphicPointHighlighted::GraphicPointHighlighted( IGeometryObject * geometryObject, Evas_Object * canvas ) : GraphicPoint( geometryObject, canvas )
{
}

GraphicPointHighlighted::~GraphicPointHighlighted()
{
}

GraphicPointHighlighted::GraphicPointHighlighted( IGeometryObject * geometryObject, Evas_Object * canvas, int x, int y ) : GraphicPoint( geometryObject, canvas )
{
	;
}

GraphicPointHighlighted::GraphicPointHighlighted( Evas_Object * canvas, const GeometryPoint & point) : GraphicPoint( canvas, point )
{
	;
}

GraphicPointHighlighted::GraphicPointHighlighted( const GraphicPoint & src ) : GraphicPoint( src )
{
	;
}

void GraphicPointHighlighted::draw( Evas * canvas )
{
	;
}










