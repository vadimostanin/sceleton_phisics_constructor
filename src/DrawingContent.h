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
	DrawingContent( Evas_Object *mainWindowObject, Evas_Object *mainLayout );
	virtual ~DrawingContent();

	Evas_Object * getDrawingCanvas();

	void update();

	void setGraphicObjects( vector<IGraphicObject *> & graphicObjects );

//	bool getPoint( int x, int y, GraphicPoint & graphicPoint );

private:

	void createDrawingLayout();
	void createDrawingCanvas();

	void drawObjects();
	void clearObjects();

	static void on_init_gles( Evas_Object * glview );
	static void on_resize_gl( Evas_Object * glview );
	static void on_draw_gl( Evas_Object * glview );

	Evas_Object * m_MainLayout;
	Evas_Object * m_DrawingLayout;

	Evas_Object * m_MainWindowObject;

	Evas_Object * m_DrawingCanvas;

	Evas_GL_API * m_glApi;

	vector<IGraphicObject *> m_GraphicObjects;

	vector<GraphicPoint> m_GraphicPoints;
	vector<GraphicPoint> m_HighlightedPoints;
};

#endif /* DRAWINGCONTENT_H_ */
