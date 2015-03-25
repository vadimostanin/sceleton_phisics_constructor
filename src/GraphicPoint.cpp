/*
 * GraphicsPoint.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: vostanin
 */

#include "GraphicPoint.h"
#include <Evas.h>
#include <GL/gl.h>
#include <iostream>
#include <fstream>
using namespace std;

static void dump( vector<float> & input, int split_count )
{
	ofstream file( "dump.txt", ios_base::app );

	for( size_t input_i = 0 ; input_i < input.size() ; input_i++ )
	{
		if( input_i != 0 && input_i % split_count == 0 )
		{
			file << endl << flush;
		}
		file << input[input_i] << " " << flush;
	}
	file << endl;
	file.close();
}

void GraphicPoint::initVertex()
{
	initCircleVertex();
}

GraphicPoint::GraphicPoint( IGeometryObject * geometryObject, Evas_Object * glview ) : GraphicObjectBase( glview )
{
	initVertex();
	initShaders();

	m_Point = (Point&)( * geometryObject );
}

GraphicPoint::GraphicPoint( Evas_Object * glview, const Point & point ) : GraphicObjectBase( glview ), m_Point( point )
{
	initVertex();
	initShaders();
}

GraphicPoint::GraphicPoint( Evas_Object * glview, int x, int y ) : GraphicObjectBase( glview )//GraphicPoint( glview, Point( x, y ) )//delegating constructors only available with -std=c++11 or -std=gnu++11 [enabled by default]
{
	m_Point.setX( x );
	m_Point.setY( y );

	initVertex();
	initShaders();
}

GraphicPoint::GraphicPoint( const GraphicPoint & src )
{
	initVertex();
	m_Point = src.m_Point;
}

GraphicPoint::~GraphicPoint()
{
}

IGeometryObject & GraphicPoint::getGeometryObject()
{
	return m_Point;
}

void GraphicPoint::initQuadVertex()
{
//	GLfloat vVertices[] = {//By Points
//			-0.5f,  0.5f,// 0.0f,
//			 0.5f,  0.5f,// 0.0f,
//			 0.5f, -0.5f,// 0.0f,
//			-0.5f, -0.5f,// 0.0f,
//	};

//	GLfloat vVertices[] = {//By Lines 3D
//				-0.05f,  0.05f, 0.0f,      0.05f,  0.05f, 0.0f,
//				 0.05f,  0.05f, 0.0f,      0.05f, -0.05f, 0.0f,
//				 0.05f, -0.05f, 0.0f,     -0.05f, -0.05f, 0.0f,
//				-0.05f, -0.05f, 0.0f,     -0.05f,  0.05f, 0.0f
//		};

	GLfloat vVertices[] = {//By Lines 2D
				-1.0f,  1.0f,      1.0f,  1.0f,
				 1.0f,  1.0f,      1.0f, -1.0f,
				 1.0f, -1.0f,     -1.0f, -1.0f,
				-1.0f, -1.0f,     -1.0f,  1.0f,
				-1.0f,  1.0f,
		};

//	GLfloat vVertices[] = {//By Triangles
//			// Left bottom triangle
//			-0.05f,  0.05f, 0.0f,
//			-0.05f, -0.05f, 0.0f,
//			 0.05f, -0.05f, 0.0f,
//			// Right top triangle
//			 0.05f, -0.05f, 0.0f,
//			 0.05f,  0.05f, 0.0f,
//			-0.05f,  0.05f, 0.0f
//	};

	m_vertexBuffer.assign( vVertices, vVertices + sizeof( vVertices )/ sizeof( vVertices[0]) );
}

void GraphicPoint::initCircleVertex()
{
	int vertexNumber = 300;

	float ang = 0;
	float da = (float) (M_PI / 180 * (360.0f / vertexNumber));
	const unsigned int coordinates_in_point = 2;


	{//Circle Points
		for(double v_i = 0; v_i < vertexNumber; v_i += 1)
		{
			float fsin = sin( ang );
			float fcos = cos( ang );
			if( v_i == 149 )
			{
				int a = 0;
				a++;
			}
			m_vertexBuffer.push_back( fcos );
			m_vertexBuffer.push_back( fsin );
	//		m_vertexBuffer.push_back( 0.0 );

			ang += da;
		}
	}
}

