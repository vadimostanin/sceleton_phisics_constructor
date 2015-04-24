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
#include "SimulationOperationTracking.h"
#include <ctime>
#include <stdlib.h>

#include "GeometryObjectsManager.h"
#include "DynamicObjectsManager.h"
#include "DynamicObjectFactory.h"
#include "MouseTrackerManager.h"
#include "ToolbarContentButton.h"
#include "ToolbarContentButtonParams.h"
#include "ToolbarContentRadio.h"
#include "ToolbarContentRadioParams.h"
#include "DynamicObjectsContructor.h"
#include "GraphicObjectsContrucor.h"

#include "GetAnglesRangeBy3PointsPredicate.h"

void test_functor_IsAngleInShortPathBetweenTwo()
{
	//left side test
	{
		GetAnglesRangeBy3PointsPredicate IsBetween( 230, 240, true, 235 );
		bool is = IsBetween.getIsTestAngleInRange();
		cout << "expected true is=" << ( ( is == true ) ? "true" : "false" ) << endl << flush;
		int minAngle = IsBetween.getMinAngle();
		int maxAngle = IsBetween.getMaxAngle();
		cout << "min 230=" << minAngle << "; max 235=" << maxAngle << endl << flush;
	}
	{
		GetAnglesRangeBy3PointsPredicate IsBetween( 240, 230, true, 235 );
		bool is = IsBetween.getIsTestAngleInRange();
		cout << "expected true is=" << ( ( is == true ) ? "true" : "false" ) << endl << flush;
		int minAngle = IsBetween.getMinAngle();
		int maxAngle = IsBetween.getMaxAngle();
		cout << "min 235=" << minAngle << "; max 240=" << maxAngle << endl << flush;
	}
	{
		GetAnglesRangeBy3PointsPredicate IsBetween( 30, 240, false, 200 );
		bool is = IsBetween.getIsTestAngleInRange();
		cout << "expected true is=" << ( ( is == true ) ? "true" : "false" ) << endl << flush;
		int minAngle = IsBetween.getMinAngle();
		int maxAngle = IsBetween.getMaxAngle();
		cout << "min 30=" << minAngle << "; max 200=" << maxAngle << endl << flush;
	}
	{
		GetAnglesRangeBy3PointsPredicate IsBetween( 240, 30, false, 200 );
		bool is = IsBetween.getIsTestAngleInRange();
		cout << "expected true is=" << ( ( is == true ) ? "true" : "false" ) << endl << flush;
		int minAngle = IsBetween.getMinAngle();
		int maxAngle = IsBetween.getMaxAngle();
		cout << "min 200=" << minAngle << "; max 240=" << maxAngle << endl << flush;
	}

	//right side test
	{
		GetAnglesRangeBy3PointsPredicate IsBetween( 230, 240, false, 10 );
		bool is = IsBetween.getIsTestAngleInRange();
		cout << "expected true is=" << ( ( is == true ) ? "true" : "false" ) << endl << flush;
		int minAngle = IsBetween.getMinAngle();
		int maxAngle = IsBetween.getMaxAngle();
		cout << "min 10=" << minAngle << "; max 230=" << maxAngle << endl << flush;
	}
	{
		GetAnglesRangeBy3PointsPredicate IsBetween( 240, 230, false, 300 );
		bool is = IsBetween.getIsTestAngleInRange();
		cout << "expected true is=" << ( ( is == true ) ? "true" : "false" ) << endl << flush;
		int minAngle = IsBetween.getMinAngle();
		int maxAngle = IsBetween.getMaxAngle();
		cout << "min -120=" << minAngle << "; max -60=" << maxAngle << endl << flush;
	}
	{
		GetAnglesRangeBy3PointsPredicate IsBetween( 30, 240, true, 10 );
		bool is = IsBetween.getIsTestAngleInRange();
		cout << "expected true is=" << ( ( is == true ) ? "true" : "false" ) << endl << flush;
		int minAngle = IsBetween.getMinAngle();
		int maxAngle = IsBetween.getMaxAngle();
		cout << "min 10=" << minAngle << "; max 30=" << maxAngle << endl << flush;
	}
	{
		GetAnglesRangeBy3PointsPredicate IsBetween( 240, 30, true, 300 );
		bool is = IsBetween.getIsTestAngleInRange();
		cout << "expected true is=" << ( ( is == true ) ? "true" : "false" ) << endl << flush;
		int minAngle = IsBetween.getMinAngle();
		int maxAngle = IsBetween.getMaxAngle();
		cout << "min -120=" << minAngle << "; max -60=" << maxAngle << endl << flush;
	}
	{
		GetAnglesRangeBy3PointsPredicate IsBetween( 200, 0, true, 300 );
		bool is = IsBetween.getIsTestAngleInRange();
		cout << "expected true is=" << ( ( is == true ) ? "true" : "false" ) << endl << flush;
		int minAngle = IsBetween.getMinAngle();
		int maxAngle = IsBetween.getMaxAngle();
		cout << "min -160=" << minAngle << "; max -60=" << maxAngle << endl << flush;
	}
	{
		GetAnglesRangeBy3PointsPredicate IsBetween( 0, 90, false, 138 );
		bool is = IsBetween.getIsTestAngleInRange();
		cout << "expected true is=" << ( ( is == true ) ? "true" : "false" ) << endl << flush;
		int minAngle = IsBetween.getMinAngle();
		int maxAngle = IsBetween.getMaxAngle();
		cout << "min -222=" << minAngle << "; max 0=" << maxAngle << endl << flush;
	}
	{
		GetAnglesRangeBy3PointsPredicate IsBetween( 354, 206, false, 193 );
		bool is = IsBetween.getIsTestAngleInRange();
		cout << "expected true is=" << ( ( is == true ) ? "true" : "false" ) << endl << flush;
		int minAngle = IsBetween.getMinAngle();
		int maxAngle = IsBetween.getMaxAngle();
		cout << "min -6=" << minAngle << "; max 193=" << maxAngle << endl << flush;
	}
}

