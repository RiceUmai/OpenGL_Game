#include "Game.h"

Game::Game() : shader("Shader/Cube.vs", "Shader/Cube.fs")
{
	std::cout << "Init Game" << std::endl;
	
	for (int i= 0; i< Wall_Index; i++)
	{
		Wall.push_back(new Cube());
		Wall.back()->SetImage("texture/container2.png");
	}
	player = new Player();
	Wall[0]->SetPosition(glm::vec3(10, 0, 0));
	Wall[0]->SetScale(glm::vec3(50, 0.5, 50));

	Wall[1]->SetPosition(glm::vec3(0, 30, 0));
	Wall[1]->SetScale(glm::vec3(50, 0.5, 50));
	//Wall[3]->SetPosition(glm::vec3(0, 30,10));
	//Wall[3]->SetScale(glm::vec3(50, 0.5, 50));
	//Wall[3]->SetScale(glm::vec3(50, 0.5, 50));
	player->SetPosition(glm::vec3(0, 10, 0));
}

Game::~Game()
{
	std::cout << "Delet Game" << std::endl;
	shader.ShaderDelete();
	MemoryFree();
}

void Game::Update(float DeltaTime)
{
	glm::vec3 temp = player->GetPosition() -= glm::vec3(0.0, 1.0, 0.0) * DeltaTime;
	for (int i = 0; i < (Wall.size()); i++)
	{
		CollisionAABB(player, Wall[i]);
		if (CollisionAABB(cameraPos, Wall[i]))
		{
			std::cout << "onCollision" << std::endl;
		}
	}
	player->SetPosition(glm::vec3(temp));

}

void Game::Draw(glm::mat4 projection, glm::mat4 view)
{
	for (int i = 0; i < Wall.size(); i++)
	{
		Wall[i]->Draw(shader, projection, view);
	}
	player->Draw(shader,projection, view);

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

//collision chacke
//====================
bool Game::CollisionAABB(Cube *Target, Cube *box)
{
	return (Target->GetMinPos().x <= box->GetMaxPos().x && Target->GetMaxPos().x >= box->GetMinPos().x) &&
		(Target->GetMinPos().y <= box->GetMaxPos().y && Target->GetMaxPos().y >= box->GetMinPos().y) &&
		(Target->GetMinPos().z <= box->GetMaxPos().z && Target->GetMaxPos().z >= box->GetMinPos().z);
}

bool Game::CollisionAABB(glm::vec3 Target, Cube* box)
{
	return  (Target.x <= box->GetMaxPos().x && Target.x >= box->GetMinPos().x) &&
		(Target.y <= box->GetMaxPos().y && Target.y >= box->GetMinPos().y) &&
		(Target.z <= box->GetMaxPos().z && Target.z >= box->GetMinPos().z);
}


