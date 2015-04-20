/*
 * GeometryLinksAngleGetPredicate.cpp
 *
 *  Created on: 17 апр. 2015
 *      Author: vadim
 */

#include "GeometryLinksAngleGetPredicate.h"
#include <cmath>

GeometryLinksAngleGetPredicate::GeometryLinksAngleGetPredicate( const GeometryLink * link1, const GeometryLink * link2 ) :
	m_link1X1( link1->getPointFrom()->getX() ), m_link1Y1( link1->getPointFrom()->getY() ),
	m_link1X2( link1->getPointTo()->getX() ), 	m_link1Y2( link1->getPointTo()->getY() ),
	m_link2X1( link2->getPointFrom()->getX() ), m_link2Y1( link2->getPointFrom()->getY() ),
	m_link2X2( link2->getPointTo()->getX() ), 	m_link2Y2( link2->getPointTo()->getY() )
{
}

GeometryLinksAngleGetPredicate::GeometryLinksAngleGetPredicate( int link1X1, int link1Y1, int link1X2, int link1Y2, int link2X1, int link2Y1, int link2X2, int link2Y2 ) :
	m_link1X1( link1X1 ), m_link1Y1( link1Y1 ),
	m_link1X2( link1X2 ), m_link1Y2( link1Y2 ),
	m_link2X1( link2X1 ), m_link2Y1( link2Y1 ),
	m_link2X2( link2X2 ), m_link2Y2( link2Y2 )
{

}

GeometryLinksAngleGetPredicate::~GeometryLinksAngleGetPredicate()
{
}

float GeometryLinksAngleGetPredicate::operator()()
{
	int linkfrom_pointfrom_x = m_link1X1;
	int linkfrom_pointto_x = m_link1X2;

	int linkfrom_pointfrom_y = m_link1Y1;
	int linkfrom_pointto_y = m_link1Y2;

	int linkto_pointfrom_x = m_link2X1;
	int linkto_pointto_x = m_link2X2;

	int linkto_pointfrom_y = m_link2Y1;
	int linkto_pointto_y = m_link2Y2;

	int linkfrom_vector_x = linkfrom_pointfrom_x - linkfrom_pointto_x;
	int linkfrom_vector_y = linkfrom_pointfrom_y - linkfrom_pointto_y;

	int linkto_vector_x = linkto_pointfrom_x - linkto_pointto_x;
	int linkto_vector_y = linkto_pointfrom_y - linkto_pointto_y;

	float cos = ( linkfrom_vector_x * linkto_vector_x + linkfrom_vector_y * linkto_vector_y )
			/
		 ( sqrt( linkfrom_vector_x * linkfrom_vector_x + linkfrom_vector_y * linkfrom_vector_y ) *
		   sqrt( linkto_vector_x * linkto_vector_x + linkto_vector_y * linkto_vector_y )
		 );

	float angle_from_cos = acosf( cos );

	return angle_from_cos;
}










