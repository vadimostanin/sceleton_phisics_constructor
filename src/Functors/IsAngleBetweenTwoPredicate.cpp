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
	m_Angle1( angle1 ), m_Angle2( angle2 ), m_IsShortAngle( isShortAngle ), m_TestAngle( testAngle ),
	m_MinAngle( 0 ), m_MaxAngle( 0 ), m_Result( false )
{
	bool leftResult = calcLeftSide();
	bool rightResult = calcRightSide();

	m_Result = leftResult || rightResult;
}

IsAngleBetweenTwoPredicate::~IsAngleBetweenTwoPredicate()
{
}

bool IsAngleBetweenTwoPredicate::calcLeftSide()
{
	int minAngle = min( m_Angle1, m_Angle2 );
	int maxAngle = max( m_Angle1, m_Angle2 );

	bool between = m_TestAngle >= minAngle && m_TestAngle <= maxAngle ;

	bool result = false;

	// left side calculating
	int angle1 = m_Angle1;
	int angle2 = m_Angle2;
	{
		if( abs( angle1 - angle2 ) > 180 )//long
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
	}

	return result;
}

bool IsAngleBetweenTwoPredicate::calcRightSide()
{
	int tempMinAngle = min( m_Angle1, m_Angle2 );
	int tempMaxAngle = max( m_Angle1, m_Angle2 ) - 360;

	int minAngle = min( tempMinAngle, tempMaxAngle );
	int maxAngle = max( tempMinAngle, tempMaxAngle );

	bool between = m_TestAngle >= minAngle && m_TestAngle <= maxAngle ;

	bool result = false;

	int angle1 = minAngle;
	int angle2 = maxAngle;
	{
		if( abs( angle1 - angle2 ) > 180 )//long
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
	}

	return result;
}

bool IsAngleBetweenTwoPredicate::operator ()()
{
	return m_Result;
}

int IsAngleBetweenTwoPredicate::getMinAngle() const
{
	return m_MinAngle;
}

int IsAngleBetweenTwoPredicate::getMaxAngle() const
{
	return m_MaxAngle;
}










