/*
 * GeometryLinksAngleGetPredicate.cpp
 *
 *  Created on: 17 апр. 2015
 *      Author: vadim
 */

#include "GeometryLinksAngleGetPredicate.h"
#include <cmath>

GeometryLinksAngleGetPredicate::GeometryLinksAngleGetPredicate( const GeometryLink * link1, const GeometryLink * link2 ) :
	m_Link1( link1 ), m_Link2( link2 )
{
}

GeometryLinksAngleGetPredicate::~GeometryLinksAngleGetPredicate()
{
}

float GeometryLinksAngleGetPredicate::operator()()
{
	int linkfrom_pointfrom_x = m_Link1->getPointFrom()->getX();
	int linkfrom_pointto_x = m_Link1->getPointTo()->getX();

	int linkfrom_pointfrom_y = m_Link1->getPointFrom()->getY();
	int linkfrom_pointto_y = m_Link1->getPointTo()->getY();

	int linkto_pointfrom_x = m_Link2->getPointFrom()->getX();
	int linkto_pointto_x = m_Link2->getPointTo()->getX();

	int linkto_pointfrom_y = m_Link2->getPointFrom()->getY();
	int linkto_pointto_y = m_Link2->getPointTo()->getY();

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










