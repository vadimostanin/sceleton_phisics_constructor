/*
 * ToolbarContentItemParams.h
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#ifndef TOOLBARCONTENTITEMPARAMS_H_
#define TOOLBARCONTENTITEMPARAMS_H_

typedef void (* ToolbarItemCallback)( void * user_data );

class ToolbarContentItemParams
{
public:
	ToolbarContentItemParams();
	virtual ~ToolbarContentItemParams();

	virtual ToolbarContentItemParams & operator = ( const ToolbarContentItemParams & src ) = 0;
};

#endif /* TOOLBARCONTENTITEMPARAMS_H_ */
