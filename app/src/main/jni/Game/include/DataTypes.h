#pragma once

template<typename T>
struct GenericVector2D
{
	T	x, y;
	GenericVector2D(): x(), y()
	{}
	GenericVector2D(T x, T y): x(x), y(y)	
	{}
	GenericVector2D(const GenericVector2D& arg)
	{
		if(&arg != this)
		{
			x = arg.x;
			y = arg.y;
		}
	}

	GenericVector2D operator-(const GenericVector2D& arg) const {
		return GenericVector2D(this->x - arg.x, this->y - arg.y);
	}

	GenericVector2D operator+(const GenericVector2D& arg) const {
		return GenericVector2D(this->x + arg.x, this->y + arg.y);
	}

	GenericVector2D operator-=(const GenericVector2D& arg) {
		return GenericVector2D(this->x -= arg.x, this->y -= arg.y);
	}

	GenericVector2D operator+=(const GenericVector2D& arg) {
		return GenericVector2D(this->x += arg.x, this->y += arg.y);
	}

	GenericVector2D operator*(float arg) const {
		return GenericVector2D(this->x * arg, this->y * arg);
	}

	GenericVector2D operator*=(float arg) {
		return GenericVector2D(this->x *= arg, this->y *= arg);
	}
};

typedef GenericVector2D<float> Vector2D;

struct Color
{
	float r, g, b;

	Color(float r = 0.f, float g = 0.f, float b = 0.f):r(r), g(g), b(b)
	{}
};
