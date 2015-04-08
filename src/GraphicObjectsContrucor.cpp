/*
 * GraphicObjectsContrucor.cpp
 *
 *  Created on: 5 ������. 2015
 *      Author: vadim
 */

#include "GraphicObjectsContrucor.h"
#include "DynamicObjectFactory.h"
#include "GeometryObjectFactory.h"

GraphicObjectsContrucor::GraphicObjectsContrucor() : m_Canvas( 0 )
{
}

GraphicObjectsContrucor::GraphicObjectsContrucor( Evas_Object * canvas ) : m_Canvas( canvas )
{
}

GraphicObjectsContrucor::~GraphicObjectsContrucor()
{
}

void GraphicObjectsContrucor::convert( vector<IGeometryObject *> & geometryObjects, vector<IGraphicObject *> & graphicObjects )
{
	vector<IGeometryObject *>::iterator begin = geometryObjects.begin();
	vector<IGeometryObject *>::iterator end = geometryObjects.end();
	vector<IGeometryObject *>::iterator iter = begin;
	for(  ; iter != end ; iter ++ )
	{
		IGraphicObject * graphicObject = GeometryObjectFactory::getInstance().createGraphicObject( (* iter), m_Canvas );

		graphicObjects.push_back( graphicObject );
	}
}

void GraphicObjectsContrucor::convert( vector<IDynamicObject *> & geometryObjects, vector<IGraphicObject *> & graphicObjects )
{
	vector<IDynamicObject *>::iterator begin = geometryObjects.begin();
	vector<IDynamicObject *>::iterator end = geometryObjects.end();
	vector<IDynamicObject *>::iterator iter = begin;
	for(  ; iter != end ; iter ++ )
	{
		IGraphicObject * graphicObject = DynamicObjectFactory::getInstance().createGraphicObject( (* iter), m_Canvas );
		if( 0 == graphicObject )
		{
			continue;
		}

		graphicObjects.push_back( graphicObject );
	}
}

void GraphicObjectsContrucor::setCanvas( Evas_Object * canvas )
{
	m_Canvas = canvas;
}

GraphicObjectsContrucor & GraphicObjectsContrucor::getInstance()
{
	static GraphicObjectsContrucor instance;
	return instance;
}














