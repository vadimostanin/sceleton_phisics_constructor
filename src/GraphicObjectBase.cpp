/*
 * GraphicObjectBase.cpp
 *
 *  Created on: Mar 20, 2015
 *      Author: vostanin
 */

#include "GraphicObjectBase.h"
#include <Elementary.h>

GraphicObjectBase::GraphicObjectBase() : m_vertexesBufferObject( 0 ), m_Program( 0 ), m_vertexShader( 0 ), m_fragmentShader( 0 )
{
	m_mvpMatrix = new float[16];
	m_glApi = 0;

	init_matrix( m_mvpMatrix );

	m_DrawCanvasWidth = 0;
	m_DrawCanvasHeight = 0;
}

GraphicObjectBase::GraphicObjectBase( Evas_Object * glview ) : m_vertexesBufferObject( 0 ), m_Program( 0 ), m_vertexShader( 0 ), m_fragmentShader( 0 ),
															   m_mvpMatrixIdx( 0 ), m_positionIdx( 0 )
{
	m_mvpMatrix = new float[16];
	m_glApi = elm_glview_gl_api_get( glview );

	init_matrix( m_mvpMatrix );

	elm_glview_size_get( glview, &m_DrawCanvasWidth, &m_DrawCanvasHeight );

}

GraphicObjectBase::GraphicObjectBase( const GraphicObjectBase & src )
{
	m_vertexBuffer = src.m_vertexBuffer;
	m_vertexesBufferObject = src.m_vertexesBufferObject;
	m_glApi = src.m_glApi;
	m_Program = src.m_Program;
	m_vertexShader = src.m_vertexShader;
	m_fragmentShader = src.m_fragmentShader;
	m_positionIdx = src.m_positionIdx;
	m_mvpMatrixIdx = src.m_mvpMatrixIdx;
	m_mvpMatrix = src.m_mvpMatrix;
	m_DrawCanvasWidth = src.m_DrawCanvasWidth;
	m_DrawCanvasHeight = src.m_DrawCanvasHeight;
}

GraphicObjectBase::~GraphicObjectBase() {
	// TODO Auto-generated destructor stub
}

void GraphicObjectBase::init_matrix( float * result )
{
	result[0] = 1.0f;
	result[1] = 0.0f;
	result[2] = 0.0f;
	result[3] = 0.0f;

	result[4] = 0.0f;
	result[5] = 1.0f;
	result[6] = 0.0f;
	result[7] = 0.0f;

	result[8] = 0.0f;
	result[9] = 0.0f;
	result[10] = 1.0f;
	result[11] = 0.0f;

	result[12] = 0.0f;
	result[13] = 0.0f;
	result[14] = 0.0f;
	result[15] = 1.0f;
}

void GraphicObjectBase::translate_xyz(float* result, const float translatex, const float translatey, const float translatez)
{
	result[12] += result[0] * translatex + result[4] * translatey
			+ result[8] * translatez;
	result[13] += result[1] * translatex + result[5] * translatey
			+ result[9] * translatez;
	result[14] += result[2] * translatex + result[6] * translatey
			+ result[10] * translatez;
	result[15] += result[3] * translatex + result[7] * translatey
			+ result[11] * translatez;
}

void GraphicObjectBase::multiply_matrix(float* result, const float *matrix0, const float *matrix1)
{
	int row_i = 0, column_i = 0;
	float temp[16] = { 0 };

	for( column_i = 0; column_i < 4; column_i++)
	{
		for( row_i = 0; row_i < 4; row_i++)
		{
			temp[column_i * 4 + row_i] = 0.0f;
			for( int column_row_i = 0; column_row_i < 4; column_row_i++)
			{
				temp[column_i * 4 + row_i] += matrix0[column_row_i * 4 + row_i] * matrix1[column_i * 4 + column_row_i];
			}
		}
	}

	for( int result_i = 0; result_i < 16; result_i++ )
	{
		result[result_i] = temp[result_i];
	}
}

