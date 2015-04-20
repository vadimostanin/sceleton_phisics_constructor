/*
 * IsAngleInShortPathBetweenTwo.cpp
 *
 *  Created on: 20 апр. 2015
 *      Author: vadim
 */

#include "Functors/IsAngleInShortPathBetweenTwo.h"
#include <cmath>
#include <algorithm>
using namespace std;

IsAngleInShortPathBetweenTwo::IsAngleInShortPathBetweenTwo( int angle1, int angle2, int testAngle ) :
	m_Angle1( angle1 ), m_Angle2( angle2 ), m_TestAngle( testAngle )
{
}

IsAngleInShortPathBetweenTwo::~IsAngleInShortPathBetweenTwo()
{
}

bool IsAngleInShortPathBetweenTwo::operator()()
{
	int minAngle = min( m_Angle1, m_Angle2 );
	int testAngleOffset = m_TestAngle - minAngle;
	int angle1Offset = m_Angle1 - minAngle;
	int angle2Offset = m_Angle2 - minAngle;

	int sumAnglesOffset = angle1Offset + angle2Offset;

	bool between = testAngleOffset > 0 && testAngleOffset <= sumAnglesOffset;

	bool result = false;

	if( sumAnglesOffset > 180 )//long
	{
		if( true == between )
		{
			result = false;
		}
		else
		{
			result = true;
		}
	}
	else//short
	{
		if( true == between )
		{
			result = true;
		}
		else
		{
			result = false;
		}
	}

	return result;
}










