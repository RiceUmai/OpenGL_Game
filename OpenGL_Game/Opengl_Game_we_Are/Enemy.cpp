#include "Enemy.h"

Enemy::Enemy()
{
	Direction = random_Direction();
	MoveSpeed = 10.0f;
	Tag = "Enemy";
}

Enemy::Enemy(glm::vec3 pos) : Cube(pos)
{
}

Enemy::Enemy(float x, float y, float z) : Cube(x,y,z)
{
}

Enemy::~Enemy()
{
}

void Enemy::Update(float DeltaTime)
{
	Position += Direction * DeltaTime * MoveSpeed;
	Updata(DeltaTime);
}

float Enemy::random_float(float min, float max)
{
	return ((float)rand() / RAND_MAX) * (max - min) + min;
}

glm::vec3 Enemy::random_Direction()
{
	glm::vec3 dir;
	dir.x = random_float(-1.0, 1.0);
	dir.y = random_float(-1.0, 1.0);
	dir.z = random_float(-1.0, 1.0);
	return dir;
}
