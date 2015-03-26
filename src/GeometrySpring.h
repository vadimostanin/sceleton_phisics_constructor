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
	GeometrySpring( const GeometrySpring & src );
	bool operator == ( const GeometrySpring & src ) const;
	bool operator != ( const GeometrySpring & src ) const;
	GeometrySpring & operator = ( const GeometrySpring & src );
	virtual ~GeometrySpring();

	const GeometryLink & getLinkFrom() 	const;
	const GeometryLink & getLinkTo() 	const;
	const int 		     getLength() 	const;

	void setLinkFrom( GeometryLink & linkFrom );
	void setLinkTo( GeometryLink & linkTo );
	void setLength( int length );

	GeometryObjectsTypes getType() const;
	int getId() const;
	void setId( int id );
	IGeometryObject * clone();
	string toString();
	IGeometryObject & operator = ( IGeometryObject & src );

private:

	GeometryLink m_geometryLinks[2];

	int m_Id;

	int m_Length;

};

#endif /* GEOMETRYSPRING_H_ */
