#include "GamePCH.h"
#include "GameObject.h"



GameObject::GameObject()
{
}

void GameObject::SetPosition(const Vector2D& position)
{
	_worldPosition = position;
}

Vector2D GameObject::GetPosition() const
{
	return _worldPosition;
}

void GameObject::Move(const Vector2D& delta)
{
	_worldPosition += delta;
}

Vector2D GameObject::GetScreenPosition(const Vector2D& cameraPosition) const
{
	return _worldPosition - cameraPosition;
}

GameObject::~GameObject()
{
}
