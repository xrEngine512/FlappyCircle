#pragma once

class GameObject;

class Tools
{
public:
	static void UpdateScreenResolution();
	static float GetAspectRatio();
	static Vector2D ConvertToUniform(const Vector2D& point);
	static bool Intersects(const GameObject* object1, const GameObject* object2);
	static bool Intersects(const Vector2D& rectPos, const Vector2D& rectSize, const Vector2D& circleCenter, float circleRadius);
	static bool Contains(const Vector2D& rectPos, const Vector2D& rectSize, const Vector2D& point);
	static std::vector<Vector2D> Triangulate(const std::vector<Vector2D>& polygon);
    static Vector2D Vector2DPosition(int x, int y);
    static Vector2D Vector2DSize(int x, int y);
};

