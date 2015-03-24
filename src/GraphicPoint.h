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

class GraphicPoint : public GraphicObjectBase
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

	virtual void draw( Evas * canvas );
private:
	Point m_Point;

//	GLint m_offset_x_idx;
//	GLint m_offset_y_idx;
//	GLint m_scale_idx;
	GLint m_perspective_idx;

	void initCircleVertex();
	void initQuadVertex();
	int initShaders();

	void draw_circle_2d();
};

#endif /* GRAPHICPOINT_H_ */
