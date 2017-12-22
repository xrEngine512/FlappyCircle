#pragma once
class Primitive
{
public:
	Primitive();
	virtual ~Primitive();
	const GLfloat* GetLocalVerticesData() const;
	GLint GetVerticesCount() const;

	void SetColor(const Color& color);
	Color GetColor() const;

protected:
	Color				_color;
	vector<Vector2D>	_vertices;
};

