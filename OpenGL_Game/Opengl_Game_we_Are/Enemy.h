#pragma once
#include <random>
#include <cmath>
#include "Cube.h"

class Enemy : public Cube
{
private:
	glm::vec3 Direction;
	float MoveSpeed;
public:
	Enemy();
	Enemy(glm::vec3 pos);
	Enemy(float rndMin, float rndMax);
	~Enemy();

	void Update(float DeltaTime);
	void SetDirection(glm::vec3 dir) { Direction=dir; };
	void Set_rnd_Position(float min, float max);

	glm::vec3 GetDirection() { return Direction; };

private:
	float random_float(float min, float max);
	glm::vec3 random_Direction();
};