void on_construct_test_objects( void * userData )
{
	DrawingContent * viewUpdater = (DrawingContent *)userData;

	GeometryObjectsManager::getInstance().initTestingState2();

	vector<IGeometryObject *> geometryObjects;
	vector<IGraphicObject *> graphicObjects;
	GeometryObjectsManager::getInstance().getObjects( geometryObjects );
	GraphicObjectsContrucor::getInstance().convert( geometryObjects, graphicObjects );

	viewUpdater->setGraphicObjects( graphicObjects );
}

void on_clear_objects( void * userData )
{
	DrawingContent * viewUpdater = (DrawingContent *)userData;

	GeometryObjectsManager::getInstance().clearObjects();

	vector<IGraphicObject *> graphicObjects;

	viewUpdater->setGraphicObjects( graphicObjects );
}

void on_save_objects( void * userData )
{
	GeometryObjectsManager::getInstance().save( "./objects.txt" );
}

void on_run_simulation( void * userData )
{
	DrawingContent * viewUpdater = (DrawingContent *)userData;

	vector<IGeometryObject *> geometryObjects;
	vector<IDynamicObject *> dynamicObjects;
	vector<IGraphicObject *> graphicObjects;

	GeometryObjectsManager::getInstance().getObjects( geometryObjects );

	DynamicObjectFactory::getInstance().setCanvasWidth( viewUpdater->getCanvasWidth() );
	DynamicObjectFactory::getInstance().setCanvasHeight( viewUpdater->getCanvasHeight() );
	DynamicObjectFactory::getInstance().init();

	DynamicObjectsContructor::getInstance().setCanvasWidth( viewUpdater->getCanvasWidth() );
	DynamicObjectsContructor::getInstance().setCanvasHeight( viewUpdater->getCanvasHeight() );

	DynamicObjectsContructor::getInstance().convertSmart( geometryObjects, dynamicObjects );

	DynamicObjectsManager::getInstance().setObjects( dynamicObjects );

	GraphicObjectsContrucor::getInstance().convert( dynamicObjects, graphicObjects );

	viewUpdater->setGraphicDynamicObjects( graphicObjects );

	MouseTrackerManager::getInstance().setMouseListenerTrackerMode( SIMULATION_MODE_E );
}

void on_sceleton_mode( void * userData )
{
	DrawingContent * viewUpdater = (DrawingContent *)userData;

	DynamicObjectsManager::getInstance().clearObjects();

	vector<IGeometryObject *> geometryObjects;
	vector<IGraphicObject *> emptyGraphicObjects;
	vector<IGraphicObject *> graphicObjects;

	viewUpdater->setGraphicDynamicObjects( emptyGraphicObjects );

	GeometryObjectsManager::getInstance().getObjects( geometryObjects );
	GraphicObjectsContrucor::getInstance().convert( geometryObjects, graphicObjects );
	viewUpdater->setGraphicObjects( graphicObjects );

	MouseTrackerManager::getInstance().setMouseListenerTrackerMode( SCELETON_MODE_E );
}

EAPI_MAIN int elm_main(int argc, char **argv)
{
	Window window;
	WindowListener windowListener;

	window.create();

	window.setListener( &windowListener );

	MainContent mainContent( window.getEvasObject() );

	window.setContentLayout( mainContent.getLayout() );

	DrawingContent drawingContent( window.getEvasObject(), mainContent.getLayout() );

	GraphicObjectsContrucor::getInstance().setCanvas( drawingContent.getDrawingCanvas() );

	ToolbarContent toolbar( mainContent.getLayout() );
	{
		string title( "Save objects" );
		ToolbarContentButtonParams * params = new ToolbarContentButtonParams( title, on_save_objects, NULL );
		ToolbarContentItem * item = new ToolbarContentButton( *params );

		toolbar.addToolbarContentItem( *item );
	}

	{
		string title( "Sceleton Mode" );
		ToolbarContentRadioParams * params2 = new ToolbarContentRadioParams( title, on_sceleton_mode, &drawingContent, NULL, true );
		ToolbarContentItem * item2 = new ToolbarContentRadio( *params2 );

		toolbar.addToolbarContentItem( *item2 );

		title = "Run simulation";
		ToolbarContentRadioParams * params3 = new ToolbarContentRadioParams( title, on_run_simulation, &drawingContent, item2->getEvas(), false );
		ToolbarContentItem * item3 = new ToolbarContentRadio( *params3 );

		toolbar.addToolbarContentItem( *item3 );
	}
	{
		string title( "Test objects" );
		ToolbarContentButtonParams * params = new ToolbarContentButtonParams( title, on_construct_test_objects, &drawingContent );
		ToolbarContentItem * item = new ToolbarContentButton( *params );

		toolbar.addToolbarContentItem( *item );
	}
	{
		string title( "Clear" );
		ToolbarContentButtonParams * params = new ToolbarContentButtonParams( title, on_clear_objects, &drawingContent );
		ToolbarContentItem * item = new ToolbarContentButton( *params );

		toolbar.addToolbarContentItem( *item );
	}

	GeometrySceletonOperationTracking geoSceletonObjectTracking( drawingContent );
	SimulationOperationTracking   geoEditingObjectTracking( drawingContent );

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
