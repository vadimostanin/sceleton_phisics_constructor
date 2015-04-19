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
	int testAngleOffset = m_TestAngle - diffAngles;
	int angle1Offset = m_Angle1 - diffAngles;
	int angle2Offset = m_Angle2 - diffAngles;

	int sumAnglesOffset = angle1Offset + angle2Offset;

	bool between = testAngleOffset > 0 && testAngleOffset <= sumAnglesOffset;

	bool result = false;

	if( sumAnglesOffset > 180 )//long
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










