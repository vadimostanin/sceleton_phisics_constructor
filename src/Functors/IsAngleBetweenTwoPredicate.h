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
	IsAngleBetweenTwoPredicate( int angleFrom, int angleTo, bool searchInShortPath, int testAngle );
	virtual ~IsAngleBetweenTwoPredicate();

	bool operator()();

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

	bool m_Result;
};

#endif /* PREDICATES_ISANGLEBETWEENTWOPREDICATE_H_ */
