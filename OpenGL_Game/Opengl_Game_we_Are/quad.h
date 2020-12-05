#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#include "Camera.h"
#include "Shader.h"

#include "Setting.h"

class quad
{
private:
	unsigned int quadVAO, quadVBO;
	unsigned int Texture;
	std::vector<Shader> Shaders;
	int Shaders_indice = 0;
	Shader test;
public:
	quad();
	~quad();
	void SetTexture(unsigned int texture) { Texture = texture; };

	void Draw();
	void Draw(Shader shader);
	
	void Next_Shaders_indice(); //useing shader Controller index(Next)
	void Previous_Shaders_indice(); //useing shader Controller index(Previous)

private:
	void Init();
	void ShadersInit();
	void ShaderControl();
};