#include "Enemy.h"

Enemy::Enemy()
{
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

void Enemy::Update()
{
	Updata();
}
