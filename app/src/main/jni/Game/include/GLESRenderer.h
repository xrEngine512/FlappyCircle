#pragma once

class Primitive;

class GLESRenderer
{
public:
	GLESRenderer();
	~GLESRenderer();

	void DrawPrimitiveAt(const Primitive& primitive, const Vector2D& screenPosition);

private:
	bool init();
    void destroy();
    GLuint createProgram(const char* pVertexSource, const char* pFragmentSource);

    GLuint		_program,
                _vs, _fs;
	GLuint		_attributePos;
	GLuint		_uniformOffset;
	GLuint		_uniformColor;

};

