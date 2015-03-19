/*
 * GraphicsPoint.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: vostanin
 */

#include "GraphicPoint.h"
#include <Evas.h>
#include <Elementary.h>
#include <iostream>
using namespace std;

GraphicPoint::GraphicPoint( Evas_Object * glview )
{
	m_glApi = elm_glview_gl_api_get( glview );
	initCircleVertex();
	initShaders();
}

GraphicPoint::GraphicPoint( Evas_Object * glview, const Point & point ) : m_Point( point ), m_vertexesBufferObject( 0 ), m_Program( 0 )
{
	m_glApi = elm_glview_gl_api_get( glview );

	initCircleVertex();
	initShaders();
}

GraphicPoint::GraphicPoint( Evas_Object * glview, int x, int y ) : m_vertexesBufferObject( 0 ), m_Program( 0 ), m_vertexShader( 0 ), m_fragmentShader( 0 )//GraphicPoint( glview, Point( x, y ) )//delegating constructors only available with -std=c++11 or -std=gnu++11 [enabled by default]
{
	m_Point.setX( x );
	m_Point.setY( y );
	m_glApi = elm_glview_gl_api_get( glview );

	initCircleVertex();
	initShaders();
}

GraphicPoint::GraphicPoint( const GraphicPoint & src )
{
	m_Point = src.m_Point;
	m_vertexBuffer = src.m_vertexBuffer;
	m_vertexesBufferObject = src.m_vertexesBufferObject;
	m_glApi = src.m_glApi;
	m_Program = src.m_Program;
	m_vertexShader = src.m_vertexShader;
	m_fragmentShader = src.m_fragmentShader;
}

GraphicPoint::~GraphicPoint()
{
	m_glApi->glDeleteBuffers( 1, &m_vertexesBufferObject );
	m_glApi->glDeleteShader( m_vertexShader );
	m_glApi->glDeleteShader( m_fragmentShader );
}

void GraphicPoint::initCircleVertex()
{
	Evas_GL_API * __evas_gl_glapi = m_glApi;

	int vertexNumber = 300;

	float ang = 0;
	float da = (float) (M_PI / 180 * (360.0f / vertexNumber));
	const unsigned int coordinates_in_point = 3;


   //	for(double d = 0; d <= 2 * 3.14; d += 0.01)
	for(double v_i = 0; v_i < vertexNumber; v_i += 1)
	{
		m_vertexBuffer.push_back( cos( ang ) / 50 );
		m_vertexBuffer.push_back( sin( ang ) / 50 );
		m_vertexBuffer.push_back( 0 );

		ang += da;
	}
	m_vertexBuffer.push_back( (float)cos( 0 ) );  // X
	m_vertexBuffer.push_back( (float)sin( 0 ) ); // Y
	m_vertexBuffer.push_back( 0 );                  // Z

	__evas_gl_glapi->glGenBuffers( 1, &m_vertexesBufferObject );
	__evas_gl_glapi->glBindBuffer( GL_ARRAY_BUFFER, m_vertexesBufferObject );
	__evas_gl_glapi->glBufferData( GL_ARRAY_BUFFER, vertexNumber * coordinates_in_point * sizeof(GLfloat), &m_vertexBuffer[0], GL_DYNAMIC_DRAW );
}

// Initialize the shader and program object
int GraphicPoint::initShaders()
{
	Evas_GL_API * __evas_gl_glapi = m_glApi;
   GLbyte vShaderStr[] =
      "attribute vec4 vPosition;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = vPosition;\n"
      "}\n";

   GLbyte fShaderStr[] =
      //"#ifdef GL_ES                                 \n"
      //"precision mediump float;                     \n"
      //"#endif                                       \n"
      "void main()\n"
      "{\n"
      "  gl_FragColor = vec4 ( 0.5, 0.5, 1.0, 1.0 );\n"
      "}\n";

   GLint linked;

   // Load the vertex/fragment shaders
   m_vertexShader  = loadShader( GL_VERTEX_SHADER, (const char*)vShaderStr);
   m_fragmentShader = loadShader( GL_FRAGMENT_SHADER, (const char*)fShaderStr);

   // Create the program object
   m_Program = __evas_gl_glapi->glCreateProgram( );
   if( m_Program == 0 )
   {
	   return 0;
   }

   __evas_gl_glapi->glAttachShader( m_Program,  m_vertexShader);
   __evas_gl_glapi->glAttachShader( m_Program,  m_fragmentShader);

   __evas_gl_glapi->glBindAttribLocation( m_Program, 0, "vPosition" );
   __evas_gl_glapi->glLinkProgram( m_Program );
   __evas_gl_glapi->glGetProgramiv( m_Program, GL_LINK_STATUS, &linked );

	if (!linked)
	{
		GLint info_len = 0;
		__evas_gl_glapi->glGetProgramiv( m_Program, GL_INFO_LOG_LENGTH, &info_len);
		if (info_len > 1)
		{
			char* info_log = (char *)malloc(sizeof(char) * info_len);

			__evas_gl_glapi->glGetProgramInfoLog( m_Program, info_len, NULL, info_log );
			printf( "Error linking program:\n%s\n", info_log );
			free( info_log );
		}
		__evas_gl_glapi->glDeleteProgram( m_Program );
		return 0;
	}
   return 1;
}

