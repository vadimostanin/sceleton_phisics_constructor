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
	m_glApi = 0;

	m_DrawCanvasWidth = 0;
	m_DrawCanvasHeight = 0;

	initProjectionMatrix( m_projectionMatrix );

	initShaders();
}

GraphicObjectBase::GraphicObjectBase( Evas_Object * glview ) : m_vertexesBufferObject( 0 ), m_Program( 0 ), m_vertexShader( 0 ), m_fragmentShader( 0 ),
															   m_positionIdx( 0 )
{
	m_glApi = elm_glview_gl_api_get( glview );

	elm_glview_size_get( glview, &m_DrawCanvasWidth, &m_DrawCanvasHeight );

	initProjectionMatrix( m_projectionMatrix );

	initShaders();
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
	m_DrawCanvasWidth = src.m_DrawCanvasWidth;
	m_DrawCanvasHeight = src.m_DrawCanvasHeight;

	initProjectionMatrix( m_projectionMatrix );
}

GraphicObjectBase::~GraphicObjectBase() {
	// TODO Auto-generated destructor stub
	if( 0 != m_vertexShader )
	{
		m_glApi->glDeleteShader( m_vertexShader );
	}
	if( 0 != m_fragmentShader )
	{
		m_glApi->glDeleteShader( m_fragmentShader );
	}
}

void GraphicObjectBase::init_matrix( GLfloat * result )
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

void GraphicObjectBase::translate_xyz(GLfloat* result, const float translatex, const float translatey, const float translatez)
{
	result[12] += result[0] * translatex + result[4] * translatey
			+ result[8] * translatez;
	result[13] += result[1] * translatex + result[5] * translatey
			+ result[9] * translatez;
	result[14] += result[2] * translatex + result[6] * translatey
			+ result[10] * translatez;
	result[15] += result[3] * translatex + result[7] * translatey
			+ result[11] * translatez;


//	result[3] += translatex + result[0] * translatex + result[1] * translatey
//			+ result[2] * translatez;
//	result[7] += result[4] * translatex + result[5] * translatey
//			+ result[6] * translatez;
//	result[11] += result[8] * translatex + result[9] * translatey
//			+ result[10] * translatez;
}

void GraphicObjectBase::scale_xyz( GLfloat* result, const float scale_x, const float scale_y, const float scale_z )
{
	result[0]  = scale_x * result[0];
	result[5]  = scale_y * result[5];
	result[10] = scale_z * result[10];
}

void GraphicObjectBase::multiply_matrix(GLfloat* result, const float *matrix0, const float *matrix1)
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

void GraphicObjectBase::view_set_ortho(GLfloat* result, const float left, const float right, const float bottom, const float top, const float near, const float far)
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

void GraphicObjectBase::view_set_perspective(GLfloat* result, const float fovy, const float aspect, const float near, const float far)
{
	float fovradian = fovy / 360.0f * M_PI;
	float top = tanf(fovradian) * near;
	float right = top * aspect;

	view_set_ortho( result, -right, right, -top, top, near, far );
}
//
////matrix will receive the calculated perspective matrix. //You would have to upload to your shader // or use glLoadMatrixf if you aren't using shaders.
//void glhPerspectivef2(float *matrix, float fovyInDegrees, float aspectRatio, float znear, float zfar)
//{
//    float ymax, xmax;
//    float temp, temp2, temp3, temp4;
//    ymax = znear * tanf(fovyInDegrees * M_PI / 360.0);
//    //ymin = -ymax;
//    //xmin = -ymax * aspectRatio;
//    xmax = ymax * aspectRatio;
//    glhFrustumf2(matrix, -xmax, xmax, -ymax, ymax, znear, zfar);
//}
//
//void glhFrustumf2(float *matrix, float left, float right, float bottom, float top, float znear, float zfar)
//{
//    float twice_near, width, height_negative , temp4;
//    twice_near = 2.0 * znear;
//    width = right - left;
//    height_negative = top - bottom;
//    temp4 = zfar - znear;
//
//    matrix[0] = twice_near / width;
//    matrix[1] = 0.0;
//    matrix[2] = 0.0;
//    matrix[3] = 0.0;
//
//    matrix[4] = 0.0;
//    matrix[5] = twice_near / height_negative ;
//    matrix[6] = 0.0;
//    matrix[7] = 0.0;
//
//    matrix[8] = (right + left) / width;
//    matrix[9] = (top + bottom) / height_negative ;
//    matrix[10] = (-zfar - znear) / temp4;
//    matrix[11] = -1.0;
//
//    matrix[12] = 0.0;
//    matrix[13] = 0.0;
//    matrix[14] = (- twice_near * zfar) / temp4;
//    matrix[15] = 0.0;
//}

