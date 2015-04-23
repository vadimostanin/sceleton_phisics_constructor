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
#include "IsAngleBetweenTwoPredicate.h"
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

//	initLineVertexes();
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

void GraphicSpring::initCircleAtLinks( int x0, int y0, int radius )
{
	const int vertexNumber = 30;

	float ang = 0;
	float da = (float) (M_PI / 180 * (360.0f / vertexNumber));

	{//Circle Points
		int first_coord_x = x0 + radius * cos( ang );
		int first_coord_y = y0 + radius * sin( ang );
		int last_coord_x = first_coord_x;
		int last_coord_y = first_coord_y;
		for(double v_i = 0; v_i < vertexNumber; v_i ++ )
		{
			float fsin = sin( ang );
			float fcos = cos( ang );
			m_vertexBuffer.push_back( pixels_to_coords_x( last_coord_x ) );
			m_vertexBuffer.push_back( pixels_to_coords_y( last_coord_y ) );
			int coordX = x0 + radius * fcos;
			int coordY = y0 + radius * fsin;
			m_vertexBuffer.push_back( pixels_to_coords_x( coordX ) );
			m_vertexBuffer.push_back( pixels_to_coords_y( coordY ) );

			last_coord_x = coordX;
			last_coord_y = coordY;

			ang += da;
		}
		m_vertexBuffer.push_back( pixels_to_coords_x( last_coord_x ) );
		m_vertexBuffer.push_back( pixels_to_coords_y( last_coord_y ) );
		m_vertexBuffer.push_back( pixels_to_coords_x( first_coord_x ) );
		m_vertexBuffer.push_back( pixels_to_coords_y( first_coord_y ) );
	}
}

void GraphicSpring::initPartialCircleVertex()
{
	const GeometrySpring * geometrySpring = (GeometrySpring *)&( getGeometryObject() );
	GeometryLinkGetAbsoluteAnglePredicate getLinkFromAbsoluteAngle( geometrySpring->getLinkFrom() );
	GeometryLinkGetAbsoluteAnglePredicate getLinkToAbsoluteAngle( geometrySpring->getLinkTo() );
	int linkFromAngle     = getLinkFromAbsoluteAngle();
	int linkToAngle     = getLinkToAbsoluteAngle();

	if( linkFromAngle == linkToAngle )
	{
		return;
	}

	GeometrySpringGetCrosslinkPredicate getCrosslinkPoint( geometrySpring );
	const GeometryPoint * crosslinkPoint = getCrosslinkPoint();
	int X0 = crosslinkPoint->getX();
	int Y0 = crosslinkPoint->getY();

	GeometrySpringGetShortestLinkPredicate getShortesLink( geometrySpring );
	const GeometryLink * shorteslink = getShortesLink();
	int outerRadius = shorteslink->getWidth() / 2;

	const int innerRadius = 5;
	initCircleAtLinks( geometrySpring->getLinkFrom()->getMiddleX(), geometrySpring->getLinkFrom()->getMiddleY(), innerRadius );

	int mouseX = MouseCoordinatesHolder::getInstance().getX();
	int mouseY = MouseCoordinatesHolder::getInstance().getY();

	GeometryLinkGetAbsoluteAnglePredicate getCurrentPointAbsoluteAngle( X0, Y0, mouseX, mouseY );
	int currentMouseAngle = getCurrentPointAbsoluteAngle();

	IsAngleBetweenTwoPredicate isMouseAngleBetween( linkFromAngle, linkToAngle, geometrySpring->getIsClosedPath(), currentMouseAngle );

	int minAngle = isMouseAngleBetween.getMinAngle();//min( currentMouseAngle, linkFromAngle );
	int maxAngle = isMouseAngleBetween.getMaxAngle();//max( currentMouseAngle, linkFromAngle );

//	cout << "minAngle=" << minAngle << "; maxAngle=" << maxAngle << endl << flush;
	float radian = ( (float)minAngle / 180.0 ) * M_PI;
//		int last_coord_x = X0 + outerRadius * cos( radian );
//		int last_coord_y = Y0 + outerRadius * sin( radian );
	for( int angle_i = minAngle ; angle_i <= maxAngle ; angle_i ++ )
	{
		radian = ( (float)angle_i / 180.0 ) * M_PI;
		int coordX = X0 + outerRadius * cos( radian );
		int coordY = Y0 - outerRadius * sin( radian );

//			m_vertexBuffer.push_back( pixels_to_coords_x( coordX ) );
//			m_vertexBuffer.push_back( pixels_to_coords_y( coordY ) );
		m_vertexBuffer.push_back( pixels_to_coords_x( coordX ) );
		m_vertexBuffer.push_back( pixels_to_coords_y( coordY ) );

//			last_coord_x = coordX;
//			last_coord_y = coordY;
	}
}

