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
	ecore_animator_del( m_Timer );
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
	m_Timer = ecore_animator_add( timer_func, this );
	ecore_animator_freeze( m_Timer );
}

void Timer::start()
{
	ecore_animator_thaw( m_Timer );
}

void Timer::stop()
{
	ecore_animator_freeze( m_Timer );
}













