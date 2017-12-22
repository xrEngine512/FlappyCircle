#include "GamePCH.h"
#include "CirclePrimitive.h"
#define _USE_MATH_DEFINES
#include <math.h>


CirclePrimitive::CirclePrimitive(float radius):
	_radius(radius)
{
	generateLocalVertices();
}


CirclePrimitive::~CirclePrimitive()
{
}

void CirclePrimitive::SetRadius(float r)
{
	_radius = r;
	generateLocalVertices();
}

float CirclePrimitive::GetRadius() const
{
	return _radius;
}

void CirclePrimitive::generateLocalVertices()
{
	_vertices.clear();

	for (int i = 0; i < segmentation; ++i)
	{
		auto angle = float(i) / segmentation * 2 * M_PI;
		auto vertex = Tools::ConvertToUniform(Vector2D(_radius * cos(angle), _radius * sin(angle)));
		_vertices.push_back(vertex);
	}

	_vertices = Tools::Triangulate(_vertices);
}
