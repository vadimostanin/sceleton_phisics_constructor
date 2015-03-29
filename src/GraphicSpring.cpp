/*
 * GraphicSpring.cpp
 *
 *  Created on: Mar 27, 2015
 *      Author: vostanin
 */

#include "GraphicSpring.h"
#include <iostream>
using namespace std;

GraphicSpring::GraphicSpring( IGeometryObject * geometryObject, Evas_Object * canvas ) : GraphicObjectBase( canvas )
{
	m_geometrySpring = *geometryObject;
}

GraphicSpring::GraphicSpring( const GraphicSpring & src )
{
	m_geometrySpring = src.m_geometrySpring;
}

GraphicSpring::~GraphicSpring()
{
}

void GraphicSpring::draw( Evas * canvas )
{
//	cout << "draw spring id=" << m_geometrySpring.getId() << endl << flush;

	initLineVertexes();

	draw_line_2d();
}

IGeometryObject & GraphicSpring::getGeometryObject()
{
	return m_geometrySpring;
}

string GraphicSpring::getVertexShader()
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

string GraphicSpring::getFragmentShader()
{
	string shader =	SHADER(

		void main()
		{
			gl_FragColor = vec4( 0.5, 0.5, 1.0, 1.0 );
		}

						);

	return shader;
}

void GraphicSpring::initLineVertexes()
{
	m_vertexBuffer.clear();
	{
		int x = ( m_geometrySpring.getLinkFrom().getPointFrom().getX() + m_geometrySpring.getLinkFrom().getPointTo().getX() ) / 2;
		int y = ( m_geometrySpring.getLinkFrom().getPointFrom().getY() + m_geometrySpring.getLinkFrom().getPointTo().getY() ) / 2;

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
		int x = ( m_geometrySpring.getLinkTo().getPointFrom().getX() + m_geometrySpring.getLinkTo().getPointTo().getX() ) / 2;
		int y = ( m_geometrySpring.getLinkTo().getPointFrom().getY() + m_geometrySpring.getLinkTo().getPointTo().getY() ) / 2;

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

void GraphicSpring::draw_line_2d()
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

















