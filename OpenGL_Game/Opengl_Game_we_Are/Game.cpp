#include "Game.h"

Game::Game() : shader("Shader/Cube.vs", "Shader/Cube.fs")
{
	cube->SetImage("texture/container2.png");
}

Game::~Game()
{
}

void Game::Update()
{
}

void Game::Draw(glm::mat4 projection, glm::mat4 view)
{
	cube->Draw(shader, projection, view);
}
