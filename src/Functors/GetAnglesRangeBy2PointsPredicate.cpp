/*
 * AngleBetweenTwo.cpp
 *
 *  Created on: 19 апр. 2015
 *      Author: vadim
 */

#include "GetAnglesRangeBy2PointsPredicate.h"
#include <cmath>
#include <algorithm>
#include <cassert>
using namespace std;

GetAnglesRangeBy2PointsPredicate::GetAnglesRangeBy2PointsPredicate( int angleFrom, int angleTo, bool isShortPath ) :
	m_AngleFrom( angleFrom ), m_AngleTo( angleTo ), m_IsShortPath( isShortPath ),
	m_MinAngle( 0 ), m_MaxAngle( 0 )
{
	bool leftResult = calcLeftSide();
	if( false == leftResult )
	{
		calcRightSide();
	}
}

GetAnglesRangeBy2PointsPredicate::~GetAnglesRangeBy2PointsPredicate()
{
}

int GetAnglesRangeBy2PointsPredicate::getMinAngle() const
{
	return m_MinAngle;
}

int GetAnglesRangeBy2PointsPredicate::getMaxAngle() const
{
	return m_MaxAngle;
}

bool GetAnglesRangeBy2PointsPredicate::calcLeftSide()
{
	int minAngle = min( m_AngleFrom, m_AngleTo );
	int maxAngle = max( m_AngleFrom, m_AngleTo );

	bool result = false;

	// left side calculating
	int angleFrom = m_AngleFrom;
	int angleTo = m_AngleTo;
	{
		if( abs( angleFrom - angleTo ) > 180 )//long
		{
			if( true == m_IsShortPath )
			{
				result = false;
			}
			else
			{
				result = true;

				m_MinAngle = minAngle;
				m_MaxAngle = maxAngle;
			}
		}
		else//short
		{
			if( true == m_IsShortPath )
			{
				result = true;

				m_MinAngle = minAngle;
				m_MaxAngle = maxAngle;
			}
			else
			{
				result = false;
			}
		}
	}

	return result;
}

bool GetAnglesRangeBy2PointsPredicate::calcRightSide()
{
	int tempMinAngle = min( m_AngleFrom, m_AngleTo );
	int tempMaxAngle = max( m_AngleFrom, m_AngleTo ) - 360;

	int minAngle = min( tempMinAngle, tempMaxAngle );
	int maxAngle = max( tempMinAngle, tempMaxAngle );

	bool result = false;

	{
		if( abs( minAngle - maxAngle ) > 180 )//long
		{
			if( true == m_IsShortPath )
			{
				result = false;
			}
			else
			{
				result = true;

				m_MinAngle = minAngle;
				m_MaxAngle = maxAngle;
			}
		}
		else//short
		{
			if( true == m_IsShortPath )
			{
				result = true;

				m_MinAngle = minAngle;
				m_MaxAngle = maxAngle;
			}
			else
			{
				result = false;
			}
		}
	}

	return result;
}












