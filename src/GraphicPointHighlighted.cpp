/*
 * GraphicPointHighlighted.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: vostanin
 */

#include "GraphicPointHighlighted.h"

GraphicPointHighlighted::GraphicPointHighlighted( Evas_Object * canvas ) : GraphicPoint( canvas )
{
}

GraphicPointHighlighted::~GraphicPointHighlighted()
{
}

GraphicPointHighlighted::GraphicPointHighlighted( Evas_Object * canvas, int x, int y ) : GraphicPoint( canvas )
{
	;
}

GraphicPointHighlighted::GraphicPointHighlighted( Evas_Object * canvas, const Point & point) : GraphicPoint( canvas, point )
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










