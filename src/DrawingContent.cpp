/*
 * DrawingContent.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "DrawingContent.h"
#include "GeometryObjectsManager.h"
#include <Elementary.h>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAIN_EDJ "./main.edj"

#define SEARCHING_POINT_RADIUS 20

DrawingContent::DrawingContent( Evas_Object *mainLayout ) : m_MainLayout( mainLayout )
{
	createDrawingLayout();
	createDrawingCanvas();
}

DrawingContent::~DrawingContent()
{
}

void DrawingContent::createDrawingLayout()
{
	m_DrawingLayout = elm_layout_add( m_MainLayout );
	elm_layout_file_set( m_DrawingLayout, MAIN_EDJ, "group.drawing_layout");
	evas_object_size_hint_weight_set( m_DrawingLayout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_content_set( m_MainLayout, "part.main.drawing", m_DrawingLayout );
}

void DrawingContent::createDrawingCanvas()
{
	evas_object_smart_need_recalculate_set( m_DrawingLayout, 1 );
	evas_object_smart_calculate( m_DrawingLayout );

	Evas_Coord x, y, w, h;
	evas_object_geometry_get( m_DrawingLayout, &x, &y, &w, &h );

	Evas * canvas = evas_object_evas_get( m_DrawingLayout );
	Evas_Object *r1 = evas_object_rectangle_add( canvas );

	evas_object_color_set(r1, 128, 128, 128, 255);
	evas_object_move(r1, 0, 50);
	evas_object_resize(r1, 800, 600);
	evas_object_show(r1);

	m_DrawingCanvas = r1;
}

Evas_Object * DrawingContent::getDrawingCanvas()
{
	return m_DrawingCanvas;
}

void DrawingContent::update()
{
	drawObjects();

//	Eina_List * updates = evas_render_updates( getDrawingCanvas() );
//	Eina_List * l = 0;
//	Eina_Rectangle *rect;
//
//	EINA_LIST_FOREACH(updates, l, rect)
//	{
//		printf( "Rectangle (%d, %d, %d, %d) on canvas got a rendering update.\n", rect->x, rect->y,	rect->w, rect->h ); fflush( stdout );
//	}
//	evas_render_updates_free(updates);
}

void DrawingContent::setGraphicObjects( vector<IGraphicObject *> & graphicObjects )
{
	clearObjects();

	m_GraphicObjects = graphicObjects;

	size_t count = m_GraphicObjects.size();

	update();
}

void DrawingContent::drawObjects()
{
	Evas * canvas = evas_object_evas_get( m_DrawingLayout );

	vector<IGraphicObject *>::iterator begin = m_GraphicObjects.begin();
	vector<IGraphicObject *>::iterator end = m_GraphicObjects.end();
	vector<IGraphicObject *>::iterator iter = begin;
	for( ; iter != end ; iter++ )
	{
		(*iter)->draw( canvas );
	}
}

void DrawingContent::clearObjects()
{
	vector<IGraphicObject *>::iterator begin = m_GraphicObjects.begin();
	vector<IGraphicObject *>::iterator end = m_GraphicObjects.end();
	vector<IGraphicObject *>::iterator iter = begin;
	for( ; iter != end ; iter++ )
	{
		delete (*iter);
	}
	m_GraphicPoints.clear();
}
/*
bool DrawingContent::getPoint( int x, int y, GraphicPoint & graphicPoint )
{
	vector<GraphicPoint>::iterator begin = m_GraphicPoints.begin();
	vector<GraphicPoint>::iterator end = m_GraphicPoints.end();
	vector<GraphicPoint>::iterator iter = begin;
	for( ; iter != end ; iter++ )
	{
		int point_x = (*iter).getX();
		int point_y = (*iter).getY();

		if( x > ( point_x + SEARCHING_POINT_RADIUS ) || x < ( point_x - SEARCHING_POINT_RADIUS ) ||
			y > ( point_y + SEARCHING_POINT_RADIUS ) || y < ( point_y - SEARCHING_POINT_RADIUS ) )
		{
			continue;
		}
		graphicPoint = (*iter);
		return true;
	}
	return false;
}
*/










