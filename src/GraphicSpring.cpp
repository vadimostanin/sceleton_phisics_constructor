/*
 * GraphicSpring.cpp
 *
 *  Created on: Mar 27, 2015
 *      Author: vostanin
 */

#include "GraphicSpring.h"
#include <iostream>
using namespace std;

GraphicSpring::GraphicSpring( IGeometryObject * geometryObject, Evas_Object * canvas )
{
	m_geometrySpring = *geometryObject;
}

GraphicSpring::GraphicSpring( const GraphicSpring & src )
{
	m_geometrySpring = src.m_geometrySpring;
}

GraphicSpring::~GraphicSpring()
{
}

void GraphicSpring::draw( Evas * canvas )
{
//	cout << "draw spring from:" << getPointFrom().getX() << "x" << getPointFrom().getY() << "; to:" <<
//						getPointTo().getX() << "x" << getPointTo().getY() << endl << flush;
	cout << "draw spring id=" << m_geometrySpring.getId() << endl << flush;
}

IGeometryObject & GraphicSpring::getGeometryObject()
{
	return m_geometrySpring;
}

















