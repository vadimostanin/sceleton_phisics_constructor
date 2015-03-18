/*
* Copyright 2012-2013 Samsung Electronics Co., Ltd
** Licensed under the Flora License, Version 1.1 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://floralicense.org/license/
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/**
* @file     Window.h
* @brief    The window class.
* @author   Denis Dolzhenko(d.dolzhenko@samsung.com)
*/

#ifndef Window_H_
#define Window_H_

#include "BaseView.h"

// Efl:
#include <Evas.h>

// Std:
#include <memory>

class IWindowListener;

class Window
	: public BaseView
{
public:
	/**
	* Constructor
	*/
	Window( Evas_Object * parent = NULL );

	/**
	* Destructor
	*/
	virtual ~Window();

	/**
	* Create window
	*/
	bool create();

	/**
	* Destroy window
	*/
	void destroy();

	/**
	* Lowe the window
	*/
	void lower();

	/**
	* Set or unset listener
	* @param listener pointer to listener, use 0 to unset listener
	*/
	void setListener(IWindowListener * listener);

	/**
	* Get host layout
	* @return host Evas_Object
	*/
	Evas_Object * getHostLayout() const;

	/**
	* Get canvas
	* @return canvas
	*/
	Evas * getEvas() const;

	/**
	* Get canvas object
	* @return canvas object
	*/
	Evas_Object * getEvasObject() const;

	/**
	* Set or unset content
	* @param layout - content layout
	*/
	void setContentLayout(Evas_Object * content);

	/**
	* Rotates the window
	* @param rotation The rotation of the window, in degrees (0-360),
	*/
	void setRotation(int rotation);

private:
	static void on_done(void *data, Evas_Object *obj, void *event_info);

//        DISALLOW_COPY_AND_ASSIGN(Window);

private:
	Evas_Object * m_Bg;
	Evas_Object * m_pContentLayout;
	Evas_Object * m_pConform;
	IWindowListener * m_pListener;
};

class IWindowListener
{
public:
	virtual ~IWindowListener() {}

	/**
	* Call if user reqest close window
	* @param win ref. to Window object
	*/
	virtual void onExitRequest(Window & win) = 0;
};

#endif /* Window_H_ */
