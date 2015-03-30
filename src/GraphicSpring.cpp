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

//void GraphicSpring::initLineVertexes()
//{
//	m_vertexBuffer.clear();
//
//	int canvas_width =  m_DrawCanvasWidth;
//	int canvas_height = m_DrawCanvasHeight;
//
//	int from_x = ( m_geometrySpring.getLinkFrom().getPointFrom().getX() + m_geometrySpring.getLinkFrom().getPointTo().getX() ) / 2;
//	int from_y = ( m_geometrySpring.getLinkFrom().getPointFrom().getY() + m_geometrySpring.getLinkFrom().getPointTo().getY() ) / 2;
//
//	int to_x = ( m_geometrySpring.getLinkTo().getPointFrom().getX() + m_geometrySpring.getLinkTo().getPointTo().getX() ) / 2;
//	int to_y = ( m_geometrySpring.getLinkTo().getPointFrom().getY() + m_geometrySpring.getLinkTo().getPointTo().getY() ) / 2;
//
//	const unsigned int segment_length_min = 20;
//
//	int katet_width = ( to_x - from_x );
//	int katet_height = ( to_y -  from_y );
//
//	if( katet_width == 0 && katet_height == 0 )
//	{
//		return;
//	}
//
//	unsigned int hypotenuze = sqrt( katet_width * katet_width + katet_height * katet_height );
//
//	int segments_count = ( hypotenuze / segment_length_min ) + 1;
//	int segment_length = hypotenuze / segments_count;
//	int segment_x_length = katet_width / segments_count;
//	int segment_y_length = katet_height / segments_count;
//
//	bool left = true;
//	float direction_angle_delta = 0.0;
//	if( katet_height > 0 && katet_width < 0 )
//	{
//		left = true;
//		direction_angle_delta = 0.0;
//	}
//	else if( katet_height < 0 && katet_width < 0 )
//	{
//		left = true;
//		direction_angle_delta = M_PI / 2;
//	}
//	else if( katet_height < 0 && katet_width > 0 )
//	{
//		left = true;
//		direction_angle_delta = M_PI;
//	}
//	else if( katet_height > 0 && katet_width > 0 )
//	{
//		left = false;
//		direction_angle_delta = M_PI * 3.0 / 2.0;
//	}
//
//	float spring_angle_sin = katet_width / hypotenuze;
//	spring_angle_sin = spring_angle_sin > 1.0 ? 1.0 : ( spring_angle_sin < -1.0 ? -1.0 : spring_angle_sin );
//	double spring_angle = asin( spring_angle_sin );
//	const float ortho_angle = M_PI / 2;
//    const float angles_max = M_PI;
//
//	const unsigned int curve_side_lenght = 20;
//
//	float last_x = 0;
//	float last_y = 0;
//
//	{
//		float translate_x =  ( from_x - canvas_width /  2.0 );
//		translate_x  /= (float)( canvas_width / 2 );
//		float translate_y = ( canvas_height / 2.0 - from_y + 60 );
//		translate_y /=  (float)( canvas_height / 2 );
//
//		m_vertexBuffer.push_back( translate_x );
//		m_vertexBuffer.push_back( translate_y );
//	}
//
//	for( int segment_i = 0 ; segment_i < segments_count ; segment_i++ )
//	{
//		float curve_angle_left = ortho_angle + direction_angle_delta - spring_angle;
//		float curve_angle_rigth = spring_angle + direction_angle_delta + ortho_angle;
//
//
//		unsigned int segment_point_x = ( from_x + segment_x_length * segment_i + segment_x_length / 2 );
//		unsigned int segment_point_y = ( from_y + segment_y_length * segment_i + segment_y_length / 2 );
//
//		int curve_left_x = segment_point_x + curve_side_lenght * cos( curve_angle_left );
//		int curve_left_y = segment_point_y + curve_side_lenght * sin( curve_angle_left );
//
//		int curve_right_x = segment_point_x + curve_side_lenght * cos( curve_angle_rigth );
//		int curve_right_y = segment_point_y + curve_side_lenght * sin( curve_angle_rigth );
//
//		if( last_x != 0 && last_y != 0 && ( segment_i ) < segments_count )
//		{
//			m_vertexBuffer.push_back( last_x );
//			m_vertexBuffer.push_back( last_y );
//		}
//
//		m_vertexBuffer.push_back( pixels_to_coords_x( curve_left_x ) );
//		m_vertexBuffer.push_back( pixels_to_coords_y( curve_left_y ) );
//
//
//		last_x = pixels_to_coords_x( curve_left_x );
//		last_y = pixels_to_coords_y( curve_left_y );
//	}
//
//	{
//		m_vertexBuffer.push_back( last_x );
//		m_vertexBuffer.push_back( last_y );
//	}
//	{
//		float translate_x =  ( to_x - canvas_width /  2.0 );
//		translate_x  /= (float)( canvas_width / 2 );
//		float translate_y = ( canvas_height / 2.0 - to_y + 60 );
//		translate_y /=  (float)( canvas_height / 2 );
//
//		m_vertexBuffer.push_back( translate_x );
//		m_vertexBuffer.push_back( translate_y );
//	}
//
//	size_t vertex_count = m_vertexBuffer.size() / 2;
//	int a = 0;
//	a++;
//}

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

	int katet_width = ( to_x - from_x );
	int katet_height = ( to_y -  from_y );

	if( katet_width == 0 && katet_height == 0 )
	{
		return;
	}

	unsigned int hypotenuze = sqrt( katet_width * katet_width + katet_height * katet_height );

	int segments_count = ( hypotenuze / segment_length_min ) + 1;
	int segment_length = hypotenuze / segments_count;
	int segment_x_length = hypotenuze / segments_count;
	int segment_y_length = hypotenuze / segments_count;

	bool left = true;
	float direction_angle_delta = 0.0;
	if( katet_height > 0 && katet_width < 0 )
	{
		left = true;
		direction_angle_delta = 0.0;
	}
	else if( katet_height < 0 && katet_width < 0 )
	{
		left = true;
		direction_angle_delta = M_PI / 2;
	}
	else if( katet_height < 0 && katet_width > 0 )
	{
		left = true;
		direction_angle_delta = M_PI;
	}
	else if( katet_height > 0 && katet_width > 0 )
	{
		left = false;
		direction_angle_delta = M_PI * 3.0 / 2.0;
	}

	float spring_angle_sin = (katet_width * 1.0) / ( hypotenuze * 1.0 );

	double spring_angle_radian = asin( spring_angle_sin );
	int dec_angle = ( spring_angle_radian / M_PI * 180 );

	const unsigned int curve_side_lenght = 20;

	const int coords_in_two_points = 4;

	vector<float> stack_last_points( coords_in_two_points, 0.0 ); //[i+0]=x, [i+1]=y

	stack_last_points[0] = pixels_to_coords_x( from_x );
	stack_last_points[1] = pixels_to_coords_y( from_y );

	stack_last_points[2] = pixels_to_coords_x( from_x );
	stack_last_points[3] = pixels_to_coords_y( from_y );

	for( int segment_i = 0 ; segment_i < segments_count ; segment_i++ )
	{
		float spring_angle_cos = 0.0;
		if( katet_width > 0 )
		{
			spring_angle_cos = cos( M_PI / 2 - spring_angle_radian );
		}
		else
		{
			spring_angle_cos = cos( M_PI / 2 + spring_angle_radian );
		}
		float rotate_x = spring_angle_cos;

		float spring_angle_sin = 0;
		if( katet_height < 0 )
		{
			spring_angle_sin = sin( M_PI / 2 - spring_angle_radian );
		}
		else
		{
			spring_angle_sin = sin( M_PI + spring_angle_radian );
		}
		float rotate_y = (-1) * spring_angle_sin;

		double tempsegment_delta = (double)( segment_x_length * segment_i + segment_x_length / 2 );
		double rotated_delta_x = tempsegment_delta * (double)rotate_x;
		unsigned int segment_middle_point_x = from_x + rotated_delta_x;

		double rotated_delta_y = tempsegment_delta * (double)rotate_y;
		unsigned int segment_middle_point_y = from_y + rotated_delta_y;


		unsigned int segment_end_point_x = from_x + (double)( segment_x_length * ( segment_i + 1 ) ) * (double)rotate_x;
		unsigned int segment_end_point_y = from_y + (double)( segment_y_length * ( segment_i + 1 ) ) * (double)rotate_y;

		segment_middle_point_x = ( -1 ) * spring_angle_sin * tempsegment_delta + spring_angle_cos * tempsegment_delta  + from_x;
		segment_middle_point_y = spring_angle_cos * tempsegment_delta + spring_angle_sin * tempsegment_delta + from_y;

		segment_end_point_x = ( -1 ) * spring_angle_sin * ( segment_y_length * ( segment_i + 1 ) ) + spring_angle_cos * ( segment_y_length * ( segment_i + 1 ) )  + from_x;
		segment_end_point_y = spring_angle_cos * ( segment_y_length * ( segment_i + 1 ) ) + spring_angle_sin * ( segment_y_length * ( segment_i + 1 ) ) + from_y;

		int curve_left_x = segment_middle_point_x - curve_side_lenght;
		int curve_left_y = segment_middle_point_y;

		int curve_right_x = segment_middle_point_x + curve_side_lenght;
		int curve_right_y = segment_middle_point_y;

		m_vertexBuffer.push_back( stack_last_points[0] );
		m_vertexBuffer.push_back( stack_last_points[1] );

		m_vertexBuffer.push_back( pixels_to_coords_x( curve_left_x ) );
		m_vertexBuffer.push_back( pixels_to_coords_y( curve_left_y ) );

		m_vertexBuffer.push_back( stack_last_points[2] );
		m_vertexBuffer.push_back( stack_last_points[3] );

		m_vertexBuffer.push_back( pixels_to_coords_x( curve_right_x ) );
		m_vertexBuffer.push_back( pixels_to_coords_y( curve_right_y ) );

		stack_last_points[0] = pixels_to_coords_x( curve_left_x ) ;
		stack_last_points[1] = pixels_to_coords_y( curve_left_y );
		stack_last_points[2] = pixels_to_coords_x( curve_right_x );
		stack_last_points[3] = pixels_to_coords_y( curve_right_y );



		m_vertexBuffer.push_back( stack_last_points[0] );
		m_vertexBuffer.push_back( stack_last_points[1] );

		m_vertexBuffer.push_back( pixels_to_coords_x( segment_end_point_x ) );
		m_vertexBuffer.push_back( pixels_to_coords_y( segment_end_point_y ) );


		m_vertexBuffer.push_back( stack_last_points[2] );
		m_vertexBuffer.push_back( stack_last_points[3] );

		m_vertexBuffer.push_back( pixels_to_coords_x( segment_end_point_x ) );
		m_vertexBuffer.push_back( pixels_to_coords_y( segment_end_point_y ) );

		stack_last_points[0] = pixels_to_coords_x( segment_end_point_x ) ;
		stack_last_points[1] = pixels_to_coords_y( segment_end_point_y );
		stack_last_points[2] = pixels_to_coords_x( segment_end_point_x );
		stack_last_points[3] = pixels_to_coords_y( segment_end_point_y );
	}

	size_t vertex_count = m_vertexBuffer.size() / 2;
	int a = 0;
	a++;
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

















