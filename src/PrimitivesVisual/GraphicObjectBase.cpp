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
}

GraphicObjectBase::GraphicObjectBase( Evas_Object * glview ) : m_vertexesBufferObject( 0 ), m_Program( 0 ), m_vertexShader( 0 ), m_fragmentShader( 0 ),
															   m_positionIdx( 0 )
{
	m_glApi = elm_glview_gl_api_get( glview );

	m_glApi->glEnable( GL_POINT_SIZE );

	elm_glview_size_get( glview, &m_DrawCanvasWidth, &m_DrawCanvasHeight );

	initProjectionMatrix( m_projectionMatrix );
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
	m_perspective_idx = src.m_perspective_idx;
	m_translate_idx = src.m_translate_idx;
	m_scale_idx = src.m_scale_idx;
	m_rotate_idx = src.m_rotate_idx;
	m_DrawCanvasWidth = src.m_DrawCanvasWidth;
	m_DrawCanvasHeight = src.m_DrawCanvasHeight;

	initProjectionMatrix( m_projectionMatrix );
}

GraphicObjectBase::~GraphicObjectBase()
{
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

void GraphicObjectBase::scale_xyz( GLfloat * result, const float scale_x, const float scale_y, const float scale_z )
{
	result[0]  = scale_x * result[0];
	result[5]  = scale_y * result[5];
	result[10] = scale_z * result[10];
}

void GraphicObjectBase::rotate_xyz( GLfloat * result, const GLfloat anglex, const GLfloat angley, const GLfloat anglez)
{
	float temp[16];
	float rz = 2.0f * M_PI * anglez / 360.0f;
	float rx = 2.0f * M_PI * anglex / 360.0f;
	float ry = 2.0f * M_PI * angley / 360.0f;
	float sy = sinf(ry);
	float cy = cosf(ry);
	float sx = sinf(rx);
	float cx = cosf(rx);
	float sz = sinf(rz);
	float cz = cosf(rz);

	init_matrix(temp);

	temp[0] = cy * cz - sx * sy * sz;
	temp[1] = cz * sx * sy + cy * sz;
	temp[2] = -cx * sy;

	temp[4] = -cx * sz;
	temp[5] = cx * cz;
	temp[6] = sx;

	temp[8] = cz * sy + cy * sx * sz;
	temp[9] = -cy * cz * sx + sy * sz;
	temp[10] = cx * cy;

	multiply_matrix(result, result, temp);
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

void GraphicObjectBase::view_set_perspective(GLfloat* result, const float fovy, const float aspect, const float near, const float far)
{
	float fovradian = fovy / 360.0f * M_PI;
	float top = tanf(fovradian) * near;
	float right = top * aspect;

	view_set_ortho( result, -right, right, -top, top, near, far );
}

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
	m_rotate_idx = 		__evas_gl_glapi->glGetUniformLocation( m_Program, "rotate" );
	m_color_idx = 		__evas_gl_glapi->glGetUniformLocation( m_Program, "v_color" );

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
							uniform mat4 rotate;

							uniform vec4 v_color;
							varying vec4 f_color;

							void main()
							{
							   gl_Position = perspective * rotate * translate * scale * vec4( vPosition, 1.0 );
							   f_color = v_color;
							}

						);

	return shader;
}

string GraphicObjectBase::getFragmentShader()
{
	string shader =	SHADER(

							varying vec4 f_color;
							void main()
							{
								gl_FragColor = f_color;
							}

						);

	return shader;
}

float GraphicObjectBase::pixels_to_coords_x( unsigned int x )
{
	float translate_x =  ( x - m_DrawCanvasWidth /  2.0 );
	translate_x  /= (float)( m_DrawCanvasWidth / 2 );

	return translate_x;
}

float GraphicObjectBase::pixels_to_coords_y( unsigned int y )
{
	float translate_y = ( m_DrawCanvasHeight / 2.0 - y + 60 );
	translate_y /=  (float)( m_DrawCanvasHeight / 2 );

	return translate_y;
}

