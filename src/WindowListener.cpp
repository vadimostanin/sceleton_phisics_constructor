/*
 * WindowListener.cpp
 *
 *  Created on: Mar 13, 2015
 *      Author: vostanin
 */

#include "WindowListener.h"
#include <Elementary.h>

WindowListener::WindowListener() {
	// TODO Auto-generated constructor stub

}

WindowListener::~WindowListener() {
	// TODO Auto-generated destructor stub
}

void WindowListener::onExitRequest(Window & win)
{
	elm_exit();
}
