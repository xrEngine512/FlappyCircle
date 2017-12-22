#pragma once
#include "GameObject.h"
#include "RectanglePrimitive.h"

class Pipe :
	public GameObject
{
public:
	explicit Pipe(float w = .1f, float h = .5f);
	~Pipe();

	void Update(float dt) override;

	Primitive& Geometry() override;
	const Primitive& Geometry() const override;
private:
	RectanglePrimitive	_view;
};

