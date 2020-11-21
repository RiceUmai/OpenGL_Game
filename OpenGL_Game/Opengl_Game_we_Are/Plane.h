#pragma once
#include "Cube.h"
#include <vector>
class Plane : public Cube
{
private:

public:
	Plane();
	~Plane();
	
	void Update(float DeltaTime);
};

