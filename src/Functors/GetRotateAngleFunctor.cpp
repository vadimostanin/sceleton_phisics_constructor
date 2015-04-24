/*
 * GetRotateAngleFunctor.cpp
 *
 *  Created on: 24 апр. 2015
 *      Author: vadim
 */

#include "GetRotateAngleFunctor.h"
#include "GeometrySpringGetAngles.h"

GetRotateAngleFunctor::GetRotateAngleFunctor( const GeometrySpring * geometrySpring ) :
	m_GeometrySpring( geometrySpring ), m_RotateAngle( 0 )
{
	GeometrySpringGetAngles getAngles( m_GeometrySpring );
	m_AngleFrom = getAngles.getLinkFromAngle();
	m_AngleTo   = getAngles.getLinkToAngle();

	m_RotateAngle = abs( m_AngleFrom ) - abs( m_AngleTo );
}

GetRotateAngleFunctor::~GetRotateAngleFunctor()
{
}

void GetRotateAngleFunctor::calcAngle()
{

}

int GetRotateAngleFunctor::getAngle() const
{
	return m_RotateAngle;
}















