#pragma once
#include "GameObject.h"
#include "CirclePrimitive.h"
#include <atomic>

class Player :
	public GameObject
{
public:
	Player();
	~Player();

	void Press();
	void Release();
	void Update(float dt) override;
	
	Primitive& Geometry() override;
	const Primitive& Geometry() const override;
private:
	CirclePrimitive				_view;
	std::atomic_bool			_isPressed;
	float						_fallingVelocity;
};

