/*
 * DynamicObjectsManager.h
 *
 *  Created on: Apr 6, 2015
 *      Author: vostanin
 */

#ifndef DYNAMICOBJECTSMANAGER_H_
#define DYNAMICOBJECTSMANAGER_H_

#include "IDynamicObject.h"
#include <vector>
using namespace std;

class DynamicObjectsManager
{
	DynamicObjectsManager();
	virtual ~DynamicObjectsManager();

public:

	void addObject( IDynamicObject * object );
	void removeObject( IDynamicObject * object );
	void getObjects( vector<IDynamicObject *> & objects );

	void setObjects( vector<IDynamicObject *> & objects );
	void appendObjects( vector<IDynamicObject *> & objects );
	void clearObjects();

	static DynamicObjectsManager & getInstance();

private:

	vector<IDynamicObject *> m_dynamicObjects;

};

#endif /* DYNAMICOBJECTSMANAGER_H_ */
