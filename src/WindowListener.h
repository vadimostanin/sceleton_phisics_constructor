/*
 * WindowListener.h
 *
 *  Created on: Mar 13, 2015
 *      Author: vostanin
 */

#ifndef WINDOWLISTENER_H_
#define WINDOWLISTENER_H_

#include "Window.h"

class WindowListener : public IWindowListener {
public:
	WindowListener();
	virtual ~WindowListener();

	virtual void onExitRequest(Window & win);
};

#endif /* WINDOWLISTENER_H_ */
