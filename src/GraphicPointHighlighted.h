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
	GraphicPointHighlighted();
	virtual ~GraphicPointHighlighted();
	GraphicPointHighlighted( int x, int y );
	GraphicPointHighlighted( const Point & point );
	GraphicPointHighlighted( const GraphicPoint & src );
	virtual void draw( Evas * canvas );
};

#endif /* GRAPHICPOINTHIGHLIGHTED_H_ */
