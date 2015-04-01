/*
 * GraphicSpring.cpp
 *
 *  Created on: Mar 27, 2015
 *      Author: vostanin
 */

#include "GraphicSpring.h"
#include <iostream>
using namespace std;

GraphicSpring::GraphicSpring( IGeometryObject * geometryObject, Evas_Object * canvas ) : GraphicObjectBase( canvas ), m_springRotateAngle( 0 )
{
	m_geometrySpring = *geometryObject;
}

GraphicSpring::GraphicSpring( const GraphicSpring & src )
{
	m_geometrySpring = src.m_geometrySpring;
	m_springRotateAngle = src.m_springRotateAngle;
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
//	const unsigned int segment_width_min = 50;
//
//	int katet_width_relative = ( to_x - from_x );
//	int katet_height_relative = ( to_y -  from_y );
//
//	if( katet_width_relative == 0 && katet_height_relative == 0 )
//	{
//		return;
//	}
//
//	unsigned int hypotenuze = sqrt( katet_width_relative * katet_width_relative + katet_height_relative * katet_height_relative );
//
//	int segments_count = ( hypotenuze / segment_width_min ) + 1;
//	const int segment_width = 50;
//	int segment_height = hypotenuze / segments_count;
//
//	float spring_angle_sin = (katet_width_relative * 1.0) / ( hypotenuze * 1.0 );
//
//
//
//	float spring_angle_radian = asin( spring_angle_sin );
//////	spring_angle_radian += 0.05;
////	float spring_angle_cos = cos( spring_angle_radian );
////	spring_angle_sin = sin( spring_angle_radian );
//
//	int dec_angle = ( spring_angle_radian / M_PI * 180 );
//	m_springRotateAngle = dec_angle;
//
//	const int coords_in_two_points = 4;
//
//	vector<float> stack_last_points( coords_in_two_points, 0.0 ); //[i+0]=x, [i+1]=y
//
//	stack_last_points[0] = pixels_to_coords_x( from_x );
//	stack_last_points[1] = pixels_to_coords_y( from_y );
//
//	stack_last_points[2] = pixels_to_coords_x( from_x );
//	stack_last_points[3] = pixels_to_coords_y( from_y );
//
//	for( int segment_i = 0 ; segment_i < segments_count ; segment_i++ )//Build up and rotate
//	{
//		unsigned int x0 = from_x;
//		unsigned int y0 = from_y;
//
//		unsigned int next_segment_half_height = segment_height * segment_i + segment_height / 2;
//		int segment_left_corner_width = ( -1 ) * segment_width;
//		int segment_right_corner_width = segment_width;
//
//		unsigned int next_segment_half_height_absolute = next_segment_half_height + from_y;
//		unsigned int segment_left_corner_width_absolute = segment_left_corner_width + from_x;
//		unsigned int segment_right_corner_width_absolute = segment_right_corner_width + from_x;
//
//		m_vertexBuffer.push_back( stack_last_points[0] );
//		m_vertexBuffer.push_back( stack_last_points[1] );
//
//		m_vertexBuffer.push_back( pixels_to_coords_x( segment_left_corner_width_absolute ) );
//		m_vertexBuffer.push_back( pixels_to_coords_y( next_segment_half_height_absolute ) );
//
//		m_vertexBuffer.push_back( stack_last_points[2] );
//		m_vertexBuffer.push_back( stack_last_points[3] );
//
//		m_vertexBuffer.push_back( pixels_to_coords_x( segment_right_corner_width_absolute ) );
//		m_vertexBuffer.push_back( pixels_to_coords_y( next_segment_half_height_absolute ) );
//
//		stack_last_points[0] = pixels_to_coords_x( segment_left_corner_width_absolute ) ;
//		stack_last_points[1] = pixels_to_coords_y( next_segment_half_height_absolute );
//		stack_last_points[2] = pixels_to_coords_x( segment_right_corner_width_absolute );
//		stack_last_points[3] = pixels_to_coords_y( next_segment_half_height_absolute );
//
//
//
//		m_vertexBuffer.push_back( stack_last_points[0] );
//		m_vertexBuffer.push_back( stack_last_points[1] );
//
//		next_segment_half_height_absolute += segment_height / 2;
//
//
//		m_vertexBuffer.push_back( pixels_to_coords_x( from_x ) );
//		m_vertexBuffer.push_back( pixels_to_coords_y( next_segment_half_height_absolute ) );
//
//
//		m_vertexBuffer.push_back( stack_last_points[2] );
//		m_vertexBuffer.push_back( stack_last_points[3] );
//
//		m_vertexBuffer.push_back( pixels_to_coords_x( from_x ) );
//		m_vertexBuffer.push_back( pixels_to_coords_y( next_segment_half_height_absolute ) );
//
//		stack_last_points[0] = pixels_to_coords_x( from_x ) ;
//		stack_last_points[1] = pixels_to_coords_y( next_segment_half_height_absolute );
//		stack_last_points[2] = pixels_to_coords_x( from_x );
//		stack_last_points[3] = pixels_to_coords_y( next_segment_half_height_absolute );
//	}
//
//	size_t vertex_count = m_vertexBuffer.size() / 2;
//	int a = 0;
//	a++;
//}

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
//	const unsigned int segment_width_min = 50;
//
//	int katet_width_relative = ( to_x - from_x );
//	int katet_height_relative = ( to_y -  from_y );
//
//	if( katet_width_relative == 0 && katet_height_relative == 0 )
//	{
//		return;
//	}
//
//	unsigned int hypotenuze = sqrt( katet_width_relative * katet_width_relative + katet_height_relative * katet_height_relative );
//
//	int segments_count = ( hypotenuze / segment_width_min ) + 1;
//	const int segment_width = 50;
//	int segment_height = hypotenuze / segments_count;
//
//	float spring_angle_sin = (katet_width_relative * 1.0) / ( hypotenuze * 1.0 );
//
//	double spring_angle_radian = asin( spring_angle_sin );
//	float spring_angle_cos = cos( spring_angle_radian );
//
//	int dec_angle = ( spring_angle_radian / M_PI * 180 );
//
//	dec_angle = dec_angle < 0 ? 360 - dec_angle : dec_angle;
//
//	m_springRotateAngle = dec_angle;
//
//	m_vertexBuffer.push_back( pixels_to_coords_x( from_x ) );
//	m_vertexBuffer.push_back( pixels_to_coords_y( from_y ) );
//
//	unsigned int vertical_x = from_x;
//
//
//	unsigned int vertical_x_rotated = from_x + ( vertical_x * spring_angle_cos ) - ( hypotenuze * spring_angle_sin );
//	unsigned int vertical_y_rotated = from_y + ( vertical_x * spring_angle_sin ) + ( hypotenuze * spring_angle_cos );
//
//	m_vertexBuffer.push_back( pixels_to_coords_x( to_x ) );
//	m_vertexBuffer.push_back( pixels_to_coords_y( to_y ) );
//
//
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

	int from_x = ( m_geometrySpring.getLinkFrom()->getPointFrom()->getX() + m_geometrySpring.getLinkFrom()->getPointTo()->getX() ) / 2;
	int from_y = ( m_geometrySpring.getLinkFrom()->getPointFrom()->getY() + m_geometrySpring.getLinkFrom()->getPointTo()->getY() ) / 2;

	int to_x = ( m_geometrySpring.getLinkTo()->getPointFrom()->getX() + m_geometrySpring.getLinkTo()->getPointTo()->getX() ) / 2;
	int to_y = ( m_geometrySpring.getLinkTo()->getPointFrom()->getY() + m_geometrySpring.getLinkTo()->getPointTo()->getY() ) / 2;

	m_vertexBuffer.push_back( pixels_to_coords_x( from_x ) );
	m_vertexBuffer.push_back( pixels_to_coords_y( from_y ) );

	m_vertexBuffer.push_back( pixels_to_coords_x( to_x ) );
	m_vertexBuffer.push_back( pixels_to_coords_y( to_y ) );
}

