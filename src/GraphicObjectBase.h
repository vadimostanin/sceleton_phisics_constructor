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

	void init_matrix( float * result );
	void translate_xyz(float* result, const float translatex, const float translatey, const float translatez);
	void multiply_matrix(float* result, const float *matrix0, const float *matrix1);
	void view_set_ortho(float* result, const float left, const float right, const float bottom, const float top, const float near, const float far);
	void view_set_perspective(float* result, const float fovy, const float aspect, const float near, const float far);

	GLuint loadShader( GLenum type, const char *shader_src );

	void initProjectionMatrix();

protected:

	vector<GLfloat> m_vertexBuffer;
	GLuint       	m_vertexesBufferObject;
	GLuint       	m_Program;
	GLuint       	m_vertexShader;
	GLuint       	m_fragmentShader;

	GLint       	m_mvpMatrixIdx;
	GLint       	m_positionIdx;

	Evas_GL_API   * m_glApi;

	float			m_projectionMatrix[16];

	int 			m_DrawCanvasHeight;
	int 			m_DrawCanvasWidth;

};

#endif /* GRAPHICOBJECTBASE_H_ */
