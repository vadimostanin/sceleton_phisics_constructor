/*
 * GraphicPointLink.h
 *
 *  Created on: Mar 17, 2015
 *      Author: vostanin
 */

#ifndef GRAPHICPOINTLINK_H_
#define GRAPHICPOINTLINK_H_

#include <Evas.h>
#include "Point.h"
#include "IGraphicObject.h"

class GraphicPointLink : public IGraphicObject
{
public:
	GraphicPointLink();
	GraphicPointLink( const GraphicPointLink & src );
	virtual ~GraphicPointLink();

	Evas_Object * getEvas() const;

	void setEvas( Evas_Object * evas );

	virtual void draw( Evas * canvas );

	void setPointFrom( Point & point );
	void setPointTo( Point & point );
private:
	Point m_Points[2];
	Evas_Object * m_Evas;
};

#endif /* GRAPHICPOINTLINK_H_ */