void GraphicSpring::draw_line_2d()
{
	Evas_GL_API * __evas_gl_glapi = m_glApi;

	GLfloat translateMatrix[16];
	GLfloat scaleMatrix[16];
	GLfloat rotateMatrix[16];
	GLfloat v_color[4] = { 0.9, 0.5, 1.0, 1.0 };

	GLfloat perspective[16];
	init_matrix( perspective );
	init_matrix( translateMatrix );
	init_matrix( scaleMatrix );
	init_matrix( rotateMatrix );

	scale_xyz( scaleMatrix, 1.0, 1.0, 1.0 );
	static int angle = 0;
	angle += 10;
//	rotate_xyz( rotateMatrix, 0, 0, 90 + m_springRotateAngle );

//	int from_x = ( m_geometrySpring.getLinkFrom().getPointFrom().getX() + m_geometrySpring.getLinkFrom().getPointTo().getX() ) / 2;
//	int from_y = ( m_geometrySpring.getLinkFrom().getPointFrom().getY() + m_geometrySpring.getLinkFrom().getPointTo().getY() ) / 2;

//	translate_xyz( translateMatrix, pixels_to_coords_x( from_x ), pixels_to_coords_y( from_y ), 0.0f );

	const int coordinates_in_point = 2;

	size_t vertixesCount = m_vertexBuffer.size() / coordinates_in_point;

	__evas_gl_glapi->glUseProgram( m_Program );

	__evas_gl_glapi->glEnableVertexAttribArray( m_positionIdx );

	__evas_gl_glapi->glVertexAttribPointer( m_positionIdx, coordinates_in_point, GL_FLOAT, GL_FALSE, coordinates_in_point * sizeof(GLfloat), &m_vertexBuffer[0] );

	const int matrixCount = 1;

	__evas_gl_glapi->glUniformMatrix4fv( m_perspective_idx, matrixCount, GL_FALSE, perspective );
	__evas_gl_glapi->glUniformMatrix4fv( m_translate_idx, matrixCount, GL_FALSE, translateMatrix );
	__evas_gl_glapi->glUniformMatrix4fv( m_scale_idx, matrixCount, GL_FALSE, scaleMatrix );
	__evas_gl_glapi->glUniformMatrix4fv( m_rotate_idx, matrixCount, GL_FALSE, rotateMatrix );
	__evas_gl_glapi->glUniform4f( m_color_idx, v_color[0], v_color[1], v_color[2], v_color[3] );

	__evas_gl_glapi->glDrawArrays( GL_LINES, 0, vertixesCount );

	__evas_gl_glapi->glDisableVertexAttribArray( m_positionIdx );

	__evas_gl_glapi->glUseProgram( 0 );
}

















