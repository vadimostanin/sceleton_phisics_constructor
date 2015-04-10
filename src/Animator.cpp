/*
 * Timer.cpp
 *
 *  Created on: Apr 3, 2015
 *      Author: vostanin
 */

#include "Animator.h"

Animator::Animator( TimerFuncType timerFunc, void * userData) : m_TimerFunc( timerFunc ), m_UserData( userData )
{
	init();
}

Animator::~Animator()
{
	ecore_animator_del( m_Animator );
}

Eina_Bool Animator::timer_func( void * userData )
{
	Animator * lpThis = (Animator *)userData;

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

void Animator::init()
{
	m_Animator = ecore_animator_add( timer_func, this );
	ecore_animator_freeze( m_Animator );
}

void Animator::start()
{
	ecore_animator_thaw( m_Animator );
}

void Animator::stop()
{
	ecore_animator_freeze( m_Animator );
}













