#include "Game.h"

Game::Game() : shader("Shader/Cube.vs", "Shader/Cube.fs")
{
	std::cout << "Init Game" << std::endl;

	//=======================
	for (int i = 0; i < Wall_Index; i++)
	{
		Wall.push_back(new Plane());
		Wall.back()->SetImage("texture/container2.png");
	}

	//(Wall Init)
	//=======================
	Wall[0]->SetPosition(glm::vec3(0, 0, 0)); //Bottom
	Wall[0]->SetScale(glm::vec3(50, 0.5, 50));
	Wall[0]->SetTag("Bottom");

	Wall[1]->SetPosition(glm::vec3(0, 50, 0));//Top 
	Wall[1]->SetScale(glm::vec3(50, 0.5, 50));
	Wall[1]->SetTag("Top");

	Wall[2]->SetPosition(glm::vec3(25, 25, 0));//Right
	Wall[2]->SetScale(glm::vec3(0.5, 50, 50));
	Wall[2]->SetTag("Right");

	Wall[3]->SetPosition(glm::vec3(-25, 25, 0));//Left
	Wall[3]->SetScale(glm::vec3(0.5, 50, 50));
	Wall[3]->SetTag("Left");

	Wall[4]->SetPosition(glm::vec3(0, 25, 25));//Front
	Wall[4]->SetScale(glm::vec3(50, 50, 0.5));
	Wall[4]->SetTag("Front");

	Wall[5]->SetPosition(glm::vec3(0, 25, -25));//Back
	Wall[5]->SetScale(glm::vec3(50, 50, 0.5));
	Wall[5]->SetTag("Back");
	//=======================

	for (int i = 0; i < enermy_Index; i++)
	{
		enemy.push_back(new Enemy());
		enemy.back()->SetImage("texture/container2.png");
		enemy[i]->SetPosition(glm::vec3(0, 20, 0));
		enemy[i]->SetScale(glm::vec3(3, 3, 3));
	}

	//=======================

}

Game::~Game()
{
	std::cout << "Delet Game" << std::endl;
	shader.ShaderDelete();
	MemoryFree();
}

void Game::Update(float DeltaTime)
{

	//=============================================
	for (int i = 0; i < enemy.size(); i++)
	{
		enemy[i]->Update(DeltaTime);

		//Wall <-> Enemy onCollision
		for (int j = 0; j < Wall.size(); j++)
		{
			if (CollisionAABB(Wall[j], enemy[i]))
			{
				std::string tag = Wall[j]->GetTag();
				std::cout << tag << std::endl;

				glm::vec3 Reflect_Dir = enemy[i]->GetDirection();

				//Bottom, Top, Right, Left, Front, Back
				if (tag == "Bottom" || tag == "Top")      Reflect_Dir.y *= Reflect_Dir.y;
				else if (tag == "Right" || tag == "Left") Reflect_Dir.x *= Reflect_Dir.x;
				else if (tag == "Front" || tag == "Back") Reflect_Dir.z *= Reflect_Dir.z;

				enemy[i]->SetDirection(Reflect_Dir);
			}
		}

		//Player <-> Enemy onCollision
		if (CollisionAABB(cameraPos, enemy[i]))
		{
			delete enemy[i];
			enemy.erase(enemy.begin() + i);
		}
	}
	//std::cout << enemy.size() << std::endl;

	//=============================================
	//=============================================

	for (int i = 0; i < (Wall.size()); i++)
	{
		if (CollisionAABB(cameraPos, Wall[i]))
		{
			std::cout << "onCollision(CameraPos, Walls)" << std::endl;
			std::cout << "==========================" << std::endl;
		}
	}
	//=============================================

}

void Game::Draw(glm::mat4 projection, glm::mat4 view)
{

	for (int i = 0; i < Wall.size(); i++)
	{
		Wall[i]->Draw(shader, projection, view);
	}

	for (int i = 0; i < enemy.size(); i++)
	{
		enemy[i]->Draw(shader, projection, view);
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

//collision chacke
//====================
bool Game::CollisionAABB(Cube* Target, Cube* box)
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
//====================
//====================


