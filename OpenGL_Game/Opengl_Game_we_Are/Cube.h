#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Image.h"

class Cube
{
protected:
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;
	
	glm::vec3 maxPos;
	glm::vec3 minPos;

	float angle;
	unsigned char texture;
	unsigned int VBO, cubeVAO;
	//float maxX, maxY, maxZ;
	//float minX, minY, minZ;

	glm::vec3 Color;

public:
	Cube();
	Cube(glm::vec3 pos);
	Cube(float x, float y, float z);
	~Cube();
	
	void Updata();
	void Draw(Shader shader, glm::mat4 projection, glm::mat4 view);

	void SetPosition(glm::vec3 pos) { Position = pos; Collision_Update(); };
	void SetRotation(glm::vec3 rot, float Angle) { Rotation = rot; angle = Angle; };;
	void SetScale(glm::vec3 scale) { Scale = scale; Collision_Update();};
	void SetColor(glm::vec3 color) { Color = color; };

	void SetImage(char const * path);

	glm::vec3 GetPosition() { return Position; };
	glm::vec3 GetRotation() { return Rotation; };
	glm::vec3 GetScale() { return Scale; };

	glm::vec3 GetMaxPos() { return maxPos; };
	glm::vec3 GetMinPos() { return minPos; };

	glm::vec3 GetColor() { return Color; };

protected:
	void Init();
	void Collision_Update();
};

