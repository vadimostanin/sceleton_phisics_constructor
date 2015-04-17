/*
 * GeometrySpring.h
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#ifndef GEOMETRYSPRING_H_
#define GEOMETRYSPRING_H_

#include "IGeometryObject.h"
#include "GeometryLink.h"

class GeometrySpring : public IGeometryObject
{
public:
	GeometrySpring();
	GeometrySpring( const GeometryLink * linkFrom, const GeometryLink * linkTo );
	GeometrySpring( const GeometrySpring & src );
	bool operator == ( const GeometrySpring & src ) const;
	bool operator != ( const GeometrySpring & src ) const;
	GeometrySpring & operator = ( const GeometrySpring & src );
	virtual ~GeometrySpring();

	const GeometryLink * getLinkFrom() 	const;
	const GeometryLink * getLinkTo() 	const;

	void setLinkFrom( const GeometryLink * linkFrom );
	void setLinkTo( const GeometryLink * linkTo );

	void setIsForward( bool isForward );
	bool getIsForward() const;

	GeometryObjectsTypes getType() const;
	GeometryObjectsConstructiongStates getConstructingState();
	int getId() const;
	void setId( int id );
	IGeometryObject * clone();
	string toString();
	IGeometryObject & operator = ( IGeometryObject & src );
	bool isValid();

private:

	const GeometryLink * m_geometryLinks[2];

	int m_Id;

	bool m_IsForward;
};

#endif /* GEOMETRYSPRING_H_ */
