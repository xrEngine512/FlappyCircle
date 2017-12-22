#pragma once
#include "Primitive.h"
class RectanglePrimitive :
	public Primitive
{
public:
	explicit RectanglePrimitive(float width = .1f, float height = .1f);
	~RectanglePrimitive();

	void SetWidth(float w) noexcept;
	void SetHeight(float h) noexcept;

	float GetWidth() const noexcept;
	float GetHeight() const noexcept;

	Vector2D GetSize() const;

private:
	float	_width, _height;

	void generateLocalVertices();
};

