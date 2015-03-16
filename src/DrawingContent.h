/*
 * DrawingContent.h
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#ifndef DRAWINGCONTENT_H_
#define DRAWINGCONTENT_H_

#include <Evas.h>
#include <vector>
using namespace std;

#include "IViewUpdatable.h"

class DrawingContent : public IViewUpdatable
{
	struct GraphicPoint
	{
		GraphicPoint( int x, int y )
		{
			m_x = x;
			m_y = y;
			m_Evas = 0;
		}
		GraphicPoint( const GraphicPoint & src )
		{
			m_x = src.m_x;
			m_y = src.m_y;
			m_Evas = src.m_Evas;
		}
		bool operator ==( const GraphicPoint & src )
		{
			if( m_x != src.m_x )
				return false;
			if( m_y != src.m_y )
				return false;
			return true;
		}
		int getX(){ return m_x; }
		int getY(){ return m_y; }

		Evas_Object * getEvas(){ return m_Evas; }

		void setEvas( Evas_Object * evas ){ m_Evas = evas; }
	private:
		int m_x;
		int m_y;
		Evas_Object * m_Evas;
	};
public:
	DrawingContent( Evas_Object *mainLayout );
	virtual ~DrawingContent();

	Evas_Object * getDrawingCanvas();

	void update();
	void highlightBegin( Point & point );
	void highlightEnd();

	bool getPoint( int x, int y, GraphicPoint & graphicPoint );

private:

	void createDrawingLayout();
	void createDrawingCanvas();

	void clear_prev_points();
	void draw_cur_points( vector<GraphicPoint> & highlighted );

	Evas_Object * m_MainLayout;
	Evas_Object * m_DrawingLayout;

	Evas_Object * m_DrawingCanvas;

	vector<GraphicPoint> m_GraphicPoints;
	vector<GraphicPoint> m_HighlightedPoints;
};

#endif /* DRAWINGCONTENT_H_ */
