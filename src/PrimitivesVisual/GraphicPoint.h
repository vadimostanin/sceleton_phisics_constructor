/*
 * GraphicsPoint.h
 *
 *  Created on: Mar 17, 2015
 *      Author: vostanin
 */

#ifndef GRAPHICPOINT_H_
#define GRAPHICPOINT_H_

#include <Evas.h>
#include "GeometryPoint.h"
#include "GraphicObjectBase.h"
#include <Evas_GL.h>
#include <vector>
using namespace std;

class GraphicPoint : public GraphicObjectBase, public IGraphicObject
{
public:
	GraphicPoint( IGeometryObject * geometryObject, Evas_Object * glview );
	GraphicPoint( Evas_Object * glview, int x, int y );
	GraphicPoint( Evas_Object * glview, GeometryPoint * point );
	GraphicPoint( const GraphicPoint & src );
	virtual ~GraphicPoint();
	bool operator ==( const GraphicPoint & src );
	int getX();
	int getY();
	void setX( int x );
	void setY( int y );

	virtual void draw();
	IGeometryObject & getGeometryObject();

	virtual string getVertexShader();
	virtual string getFragmentShader();

private:
	GeometryPoint * m_Point;

	void initCircleVertex();
	void initQuadVertex();
	void initVertex();

	void draw_circle_2d();
};

#endif /* GRAPHICPOINT_H_ */
