/*
 * GeometryLinkGetAbsoluteAnglePredicate.cpp
 *
 *  Created on: 17 апр. 2015
 *      Author: vadim
 */

#include "GeometryLinkGetAbsoluteAnglePredicate.h"
#include <cmath>

GeometryLinkGetAbsoluteAnglePredicate::GeometryLinkGetAbsoluteAnglePredicate( const GeometryLink * link ) :
	m_linkX1( link->getPointFrom()->getX() ), m_linkY1( link->getPointFrom()->getY() ),
	m_linkX2( link->getPointTo()->getX() ),   m_linkY2( link->getPointTo()->getY() )
{
}

GeometryLinkGetAbsoluteAnglePredicate::GeometryLinkGetAbsoluteAnglePredicate( int linkX1, int linkY1, int linkX2, int linkY2 ) :
	m_linkX1( linkX1 ), m_linkY1( linkY1 ),
	m_linkX2( linkX2 ), m_linkY2( linkY2 )
{

}

GeometryLinkGetAbsoluteAnglePredicate::~GeometryLinkGetAbsoluteAnglePredicate()
{
}

int GeometryLinkGetAbsoluteAnglePredicate::operator()()
{
	int linkfrom_pointfrom_x = -m_linkX1;
	int linkfrom_pointto_x = -m_linkX2;

	int linkfrom_pointfrom_y = m_linkY1;
	int linkfrom_pointto_y = m_linkY2;

	int linkfrom_vector_x = linkfrom_pointfrom_x - linkfrom_pointto_x;
	int linkfrom_vector_y = linkfrom_pointfrom_y - linkfrom_pointto_y;

	int tempLinkVertical_vector_x = 0;
	int tempLinkVertical_vector_y = 10;

	int tempLinkHorizantal_vector_x = 10;
	int tempLinkHorizantal_vector_y = 0;

	float cosRelativeVerticalVector = ( linkfrom_vector_x * tempLinkVertical_vector_x + linkfrom_vector_y * tempLinkVertical_vector_y )
			/
		 ( sqrt( linkfrom_vector_x * linkfrom_vector_x + linkfrom_vector_y * linkfrom_vector_y ) *
		   sqrt( tempLinkVertical_vector_x * tempLinkVertical_vector_x + tempLinkVertical_vector_y * tempLinkVertical_vector_y )
		 );

	float cosRelativeHorizontalVector = ( linkfrom_vector_x * tempLinkHorizantal_vector_x + linkfrom_vector_y * tempLinkHorizantal_vector_y )
			/
		 ( sqrt( linkfrom_vector_x * linkfrom_vector_x + linkfrom_vector_y * linkfrom_vector_y ) *
		   sqrt( tempLinkHorizantal_vector_x * tempLinkHorizantal_vector_x + tempLinkHorizantal_vector_y * tempLinkHorizantal_vector_y )
		 );

	float angleCosRelativeVerticalVector = acosf( cosRelativeVerticalVector );
	float angleCosRelativeHorizontalVector = acosf( cosRelativeHorizontalVector );

	float angleCosRelativeVerticalVectorInt = angleCosRelativeVerticalVector / M_PI * 180;
	float angleCosRelativeHorizontalVectorInt = angleCosRelativeHorizontalVector / M_PI * 180;

	int angleResultInt = 0;
	if( angleCosRelativeVerticalVectorInt <= 90 )//first and second quarter
	{
		angleResultInt = angleCosRelativeHorizontalVectorInt;
	}
	else//third and fourth quarter
	{
		angleResultInt = 360 - angleCosRelativeHorizontalVectorInt;
	}

	return angleResultInt;
}










