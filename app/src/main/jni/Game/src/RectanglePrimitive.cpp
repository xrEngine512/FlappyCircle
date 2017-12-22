#include "GamePCH.h"
#include "RectanglePrimitive.h"


RectanglePrimitive::RectanglePrimitive(float width, float height):
	_width(width),
	_height(height)
{
	generateLocalVertices();
}

RectanglePrimitive::~RectanglePrimitive()
{
}

void RectanglePrimitive::SetWidth(float w) noexcept
{
	_width = w;
	generateLocalVertices();
}

void RectanglePrimitive::SetHeight(float h) noexcept
{
	_height = h;
	generateLocalVertices();
}

float RectanglePrimitive::GetWidth() const noexcept
{
	return _width;
}

float RectanglePrimitive::GetHeight() const noexcept
{
	return _height;
}

Vector2D RectanglePrimitive::GetSize() const
{
	return Vector2D(_width, _height);
}

void RectanglePrimitive::generateLocalVertices()
{
	_vertices.clear();

	auto vertex = Vector2D(0.f, 0.f);
	_vertices.push_back(vertex);

	vertex = Tools::ConvertToUniform(Vector2D(_width, 0.f));
	_vertices.push_back(vertex);

	vertex = Tools::ConvertToUniform(Vector2D(_width, -_height));
	_vertices.push_back(vertex);

	vertex = Tools::ConvertToUniform(Vector2D(0.f, -_height));
	_vertices.push_back(vertex);

	_vertices = Tools::Triangulate(_vertices);
}
