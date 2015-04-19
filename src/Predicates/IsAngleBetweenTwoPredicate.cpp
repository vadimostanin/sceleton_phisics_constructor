/*
 * AngleBetweenTwo.cpp
 *
 *  Created on: 19 апр. 2015
 *      Author: vadim
 */

#include "IsAngleBetweenTwoPredicate.h"
#include <cmath>
using namespace std;

IsAngleBetweenTwoPredicate::IsAngleBetweenTwoPredicate( int angle1, int angle2, bool isShortAngle, int testAngle ) :
	m_Angle1( angle1 ), m_Angle2( angle2 ), m_IsShortAngle( isShortAngle ), m_TestAngle( testAngle )
{
}

IsAngleBetweenTwoPredicate::~IsAngleBetweenTwoPredicate()
{
}

bool IsAngleBetweenTwoPredicate::operator ()()
{
	int diffAngles = abs( m_Angle1 - m_Angle2 );

	if( true == m_IsShortAngle )
	{
		if( diffAngles > 180 )
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		if( diffAngles > 180 )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}










