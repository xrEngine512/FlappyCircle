#pragma once
#include "Primitive.h"

const int segmentation = 32;

class CirclePrimitive :
	public Primitive
{
public:
	CirclePrimitive(float radius = 0.1f);
	~CirclePrimitive();

	void SetRadius(float r);
	float GetRadius() const;

private:
	float		_radius;

	void generateLocalVertices();
};

