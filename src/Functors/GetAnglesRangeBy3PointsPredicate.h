/*
 * AngleBetweenTwo.h
 *
 *  Created on: 19 апр. 2015
 *      Author: vadim
 */

#ifndef PREDICATES_GetAnglesRangeBy3PointsPredicate_H_
#define PREDICATES_GetAnglesRangeBy3PointsPredicate_H_

class GetAnglesRangeBy3PointsPredicate
{
public:
	GetAnglesRangeBy3PointsPredicate( int angleFrom, int angleTo, bool searchInShortPath, int testAngle );
	virtual ~GetAnglesRangeBy3PointsPredicate();

	bool getIsTestAngleInRange() const;

	int getIsBigArea() const;

	int getMinAngle() const;
	int getMaxAngle() const;

private:

	bool calcLeftSide();
	bool calcRightSide();

	int  m_AngleFrom;
	int  m_AngleTo;
	bool m_SearchInShortPath;
	int  m_TestAngle;

	int m_MinAngle;
	int m_MaxAngle;

	bool m_IsTestAngleInRange;
};

#endif /* PREDICATES_GetAnglesRangeBy3PointsPredicate_H_ */
