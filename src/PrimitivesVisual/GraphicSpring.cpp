/*
 * GraphicSpring.cpp
 *
 *  Created on: Mar 27, 2015
 *      Author: vostanin
 */

#include "GraphicSpring.h"
#include "GeometrySpringGetCrosslinkPredicate.h"
#include "GeometrySpringGetShortestLinkPredicate.h"
#include "GeometryLinkGetAbsoluteAnglePredicate.h"
#include "GetAnglesRangeBy3PointsPredicate.h"
#include "GetAnglesRangeBy2PointsPredicate.h"
#include "GeometrySpringGetAngles.h"
#include "MouseCoordinatesHolder.h"
#include "GetCoordsOnPhypotenuzeByWidth.h"
#include <iostream>
using namespace std;

GraphicSpring::GraphicSpring( IGeometryObject * geometryObject, Evas_Object * canvas ) : GraphicObjectBase( canvas ), m_springRotateAngle( 0 )
{
	m_geometrySpring = (GeometrySpring *)geometryObject;

	initShaders();
}

GraphicSpring::GraphicSpring( const GraphicSpring & src )
{
	m_geometrySpring = src.m_geometrySpring;
	m_springRotateAngle = src.m_springRotateAngle;

	initShaders();
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

		attribute vec2 vPosition;
		uniform mat4 perspective;
		uniform mat4 translate;
		uniform mat4 scale;
		void main()
		{
			gl_PointSize = 100.0;
			gl_Position = perspective * translate * scale * vec4( vPosition.xy, 0.0, 1.0 );
		}

						);

	return shader;
}

string GraphicSpring::getFragmentShader()
{
	string shader =	SHADER(
\n
\n		void main()
\n		{
\n			gl_FragColor = vec4( 1.0, 0.0, 0.0, 1.0 );
\n		}
\n
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
	const int vertexNumber = 20;

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
			int coordX = x0 + radius * fcos;
			int coordY = y0 + radius * fsin;

			m_vertexBuffer.push_back( pixels_to_coords_x( x0 ) );
			m_vertexBuffer.push_back( pixels_to_coords_y( y0 ) );
			m_vertexBuffer.push_back( pixels_to_coords_x( last_coord_x ) );
			m_vertexBuffer.push_back( pixels_to_coords_y( last_coord_y ) );
			m_vertexBuffer.push_back( pixels_to_coords_x( coordX ) );
			m_vertexBuffer.push_back( pixels_to_coords_y( coordY ) );

			last_coord_x = coordX;
			last_coord_y = coordY;

			ang += da;
		}
		m_vertexBuffer.push_back( pixels_to_coords_x( x0 ) );
		m_vertexBuffer.push_back( pixels_to_coords_y( y0 ) );
		m_vertexBuffer.push_back( pixels_to_coords_x( last_coord_x ) );
		m_vertexBuffer.push_back( pixels_to_coords_y( last_coord_y ) );
		m_vertexBuffer.push_back( pixels_to_coords_x( first_coord_x ) );
		m_vertexBuffer.push_back( pixels_to_coords_y( first_coord_y ) );
	}
}

void GraphicSpring::initPartialCircleVertex()
{
	const GeometrySpring * geometrySpring = (GeometrySpring *)&( getGeometryObject() );

	GeometrySpringGetAngles getAngles( geometrySpring );
	int linkFromAngle = getAngles.getLinkFromAngle();
	int linkToAngle = getAngles.getLinkToAngle();

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

	int mouseX = MouseCoordinatesHolder::getInstance().getX();
	int mouseY = MouseCoordinatesHolder::getInstance().getY();

	GeometryLinkGetAbsoluteAnglePredicate getCurrentPointAbsoluteAngle( X0, Y0, mouseX, mouseY );
	int currentMouseAngle = getCurrentPointAbsoluteAngle();

	GetAnglesRangeBy3PointsPredicate isMouseAngleBetween( linkFromAngle, linkToAngle, geometrySpring->getIsClosedPath(), currentMouseAngle );

	int minAngle = isMouseAngleBetween.getMinAngle();//min( currentMouseAngle, linkFromAngle );
	int maxAngle = isMouseAngleBetween.getMaxAngle();//max( currentMouseAngle, linkFromAngle );

//	cout << "minAngle=" << minAngle << "; maxAngle=" << maxAngle << endl << flush;
	float radian = ( (float)minAngle / 180.0 ) * M_PI;
		int last_coord_x = X0 + outerRadius * cos( radian );
		int last_coord_y = Y0 - outerRadius * sin( radian );
	const int segmentMinAngle = 20;
	float segmentsCount = (float)( abs( maxAngle - minAngle ) ) / (float)segmentMinAngle;
	float deltaAngle = (float)( maxAngle - minAngle ) / (float)segmentsCount;
	for( int angle_i = minAngle ; angle_i < maxAngle ; angle_i += deltaAngle )
	{
		radian = ( (float)angle_i / 180.0 ) * M_PI;
		int coordX = X0 + outerRadius * cos( radian );
		int coordY = Y0 - outerRadius * sin( radian );

		initCircleAtLinks( coordX, coordY, 3 );

//		m_vertexBuffer.push_back( pixels_to_coords_x( last_coord_x ) );
//		m_vertexBuffer.push_back( pixels_to_coords_y( last_coord_y ) );
//		m_vertexBuffer.push_back( pixels_to_coords_x( coordX ) );
//		m_vertexBuffer.push_back( pixels_to_coords_y( coordY ) );

			last_coord_x = coordX;
			last_coord_y = coordY;
	}
}

