/*
 * DrawingContent.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "Window.h"
#include "DrawingContent.h"
#include "GeometryObjectsManager.h"
#include "DynamicTimeLineManager.h"
#include "GraphicObjectFindPredicate.h"
#include <Elementary.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <png++/png.hpp>
#include <png++/types.hpp>
using namespace std;

#define MAIN_EDJ "./main.edj"

DrawingContent * lpThis = 0;

DrawingContent::DrawingContent( Evas_Object *mainWindowObject, Evas_Object *mainLayout ) : m_MainLayout( mainLayout ), m_MainWindowObject( mainWindowObject ),
		m_DynamicTimer( DynamicDrawTimer, this, 0.1 ), m_DrawDynamic( false )
{
	createDrawingLayout();
	createDrawingCanvas();
	lpThis = this;
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

void DrawingContent::on_init_gles( Evas_Object * glview )
{
   Evas_GL_API * __evas_gl_glapi = elm_glview_gl_api_get( glview );

   __evas_gl_glapi->glClearColor( 0.0, 0.0, 0.0, 1.0 );

   __evas_gl_glapi->glEnable( GL_CULL_FACE );
   __evas_gl_glapi->glEnable( GL_POINT_SMOOTH );
   __evas_gl_glapi->glLineWidth( 4.0f );
   __evas_gl_glapi->glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
   __evas_gl_glapi->glEnable( GL_BLEND );
   __evas_gl_glapi->glEnable( GL_LINE_SMOOTH );
   __evas_gl_glapi->glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
   __evas_gl_glapi->glCullFace( GL_BACK );
//
   __evas_gl_glapi->glEnable( GL_DEPTH_TEST );
   __evas_gl_glapi->glDepthFunc( GL_EQUAL );
   __evas_gl_glapi->glEnable( GL_MULTISAMPLE );

    __evas_gl_glapi->glEnable( GL_TEXTURE_2D );.

   lpThis->initCanvasBackground();
}

// resize callback gets called every time object is resized
void DrawingContent::on_resize_gl( Evas_Object * glview )
{
	DrawingContent * lpThis = ( DrawingContent * )evas_object_data_get( glview, "DrawingContent");

	Evas_GL_API * __evas_gl_glapi = lpThis->m_glApi;

	elm_glview_size_get( glview, &lpThis->m_CanvasWidth, &lpThis->m_CanvasHeight );

	// GL Viewport stuff. you can avoid doing this if viewport is all the
	// same as last frame if you want
	__evas_gl_glapi->glViewport( 0, 0, lpThis->m_CanvasWidth, lpThis->m_CanvasHeight );
}

// draw callback is where all the main GL rendering happens
void DrawingContent::on_draw_gl( Evas_Object * glview )
{
	DrawingContent * lpThis = ( DrawingContent * )evas_object_data_get( glview, "DrawingContent");

	lpThis->preDraw();

   lpThis->drawCanvasBackground();

	lpThis->drawObjects();

	lpThis->postDraw();
}

bool DrawingContent::DynamicDrawTimer( void * userData )
{
	DrawingContent * lpThis = ( DrawingContent * )userData;

		elm_glview_changed_set( (Elm_Glview *)lpThis->getDrawingCanvas() );

	return true;
}

void DrawingContent::preDraw()
{
	 m_glApi ->glClearColor( 1.0, 0.8, 0.3, 1 );
	 m_glApi ->glClear(GL_COLOR_BUFFER_BIT);
}

void DrawingContent::postDraw()
{
   // Optional - Flush the GL pipeline
	 m_glApi->glFinish();
}
void DrawingContent::createDrawingCanvas()
{
	Evas_Object * glview = elm_glview_version_add( m_DrawingLayout, EVAS_GL_GLES_2_X );

	elm_object_part_content_set( m_DrawingLayout, "drawing_canvas", glview );

	evas_object_size_hint_align_set( glview, EVAS_HINT_FILL, EVAS_HINT_FILL );
	evas_object_size_hint_weight_set( glview, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND );

	elm_glview_mode_set( glview, (Elm_GLView_Mode)( ELM_GLVIEW_ALPHA/* | ELM_GLVIEW_DEPTH *//*cause problem when rendering, leave empty peaces*/ ) );

	elm_glview_resize_policy_set( glview, ELM_GLVIEW_RESIZE_POLICY_RECREATE );
	elm_glview_render_policy_set( glview, ELM_GLVIEW_RENDER_POLICY_ON_DEMAND );

	elm_glview_init_func_set( glview, on_init_gles );
	elm_glview_resize_func_set( glview, on_resize_gl );

	elm_glview_render_func_set( glview, on_draw_gl );

	elm_object_focus_set( glview, EINA_TRUE);

	evas_object_show( glview );

	m_DrawingCanvas = glview;
	m_glApi = elm_glview_gl_api_get( m_DrawingCanvas );
	evas_object_data_set( glview, "DrawingContent", this );

	elm_glview_size_get( glview, &m_CanvasWidth, &m_CanvasHeight );
}

