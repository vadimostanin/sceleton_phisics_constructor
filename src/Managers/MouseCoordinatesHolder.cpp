/*
 * MouseCoordinatesHolder.cpp
 *
 *  Created on: 17 апр. 2015
 *      Author: vadim
 */

#include <MouseCoordinatesHolder.h>

MouseCoordinatesHolder::MouseCoordinatesHolder()
{
}

MouseCoordinatesHolder::~MouseCoordinatesHolder()
{
}

void MouseCoordinatesHolder::setX( int x)
{
	m_X = x;
}

void MouseCoordinatesHolder::setY( int y )
{
	m_Y = y;
}

int MouseCoordinatesHolder::getX() const
{
	return m_X;
}

int MouseCoordinatesHolder::getY() const
{
	return m_Y;
}

MouseCoordinatesHolder & MouseCoordinatesHolder::getInstance()
{
	static MouseCoordinatesHolder instance;
	return instance;
}










