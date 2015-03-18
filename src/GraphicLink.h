/*
 * GraphicLink.h
 *
 *  Created on: Mar 17, 2015
 *      Author: vostanin
 */

#ifndef GRAPHICLINK_H_
#define GRAPHICLINK_H_

#include <Evas.h>
#include "Point.h"
#include "PointsLink.h"
#include "IGraphicObject.h"

class GraphicLink : public IGraphicObject
{
public:
	GraphicLink();
	GraphicLink( const GraphicLink & src );
//	GraphicLink( const PointsLink src );
	virtual ~GraphicLink();

	Evas_Object * getEvas() const;

	void setEvas( Evas_Object * evas );

	virtual void draw( Evas * canvas );

	void setPointFrom( Point & point );
	void setPointTo( Point & point );

	Point & getPointFrom();
	Point & getPointTo();

	GraphicLink & operator = ( PointsLink & src );

private:
	Point m_Points[2];
	Evas_Object * m_Evas;
};

#endif /* GRAPHICLINK_H_ */
