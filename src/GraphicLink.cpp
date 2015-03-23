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

GraphicLink::GraphicLink( Evas_Object * glview ) : GraphicObjectBase( glview )
{
	initShaders();
}

GraphicLink::GraphicLink( const GraphicLink & src )
{
	GraphicLink & src1 = const_cast<GraphicLink &>( src );

	setPointFrom( src1.getPointFrom() );
	setPointTo( src1.getPointTo() );
}

//GraphicLink::GraphicLink( const GeometryLink src ) : m_Evas( 0 )
//{
//	setPointFrom( src.getPointFrom() );
//	setPointTo( src.getPointTo() );
//}

GraphicLink & GraphicLink::operator = ( GeometryLink & src )
{
	GeometryLink & src_unconst = const_cast<GeometryLink&>( src );

	setPointFrom( src_unconst.getPointFrom() );
	setPointTo( src_unconst.getPointTo() );

	return *this;
}

GraphicLink::~GraphicLink()
{
}

void GraphicLink::draw( Evas * canvas )
{
	cout << "draw link from:" << getPointFrom().getX() << "x" << getPointFrom().getY() << "; to:" <<
						getPointTo().getX() << "x" << getPointTo().getY() << endl << flush;

	initLineVertexes();

	draw_line_2d();
}

void GraphicLink::setPointFrom( Point & point )
{
	m_Points[0] = point;
}

void GraphicLink::setPointTo( Point & point )
{
	m_Points[1] = point;
}

Point & GraphicLink::getPointFrom()
{
	return m_Points[0];
}

Point & GraphicLink::getPointTo()
{
	return m_Points[1];
}

void GraphicLink::initLineVertexes()
{
	m_vertexBuffer.clear();
	{
		int x = getPointFrom().getX();
		int y = getPointFrom().getY();

		int width =  m_DrawCanvasWidth;
		int height = m_DrawCanvasHeight;

		float translate_x =  ( x - width/  2.0 );
		translate_x  /= (float)( width / 2 );
		float translate_y = ( height / 2.0 - y + 60 );
		translate_y /=  (float)( height / 2 );
		translate_y *= 1.45;
		translate_x *= 2.13;

		m_vertexBuffer.push_back( translate_x );
		m_vertexBuffer.push_back( translate_y );
		m_vertexBuffer.push_back( 0.0 );
	}

	{
		int x = getPointTo().getX();
		int y = getPointTo().getY();

		int width =  m_DrawCanvasWidth;
		int height = m_DrawCanvasHeight;

		float translate_x =  ( x - width /  2.0 );
		translate_x  /= (float)( width / 2 );
		float translate_y = ( height / 2.0 - y + 60 );
		translate_y /=  (float)( height / 2 );
		translate_y *= 1.45;
		translate_x *= 2.13;

		m_vertexBuffer.push_back( translate_x );
		m_vertexBuffer.push_back( translate_y );
		m_vertexBuffer.push_back( 0.0 );
	}
}

// Initialize the shader and program object
int GraphicLink::initShaders()
{
	Evas_GL_API * __evas_gl_glapi = m_glApi;
	GLbyte vShaderStr[] =
		"attribute vec3 vPosition;\n"
		"uniform mat4 u_mvpMatrix;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = u_mvpMatrix * vec4( vPosition, 1.0 );\n"
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

	GLint vPositionLocation = __evas_gl_glapi->glGetAttribLocation( m_Program, "vPosition" );
	m_positionIdx = vPositionLocation;

	m_mvpMatrixIdx = __evas_gl_glapi->glGetUniformLocation( m_Program, "u_mvpMatrix");

	return 1;
}

void GraphicLink::draw_line_2d()
{
	Evas_GL_API * __evas_gl_glapi = m_glApi;

	float model[16], mvpMatrix[16];

	init_matrix(model);

	int w = m_DrawCanvasWidth;
	int h = m_DrawCanvasHeight;

	int x = getPointFrom().getX();
	int y = getPointFrom().getY();

	float aspect = (float) w / (float) h;

	float translate_x =  ( x - w/2.0 );
	translate_x  /= (float)( w/2 );
	float translate_y = ( h/2.0 - y + 60 );
	translate_y /=  (float)( h/2 );
	translate_y *= 1.45;
	translate_x *= 2.13;

//	static float trans_x = 0.0;
//	trans_x += 0.01;

//	cout << "x=" << x << "; trans_x=" << translate_x << endl << flush;
//	cout << "y=" << y << "; trans_y=" << translate_y << endl << flush;

	translate_xyz(model, translate_x, translate_y, -2.5f);
//	view_set_perspective(view, 0.0f, aspect, -20.0f, 20.0f);

	multiply_matrix( mvpMatrix, m_projectionMatrix, model);

	const int coordinates_in_point = 3;

	size_t vertixesCount = m_vertexBuffer.size() / coordinates_in_point;

	__evas_gl_glapi->glUseProgram( m_Program );

	__evas_gl_glapi->glEnableVertexAttribArray( m_positionIdx );
	__evas_gl_glapi->glEnableVertexAttribArray( m_mvpMatrixIdx );

	__evas_gl_glapi->glVertexAttribPointer( m_positionIdx, coordinates_in_point, GL_FLOAT, GL_FALSE, coordinates_in_point * sizeof(GLfloat), &m_vertexBuffer[0] );

	const int matrixCount = 1;

	__evas_gl_glapi->glUniformMatrix4fv( m_mvpMatrixIdx, matrixCount, GL_FALSE, mvpMatrix );

	__evas_gl_glapi->glDrawArrays( GL_LINES, 0, vertixesCount * coordinates_in_point );

	__evas_gl_glapi->glDisableVertexAttribArray( m_positionIdx );
	__evas_gl_glapi->glDisableVertexAttribArray( m_mvpMatrixIdx );

	__evas_gl_glapi->glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind
}










