#include "GamePCH.h"
#include "Player.h"
#include "CirclePrimitive.h"
#include <algorithm>

Player::Player():
	_view(0.05f),
	_isPressed(false), 
	_fallingVelocity(0)
{
	_view.SetColor(Color(.3f, .3f, .7f));
}

Player::~Player()
{
}

void Player::Press()
{
 	_isPressed.store(true);
}

void Player::Release()
{
	_isPressed.store(false);
}

void Player::Update(float dt)
{
	if (_isPressed.is_lock_free() && _isPressed.load())	// avoiding lock for smooth gameplay
	{
		_fallingVelocity -= 7;

		_fallingVelocity = std::min(std::max(_fallingVelocity, -2.5f), -1.5f);		
	}
	else
		_fallingVelocity += 9.8 * dt;
	

	_worldPosition.y -= _fallingVelocity * dt * Constants::FallingAndFlyingSpeed;
}

Primitive& Player::Geometry()
{
	return _view;
}

const Primitive& Player::Geometry() const
{
	return _view;
}

