#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Cube
{
private:
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

public:
	Cube();
	void Draw();

	glm::vec3 SetPosition(glm::vec3 pos) { Position = pos; };
	glm::vec3 SetRotation(glm::vec3 rot) { Rotation = rot; };
	glm::vec3 SetScale(glm::vec3 scale) { Scale = scale; };

	glm::vec3 GetPosition() { return Position; };
	glm::vec3 GetRotation() { return Rotation; };
	glm::vec3 GetScale() { return Scale; };
};