void GraphicSpring::initCompleteCircleVertex()
{
	const GeometrySpring * geometrySpring = (GeometrySpring *)&( getGeometryObject() );
	GeometrySpringGetAngles getAngles( geometrySpring );
	int linkFromAngle = getAngles.getLinkFromAngle();
	int linkToAngle = getAngles.getLinkToAngle();

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

	GetAnglesRangeBy2PointsPredicate getRange( linkFromAngle, linkToAngle, geometrySpring->getIsClosedPath() );

	int minAngle = getRange.getMinAngle();
	int maxAngle = getRange.getMaxAngle();

	cout << "minAngle=" << minAngle << "; maxAngle=" << maxAngle << endl << flush;
	float radian = ( (float)minAngle / 180.0 ) * M_PI;
	int last_coord_x = X0 + outerRadius * cos( radian );
	int last_coord_y = Y0 - outerRadius * sin( radian );
	const int segmentMinAngle = 20;
	float segmentsCount = (float)( abs( maxAngle - minAngle ) ) / (float)segmentMinAngle;
	float deltaAngle = (float)( maxAngle - minAngle ) / (float)segmentsCount;

	for( int angle_i = minAngle ; angle_i < maxAngle ; angle_i += deltaAngle )
	{
		radian = ( (float)angle_i / 180.0 ) * M_PI;
		int coordX = X0 + outerRadius * cos( radian );
		int coordY = Y0 - outerRadius * sin( radian );

		initCircleAtLinks( coordX, coordY, 3 );

		last_coord_x = coordX;
		last_coord_y = coordY;
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
		const int innerRadius = 5;
		GeometrySpringGetAngles getAngles( geometrySpring );
		const GeometryPoint * crossPoint = getAngles.getCrospoint();
		const GeometryPoint * linkFromAdjustmentPoint = getAngles.getLinkFromAdjacentPoint();
		const GeometryPoint * linkToAdjustmentPoint = getAngles.getLinkToAdjacentPoint();

		{
			GeometrySpringGetShortestLinkPredicate getShortestLink( geometrySpring );

			int shortHalfWidth = getShortestLink()->getWidth() / 2;

			GetCoordsOnPhypotenuzeByWidth getWidthCoords( crossPoint, linkFromAdjustmentPoint, shortHalfWidth );

			int widthX = getWidthCoords.getX();
			int widthY = getWidthCoords.getY();

			initCircleAtLinks( widthX, widthY, innerRadius );
		}

		initPartialCircleVertex();

		{
			GeometrySpringGetShortestLinkPredicate getShortestLink( geometrySpring );

			int shortHalfWidth = getShortestLink()->getWidth() / 2;
			GeometrySpringGetAngles getAngles( geometrySpring );
			const GeometryPoint * crossPoint = getAngles.getCrospoint();
			const GeometryPoint * linkToAdjustmentPoint = getAngles.getLinkToAdjacentPoint();

			GetCoordsOnPhypotenuzeByWidth getWidthCoords( crossPoint, linkToAdjustmentPoint, shortHalfWidth );
			int widthX = getWidthCoords.getX();
			int widthY = getWidthCoords.getY();

			initCircleAtLinks( widthX, widthY, innerRadius );
		}
	}
	else
	{
		const int innerRadius = 5;
		GeometrySpringGetAngles getAngles( geometrySpring );
		const GeometryPoint * crossPoint = getAngles.getCrospoint();
		const GeometryPoint * linkToAdjustmentPoint = getAngles.getLinkToAdjacentPoint();

		{
			GeometrySpringGetShortestLinkPredicate getShortestLink( geometrySpring );

			int shortHalfWidth = getShortestLink()->getWidth() / 2;

			GetCoordsOnPhypotenuzeByWidth getWidthCoords( crossPoint, linkToAdjustmentPoint, shortHalfWidth );

			int widthX = getWidthCoords.getX();
			int widthY = getWidthCoords.getY();

			initCircleAtLinks( geometrySpring->getLinkFrom()->getMiddleX(), geometrySpring->getLinkFrom()->getMiddleY(), innerRadius );
		}

		initCompleteCircleVertex();

		GeometrySpringGetShortestLinkPredicate getShortestLink( geometrySpring );

		int Width = getShortestLink()->getWidth() / 2;

		GetCoordsOnPhypotenuzeByWidth getWidthCoords( crossPoint, linkToAdjustmentPoint, Width );
		int widthX = getWidthCoords.getX();
		int widthY = getWidthCoords.getY();

		initCircleAtLinks( geometrySpring->getLinkTo()->getMiddleX(), geometrySpring->getLinkTo()->getMiddleY(), innerRadius );
	}
}
#include <fstream>
#include <cassert>
void dump( vector<float> & arr )
{
	ofstream file( "./dump.txt" );
	if( false == file.is_open() )
	{
		assert( false );
	}

	file << arr.size() << endl << endl << flush;

	vector<float>::iterator begin = arr.begin();
	vector<float>::iterator end = arr.end();
	vector<float>::iterator iter = begin;
	for(  ; iter != end ; iter++ )
	{
		file << (* iter) << endl << flush;
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

	__evas_gl_glapi->glDrawArrays( GL_TRIANGLES, 0, vertixesCount );

	__evas_gl_glapi->glDisableVertexAttribArray( m_positionIdx );

	__evas_gl_glapi->glUseProgram( 0 );
}

















