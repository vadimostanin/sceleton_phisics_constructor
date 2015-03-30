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

		m_vertexBuffer.push_back( pixels_to_coords_x( x ) );
		m_vertexBuffer.push_back( pixels_to_coords_y( y ) );
//		m_vertexBuffer.push_back( 0.0 );
	}

	{
		int x = m_geometryLink.getPointTo().getX();
		int y = m_geometryLink.getPointTo().getY();

		m_vertexBuffer.push_back( pixels_to_coords_x( x ) );
		m_vertexBuffer.push_back( pixels_to_coords_y( y ) );
//		m_vertexBuffer.push_back( 0.0 );
	}
}

string GraphicLink::getVertexShader()
{
	string shader = SHADER(

		attribute vec3 vPosition;
		uniform mat4 perspective;
		uniform mat4 translate;
		uniform mat4 scale;
		void main()
		{
		   gl_Position = perspective * translate * scale * vec4( vPosition, 1.0 );
		}

						);

	return shader;
}

string GraphicLink::getFragmentShader()
{
	string shader =	SHADER(

		void main()
		{
			gl_FragColor = vec4( 0.5, 0.5, 1.0, 1.0 );
		}

						);

	return shader;
}

void GraphicLink::draw_line_2d()
{
	Evas_GL_API * __evas_gl_glapi = m_glApi;

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










