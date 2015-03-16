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

DrawingContent::~DrawingContent() {
	// TODO Auto-generated destructor stub
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
	clear_prev_points();

	vector<GraphicPoint> highlighted;

	draw_cur_points( highlighted );
}

void DrawingContent::highlightBegin( Point & point )
{
	clear_prev_points();

	GraphicPoint graphicPoint( point.getX(), point.getY() );
	m_HighlightedPoints.push_back( graphicPoint );

	size_t count = m_HighlightedPoints.size();

	draw_cur_points( m_HighlightedPoints );
}

void DrawingContent::highlightEnd()
{
	m_HighlightedPoints.clear();
}

void DrawingContent::draw_cur_points( vector<GraphicPoint> & highlighted )
{
	vector<Point> points;
	GeometryObjectsManager::getInstance().getPoints( points );

	Evas * canvas = evas_object_evas_get( m_DrawingLayout );
	const int rect_width = 10;
	const int rect_height = 10;

	vector<Point>::iterator begin = points.begin();
	vector<Point>::iterator end = points.end();
	vector<Point>::iterator iter = begin;
	for( ; iter != end ; iter++ )
	{
		int point_x = (*iter).getX();
		int point_y = (*iter).getY();

		GraphicPoint searchPoint( (*iter).getX(), (*iter).getY() );

		Evas_Object *r1 = evas_object_rectangle_add( canvas );

		evas_object_move( r1, point_x - rect_width/2, point_y - rect_height / 2 );

		if( std::find( highlighted.begin(), highlighted.end(), searchPoint ) != highlighted.end() )
		{
			evas_object_color_set(r1, 0, 255, 0, 255);
		}
		else
		{
			evas_object_color_set(r1, 0, 0, 255, 255);
		}

		evas_object_resize(r1, rect_width, rect_height);
		evas_object_show(r1);

		GraphicPoint graphicPoint( (*iter).getX(), (*iter).getY() );
		graphicPoint.setEvas( r1 );

		m_GraphicPoints.push_back( graphicPoint );
	}
}

void DrawingContent::clear_prev_points()
{
	vector<GraphicPoint>::iterator begin = m_GraphicPoints.begin();
	vector<GraphicPoint>::iterator end = m_GraphicPoints.end();
	vector<GraphicPoint>::iterator iter = begin;
	for( ; iter != end ; iter++ )
	{
		evas_object_del( (*iter).getEvas() );
	}
	m_GraphicPoints.clear();
}

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






