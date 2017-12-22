#include "GamePCH.h"
#include "GLESRenderer.h"
#include "Shaders.h"
#include "Primitive.h"
#include "log.h"

#define LOG_TAG "GLESRenderer"

GLESRenderer::GLESRenderer()
{
	LOG_INFO("Constructor");
	init();
}


GLESRenderer::~GLESRenderer()
{
    destroy();
}

GLuint loadShader(GLenum shaderType, const char* pSource) {
	LOG_INFO("loadShader");
	GLuint shader = glCreateShader(shaderType);
	if (shader) {
		glShaderSource(shader, 1, &pSource, NULL);
		glCompileShader(shader);
		GLint compiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen) {
				char* buf = (char*)malloc(infoLen);
				if (buf) {
					glGetShaderInfoLog(shader, infoLen, NULL, buf);
					LOG_ERROR("Shader compile error");
					free(buf);
				}
				glDeleteShader(shader);
				shader = 0;
			}
		}
	}
	return shader;
}

GLuint GLESRenderer::createProgram(const char* pVertexSource, const char* pFragmentSource) {
	_vs = loadShader(GL_VERTEX_SHADER, pVertexSource);
	if (!_vs) {
		LOG_INFO("couldnt load shader");
		return 0;
	}

	LOG_INFO("loaded shader");

	_fs = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
	if (!_fs) {
		return 0;
	}

	GLuint program = glCreateProgram();
	if (program) {
		glAttachShader(program, _vs);
		glAttachShader(program, _fs);
		glLinkProgram(program);
		GLint linkStatus = GL_FALSE;
		glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
		if (linkStatus != GL_TRUE) {
			GLint bufLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
			if (bufLength) {
				char* buf = (char*)malloc(bufLength);
				if (buf) {
					glGetProgramInfoLog(program, bufLength, NULL, buf);
					free(buf);
				}
			}
			glDeleteProgram(program);
			program = 0;
		}
	}
	return program;
}

bool GLESRenderer::init()
{
	_program = createProgram(vShaderStr, fShaderStr);
	if (!_program)
		return false;

	_attributePos = glGetAttribLocation(_program, "vPosition");
	_uniformOffset = glGetUniformLocation(_program, "vOffset");
	_uniformColor = glGetUniformLocation(_program, "vColor");

	glUseProgram(_program);

	return true;
}

void GLESRenderer::DrawPrimitiveAt(const Primitive& primitive, const Vector2D& screenPosition)
{
	auto primitiveColor = primitive.GetColor();

	auto vVertices = primitive.GetLocalVerticesData();

	glVertexAttribPointer(_attributePos, 2, GL_FLOAT, 1, 0, vVertices);

	glUniform2f(_uniformOffset, screenPosition.x, screenPosition.y);

	glUniform4f(_uniformColor, primitiveColor.r, primitiveColor.g, primitiveColor.b, 1.f);

	glEnableVertexAttribArray(_attributePos);

	glDrawArrays(GL_TRIANGLES, 0, primitive.GetVerticesCount());
}

void GLESRenderer::destroy()
{
    glUseProgram(0);
    glDeleteProgram(_program);
    glDeleteShader(_vs);
    glDeleteShader(_fs);

    _program = _vs = _fs = 0;
}