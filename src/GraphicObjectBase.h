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

#define SHADER(shader) #shader

class GraphicObjectBase
{
protected:
	GraphicObjectBase();
	GraphicObjectBase( Evas_Object * glview );
	GraphicObjectBase( const GraphicObjectBase & src );
	virtual ~GraphicObjectBase();

	void init_matrix( GLfloat * result );
	void translate_xyz( GLfloat* result, const float translatex, const float translatey, const float translatez );
	void scale_xyz( GLfloat* result, const float scale_x, const float scale_y, const float scale_z );
	void rotate_xyz( GLfloat* result, const GLfloat anglex, const GLfloat angley, const GLfloat anglez );
	void multiply_matrix( GLfloat* result, const float *matrix0, const float *matrix1 );
	void view_set_ortho( GLfloat* result, const float left, const float right, const float bottom, const float top, const float near, const float far );
	void view_set_perspective( GLfloat* result, const float fovy, const float aspect, const float near, const float far );

	float pixels_to_coords_x( unsigned int x );
	float pixels_to_coords_y( unsigned int y );

	int initShaders();
	GLuint loadShader( GLenum type, const char *shader_src );

	void initProjectionMatrix( GLfloat * result );

	virtual string getVertexShader();
	virtual string getFragmentShader();

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

	GLint m_perspective_idx;
	GLint m_translate_idx;
	GLint m_scale_idx;
	GLint m_rotate_idx;

	GLint m_color_idx;

};

#endif /* GRAPHICOBJECTBASE_H_ */
