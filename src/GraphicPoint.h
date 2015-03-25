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
#include "GraphicObjectBase.h"
#include <Evas_GL.h>
#include <vector>
using namespace std;

class GraphicPoint : public GraphicObjectBase, public IGraphicObject
{
public:
	GraphicPoint( Evas_Object * glview );
	GraphicPoint( Evas_Object * glview, int x, int y );
	GraphicPoint( Evas_Object * glview, const Point & point );
	GraphicPoint( const GraphicPoint & src );
	virtual ~GraphicPoint();
	bool operator ==( const GraphicPoint & src );
	int getX();
	int getY();
	void setX( int x );
	void setY( int y );

	void draw( Evas * canvas );
	IGeometryObject & getGeometryObject();

private:
	Point m_Point;

	GLint m_perspective_idx;
	GLint m_translate_idx;
	GLint m_scale_idx;

	void initCircleVertex();
	void initQuadVertex();
	void initVertex();
	int initShaders();

	void draw_circle_2d();
};

#endif /* GRAPHICPOINT_H_ */
