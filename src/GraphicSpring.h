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

private:
	GeometrySpring m_geometrySpring;
};

#endif /* GRAPHICSPRING_H_ */
