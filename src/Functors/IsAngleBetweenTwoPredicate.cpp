/*
 * AngleBetweenTwo.cpp
 *
 *  Created on: 19 апр. 2015
 *      Author: vadim
 */

#include "IsAngleBetweenTwoPredicate.h"
#include <cmath>
#include <algorithm>
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
	int minAngle = min( m_Angle1, m_Angle2 );
	int maxAngle = max( m_Angle1, m_Angle2 );

	bool between = m_TestAngle >= minAngle && m_TestAngle <= maxAngle ;

	bool result = false;

	if( abs( m_Angle1 - m_Angle2 ) > 180 )//long
	{
		if( true == between )
		{
			if( true == m_IsShortAngle )
			{
				result = false;
			}
			else
			{
				result = true;
			}
		}
	}
	else//short
	{
		if( true == between )
		{
			if( true == m_IsShortAngle )
			{
				result = true;
			}
			else
			{
				result = false;
			}
		}
	}

	return result;
}










