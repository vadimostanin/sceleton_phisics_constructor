/*
 * GraphicsPoint.h
 *
 *  Created on: Mar 17, 2015
 *      Author: vostanin
 */

#ifndef GRAPHICPOINT_H_
#define GRAPHICPOINT_H_

#include <Evas.h>
#include "Point.h"
#include "IGraphicObject.h"

class GraphicPoint : public IGraphicObject
{
public:
	GraphicPoint();
	GraphicPoint( int x, int y );
	GraphicPoint( const Point & point );
	GraphicPoint( const GraphicPoint & src );
	virtual ~GraphicPoint();
	bool operator ==( const GraphicPoint & src );
	int getX();
	int getY();
	void setX( int x );
	void setY( int y );

	Evas_Object * getEvas() const;

	void setEvas( Evas_Object * evas );

	virtual void draw( Evas * canvas );
private:
	Point m_Point;
	Evas_Object * m_Evas;
};

#endif /* GRAPHICPOINT_H_ */
