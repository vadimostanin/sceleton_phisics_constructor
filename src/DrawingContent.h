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
#include "GraphicPoint.h"

class DrawingContent : public IViewUpdatable
{

public:
	DrawingContent( Evas_Object *mainLayout );
	virtual ~DrawingContent();

	Evas_Object * getDrawingCanvas();

	void update();
	void highlightBegin( Point & point );
	void highlightEnd();

	void setGraphicObjects( vector<IGraphicObject *> & graphicObjects );

	bool getPoint( int x, int y, GraphicPoint & graphicPoint );

private:

	void createDrawingLayout();
	void createDrawingCanvas();

//	void clear_prev_points();
//	void draw_cur_points( vector<GraphicPoint> & highlighted );
	void drawObjects();
	void clearObjects();

	Evas_Object * m_MainLayout;
	Evas_Object * m_DrawingLayout;

	Evas_Object * m_DrawingCanvas;

	vector<IGraphicObject *> m_GraphicObjects;

	vector<GraphicPoint> m_GraphicPoints;
	vector<GraphicPoint> m_HighlightedPoints;
};

#endif /* DRAWINGCONTENT_H_ */