Evas_Object * DrawingContent::getDrawingCanvas()
{
	return m_DrawingCanvas;
}

void DrawingContent::update()
{
	elm_glview_changed_set( (Elm_Glview *)m_DrawingCanvas );
}

void DrawingContent::setGraphicObjects( vector<IGraphicObject *> & graphicObjects )
{
	clearObjects();

	m_GraphicObjects = graphicObjects;

   m_DynamicTimer.stop();
   m_DrawDynamic = false;

	elm_glview_render_func_set( getDrawingCanvas(), on_draw_gl );
	update();
}

void DrawingContent::setGraphicDynamicObjects( vector<IGraphicObject *> & graphicObjects )
{
	m_DrawDynamic = true;

  	m_DynamicTimer.start();

	setGraphicObjects( graphicObjects );
}

void DrawingContent::addGraphicObject( IGraphicObject * graphicObject )
{
	if( NULL == graphicObject )
	{
		return;
	}
	m_GraphicObjects.push_back( graphicObject );

	update();
}

void DrawingContent::deleteGraphicObject( IGraphicObject * graphicObject )
{
	GraphicObjectFindPredicate predicate( graphicObject );
	vector<IGraphicObject *>::iterator foundIter = find_if( m_GraphicObjects.begin(), m_GraphicObjects.end(), predicate );
	if( foundIter == m_GraphicObjects.end() )
	{
		return;
	}
	delete (*foundIter);
	m_GraphicObjects.erase( foundIter );

	update();
}

void DrawingContent::changeGraphicObject( IGraphicObject * graphicObject )
{
	GraphicObjectFindPredicate predicate( graphicObject );
	vector<IGraphicObject *>::iterator foundIter = find_if( m_GraphicObjects.begin(), m_GraphicObjects.end(), predicate );
	if( foundIter != m_GraphicObjects.end() )
	{
		delete (*foundIter);
		m_GraphicObjects.erase( foundIter );
	}
	m_GraphicObjects.push_back( graphicObject );

	update();
}

void DrawingContent::drawObjects()
{
	if( true == m_DrawDynamic )
	{
		DynamicTimeLineManager::getInstance().stepSpace();
	}
	vector<IGraphicObject *>::iterator begin = m_GraphicObjects.begin();
	vector<IGraphicObject *>::iterator end = m_GraphicObjects.end();
	vector<IGraphicObject *>::iterator iter = begin;
	for( ; iter != end ; iter++ )
	{
		(*iter)->draw();
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
	m_GraphicObjects.clear();
}

unsigned int DrawingContent::getCanvasWidth() const
{
	return m_CanvasWidth;
}

unsigned int DrawingContent::getCanvasHeight() const
{
	return m_CanvasHeight;
}

// a helper function to load shaders from a shader source
GLuint DrawingContent::loadShader( GLenum type, const char *shader_src )
{
	GLuint shader;
	GLint compiled;

	// Create the shader object
	shader = m_glApi->glCreateShader(type);
	if( shader == 0 )
	{
		return 0;
	}

	// Load/Compile shader source
	m_glApi->glShaderSource(shader, 1, &shader_src, NULL);
	m_glApi->glCompileShader(shader);
	m_glApi->glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		GLint info_len = 0;
		m_glApi->glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);
		if (info_len > 1)
		{
			char* info_log = (char *)malloc(sizeof(char) * info_len);

			m_glApi->glGetShaderInfoLog(shader, info_len, NULL, info_log);
			printf("Error compiling shader:\n%s\n======\n%s\n======\n", info_log, shader_src );
			free(info_log);
		}
		m_glApi->glDeleteShader(shader);
		return 0;
	}

	return shader;
}

