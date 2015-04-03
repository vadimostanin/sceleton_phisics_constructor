/*
 * Timer.h
 *
 *  Created on: Apr 3, 2015
 *      Author: vostanin
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <Ecore.h>

typedef bool (* TimerFuncType )( void * userData );

class Timer
{
public:
	Timer( TimerFuncType timerFunc, void * userData, const double interval );
	virtual ~Timer();

	void start();
	void stop();

private:

	void init();

	static Eina_Bool timer_func( void * userData );

	Ecore_Timer * m_Timer;
	TimerFuncType m_TimerFunc;
	void 		* m_UserData;
	const double m_Interval;
};

#endif /* TIMER_H_ */
