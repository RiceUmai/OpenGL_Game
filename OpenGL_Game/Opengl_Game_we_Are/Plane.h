#pragma once
#include "Cube.h"
#include <vector>
class Plane : public Cube
{
private:
	std::vector<Plane> plane;
	int planeIndex = 4;
public:
	Plane();
	~Plane();
	
	void Update();
};

