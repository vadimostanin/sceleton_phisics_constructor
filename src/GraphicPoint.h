/*
 * GraphicsPoint.h
 *
 *  Created on: Mar 17, 2015
 *      Author: vostanin
 */

#ifndef GRAPHICPOINT_H_
#define GRAPHICPOINT_H_

#include <Evas.h>
#include "Point.h"
#include "IGraphicObject.h"
#include <Evas_GL.h>
#include <vector>
using namespace std;

class GraphicPoint : public IGraphicObject
{
public:
	GraphicPoint( Evas_Object * glview );
	GraphicPoint( Evas_Object * glview, int x, int y );
	GraphicPoint( Evas_Object * glview, const Point & point );
	GraphicPoint( const GraphicPoint & src );
	virtual ~GraphicPoint();
	bool operator ==( const GraphicPoint & src );
	int getX();
	int getY();
	void setX( int x );
	void setY( int y );

	virtual void draw( Evas * canvas );
private:
	Point m_Point;

	vector<GLfloat> m_vertexBuffer;
	GLuint       	m_vertexesBufferObject;
	GLuint       	m_vboPosition;
	Evas_GL_API   * m_glApi;

	GLuint       	m_Program;
	GLuint       	m_vertexShader;
	GLuint       	m_fragmentShader;

	void initCircleVertex();
	int initShaders();
	GLuint loadShader( GLenum type, const char *shader_src );

	void draw_circle_2d();
};

#endif /* GRAPHICPOINT_H_ */
