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
#include "GeometryLink.h"
#include "GraphicObjectBase.h"

class GraphicLink : public GraphicObjectBase
{
public:
	GraphicLink( Evas_Object * glview );
	GraphicLink( const GraphicLink & src );
//	GraphicLink( const GeometryLink src );
	virtual ~GraphicLink();

	Evas_Object * getEvas() const;

	void setEvas( Evas_Object * evas );

	virtual void draw( Evas * canvas );

	void setPointFrom( Point & point );
	void setPointTo( Point & point );

	Point & getPointFrom();
	Point & getPointTo();

	GraphicLink & operator = ( GeometryLink & src );

private:

	GLint m_perspective_idx;
	GLint m_translate_idx;
	GLint m_scale_idx;

	void initLineVertexes();
	int initShaders();
	void draw_line_2d();

	Point m_Points[2];
};

#endif /* GRAPHICLINK_H_ */
