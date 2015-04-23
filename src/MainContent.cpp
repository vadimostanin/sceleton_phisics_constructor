/*
 * MainContent.cpp
 *
 *  Created on: Mar 13, 2015
 *      Author: vostanin
 */

#include "MainContent.h"

#include <Elementary.h>

#include <Evas_Engine_Buffer.h>
#include <iostream>
using namespace std;

//#define MAIN_EDJ "/opt/usr/apps/org.tizen.tizen_porting/res/edje/main.edj"
#define MAIN_EDJ "./main.edj"

MainContent::MainContent( Evas_Object *parent ) : m_Parent( parent ), m_MainLayout( NULL )
{
	createLayout();
}

MainContent::~MainContent()
{

}

Evas_Object * MainContent::getLayout()
{
	return m_MainLayout;
}

void MainContent::createLayout()
{
	Evas_Object *layout = elm_layout_add( m_Parent );
	elm_layout_file_set(layout, MAIN_EDJ, "main_layout");
	evas_object_show(layout);

	m_MainLayout = layout;
}


















