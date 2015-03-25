/*
 * GraphicLink.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: vostanin
 */

#include <iostream>
#include <Evas_GL.h>
#include "GraphicLink.h"
using namespace std;

GraphicLink::GraphicLink( IGeometryObject * geometryObject, Evas_Object * glview ) : GraphicObjectBase( glview )
{
	initShaders();

	m_geometryLink = *geometryObject;
}

GraphicLink::GraphicLink( const GraphicLink & src )
{
	m_geometryLink = src.m_geometryLink;
	m_perspective_idx = src.m_perspective_idx;
	m_translate_idx = src.m_translate_idx;
	m_scale_idx = src.m_scale_idx;
}

GraphicLink::GraphicLink( const GeometryLink & src )
{
	initShaders();

	m_geometryLink = src;
}

GraphicLink & GraphicLink::operator = ( const GeometryLink & src )
{
	m_geometryLink = src;

	return *this;
}

GraphicLink::~GraphicLink()
{
}

void GraphicLink::draw( Evas * canvas )
{
//	cout << "draw link from:" << getPointFrom().getX() << "x" << getPointFrom().getY() << "; to:" <<
//						getPointTo().getX() << "x" << getPointTo().getY() << endl << flush;

	initLineVertexes();

	draw_line_2d();
}

IGeometryObject & GraphicLink::getGeometryObject()
{
	return m_geometryLink;
}

void GraphicLink::initLineVertexes()
{
	m_vertexBuffer.clear();
	{
		int x = m_geometryLink.getPointFrom().getX();
		int y = m_geometryLink.getPointFrom().getY();

		int width =  m_DrawCanvasWidth;
		int height = m_DrawCanvasHeight;

		float translate_x =  ( x - width/  2.0 );
		translate_x  /= (float)( width / 2 );
		float translate_y = ( height / 2.0 - y + 60 );
		translate_y /=  (float)( height / 2 );

		m_vertexBuffer.push_back( translate_x );
		m_vertexBuffer.push_back( translate_y );
//		m_vertexBuffer.push_back( 0.0 );
	}

	{
		int x = m_geometryLink.getPointTo().getX();
		int y = m_geometryLink.getPointTo().getY();

		int width =  m_DrawCanvasWidth;
		int height = m_DrawCanvasHeight;

		float translate_x =  ( x - width /  2.0 );
		translate_x  /= (float)( width / 2 );
		float translate_y = ( height / 2.0 - y + 60 );
		translate_y /=  (float)( height / 2 );

		m_vertexBuffer.push_back( translate_x );
		m_vertexBuffer.push_back( translate_y );
//		m_vertexBuffer.push_back( 0.0 );
	}
}

#define SHADER(shader) #shader

// Initialize the shader and program object
int GraphicLink::initShaders()
{
	Evas_GL_API * __evas_gl_glapi = m_glApi;
	GLbyte vShaderStr[] = SHADER(
		attribute vec3 vPosition;
		uniform mat4 perspective;
		uniform mat4 translate;
		uniform mat4 scale;
		void main()
		{
		   gl_Position = perspective * translate * scale * vec4( vPosition, 1.0 );
		}
		);

	GLbyte fShaderStr[] = SHADER(void main()\n
								{\n
									gl_FragColor = vec4( 0.5, 0.5, 1.0, 1.0 );\n
								}\n
		   );

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

	return 1;
}

void GraphicLink::draw_line_2d()
{
	Evas_GL_API * __evas_gl_glapi = m_glApi;

	int x = m_geometryLink.getPointFrom().getX();
	int y = m_geometryLink.getPointFrom().getY();

	float dimension = (float) m_DrawCanvasWidth / (float) m_DrawCanvasHeight;

	float translate_x =  ( x - m_DrawCanvasWidth / 2.0 );
	translate_x  /= (float)( m_DrawCanvasWidth / 2 );
	float translate_y = ( m_DrawCanvasHeight / 2.0 - y + 60 );
	translate_y /=  (float)( m_DrawCanvasHeight / 2 );

	GLfloat translateMatrix[16];
	GLfloat scaleMatrix[16];

	GLfloat perspective[16];
	init_matrix( perspective );
	init_matrix( translateMatrix );
	init_matrix( scaleMatrix );

	scale_xyz( scaleMatrix, 1.0, 1.0, 1.0 );

	const int coordinates_in_point = 2;

	size_t vertixesCount = m_vertexBuffer.size() / coordinates_in_point;

	__evas_gl_glapi->glUseProgram( m_Program );

	__evas_gl_glapi->glEnableVertexAttribArray( m_positionIdx );

	__evas_gl_glapi->glVertexAttribPointer( m_positionIdx, coordinates_in_point, GL_FLOAT, GL_FALSE, coordinates_in_point * sizeof(GLfloat), &m_vertexBuffer[0] );

	const int matrixCount = 1;

	__evas_gl_glapi->glUniformMatrix4fv( m_perspective_idx, matrixCount, GL_FALSE, perspective );
	__evas_gl_glapi->glUniformMatrix4fv( m_translate_idx, matrixCount, GL_FALSE, translateMatrix );
	__evas_gl_glapi->glUniformMatrix4fv( m_scale_idx, matrixCount, GL_FALSE, scaleMatrix );

	__evas_gl_glapi->glDrawArrays( GL_LINES, 0, vertixesCount );

	__evas_gl_glapi->glDisableVertexAttribArray( m_positionIdx );

	__evas_gl_glapi->glUseProgram( 0 );
}










