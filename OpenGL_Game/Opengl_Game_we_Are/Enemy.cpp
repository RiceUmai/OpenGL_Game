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

Enemy::~Enemy()
{
}

void Enemy::Update(float DeltaTime)
{
	angle = glfwGetTime() * 5;
	Rotation = Direction;
	Rotation.z = 0;
	Position += Direction * DeltaTime * MoveSpeed;
	Updata(DeltaTime);
}

void Enemy::Set_rnd_Position(float min, float max)
{
	Position.x = random_float(min + 25, max + 25);
	Position.y = random_float(min, max);
	Position.z = random_float(min, max);

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

	dir.z = sqrt(1- (pow(dir.x, 2) + pow(dir.y, 2)));
	//dir.z = random_float(-1.0, 1.0);
	return dir;
}
