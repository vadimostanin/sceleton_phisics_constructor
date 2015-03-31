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

class GraphicSpring: public GraphicObjectBase, public IGraphicObject {
public:
	GraphicSpring( IGeometryObject * geometryObject, Evas_Object * canvas );
	GraphicSpring( const GraphicSpring & src );
	virtual ~GraphicSpring();

	void draw( Evas * canvas );
	IGeometryObject & getGeometryObject();

	string getVertexShader();
	string getFragmentShader();

private:

	void initLineVertexes();
	void draw_line_2d();

	GeometrySpring m_geometrySpring;
	unsigned int m_springRotateAngle;
};

#endif /* GRAPHICSPRING_H_ */
