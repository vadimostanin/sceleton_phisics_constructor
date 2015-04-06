/*
 * DynamicTimeLineManager.h
 *
 *  Created on: Apr 6, 2015
 *      Author: vostanin
 */

#ifndef DYNAMICTIMELINEMANAGER_H_
#define DYNAMICTIMELINEMANAGER_H_

#include <chipmunk/chipmunk.h>

class DynamicTimeLineManager
{
public:
	DynamicTimeLineManager();
	virtual ~DynamicTimeLineManager();

	void setSpace( cpSpace * space );
	void stepSpace();

	static DynamicTimeLineManager & getInstance();

private:

	cpSpace * m_Space;

};

#endif /* DYNAMICTIMELINEMANAGER_H_ */
