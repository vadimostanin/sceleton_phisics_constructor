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

	void setIsClosedPath( int x, int y );
	bool getIsClosedPath() const;

	void setConstructingState( GeometryObjectsConstructiongStates state );

	GeometryObjectsTypes getType() const;
	GeometryObjectsConstructiongStates getConstructingState() const;
	int getId() const;
	void setId( int id );
	IGeometryObject * clone();
	string toString();
	IGeometryObject & operator = ( IGeometryObject & src );
	bool isValid();

private:

	void setIsClosedPath( bool isClosedPath );

	const GeometryLink * m_geometryLinks[2];

	int m_Id;

	bool m_IsClosedPath;

	GeometryObjectsConstructiongStates m_State;
};

#endif /* GEOMETRYSPRING_H_ */
