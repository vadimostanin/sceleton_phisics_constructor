/*
 * GraphicPointLink.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: vostanin
 */

#include "GraphicPointLink.h"
#include <iostream>
using namespace std;

GraphicPointLink::GraphicPointLink() : m_Evas( 0 )
{

}

GraphicPointLink::GraphicPointLink( const GraphicPointLink & src )
{
	setEvas( src.getEvas() );
}

GraphicPointLink::~GraphicPointLink()
{
}

void GraphicPointLink::draw( Evas * canvas )
{
	cout << "draw GraphicPointLink" << endl << flush;
}

Evas_Object * GraphicPointLink::getEvas() const
{
	return m_Evas;
}

void GraphicPointLink::setEvas( Evas_Object * evas )
{
	m_Evas = evas;
}

void GraphicPointLink::setPointFrom( Point & point )
{
	m_Points[0] = point;
}

void GraphicPointLink::setPointTo( Point & point )
{
	m_Points[1] = point;
}








