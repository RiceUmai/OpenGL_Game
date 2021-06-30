#include "quad.h"

quad::quad()
{
	Init();
	ShadersInit();
}

quad::~quad()
{
	glDeleteVertexArrays(1, &quadVAO);
	glDeleteBuffers(1, &quadVBO);
}

//===================================================
//Screen Draw
//===================================================
void quad::Draw()
{
	ShaderControl();
	glBindVertexArray(quadVAO);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void quad::Draw(Shader shader)
{
	shader.use();
	glBindVertexArray(quadVAO);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
//===================================================
//===================================================

/// <summary>
/// Shaders(Vector Type) index increase
/// </summary>
void quad::Next_Shaders_indice()
{
	if (Shaders_indice < Shaders.size() - 1)	Shaders_indice++;
	else Shaders_indice = Shaders.size() - 1;

	std::cout << Shaders_indice << std::endl;
}

/// <summary>
/// Shaders(Vector Type) index decrease
/// </summary>
void quad::Previous_Shaders_indice()
{
	if (Shaders_indice > 0) Shaders_indice--;
	else Shaders_indice = 0;

	std::cout << Shaders_indice << std::endl;
}

/// <summary>
/// Class Init
/// </summary>
void quad::Init()
{
	float quadVertices[] =
	{
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

/// <summary>
/// Shader登録
/// </summary>
void quad::ShadersInit()
{
	//ShaderData is Init in Shaders(Vector Type) 
	Shaders.push_back(Shader("Shader/framebuffers_screen.vs", "Shader/framebuffers_screen.fs"));
	Shaders.push_back(Shader("Shader/screen_Moveing.vs", "Shader/screen_Moveing.fs"));
	Shaders.push_back(Shader("Shader/screen_split.vs", "Shader/screen_split.fs"));
	Shaders.push_back(Shader("Shader/Mosaic.vs", "Shader/Mosaic.fs"));
	Shaders.push_back(Shader("Shader/Grayscale.vs", "Shader/Grayscale.fs"));
}

/// <summary>
/// Shaderを変更、コントロール
/// </summary>
void quad::ShaderControl()
{
	switch (Shaders_indice)
	{
	case 0:
		Shaders[Shaders_indice].setFloat("Time", glfwGetTime());
		Shaders[Shaders_indice].use();
		break;
	case 1:
		Shaders[Shaders_indice].use();
		Shaders[Shaders_indice].setFloat("Time", glfwGetTime());
		break;
	case 2:
		Shaders[Shaders_indice].use();
		Shaders[Shaders_indice].setFloat("Time", glfwGetTime());
		break;
	case 3:
		Shaders[Shaders_indice].use();
		Shaders[Shaders_indice].setFloat("Time", glfwGetTime());
	case 4:
		Shaders[Shaders_indice].use();
		Shaders[Shaders_indice].setFloat("Time", glfwGetTime());
		break;
	default:
		break;
	}
}