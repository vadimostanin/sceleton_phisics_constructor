/*
 * AngleBetweenTwo.h
 *
 *  Created on: 19 апр. 2015
 *      Author: vadim
 */

#ifndef PREDICATES_ISANGLEBETWEENTWOPREDICATE_H_
#define PREDICATES_ISANGLEBETWEENTWOPREDICATE_H_

class IsAngleBetweenTwoPredicate
{
public:
	IsAngleBetweenTwoPredicate( int angle1, int angle2, bool shortAngle, int testAngle );
	virtual ~IsAngleBetweenTwoPredicate();

	bool operator()();

private:

	int  m_Angle1;
	int  m_Angle2;
	bool m_IsShortAngle;
	int  m_TestAngle;

};

#endif /* PREDICATES_ISANGLEBETWEENTWOPREDICATE_H_ */
