/*
 * GraphicSpring.cpp
 *
 *  Created on: Mar 27, 2015
 *      Author: vostanin
 */

#include "GraphicSpring.h"
#include "GeometrySpringGetCrosslinkPredicate.h"
#include "GeometrySpringGetShortestLinkPredicate.h"
#include "GeometryLinksAngleGetPredicate.h"
#include "GeometryLinkGetAbsoluteAnglePredicate.h"
#include "MouseCoordinatesHolder.h"
#include <iostream>
using namespace std;

GraphicSpring::GraphicSpring( IGeometryObject * geometryObject, Evas_Object * canvas ) : GraphicObjectBase( canvas ), m_springRotateAngle( 0 )
{
	m_geometrySpring = (GeometrySpring *)geometryObject;
}

GraphicSpring::GraphicSpring( const GraphicSpring & src )
{
	m_geometrySpring = src.m_geometrySpring;
	m_springRotateAngle = src.m_springRotateAngle;
}

GraphicSpring::~GraphicSpring()
{
}

void GraphicSpring::draw()
{
//	cout << "draw spring id=" << m_geometrySpring.getId() << endl << flush;

	initLineVertexes();
	initCircleVertexes();

	draw_line_2d();
}

IGeometryObject & GraphicSpring::getGeometryObject()
{
	return *m_geometrySpring;
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

	int from_x = ( m_geometrySpring->getLinkFrom()->getPointFrom()->getX() + m_geometrySpring->getLinkFrom()->getPointTo()->getX() ) / 2;
	int from_y = ( m_geometrySpring->getLinkFrom()->getPointFrom()->getY() + m_geometrySpring->getLinkFrom()->getPointTo()->getY() ) / 2;

	int to_x = ( m_geometrySpring->getLinkTo()->getPointFrom()->getX() + m_geometrySpring->getLinkTo()->getPointTo()->getX() ) / 2;
	int to_y = ( m_geometrySpring->getLinkTo()->getPointFrom()->getY() + m_geometrySpring->getLinkTo()->getPointTo()->getY() ) / 2;

	m_vertexBuffer.push_back( pixels_to_coords_x( from_x ) );
	m_vertexBuffer.push_back( pixels_to_coords_y( from_y ) );

	m_vertexBuffer.push_back( pixels_to_coords_x( to_x ) );
	m_vertexBuffer.push_back( pixels_to_coords_y( to_y ) );
}

void GraphicSpring::initCircleVertexes()
{
//	m_vertexBuffer.clear();

//	GeometrySpringGetShortestLinkPredicate getShortesLink( geometrySpring );
//	const GeometryLink * shorteslink = getShortesLink();
//
//	int crosslink_x = crosslinkPoint->getX();
//	int crosslink_y = crosslinkPoint->getY();
//
//	float degree = M_PI / 180.0;
//
//	GeometryPoint pointX0Y0( crosslink_x, crosslink_y );
//	GeometryPoint pointX0Y1( crosslink_x, crosslink_y + shorteslink->getWidth() );
//	GeometryLink linkY0( &pointX0Y0, &pointX0Y1 );
//
//	GeometryLinksAngleGetPredicate getAngle( geometrySpring->getLinkFrom(), &linkY0 );
//
//	float angle = getAngle();
//
//	int angle_int = angle / M_PI * 180.0;
//
//	cout << "angle=" << angle_int << endl << flush;
//
//	for( float angle_i = ( -1 ) * M_PI ; angle_i < M_PI ; angle_i += degree )
//	{
//		;
//	}

	int mouseX = MouseCoordinatesHolder::getInstance().getX();
	int mouseY = MouseCoordinatesHolder::getInstance().getY();

	GeometrySpring * geometrySpring = (GeometrySpring *)&( getGeometryObject() );
	GeometrySpringGetCrosslinkPredicate getCrosslinkPoint( geometrySpring );
	const GeometryPoint * crosslinkPoint = getCrosslinkPoint();
	GeometryLinkGetAbsoluteAnglePredicate getCurrentPointAbsoluteAngle( crosslinkPoint->getX(), crosslinkPoint->getY(), mouseX, mouseY );

	float degree = M_PI / 180.0;

	for( float angle_i = ( -1 ) * M_PI ; angle_i < M_PI ; angle_i += degree )
	{
		;
	}

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

















