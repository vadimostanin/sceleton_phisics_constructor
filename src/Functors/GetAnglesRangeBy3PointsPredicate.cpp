/*
 * AngleBetweenTwo.cpp
 *
 *  Created on: 19 апр. 2015
 *      Author: vadim
 */

#include "GetAnglesRangeBy3PointsPredicate.h"
#include <cmath>
#include <algorithm>
#include <cassert>
using namespace std;

GetAnglesRangeBy3PointsPredicate::GetAnglesRangeBy3PointsPredicate( int angleFrom, int angleTo, bool searchInShortPath, int testAngle ) :
	m_AngleFrom( angleFrom ), m_AngleTo( angleTo ), m_SearchInShortPath( searchInShortPath ), m_TestAngle( testAngle ),
	m_MinAngle( 0 ), m_MaxAngle( 0 ), m_IsTestAngleInRange( false )
{
	bool leftResult = calcLeftSide();
	if( true == leftResult )
	{
		m_IsTestAngleInRange = true;
	}
	else
	{
		bool rightResult = calcRightSide();
		if( true == rightResult )
		{
			m_IsTestAngleInRange = true;
		}
	}
}

GetAnglesRangeBy3PointsPredicate::~GetAnglesRangeBy3PointsPredicate()
{
}

int GetAnglesRangeBy3PointsPredicate::getMinAngle() const
{
	return m_MinAngle;
}

int GetAnglesRangeBy3PointsPredicate::getMaxAngle() const
{
	return m_MaxAngle;
}

bool GetAnglesRangeBy3PointsPredicate::calcLeftSide()
{
	int minAngle = min( m_AngleFrom, m_AngleTo );
	int maxAngle = max( m_AngleFrom, m_AngleTo );

	bool between = m_TestAngle >= minAngle && m_TestAngle <= maxAngle ;

	bool result = false;

	// left side calculating
	int angleFrom = m_AngleFrom;
	int angleTo = m_AngleTo;
	{
		if( abs( angleFrom - angleTo ) > 180 )//long
		{
			if( true == between )
			{
				if( true == m_SearchInShortPath )
				{
					result = false;
				}
				else
				{
					result = true;
				}

				if( angleFrom < m_TestAngle )
				{
					m_MinAngle = m_AngleFrom;
					m_MaxAngle = m_TestAngle;
				}
				else
				{
					m_MinAngle = m_TestAngle;
					m_MaxAngle = m_AngleFrom;
				}
			}
		}
		else//short
		{
			if( true == between )
			{
				if( true == m_SearchInShortPath )
				{
					result = true;
				}
				else
				{
					result = false;
				}

				if( angleFrom <= m_TestAngle )
				{
					m_MinAngle = m_AngleFrom;
					m_MaxAngle = m_TestAngle;
				}
				else
				{
					m_MinAngle = m_TestAngle;
					m_MaxAngle = m_AngleFrom;
				}
			}
		}
	}

	return result;
}

bool GetAnglesRangeBy3PointsPredicate::calcRightSide()
{
	int tempMinAngle = min( m_AngleFrom, m_AngleTo );
	int tempMaxAngle = max( m_AngleFrom, m_AngleTo ) - 360;

	int minAngle = min( tempMinAngle, tempMaxAngle );
	int maxAngle = max( tempMinAngle, tempMaxAngle );

	int tempTestAngle = m_TestAngle;
	if( tempTestAngle > max( m_AngleFrom, m_AngleTo ) )
//	if( tempTestAngle >= 180 )
	{
		tempTestAngle -= 360;
	}

	bool between = tempTestAngle >= minAngle && tempTestAngle <= maxAngle ;

	bool result = false;

	{
		if( abs( minAngle - maxAngle ) > 180 )//long
		{
			if( true == between )
			{
				if( true == m_SearchInShortPath )
				{
					result = false;
				}
				else
				{
					result = true;
				}

				if( m_AngleFrom < m_AngleTo )
				{
					int tempMin = min( tempTestAngle, m_AngleFrom );
					int tempMax = max( tempTestAngle, m_AngleFrom );

					m_MinAngle = tempMin;
					m_MaxAngle = tempMax;
				}
				else
				{
					int tempMin = min( tempTestAngle, tempMaxAngle );
					int tempMax = max( tempTestAngle, tempMaxAngle );

					m_MinAngle = tempMin;
					m_MaxAngle = tempMax;
				}
			}
		}
		else//short
		{
			if( true == between )
			{
				if( true == m_SearchInShortPath )
				{
					result = true;
				}
				else
				{
					result = false;
				}

				if( m_AngleFrom < m_AngleTo )
				{
					int tempMin = min( tempTestAngle, m_AngleFrom );
					int tempMax = max( tempTestAngle, m_AngleFrom );

					m_MinAngle = tempMin;
					m_MaxAngle = tempMax;
				}
				else
				{
					int tempMin = min( tempTestAngle, ( m_AngleFrom - 360 ) );
					int tempMax = max( tempTestAngle, ( m_AngleFrom - 360 ) );

					m_MinAngle = tempMin;
					m_MaxAngle = tempMax;
				}
			}
		}
	}

	return result;
}

int GetAnglesRangeBy3PointsPredicate::getIsBigArea() const
{
	return false;
}

bool GetAnglesRangeBy3PointsPredicate::getIsTestAngleInRange() const
{
	return m_IsTestAngleInRange;
}











