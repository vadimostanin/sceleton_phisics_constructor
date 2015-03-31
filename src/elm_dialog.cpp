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
