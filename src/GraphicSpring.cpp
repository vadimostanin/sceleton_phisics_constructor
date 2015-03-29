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

	int canvas_width =  m_DrawCanvasWidth;
	int canvas_height = m_DrawCanvasHeight;

	int from_x = ( m_geometrySpring.getLinkFrom().getPointFrom().getX() + m_geometrySpring.getLinkFrom().getPointTo().getX() ) / 2;
	int from_y = ( m_geometrySpring.getLinkFrom().getPointFrom().getY() + m_geometrySpring.getLinkFrom().getPointTo().getY() ) / 2;

	int to_x = ( m_geometrySpring.getLinkTo().getPointFrom().getX() + m_geometrySpring.getLinkTo().getPointTo().getX() ) / 2;
	int to_y = ( m_geometrySpring.getLinkTo().getPointFrom().getY() + m_geometrySpring.getLinkTo().getPointTo().getY() ) / 2;

	const unsigned int segment_length_min = 50;

	int katet_width = ( from_x - to_x );
	int katet_height = ( from_y - to_y );

	if( katet_width == 0 && katet_height == 0 )
	{
		return;
	}

	unsigned int hypotenuze = sqrt( katet_width * katet_width + katet_height * katet_height );

	int segments_count = ( hypotenuze / segment_length_min ) + 1;
	int segment_length = hypotenuze / segments_count;
	int segment_x_length = katet_width / segments_count;
	int segment_y_length = katet_height / segments_count;


	double spring_angle = asin( katet_width / hypotenuze );
	const float ortho_angle = M_PI / 2;

	float curve_angle = spring_angle + ortho_angle;

	const unsigned int curve_side_lenght = 20;

	float last_x = 0;
	float last_y = 0;

	{
		float translate_x =  ( from_x - canvas_width /  2.0 );
		translate_x  /= (float)( canvas_width / 2 );
		float translate_y = ( canvas_height / 2.0 - from_y + 60 );
		translate_y /=  (float)( canvas_height / 2 );

		m_vertexBuffer.push_back( translate_x );
		m_vertexBuffer.push_back( translate_y );
	}

	for( int segment_i = 0 ; segment_i < segments_count ; segment_i++ )
	{
		unsigned int segment_point_x = ( from_x + segment_x_length * segment_i + segment_x_length / 2 );
		unsigned int segment_point_y = ( from_y + segment_y_length * segment_i + segment_y_length / 2 );
		int curve_x = segment_point_x + curve_side_lenght * cos( curve_angle );
		int curve_y = segment_point_y + curve_side_lenght * sin( curve_angle );

		float translate_x =  ( curve_x - canvas_width /  2.0 );
		translate_x  /= (float)( canvas_width / 2 );
		float translate_y = ( canvas_height / 2.0 - curve_y + 60 );
		translate_y /=  (float)( canvas_height / 2 );

		m_vertexBuffer.push_back( translate_x );
		m_vertexBuffer.push_back( translate_y );

		if( last_x != 0 && last_y != 0 && ( segment_i + 1 ) < segments_count )
		{
			m_vertexBuffer.push_back( last_x );
			m_vertexBuffer.push_back( last_y );
		}
		last_x = translate_x;
		last_y = translate_y;
	}

	{
		m_vertexBuffer.push_back( last_x );
		m_vertexBuffer.push_back( last_y );
	}
	{
		float translate_x =  ( to_x - canvas_width /  2.0 );
		translate_x  /= (float)( canvas_width / 2 );
		float translate_y = ( canvas_height / 2.0 - to_y + 60 );
		translate_y /=  (float)( canvas_height / 2 );

		m_vertexBuffer.push_back( translate_x );
		m_vertexBuffer.push_back( translate_y );
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

















