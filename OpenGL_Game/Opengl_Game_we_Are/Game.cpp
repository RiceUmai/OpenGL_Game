#include "Game.h"

Game::Game() : shader("Shader/Cube.vs", "Shader/Cube.fs")
{
	cube = new Cube();
	cube->SetImage("texture/container2.png");
	std::cout << "Init Game" << std::endl;
}

Game::~Game()
{
	std::cout << "Delet Game" << std::endl;
	shader.ShaderDelete();
	delete cube;
}

void Game::Update()
{
}

void Game::Draw(glm::mat4 projection, glm::mat4 view)
{
	cube->SetPosition(glm::vec3(0,0, -5));
	cube->SetScale(glm::vec3(50, 0.5, 50));

	cube->Draw(shader, projection, view);
}

void Game::Reset()
{
}


