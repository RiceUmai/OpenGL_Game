#include "Plane.h"

Plane::Plane()
{
	Tag = "Plane";
}

Plane::~Plane()
{
}

void Plane::Update(float DeltaTime)
{
	Updata(DeltaTime);
}