string DrawingContent::getVertexShader()
{
	string shader = SHADER(
\n
							attribute vec2 vPosition;\n
							attribute vec2 textureCoords;\n
\n
							varying vec2 textureCoordinates;\n
\n
							void main()\n
							{\n
							   gl_Position = vec4( vPosition, 0.0, 1.0 );\n
							   textureCoordinates = textureCoords;\n
							}\n
\n
						);

	return shader;
}

string DrawingContent::getFragmentShader()
{
	string shader =	SHADER(
							varying vec2 textureCoordinates;\n
							uniform sampler2D textureIndex;\n
\n
							void main()\n
							{\n
								gl_FragColor = vec4( 1.0, 0.5, 0.5, 1.0 );//texture2D( textureIndex, textureCoordinates );\n
							}\n
\n
						);

	return shader;
}

// Initialize the shader and program object
int DrawingContent::initShaders()
{
	string v_shader = getVertexShader();
	GLbyte * vShaderStr = (GLbyte *)v_shader.c_str();

	string f_shader = getFragmentShader();
	GLbyte * fShaderStr = (GLbyte *)f_shader.c_str();

	GLint linked;

	// Load the vertex/fragment shaders
	m_vertexShader  = loadShader( GL_VERTEX_SHADER, (const char*)vShaderStr);
	m_fragmentShader = loadShader( GL_FRAGMENT_SHADER, (const char*)fShaderStr);

	// Create the program object
	m_Program = m_glApi->glCreateProgram( );
	if( m_Program == 0 )
	{
		return 0;
	}

	m_glApi->glAttachShader( m_Program,  m_vertexShader);
	m_glApi->glAttachShader( m_Program,  m_fragmentShader);

	m_glApi->glLinkProgram( m_Program );
	m_glApi->glGetProgramiv( m_Program, GL_LINK_STATUS, &linked );

	if( 0 == linked )
	{
		GLint info_len = 0;
		m_glApi->glGetProgramiv( m_Program, GL_INFO_LOG_LENGTH, &info_len);
		if (info_len > 1)
		{
			char* info_log = (char *)malloc(sizeof(char) * info_len);

			m_glApi->glGetProgramInfoLog( m_Program, info_len, NULL, info_log );
			printf( "Error linking program:\n%s\n", info_log );
			free( info_log );
		}
		m_glApi->glDeleteProgram( m_Program );
		return 0;
	}

	return 1;
}

float textures[] = {
//   Texcoords
    0.0f, 0.0f, // Top-left
    1.0f, 0.0f, // Top-right
    1.0f, 1.0f, // Bottom-right
    0.0f, 1.0f  // Bottom-left
};

float vertices[] = {
//    Position
    -1.0f,  1.0f, // Top-left
	 1.0f,  1.0f, // Top-right
	 1.0f, -1.0f, // Bottom-right
    -1.0f, -1.0f,  // Bottom-left
	-1.0f,  1.0f // Top-left
};

//float vertices[] = {
////    Position    Texcoords
//		-0.5f,  0.5f, 0.0f, 0.0f, // Top-left
//		 0.5f,  0.5f, 1.0f, 0.0f, // Top-right
//		 0.5f, -0.5f, 1.0f, 1.0f, // Bottom-right
//		-0.5f, -0.5f, 0.0f, 1.0f  // Bottom-left
//};

GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };

