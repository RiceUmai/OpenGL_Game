#include "Plane.h"

Plane::Plane()
{
	Position = glm::vec3(0, 0, 0);
	Rotation = glm::vec3(1.0f, 1.0f, 1.0f);
	Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	angle = 0;
	void Init();
}

Plane::Plane(glm::vec3 pos)
{
	Position = pos;
	Rotation = glm::vec3(1.0f, 1.0f, 1.0f);
	Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	angle = 0;
	void Init();
}

Plane::Plane(float x, float y, float z)
{
	Position.x = x;
	Position.y = y;
	Position.z = z;
	Rotation = glm::vec3(1.0f, 1.0f, 1.0f);
	Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	angle = 0;
	void Init();
}

void Plane::Draw(Shader shader, glm::mat4 projection, glm::mat4 view)
{
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	shader.use();

	glm::mat4 model = glm::mat4(1.0f);

	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	shader.setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Plane::SetImage(char const* path)
{
	Image image(path);
	texture = image.getTextureID();
}

void Plane::Init()
{

	float Vertices[] = {
		// positions          // texture Coords 
		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}
