//============================================================================
// Name        : elm_dialog.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include <Elementary.h>

#include "Window.h"
#include "MainContent.h"
#include "ToolbarContent.h"
#include "DrawingContent.h"
#include "WindowListener.h"
#include "MouseListener.h"
#include "GeometrySceletonOperationTracking.h"
#include "GeometryEditingOperationTracking.h"
#include "DynamicObjectFactory.h"
#include <ctime>
#include <stdlib.h>

#include "GeometryObjectsManager.h"
#include "ToolbarContentButton.h"
#include "ToolbarContentButtonParams.h"
#include "ToolbarContentRadio.h"
#include "ToolbarContentRadioParams.h"
#include "MouseTrackerManager.h"

void on_save_objects( void * userData )
{
	GeometryObjectsManager::getInstance().save( "./objects.txt" );
}

void on_run_simulation( void * userData )
{
	DrawingContent * viewUpdater = (DrawingContent *)userData;

	vector<IGraphicObject *> graphicObjects;

	vector<IGeometryObject *> objects;
	GeometryObjectsManager::getInstance().getObjects( objects );

	vector<IGeometryObject *>::iterator begin = objects.begin();
	vector<IGeometryObject *>::iterator end = objects.end();
	vector<IGeometryObject *>::iterator iter = begin;

	for(  ; iter != end ; iter ++ )
	{
		GeometryPointDynamic * dynamicObject = (GeometryPointDynamic *)DynamicObjectFactory::getInstance().createDynamicObject( (*iter) );
		IGraphicObject * graphicObject = DynamicObjectFactory::getInstance().createGraphicObject( dynamicObject, viewUpdater->getDrawingCanvas() );

		graphicObjects.push_back( graphicObject );
	}

	viewUpdater->setGraphicDynamicObjects( graphicObjects );
}

void on_sceleton_mode( void * userData )
{
	MouseTrackerManager::getInstance().setMouseListenerTrackerMode( SCELETON_MODE_E );
}

void on_spring_mode( void * userData )
{
	MouseTrackerManager::getInstance().setMouseListenerTrackerMode( EDITING_MODE_E );
}

EAPI_MAIN int elm_main(int argc, char **argv)
{
	Window window;
	WindowListener windowListener;

	window.create();

	window.setListener( &windowListener );

	MainContent mainContent( window.getEvasObject() );

	window.setContentLayout( mainContent.getLayout() );

	ToolbarContent toolbar( mainContent.getLayout() );
	{
		string title( "Save objects" );
		ToolbarContentButtonParams * params = new ToolbarContentButtonParams( title, on_save_objects, NULL );
		ToolbarContentItem * item = new ToolbarContentButton( *params );

		toolbar.addToolbarContentItem( *item );
	}

	{
		string title( "Sceleton Mode" );
		ToolbarContentRadioParams * params2 = new ToolbarContentRadioParams( title, on_sceleton_mode, NULL, NULL, true );
		ToolbarContentItem * item2 = new ToolbarContentRadio( *params2 );

		toolbar.addToolbarContentItem( *item2 );

		title = "Editing Mode";
		ToolbarContentRadioParams * params3 = new ToolbarContentRadioParams( title, on_spring_mode, NULL, item2->getEvas(), false );
		ToolbarContentItem * item3 = new ToolbarContentRadio( *params3 );

		toolbar.addToolbarContentItem( *item3 );
	}


	DrawingContent drawingContent( window.getEvasObject(), mainContent.getLayout() );

	{
		string title( "Run simulating" );
		ToolbarContentButtonParams * params = new ToolbarContentButtonParams( title, on_run_simulation, &drawingContent );
		ToolbarContentItem * item = new ToolbarContentButton( *params );

		toolbar.addToolbarContentItem( *item );
	}

//	GeometryObjectsManager::getInstance().initTestingState();

	GeometrySceletonOperationTracking geoSceletonObjectTracking( drawingContent );
	GeometryEditingOperationTracking   geoEditingObjectTracking( drawingContent );

	MouseListener mouseListener( NULL, drawingContent.getDrawingCanvas() );

	MouseTrackerManager::getInstance().setMouseListener( &mouseListener );
	MouseTrackerManager::getInstance().addTracker( &geoSceletonObjectTracking );
	MouseTrackerManager::getInstance().addTracker( &geoEditingObjectTracking );

	MouseTrackerManager::getInstance().setMouseListenerTrackerMode( SCELETON_MODE_E );

	window.setMaxSize( 800, 600 );

	srand( time ( 0 ) );

	elm_run();
	return 0;
}
ELM_MAIN()