void GraphicSpring::initCompleteCircleVertex()
{
	const GeometrySpring * geometrySpring = (GeometrySpring *)&( getGeometryObject() );
	GeometryLinkGetAbsoluteAnglePredicate getLinkFromAbsoluteAngle( geometrySpring->getLinkFrom() );
	GeometryLinkGetAbsoluteAnglePredicate getLinkToAbsoluteAngle( geometrySpring->getLinkTo() );
	int linkFromAngle     = getLinkFromAbsoluteAngle();
	int linkToAngle     = getLinkToAbsoluteAngle();

	if( linkFromAngle == linkToAngle )
	{
		return;
	}

	GeometrySpringGetCrosslinkPredicate getCrosslinkPoint( geometrySpring );
	const GeometryPoint * crosslinkPoint = getCrosslinkPoint();
	int X0 = crosslinkPoint->getX();
	int Y0 = crosslinkPoint->getY();

	GeometrySpringGetShortestLinkPredicate getShortesLink( geometrySpring );
	const GeometryLink * shorteslink = getShortesLink();
	int outerRadius = shorteslink->getWidth() / 2;

	const int innerRadius = 5;
	initCircleAtLinks( geometrySpring->getLinkFrom()->getMiddleX(), geometrySpring->getLinkFrom()->getMiddleY(), innerRadius );

	IsAngleBetweenTwoPredicate isMouseAngleBetween( linkFromAngle, linkToAngle, geometrySpring->getIsClosedPath(), linkToAngle );

	int minAngle = isMouseAngleBetween.getMinAngle();
	int maxAngle = isMouseAngleBetween.getMaxAngle();

//	cout << "minAngle=" << minAngle << "; maxAngle=" << maxAngle << endl << flush;
	float radian = ( (float)minAngle / 180.0 ) * M_PI;
//	int last_coord_x = X0 + Radius * cos( radian );
//	int last_coord_y = Y0 + Radius * sin( radian );
	for( int angle_i = minAngle ; angle_i <= maxAngle ; angle_i ++ )
	{
		radian = ( (float)angle_i / 180.0 ) * M_PI;
		int coordX = X0 + outerRadius * cos( radian );
		int coordY = Y0 - outerRadius * sin( radian );

//		m_vertexBuffer.push_back( pixels_to_coords_x( coordX ) );
//		m_vertexBuffer.push_back( pixels_to_coords_y( coordY ) );
		m_vertexBuffer.push_back( pixels_to_coords_x( coordX ) );
		m_vertexBuffer.push_back( pixels_to_coords_y( coordY ) );

//		last_coord_x = coordX;
//		last_coord_y = coordY;
	}
}

void GraphicSpring::initCircleVertexes()
{
	m_vertexBuffer.clear();

	const GeometrySpring * geometrySpring = (GeometrySpring *)&( getGeometryObject() );
	GeometryLinkGetAbsoluteAnglePredicate getLinkFromAbsoluteAngle( geometrySpring->getLinkFrom() );
	GeometryLinkGetAbsoluteAnglePredicate getLinkToAbsoluteAngle( geometrySpring->getLinkTo() );
	int linkFromAngle     = getLinkFromAbsoluteAngle();
	int linkToAngle     = getLinkToAbsoluteAngle();

	if( linkFromAngle == linkToAngle )
	{
		return;
	}

	GeometrySpringGetCrosslinkPredicate getCrosslinkPoint( geometrySpring );

	if( geometrySpring->getConstructingState() == GEOMETRYOBJECTCONSTRUCTING_INPROGRESS )
	{
		initPartialCircleVertex();

		const int radiusFrom = 5;
		initCircleAtLinks( geometrySpring->getLinkTo()->getMiddleX(), geometrySpring->getLinkTo()->getMiddleY(), radiusFrom );
	}
	else
	{
		initCompleteCircleVertex();

		const int innerRadiusFrom = 5;
		initCircleAtLinks( geometrySpring->getLinkTo()->getMiddleX(), geometrySpring->getLinkTo()->getMiddleY(), innerRadiusFrom );
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

	__evas_gl_glapi->glDrawArrays( GL_POINTS, 0, vertixesCount );

	__evas_gl_glapi->glDisableVertexAttribArray( m_positionIdx );

	__evas_gl_glapi->glUseProgram( 0 );
}

















