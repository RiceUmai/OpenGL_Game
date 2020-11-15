#include "Game.h"

Game::Game() : shader("Shader/Cube.vs", "Shader/Cube.fs")
{
	std::cout << "Init Game" << std::endl;
	
	for (int i= 0; i< Wall_Index; i++)
	{
		Wall.push_back(new Cube());
		Wall.back()->SetImage("texture/container2.png");
	}
}

Game::~Game()
{
	std::cout << "Delet Game" << std::endl;
	shader.ShaderDelete();
	MemoryFree();
}

void Game::Update()
{
	Wall[0]->SetPosition(glm::vec3(0, 0, 0));
	Wall[0]->SetScale(glm::vec3(50, 0.5, 50));	
	
	Wall[1]->SetPosition(glm::vec3(0, 70, 0));
	Wall[1]->SetScale(glm::vec3(50, 0.5, 50));
	//Wall[3]->SetPosition(glm::vec3(0, 30,10));
	//Wall[3]->SetScale(glm::vec3(50, 0.5, 50));

}

void Game::Draw(glm::mat4 projection, glm::mat4 view)
{
	for (int i = 0; i < Wall.size(); i++)
	{
		Wall[i]->Draw(shader, projection, view);
	}
}

void Game::Reset()
{

}

void Game::MemoryFree()
{
	for (int i = 0; i < Wall.size(); i++)
	{
		delete Wall[i];
	}
}


