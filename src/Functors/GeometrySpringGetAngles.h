/*
 * GeometrySpringGetAngles.h
 *
 *  Created on: 22 апр. 2015
 *      Author: vadim
 */

#ifndef FUNCTORS_GEOMETRYSPRINGGETANGLES_H_
#define FUNCTORS_GEOMETRYSPRINGGETANGLES_H_

#include "GeometrySpring.h"

class GeometrySpringGetAngles
{
public:
	GeometrySpringGetAngles( const GeometrySpring * geometrySpring );
	virtual ~GeometrySpringGetAngles();

	bool getIsValid() const;

	int getLinkFromAngle() const;
	int getLinkToAngle() const;

	const GeometryPoint * getLinkFromAdjacentPoint() const;
	const GeometryPoint * getLinkToAdjacentPoint() const;

	const GeometryPoint * getCrospoint() const;

private:

	const GeometrySpring * m_GeometrySpring;

	const GeometryPoint * m_CrossPoint;

};

#endif /* FUNCTORS_GEOMETRYSPRINGGETANGLES_H_ */
