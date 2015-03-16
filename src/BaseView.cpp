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
* @file     BaseView.cpp
* @brief    Base View for all view classes.
* @author   Denis Dolzhenko(d.dolzhenko@samsung.com)
*/

#include "BaseView.h"

BaseView::BaseView(BaseView & parent)
    : m_pParent(parent.getMainLayout())
    , m_pMainLayout(0)
{

}

BaseView::BaseView(Evas_Object * parent)
    : m_pParent(parent)
    , m_pMainLayout(0)
{

}

BaseView::~BaseView()
{

}

void BaseView::setVisibility(bool val)
{
    if(m_pMainLayout)
    {
        if(val)
            evas_object_show(m_pMainLayout);
        else
            evas_object_hide(m_pMainLayout);
    }
}

Evas_Object * BaseView::getParentLayout() const
{
    return m_pParent;
}

Evas_Object * BaseView::getMainLayout() const
{
    return m_pMainLayout;
}

void BaseView::move(int x, int y)
{
    if(m_pMainLayout)
        evas_object_move(m_pMainLayout, x, y);
}

void BaseView::setMaxSize(int width, int height)
{
    if(m_pMainLayout)
        evas_object_size_hint_max_set(m_pMainLayout, width, height);
}

void BaseView::setSize(int width, int height)
{
    if(m_pMainLayout)
        evas_object_size_hint_max_set(m_pMainLayout, width, height);
}