void DrawingContent::initCanvasBackground()
{
	initShaders();

	m_glApi->glUseProgram( m_Program );

	m_positionIdx 		= 	m_glApi->glGetAttribLocation( m_Program, "vPosition" );
	m_textureCoordsIdx 	=   m_glApi->glGetAttribLocation( m_Program, "textureCoords" );
	GLint info_len = 0;
			m_glApi->glGetProgramiv( m_Program, GL_INFO_LOG_LENGTH, &info_len);
			if (info_len > 1)
			{
				char* info_log = (char *)malloc(sizeof(char) * info_len);

				m_glApi->glGetProgramInfoLog( m_Program, info_len, NULL, info_log );
				printf( "Error linking program:\n%s\n", info_log );
				free( info_log );
			}
	m_fragmentUniformTextureIdx = m_glApi->glGetUniformLocation( m_Program, "textureIndex" );

	string filename( "images/background_1.png" );
	loadPng( filename, m_rgbRawData, m_BackgroundWidth, m_BackgroundHeight );


	m_glApi->glGenTextures( 1, &m_textureIdx );
}

void DrawingContent::drawCanvasBackground()
{

	// Create a Vertex Buffer Object and copy the vertex data to it
//	GLuint vbo;
//	m_glApi->glGenBuffers( 1, &vbo );
//
//	m_glApi->glBindBuffer( GL_ARRAY_BUFFER, vbo );
//	m_glApi->glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
//
////	 Create an element array
//	GLuint ebo;
//	m_glApi->glGenBuffers( 1, &ebo );
//
//	m_glApi->glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
//	m_glApi->glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW );

	const int coordinates_in_point = 2;

//	m_glApi->glEnableVertexAttribArray( m_positionIdx );
//	m_glApi->glVertexAttribPointer( m_positionIdx, coordinates_in_point, GL_FLOAT, GL_FALSE, 4 * sizeof( GLfloat ), 0 );
//
//	m_glApi->glEnableVertexAttribArray( m_textureCoordsIdx );
//	m_glApi->glVertexAttribPointer( m_textureCoordsIdx, coordinates_in_point, GL_FLOAT, GL_FALSE, coordinates_in_point * sizeof( GLfloat ), ( void * )( 2 * sizeof( GLfloat ) ) );

	m_glApi->glUseProgram( m_Program );

	m_glApi->glEnableVertexAttribArray( m_positionIdx );
	m_glApi->glVertexAttribPointer( m_positionIdx, coordinates_in_point, GL_FLOAT, GL_FALSE, coordinates_in_point * sizeof(GLfloat), &vertices[0] );

	m_glApi->glEnableVertexAttribArray( m_textureCoordsIdx );
	m_glApi->glVertexAttribPointer( m_textureCoordsIdx, coordinates_in_point, GL_FLOAT, GL_FALSE, coordinates_in_point * sizeof( GLfloat ), &textures[0] );

	m_glApi->glActiveTexture( GL_TEXTURE0 );
	m_glApi->glBindTexture( GL_TEXTURE_2D, m_textureIdx );

	m_glApi->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	m_glApi->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	m_glApi->glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, m_BackgroundWidth, m_BackgroundHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, &m_rgbRawData[0] );

	m_glApi->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	m_glApi->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	m_glApi->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	m_glApi->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	m_glApi->glUniform1i( m_fragmentUniformTextureIdx, m_textureIdx );

	// Draw a rectangle from the 2 triangles using 6 indices
//	m_glApi->glDrawElements( GL_TRIANGLES, 4, GL_UNSIGNED_INT, 0 );

	m_glApi->glDrawArrays( GL_TRIANGLE_STRIP, 0, 5 );
//	m_glApi->glDrawArrays( GL_TRIANGLES, 1, 3 );

	m_glApi->glDisableVertexAttribArray( m_positionIdx );

	m_glApi->glDisableVertexAttribArray( m_textureCoordsIdx );

	m_glApi->glUseProgram( 0 );
}

void DrawingContent::loadPng( string & filename, vector<unsigned char> & rgbRawData, int & width, int & height )
{
	ifstream png_file( filename.c_str() );
	rgbRawData.clear();
	if( false == png_file.is_open() )
	{
		return;
	}
	png::reader<ifstream> reader(png_file);
	reader.read_info();
	height = reader.get_height();
	width = reader.get_width();

	const int colors_in_rgb = 3;

	rgbRawData.resize( height * width * colors_in_rgb, 0.0 );

	for( int row_i = 0 ; row_i < height ; row_i++ )
	{
		reader.read_row( &rgbRawData[0] + sizeof(png::byte) * ( row_i * width * colors_in_rgb ) );
	}
}








