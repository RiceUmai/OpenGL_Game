#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Image.h"
#include "Camera.h"


class Cube
{
private:
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;
	float angle;
	unsigned char texture;
	unsigned int VBO, cubeVAO;
	Camera camera;
public:
	Cube();
	Cube(glm::vec3 pos);
	Cube(float x, float y, float z);
	~Cube();
	void Draw(Shader shader, glm::mat4 projection, glm::mat4 view);

	void SetPosition(glm::vec3 pos) { Position = pos; };
	void SetRotation(glm::vec3 rot, float Angle) { Rotation = rot; angle = Angle; };;
	void SetScale(glm::vec3 scale) { Scale = scale; };

	void SetImage(char const * path);

	glm::vec3 GetPosition() { return Position; };
	glm::vec3 GetRotation() { return Rotation; };
	glm::vec3 GetScale() { return Scale; };

private:
	void Init();
};

