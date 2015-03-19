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
#include "GeometryOperationTracking.h"
#include <ctime>
#include <stdlib.h>

EAPI_MAIN int elm_main(int argc, char **argv)
{
	Window window;
	WindowListener windowListener;

	window.create();

	window.setListener( &windowListener );

	MainContent mainContent( window.getEvasObject() );

	window.setContentLayout( mainContent.getLayout() );

	ToolbarContent toolbar( mainContent.getLayout() );
	DrawingContent drawingContent( window.getEvasObject(), mainContent.getLayout() );

	GeometryOperationTracking geoObjectTracking( drawingContent );

	MouseListener mouseListener( geoObjectTracking, drawingContent.getDrawingCanvas() );

	window.setMaxSize( 800, 600 );

	srand( time ( 0 ) );

	elm_run();
	return 0;
}
ELM_MAIN()
