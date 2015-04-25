/*
 * GraphicSpring.h
 *
 *  Created on: Mar 27, 2015
 *      Author: vostanin
 */

#ifndef GRAPHICSPRING_H_
#define GRAPHICSPRING_H_

#include "GraphicObjectBase.h"
#include "IGraphicObject.h"
#include "GeometrySpring.h"

class GraphicSpring: public GraphicObjectBase, public IGraphicObject
{
public:

	GraphicSpring( IGeometryObject * geometryObject, Evas_Object * canvas );
	GraphicSpring( const GraphicSpring & src );
	virtual ~GraphicSpring();

	void draw();
	IGeometryObject & getGeometryObject();

	string getVertexShader();
	string getFragmentShader();

private:

	vector<int> m_vertexCircleLinkFrom;

	void initLineVertexes();
	void initCircleVertexes();
	void initPartialCircleVertex();
	void initCompleteCircleVertex();
	void initCircleAtLinks( int x0, int y0, int radius );
	void draw_line_2d();

	GeometrySpring * m_geometrySpring;
	unsigned int m_springRotateAngle;

};

#endif /* GRAPHICSPRING_H_ */
