#pragma once
#include "Cube.h"
class Enemy : public Cube
{
private:

public:
	Enemy();
	Enemy(glm::vec3 pos);
	Enemy(float x, float y, float z);
	~Enemy();

	void Update();
};

