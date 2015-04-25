/*
 * GetCoordsOnPhypotenuzeByWidth.cpp
 *
 *  Created on: 25 апр. 2015
 *      Author: vadim
 */

#include "GetCoordsOnPhypotenuzeByWidth.h"
#include <cmath>

GetCoordsOnPhypotenuzeByWidth::GetCoordsOnPhypotenuzeByWidth( const GeometryPoint * pointStart, const GeometryPoint * pointEnd, int offset ) :
	m_PointStart( pointStart ), m_PointEnd( pointEnd ), m_Offset( offset )
{
	calc();
}

GetCoordsOnPhypotenuzeByWidth::~GetCoordsOnPhypotenuzeByWidth()
{
}

void GetCoordsOnPhypotenuzeByWidth::calc()
{
	int katet_x = m_PointStart->getX() - m_PointEnd->getX();
	int katet_y = m_PointStart->getY() - m_PointEnd->getY();
	int phypotenuze = sqrt( katet_x * katet_x + katet_y * katet_y );

	float part = (float)m_Offset / (float)phypotenuze;

	m_X = m_PointStart->getX() - (float)katet_x * part;
	m_Y = m_PointStart->getY() - (float)katet_y * part;
}

int GetCoordsOnPhypotenuzeByWidth::getX() const
{
	return m_X;
}

int GetCoordsOnPhypotenuzeByWidth::getY() const
{
	return m_Y;
}














