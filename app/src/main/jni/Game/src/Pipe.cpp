#include "GamePCH.h"
#include "Pipe.h"


Pipe::Pipe(float w, float h):
	_view(w, h)
{
	_view.SetColor(Color(0.f, 1.f, 0.f));
}


Pipe::~Pipe()
{
}

void Pipe::Update(float dt)
{

}

Primitive& Pipe::Geometry()
{
	return _view;
}

const Primitive& Pipe::Geometry() const
{
	return _view;
}
