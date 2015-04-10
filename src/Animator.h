/*
 * Timer.h
 *
 *  Created on: Apr 3, 2015
 *      Author: vostanin
 */

#ifndef ANIMATOR_H_
#define ANIMATOR_H_

#include <Ecore.h>

typedef bool (* TimerFuncType )( void * userData );

class Animator
{
public:
	Animator( TimerFuncType timerFunc, void * userData );
	virtual ~Animator();

	void start();
	void stop();

private:

	void init();

	static Eina_Bool timer_func( void * userData );

	Ecore_Animator * 	m_Animator;
	TimerFuncType 		m_TimerFunc;
	void 		* 		m_UserData;
};

#endif /* ANIMATOR_H_ */
