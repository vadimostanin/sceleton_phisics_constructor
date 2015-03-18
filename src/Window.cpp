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
* @file     Window.cpp
* @brief    The window class.
* @author   Denis Dolzhenko(d.dolzhenko@samsung.com)
*/

#include "Window.h"

#include <Elementary.h>
#include <Ecore.h>
#include <Ecore_X.h>
#include <iostream>
using namespace std;

#define PACKAGE "elm_dialog"

Window::Window( Evas_Object * parent )
    : BaseView( parent )
    , m_Bg(0)
    , m_pContentLayout(0)
    , m_pConform(0)
    , m_pListener(0)
{
}

Window::~Window()
{
    destroy();
}

bool Window::create()
{
    int w, h;
    m_pMainLayout = elm_win_add( m_pParent, PACKAGE, ELM_WIN_BASIC);
    elm_win_title_set(m_pMainLayout, PACKAGE);

    ecore_x_window_size_get(ecore_x_window_root_first_get(), &w, &h);
    evas_object_resize(m_pMainLayout, w, h);
    evas_object_smart_callback_add(m_pMainLayout, "delete,request", on_done, this);
    elm_win_conformant_set(m_pMainLayout, EINA_TRUE);
    evas_object_show(m_pMainLayout);

    elm_win_indicator_mode_set(m_pMainLayout, ELM_WIN_INDICATOR_SHOW);

    m_Bg = elm_bg_add(m_pMainLayout);
    evas_object_size_hint_weight_set(m_Bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_win_resize_object_add(m_pMainLayout, m_Bg);
    elm_bg_color_set( m_Bg, 255, 255, 255 );
    evas_object_show(m_Bg);

    m_pConform = elm_conformant_add(m_pMainLayout);
    if (!m_pConform)
    {
        return false;
    }

    evas_object_size_hint_weight_set(m_pConform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_win_resize_object_add(m_pMainLayout, m_pConform);
    evas_object_show(m_pConform);

    return m_pMainLayout != 0;
}

void Window::destroy()
{
    if(m_pMainLayout)
    {
        evas_object_del(m_pMainLayout);
        m_pMainLayout = 0;
    }
}

void Window::lower()
{
    if(m_pMainLayout)
        elm_win_lower(m_pMainLayout);
}

Evas_Object * Window::getHostLayout() const
{
    return m_pConform;
}

Evas * Window::getEvas() const
{
    return evas_object_evas_get(m_pMainLayout);
}

Evas_Object * Window::getEvasObject() const
{
    return m_pMainLayout;
}

void Window::on_done(void *data, Evas_Object *obj, void *event_info)
{
    Window * win = static_cast<Window*>(data);
    if(win && win->m_pListener)
        win->m_pListener->onExitRequest(*win);
}

void Window::setListener(IWindowListener * listener)
{
    m_pListener = listener;
}

void Window::setContentLayout(Evas_Object * layout)
{
    if(layout)
    {
        Evas_Object * old = elm_object_content_get(m_pConform);
        if(old != layout)
        {
            elm_object_content_unset(m_pConform);
            elm_object_content_set(m_pConform, layout);
        }
    }

    /*
    if(m_pContentLayout)
        elm_win_resize_object_del(m_pMainLayout, m_pContentLayout);

    m_pContentLayout = layout;
    if(m_pContentLayout)
    {
        evas_object_size_hint_weight_set(m_pContentLayout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
        elm_win_resize_object_add(m_pMainLayout, layout);
        evas_object_show(m_pContentLayout);
    }
    */
}

void Window::setRotation(int rotation)
{
    if(m_pMainLayout)
        elm_win_rotation_set(m_pMainLayout, rotation);
}
