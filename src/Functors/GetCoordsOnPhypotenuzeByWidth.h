/*
 * GetCoordsOnPhypotenuzeByWidth.h
 *
 *  Created on: 25 апр. 2015
 *      Author: vadim
 */

#ifndef FUNCTORS_GETCOORDSONPHYPOTENUZEBYWIDTH_H_
#define FUNCTORS_GETCOORDSONPHYPOTENUZEBYWIDTH_H_

#include "GeometryPoint.h"

class GetCoordsOnPhypotenuzeByWidth
{
public:
	GetCoordsOnPhypotenuzeByWidth( const GeometryPoint * pointStart, const GeometryPoint * pointEnd, int offset );
	virtual ~GetCoordsOnPhypotenuzeByWidth();

	int getX() const;
	int getY() const;

private:

	void calc();

	const GeometryPoint * m_PointStart;
	const GeometryPoint * m_PointEnd;
	int m_Offset;

	int m_X;
	int m_Y;

};

#endif /* FUNCTORS_GETCOORDSONPHYPOTENUZEBYWIDTH_H_ */
