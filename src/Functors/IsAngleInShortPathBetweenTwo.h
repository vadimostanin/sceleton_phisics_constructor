/*
 * IsAngleInShortPathBetweenTwo.h
 *
 *  Created on: 20 апр. 2015
 *      Author: vadim
 */

#ifndef FUNCTORS_ISANGLEINSHORTPATHBETWEENTWO_H_
#define FUNCTORS_ISANGLEINSHORTPATHBETWEENTWO_H_

class IsAngleInShortPathBetweenTwo
{
public:
	IsAngleInShortPathBetweenTwo( int angle1, int angle2, int testAngle );
	virtual ~IsAngleInShortPathBetweenTwo();

	bool operator()();

private:

	int m_Angle1;
	int m_Angle2;
	int m_TestAngle;
};

#endif /* FUNCTORS_ISANGLEINSHORTPATHBETWEENTWO_H_ */
