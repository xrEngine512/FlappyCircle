#pragma once
#include "DataTypes.h"

class Primitive;

class GameObject
{
public:
	GameObject();
	void SetPosition(const Vector2D& position);
	Vector2D GetPosition() const;
	void Move(const Vector2D& delta);
	Vector2D GetScreenPosition(const Vector2D& cameraPosition) const;

	virtual void Update(float dt) = 0;
	virtual Primitive& Geometry() = 0;
	virtual const Primitive& Geometry() const = 0;

	virtual ~GameObject();
protected:
	Vector2D	_worldPosition;
};

