/*
 * Timer.cpp
 *
 *  Created on: Apr 3, 2015
 *      Author: vostanin
 */

#include "Timer.h"

Timer::Timer( TimerFuncType timerFunc, void * userData, const double interval ) : m_TimerFunc( timerFunc ), m_UserData( userData ), m_Interval( interval )
{
	init();
}

Timer::~Timer()
{
	ecore_timer_del( m_Timer );
}

Eina_Bool Timer::timer_func( void * userData )
{
	Timer * lpThis = (Timer *)userData;

	if( ! lpThis->m_TimerFunc )
	{
		return ECORE_CALLBACK_CANCEL;
	}

	if( lpThis->m_TimerFunc( lpThis->m_UserData ) == true )
	{
		return ECORE_CALLBACK_RENEW;
	}

	return ECORE_CALLBACK_CANCEL;
}

void Timer::init()
{
	m_Timer = ecore_timer_add( m_Interval, timer_func, this );
	ecore_timer_freeze( m_Timer );
}

void Timer::start()
{
	ecore_timer_thaw( m_Timer );
}

void Timer::stop()
{
	ecore_timer_freeze( m_Timer );
}