void GraphicObjectBase::view_set_ortho(float* result, const float left, const float right, const float bottom, const float top, const float near, const float far)
{
	float diffx = right - left;
	float diffy = top - bottom;
	float diffz = far - near;

	if( ( near <= 0.0f ) || ( far <= 0.0f ) || ( diffx <= 0.0f ) || ( diffy <= 0.0f ) || ( diffz <= 0.0f ) )
	{
		return;
	}

	result[0] = 2.0f * near / diffx;
	result[1] = 0.0f;
	result[2] = 0.0f;
	result[3] = 0.0f;

	result[4] = 0.0f;
	result[5] = 2.0f * near / diffy;
	result[6] = 0.0f;
	result[7] = 0.0f;

	result[8] = (right + left) / diffx;
	result[9] = (top + bottom) / diffy;
	result[10] = -(near + far) / diffz;
	result[11] = -1.0f;

	result[12] = 0.0f;
	result[13] = 0.0f;
	result[14] = -2.0f * near * far / diffz;
	result[15] = 0.0f;
}

void makeFrustum( float * result, const float left, const float right, const float bottom, const float top, const float near, const float far )
{
	result[0] = 2.0f * near / (right - left);
	result[1] = 0.0;
	result[2] = 0.0;
	result[3] = 0.0;

	result[4] = 0.0;
	result[5] = 2.0f * near / (top - bottom);
	result[6] = 0.0;
	result[7] = 0.0;

	result[8] = (right + left) / (right - left);
	result[9] = (top + bottom) / (top - bottom);
	result[10] = - (far + near) / (far - near);
	result[11] = -1.0f;

	result[12] = 0.0;
	result[13] = 0.0;
	result[14] = -2.0f * far * near / (far - near);
	result[15] = 0.0;
}

void GraphicObjectBase::view_set_perspective(float* result, const float fovy, const float aspect, const float near, const float far)
{
	float fovradian = fovy / 360.0f * M_PI;
	float top = tanf(fovradian) * near;
	float right = top * aspect;

	view_set_ortho( result, -right, right, -top, top, near, far );

//	const float range = near - far;
//	const float fovradian = fovy / 2 / 360.0f * M_PI;
//	const float tanHalfFOV = tanf( fovradian );
//
//	result[0] = 1.0;
//	result[1] = 0.0;
//	result[2] = 0.0;
//	result[3] = 0.0;
//
//	result[4] = 0.0;
//	result[5] = 1.0;
//	result[6] = 0.0;
//	result[7] = 0.0;
//
//	result[8] = 0.0;
//	result[9] = 0.0;
//	result[10] = ( ( -1 ) * near - far ) / range;
//	result[11] = 2.0 * far * near / range;
//
//	result[12] = 0.0;
//	result[13] = 0.0;
//	result[14] = 1.0;
//	result[15] = 0.0;

//	const float range = near - far;
//	const float fovradian = fovy / 2 / 360.0f * M_PI;
//	const float tanHalfFOV = tanf( fovradian );
//	const float size = near * tanf( fovradian );
//
//	makeFrustum( result, -size, size, -size / aspect, size / aspect, near, far );

}

//--------------------------------//
// a helper function to load shaders from a shader source
GLuint GraphicObjectBase::loadShader( GLenum type, const char *shader_src )
{
	Evas_GL_API * __evas_gl_glapi = m_glApi;
	GLuint shader;
	GLint compiled;

	// Create the shader object
	shader = __evas_gl_glapi->glCreateShader(type);
	if( shader == 0 )
	{
		return 0;
	}

	// Load/Compile shader source
	__evas_gl_glapi->glShaderSource(shader, 1, &shader_src, NULL);
	__evas_gl_glapi->glCompileShader(shader);
	__evas_gl_glapi->glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		GLint info_len = 0;
		__evas_gl_glapi->glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);
		if (info_len > 1)
		{
			char* info_log = (char *)malloc(sizeof(char) * info_len);

			__evas_gl_glapi->glGetShaderInfoLog(shader, info_len, NULL, info_log);
			printf("Error compiling shader:\n%s\n======\n%s\n======\n", info_log, shader_src );
			free(info_log);
		}
		__evas_gl_glapi->glDeleteShader(shader);
		return 0;
	}

	return shader;
}