//--------------------------------//
// a helper function to load shaders from a shader source
GLuint GraphicPoint::loadShader( GLenum type, const char *shader_src )
{
	Evas_GL_API * __evas_gl_glapi = m_glApi;
	GLuint shader;
	GLint compiled;

	// Create the shader object
	shader = __evas_gl_glapi->glCreateShader(type);
	if( shader == 0 )
	{
		return 0;
	}

	// Load/Compile shader source
	__evas_gl_glapi->glShaderSource(shader, 1, &shader_src, NULL);
	__evas_gl_glapi->glCompileShader(shader);
	__evas_gl_glapi->glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		GLint info_len = 0;
		__evas_gl_glapi->glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);
		if (info_len > 1)
		{
			char* info_log = (char *)malloc(sizeof(char) * info_len);

			__evas_gl_glapi->glGetShaderInfoLog(shader, info_len, NULL, info_log);
			printf("Error compiling shader:\n%s\n======\n%s\n======\n", info_log, shader_src );
			free(info_log);
		}
		__evas_gl_glapi->glDeleteShader(shader);
		return 0;
	}

	return shader;
}

bool GraphicPoint::operator ==( const GraphicPoint & src )
{
	if( m_Point == src.m_Point )
	{
		return true;
	}
	return false;
}

int GraphicPoint::getX()
{
	return m_Point.getX();
}

int GraphicPoint::getY()
{
	return m_Point.getY();
}

void GraphicPoint::setX( int x )
{
	m_Point.setX( x );
}

void GraphicPoint::setY( int y )
{
	m_Point.setY( y );
}

void GraphicPoint::draw_triangle_2d()
{
	GLfloat vVertices[] = {
	        0.0f,  0.5f, 0.0f,
	        -0.5f, -0.5f, 0.0f,
	        0.5f, -0.5f, 0.0f };

	Evas_GL_API * __evas_gl_glapi = m_glApi;

	__evas_gl_glapi->glUseProgram( m_Program );

	__evas_gl_glapi->glGenBuffers( 1, &m_vertexesBufferObject );
	__evas_gl_glapi->glBindBuffer( GL_ARRAY_BUFFER, m_vertexesBufferObject );
	__evas_gl_glapi->glBufferData( GL_ARRAY_BUFFER, 3 * 3 * sizeof(float), vVertices, GL_STATIC_DRAW );


	__evas_gl_glapi->glBindBuffer( GL_ARRAY_BUFFER, m_vertexesBufferObject );
	__evas_gl_glapi->glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
	__evas_gl_glapi->glEnableVertexAttribArray( 0 );

	__evas_gl_glapi->glDrawArrays( GL_TRIANGLES, 0, 3 );


	__evas_gl_glapi->glDeleteBuffers( 1, &m_vertexesBufferObject );
}

void GraphicPoint::draw_quad_2d()
{
//	GLfloat vVertices[] = {//By Triangles
//			// Left bottom triangle
//			-0.5f, 0.5f, 0.0f,
//			-0.5f, -0.5f, 0.0f,
//			0.5f, -0.5f, 0.0f,
//			// Right top triangle
//			0.5f, -0.5f, 0.0f,
//			0.5f, 0.5f, 0.0f,
//			-0.5f, 0.5f, 0.0f
//	};

	GLfloat vVertices[] = {//By Lines
			     0.0f,  0.0f, 0.0f,//Zero
				-0.5f,  0.5f, 0.0f,//First line begin
				 0.5f,  0.5f, 0.0f,//First line end
				 0.5f,  0.5f, 0.0f,//Second line begin
				 0.5f, -0.5f, 0.0f,//Second line end
				 0.5f, -0.5f, 0.0f,//Third line begin
				-0.5f, -0.5f, 0.0f,//Third line end
				-0.5f, -0.5f, 0.0f,//Fourth line begin
				-0.5f,  0.5f, 0.0f//Fourth line end equal to First line begin
		};

	const unsigned int coordinates_in_point = 3;

	size_t vertices_count = sizeof( vVertices )/ sizeof( vVertices[0] ) / 3;

	Evas_GL_API * __evas_gl_glapi = m_glApi;

	__evas_gl_glapi->glGenBuffers( 1, &m_vertexesBufferObject );
	__evas_gl_glapi->glBindBuffer( GL_ARRAY_BUFFER, m_vertexesBufferObject );
	__evas_gl_glapi->glBufferData( GL_ARRAY_BUFFER, vertices_count * coordinates_in_point * sizeof(GLfloat), vVertices, GL_STATIC_DRAW );


	__evas_gl_glapi->glBindBuffer( GL_ARRAY_BUFFER, m_vertexesBufferObject );
	__evas_gl_glapi->glVertexAttribPointer( 0, coordinates_in_point, GL_FLOAT, GL_FALSE, 0, 0 );
	__evas_gl_glapi->glEnableVertexAttribArray( 0 );

	__evas_gl_glapi->glDrawArrays( GL_POINTS, 0, 1 );
	__evas_gl_glapi->glDrawArrays( GL_LINES, 1, vertices_count - 1 );


//	__evas_gl_glapi->glDeleteBuffers( 1, &vertexesBufferObject );
}

void GraphicPoint::draw_circle_2d()
{
	Evas_GL_API * __evas_gl_glapi = m_glApi;


	const int coordinates_in_point = 3;
	const int vertexNumber = 300;

	__evas_gl_glapi->glUseProgram( m_Program );

	__evas_gl_glapi->glBindBuffer( GL_ARRAY_BUFFER, m_vertexesBufferObject );
	__evas_gl_glapi->glVertexAttribPointer( 0, coordinates_in_point, GL_FLOAT, GL_FALSE, 0, 0 );
	__evas_gl_glapi->glEnableVertexAttribArray( 0 );

	__evas_gl_glapi->glDrawArrays( GL_TRIANGLE_FAN, 0, vertexNumber + 2 );
}

void GraphicPoint::draw( Evas * canvas )
{
//	cout << "point draw:"<< getX() << "x" << getY() << endl << flush;

	draw_circle_2d();
}








