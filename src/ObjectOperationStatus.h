/*
 * ObjectOperationStatus.h
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#ifndef OBJECTOPERATIONSTATUS_H_
#define OBJECTOPERATIONSTATUS_H_


typedef enum
{
	OBJECT_NONE,
	OBJECT_POINT_CREATING,
	OBJECT_POINT_CREATED,
	OBJECT_LINK_CREATING,
	OBJECT_LINK_CREATED,
}ObjectState;


#endif /* OBJECTOPERATIONSTATUS_H_ */
