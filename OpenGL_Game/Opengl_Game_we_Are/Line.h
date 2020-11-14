#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

class Line
{
private:
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scals;

	glm::vec3 color;

	float Width;
	float angle;

	unsigned int VBO, LineVAO;
public:
	Line();
	Line(glm::vec3 position);
	~Line();
	
	void SetWidth(float width) { Width = width; };
	void SetColor(glm::vec3 Color) { color = Color; };
	void SetPosition(glm::vec3 pos) { Position = pos; };
	void SetScals(glm::vec3 scale) { Scals = scale; };

	void Draw(Shader shader, glm::mat4 projection, glm::mat4 view);

private:
	void Init();
};

