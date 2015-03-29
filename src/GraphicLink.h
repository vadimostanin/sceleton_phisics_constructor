/*
 * GraphicLink.h
 *
 *  Created on: Mar 17, 2015
 *      Author: vostanin
 */

#ifndef GRAPHICLINK_H_
#define GRAPHICLINK_H_

#include <Evas.h>
#include "GeometryPoint.h"
#include "GeometryLink.h"
#include "GraphicObjectBase.h"

class GraphicLink : public GraphicObjectBase, public IGraphicObject
{
public:
	GraphicLink( IGeometryObject * geometryObject, Evas_Object * glview );
	GraphicLink( const GraphicLink & src );
	GraphicLink( const GeometryLink & src );
	virtual ~GraphicLink();

	void draw( Evas * canvas );
	IGeometryObject & getGeometryObject();

	GraphicLink & operator = ( const GeometryLink & src );

	string getVertexShader();
	string getFragmentShader();

private:

	GeometryLink m_geometryLink;

	void initLineVertexes();
	void draw_line_2d();
};

#endif /* GRAPHICLINK_H_ */
