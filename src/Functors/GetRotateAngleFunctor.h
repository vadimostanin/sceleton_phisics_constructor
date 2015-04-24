/*
 * GetRotateAngleFunctor.h
 *
 *  Created on: 24 апр. 2015
 *      Author: vadim
 */

#ifndef FUNCTORS_GETROTATEANGLEFUNCTOR_H_
#define FUNCTORS_GETROTATEANGLEFUNCTOR_H_

#include "GeometrySpring.h"

class GetRotateAngleFunctor
{
public:
	GetRotateAngleFunctor( const GeometrySpring * geometrySpring );
	virtual ~GetRotateAngleFunctor();

	int getAngle() const;

private:

	void calcAngle();

	const GeometrySpring * m_GeometrySpring;

	int m_AngleFrom;
	int m_AngleTo;

	int m_RotateAngle;

};

#endif /* FUNCTORS_GETROTATEANGLEFUNCTOR_H_ */
