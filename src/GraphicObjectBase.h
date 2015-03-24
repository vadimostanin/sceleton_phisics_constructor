/*
 * GraphicObjectBase.h
 *
 *  Created on: Mar 20, 2015
 *      Author: vostanin
 */

#ifndef GRAPHICOBJECTBASE_H_
#define GRAPHICOBJECTBASE_H_

#include "IGraphicObject.h"
#include <Evas_GL.h>
#include <vector>
using namespace std;

class GraphicObjectBase : public IGraphicObject
{
protected:
	GraphicObjectBase();
	GraphicObjectBase( Evas_Object * glview );
	GraphicObjectBase( const GraphicObjectBase & src );
	virtual ~GraphicObjectBase();

	void init_matrix( GLfloat * result );
	void translate_xyz( GLfloat* result, const float translatex, const float translatey, const float translatez );
	void scale_xyz( GLfloat* result, const float scale_x, const float scale_y, const float scale_z );
	void multiply_matrix( GLfloat* result, const float *matrix0, const float *matrix1 );
	void view_set_ortho( GLfloat* result, const float left, const float right, const float bottom, const float top, const float near, const float far );
	void view_set_perspective( GLfloat* result, const float fovy, const float aspect, const float near, const float far );

	GLuint loadShader( GLenum type, const char *shader_src );

	void initProjectionMatrix( GLfloat * result );

protected:

	vector<GLfloat> m_vertexBuffer;
	GLuint       	m_vertexesBufferObject;
	GLuint       	m_Program;
	GLuint       	m_vertexShader;
	GLuint       	m_fragmentShader;

	GLint       	m_positionIdx;

	Evas_GL_API   * m_glApi;

	float			m_projectionMatrix[16];

	int 			m_DrawCanvasHeight;
	int 			m_DrawCanvasWidth;

};

#endif /* GRAPHICOBJECTBASE_H_ */