// Initialize the shader and program object
int GraphicObjectBase::initShaders()
{
	Evas_GL_API * __evas_gl_glapi = m_glApi;
	string v_shader = getVertexShader();
	GLbyte * vShaderStr = (GLbyte *)v_shader.c_str();

	string f_shader = getFragmentShader();
	GLbyte * fShaderStr = (GLbyte *)f_shader.c_str();

	GLint linked;

	// Load the vertex/fragment shaders
	m_vertexShader  = loadShader( GL_VERTEX_SHADER, (const char*)vShaderStr);
	m_fragmentShader = loadShader( GL_FRAGMENT_SHADER, (const char*)fShaderStr);

	// Create the program object
	m_Program = __evas_gl_glapi->glCreateProgram( );
	if( m_Program == 0 )
	{
		return 0;
	}

	__evas_gl_glapi->glAttachShader( m_Program,  m_vertexShader);
	__evas_gl_glapi->glAttachShader( m_Program,  m_fragmentShader);

	__evas_gl_glapi->glLinkProgram( m_Program );
	__evas_gl_glapi->glGetProgramiv( m_Program, GL_LINK_STATUS, &linked );

	if( 0 == linked )
	{
		GLint info_len = 0;
		__evas_gl_glapi->glGetProgramiv( m_Program, GL_INFO_LOG_LENGTH, &info_len);
		if (info_len > 1)
		{
			char* info_log = (char *)malloc(sizeof(char) * info_len);

			__evas_gl_glapi->glGetProgramInfoLog( m_Program, info_len, NULL, info_log );
			printf( "Error linking program:\n%s\n", info_log );
			free( info_log );
		}
		__evas_gl_glapi->glDeleteProgram( m_Program );
		return 0;
	}

	m_positionIdx = 	__evas_gl_glapi->glGetAttribLocation( m_Program, "vPosition" );
	m_perspective_idx = __evas_gl_glapi->glGetUniformLocation( m_Program, "perspective" );
	m_translate_idx = 	__evas_gl_glapi->glGetUniformLocation( m_Program, "translate" );
	m_scale_idx = 		__evas_gl_glapi->glGetUniformLocation( m_Program, "scale" );

	return 1;
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

void GraphicObjectBase::initProjectionMatrix( GLfloat * result )
{
	result[0] = 2.0 / m_DrawCanvasHeight;
	result[4] = 0.0;
	result[8] = 0.0;
	result[12] = 0.0;

	result[1] = 0.0;
	result[5] = 2.0 / m_DrawCanvasWidth;
	result[9] = 0.0;
	result[13] = 0.0;

	result[2] = 0.0;
	result[6] = 0.0;
	result[10] = 2.0/2.0;
	result[14] = 0.0;

	result[3] = -1.0;
	result[7] = -1.0;
	result[11] = -1.0;
	result[15] = 1.0;



//	result[0] = 2.0 / m_DrawCanvasHeight;
//	result[1] = 0.0;
//	result[2] = 0.0;
//	result[3] = -1.0;
//
//	result[4] = 0.0;
//	result[5] = 2.0 / m_DrawCanvasWidth;
//	result[6] = 0.0;
//	result[7] = -1.0;
//
//	result[8] = 0.0;
//	result[9] = 0.0;
//	result[10] = 2.0/2.0;
//	result[11] = -1.0;
//
//	result[12] = 0.0;
//	result[13] = 0.0;
//	result[14] = 0.0;
//	result[15] = 1.0;
}


string GraphicObjectBase::getVertexShader()
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

string GraphicObjectBase::getFragmentShader()
{
	string shader =	SHADER(

void main()
{
	gl_FragColor = vec4( 0.5, 0.5, 1.0, 1.0 );
}

						);

	return shader;
}

