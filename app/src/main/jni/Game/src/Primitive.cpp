#include "GamePCH.h"
#include "Primitive.h"


Primitive::Primitive():
	_color()
{
}


Primitive::~Primitive()
{
}

const GLfloat* Primitive::GetLocalVerticesData() const
{
	return reinterpret_cast<const GLfloat*>(_vertices.data());
}

GLint Primitive::GetVerticesCount() const
{
	return _vertices.size();
}

void Primitive::SetColor(const Color& color)
{
	_color = color;
}

Color Primitive::GetColor() const
{
	return _color;
}