// Initialize the shader and program object
int GraphicPoint::initShaders()
{
	Evas_GL_API * __evas_gl_glapi = m_glApi;
   GLbyte vShaderStr[] =
		"attribute vec2 vPosition;\n"
	    "uniform mat4 perspective;\n"
		"uniform mat4 translate;\n"
		"uniform mat4 scale;\n"
		"void main()\n"
		"{\n"
	    "   gl_Position = perspective * translate * scale * vec4( vPosition.x, vPosition.y, 0.0, 1.0 );\n"
		"}\n";

   GLbyte fShaderStr[] =
		   "precision mediump float;                     \n"
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

   __evas_gl_glapi->glLinkProgram( m_Program );
   __evas_gl_glapi->glGetProgramiv( m_Program, GL_LINK_STATUS, &linked );

	if( 0 == linked )
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


	m_positionIdx = 	__evas_gl_glapi->glGetAttribLocation( m_Program, "vPosition" );
	m_perspective_idx = __evas_gl_glapi->glGetUniformLocation( m_Program, "perspective" );
	m_translate_idx = 	__evas_gl_glapi->glGetUniformLocation( m_Program, "translate" );
	m_scale_idx = 		__evas_gl_glapi->glGetUniformLocation( m_Program, "scale" );

//	__evas_gl_glapi->glGenBuffers( 1, &m_vertexesBufferObject );

	return 1;
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

void dump_mat4( float mat4[16] )
{
	for( int mat_i = 0 ; mat_i < 16 ; mat_i += 4 )
	{
		cout << mat4[mat_i] << " " << mat4[mat_i + 1] << " " << mat4[mat_i + 2] << " " << mat4[mat_i + 3] << endl << flush;
	}
}

void dump_short_mat4( float mat4[16] )
{
	cout << mat4[0] << " " << mat4[5] << " " << mat4[10] << " " << mat4[15] << endl << flush;
}

void GraphicPoint::draw_circle_2d()
{
	Evas_GL_API * __evas_gl_glapi = m_glApi;

	const int coordinates_in_point = 2;
	int x = getX();
	int y = getY();
	float translate_x =  ( x - m_DrawCanvasWidth / 2.0 );
	translate_x  /= (float)( m_DrawCanvasWidth / 2 );
	float translate_y = ( m_DrawCanvasHeight / 2.0 - y + 60 );
	translate_y /=  (float)( m_DrawCanvasHeight / 2 );

	float dimension = m_DrawCanvasWidth / (float)m_DrawCanvasHeight;

	GLfloat offset_x = translate_x;
	GLfloat offset_y = translate_y;

	GLfloat translateMatrix[16];
	GLfloat scaleMatrix[16];

	GLfloat perspective[16];
	init_matrix( perspective );
	init_matrix( translateMatrix );
	init_matrix( scaleMatrix );

	translate_xyz( translateMatrix, offset_x, offset_y, 0.0f );
	scale_xyz( scaleMatrix, 0.025 / dimension, 0.025, 1.0 );

	size_t vertixesCount = m_vertexBuffer.size() / coordinates_in_point;

	__evas_gl_glapi->glUseProgram( m_Program );

//	__evas_gl_glapi->glVertexAttribPointer( 0, coordinates_in_point, GL_FLOAT, GL_FALSE, 0, 0 );
//
//	__evas_gl_glapi->glBufferData( GL_ARRAY_BUFFER, vertixesCount * coordinates_in_point * sizeof( GLfloat ), &m_vertexBuffer[0], GL_STATIC_DRAW );
//
//	__evas_gl_glapi->glBindBuffer( GL_ARRAY_BUFFER, m_vertexesBufferObject );

	__evas_gl_glapi->glEnableVertexAttribArray( m_positionIdx );

	__evas_gl_glapi->glVertexAttribPointer( m_positionIdx, coordinates_in_point, GL_FLOAT, GL_FALSE, coordinates_in_point * sizeof(GLfloat), &m_vertexBuffer[0] );

	__evas_gl_glapi->glUniformMatrix4fv( m_perspective_idx, 1, GL_FALSE, perspective );
	__evas_gl_glapi->glUniformMatrix4fv( m_translate_idx, 1, GL_FALSE, translateMatrix );
	__evas_gl_glapi->glUniformMatrix4fv( m_scale_idx, 1, GL_FALSE, scaleMatrix );

	__evas_gl_glapi->glDrawArrays( GL_TRIANGLE_FAN, 0, vertixesCount );

	__evas_gl_glapi->glDisableVertexAttribArray( m_positionIdx );

	__evas_gl_glapi->glUseProgram( 0 );
}

void GraphicPoint::draw( Evas * canvas )
{
	draw_circle_2d();
}








