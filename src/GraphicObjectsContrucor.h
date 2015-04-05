/*
 * GraphicObjectsContrucor.h
 *
 *  Created on: 5 апр. 2015
 *      Author: vadim
 */

#ifndef GRAPHICOBJECTSCONTRUCOR_H_
#define GRAPHICOBJECTSCONTRUCOR_H_

#include "IGeometryObject.h"
#include "IDynamicObject.h"
#include "IGraphicObject.h"
#include <vector>

class GraphicObjectsContrucor
{
public:
	GraphicObjectsContrucor();
	GraphicObjectsContrucor( Evas_Object * canvas );
	virtual ~GraphicObjectsContrucor();

	void convert( vector<IGeometryObject *> & geometryObjects, vector<IGraphicObject *> & dynamicObjects );
	void convert( vector<IDynamicObject *> & geometryObjects, vector<IGraphicObject *> & dynamicObjects );

	void setCanvas( Evas_Object * canvas );

	static GraphicObjectsContrucor & getInstance();

private:

	 Evas_Object * m_Canvas;
};

#endif /* GRAPHICOBJECTSCONTRUCOR_H_ */
