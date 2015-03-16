/*
* Copyright 2012-2013 Samsung Electronics Co., Ltd
* Licensed under the Flora License, Version 1.1 (the "License");
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
* @file     BaseView.h
* @brief    Base View for all view classes.
* @author   Denis Dolzhenko(d.dolzhenko@samsung.com)
*/

#ifndef BaseView_h_
#define BaseView_h_

#include <Evas.h>

class BaseView
{
public:
	/**
	* Constructor
	* @param ref. to parent parent view
	*/
	BaseView(BaseView & parent);

	/**
	* Constructor
	* @param pointer to parent Evas_Object
	*/
	BaseView(Evas_Object * parent);

	/**
	* Destructor
	*/
	virtual ~BaseView();

	/**
	* Set visibility
	* @param val true - show, false - hide
	*/
	virtual void setVisibility(bool val);

	/**
	* Move view
	* @param x position to move the object to, in canvas.
	* @param y position to move the object to, in canvas.
	*/
	virtual void move(int x, int y);

	/**
	* Set max size of view
	* @param width max width
	* @param height max height
	*/
	virtual void setMaxSize(int width, int height);

	/**
	* Set size
	* @param width width of view
	* @param height height of view
	*/
	virtual void setSize(int width, int height);

	/**
	* Get parent layout
	* @return pointer to layout
	*/
	virtual Evas_Object * getParentLayout() const;

	/**
	* Get main layout of view
	* @return pointer to layout
	*/
	virtual Evas_Object * getMainLayout() const;

protected:
	Evas_Object * m_pParent;
	Evas_Object * m_pMainLayout;
};

#endif // BaseView_h_
