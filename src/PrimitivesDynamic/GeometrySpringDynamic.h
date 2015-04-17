/*
 * GeometrySpringDynamic.h
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#ifndef GEOMETRYSPRINGDYNAMIC_H_
#define GEOMETRYSPRINGDYNAMIC_H_

#include "GeometrySpring.h"
#include "GeometryLinkDynamic.h"
#include "IDynamicObject.h"
#include <chipmunk/chipmunk.h>

class GeometrySpringDynamic: public GeometrySpring, public IDynamicObject
{
public:
	GeometrySpringDynamic( cpSpace * space, GeometrySpring * geometrySpring );
	virtual ~GeometrySpringDynamic();

	void setDynamicLinkFrom( GeometryLinkDynamic * dynamicLink );
	void setDynamicLinkTo( GeometryLinkDynamic * dynamicLink );

	const GeometryLinkDynamic * getDynamicLinkFrom() const;
	const GeometryLinkDynamic * getDynamicLinkTo() const;

	const IGeometryObject & getGeometryObject() const;

	void update();

private:

	void initSpring();
	void initJoints();
	void clearJoints();

	cpSpace * m_Space;
	cpBody  * m_Body;
	cpShape * m_Shape;

	cpConstraint * m_ConstraintGear;


	GeometryLinkDynamic * m_DynamicLinks[2];
};

#endif /* GEOMETRYSPRINGDYNAMIC_H_ */
