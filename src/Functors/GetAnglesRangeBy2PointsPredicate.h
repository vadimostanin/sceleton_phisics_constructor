/*
 * AngleBetweenTwo.h
 *
 *  Created on: 19 апр. 2015
 *      Author: vadim
 */

#ifndef PREDICATES_GetAnglesRangeBy2PointsPredicate_H_
#define PREDICATES_GetAnglesRangeBy2PointsPredicate_H_

class GetAnglesRangeBy2PointsPredicate
{
public:
	GetAnglesRangeBy2PointsPredicate( int angleFrom, int angleTo, bool isShortPath );
	virtual ~GetAnglesRangeBy2PointsPredicate();

	int getMinAngle() const;
	int getMaxAngle() const;

private:

	bool calcLeftSide();
	bool calcRightSide();

	int  m_AngleFrom;
	int  m_AngleTo;
	bool m_IsShortPath;

	int m_MinAngle;
	int m_MaxAngle;
};

#endif /* PREDICATES_GetAnglesRangeBy2PointsPredicate_H_ */
