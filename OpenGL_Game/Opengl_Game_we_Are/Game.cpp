#include "Game.h"

Game::Game() : shader("Shader/Cube.vs", "Shader/Cube.fs"),
text("font/arial.ttf"),
fontShader("Shader/font.vs", "Shader/font.fs")
{
	font_projection = glm::ortho(0.0f, (float)Setting::SCR_WIDTH, 0.0f, (float)Setting::SCR_HEIGHT);
	fontShader.use();
	fontShader.setMat4("projection", font_projection);

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
		enemy.back()->SetImage("texture/PngItem.png");
		enemy[i]->SetPosition(glm::vec3(0, 25, 0));
		enemy[i]->SetScale(glm::vec3(5, 5, 5));
	}
}

Game::~Game()
{
	std::cout << "Delet Game" << std::endl;
	shader.ShaderDelete();
	fontShader.ShaderDelete();
	MemoryFree();
}

void Game::Update(float DeltaTime)
{
	if (Result) return;
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
				glm::vec3 Reflect_Dir = enemy[i]->GetDirection();

				//Bottom, Top, Right, Left, Front, Back
				if (tag == "Bottom" || tag == "Top") Reflect_Dir.y = -Reflect_Dir.y;
				if (tag == "Right" || tag == "Left") Reflect_Dir.x = -Reflect_Dir.x;
				if (tag == "Front" || tag == "Back") Reflect_Dir.z = -Reflect_Dir.z;
				enemy[i]->SetDirection(Reflect_Dir);
			}
		}


		//Enemy <-> Enemy onCollision
		for (int j = i + 1; j < enemy.size() - 1; j++)
		{
			if (CollisionAABB(enemy[j], enemy[i]) && glfwGetTime() >= 2)
			{
				glm::vec3 Dir1 = enemy[i]->GetDirection();
				glm::vec3 Dir2 = enemy[j]->GetDirection();

				Dir1.z = -Dir1.z;
				Dir1.z = -Dir2.z;

				enemy[i]->SetDirection(-Dir2);
				enemy[j]->SetDirection(-Dir1);
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
		}
	}
	//=============================================
	Game_Time -= DeltaTime;


	if (Game_Time <= 0)
	{
		Game_Time = 0;
		TimeOut = true;
		Result = true;
	}

	if (enemy.size() == 0)
	{
		GameClear = true;
		Result = true;
	}
}

void Game::Draw(glm::mat4 projection, glm::mat4 view)
{
	if (Result)
	{
		if (TimeOut) Result_text = "Time Out, Press SpaceBar to game reset";
		else if (GameClear) Result_text = "Game Clear, Press SpaceBar to game reset";
		text.Draw(fontShader, Result_text, 50.0f, 500.0f, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));
	}

	for (int i = 0; i < Wall.size(); i++)
	{
		Wall[i]->Draw(shader, projection, view);
	}

	for (int i = 0; i < enemy.size(); i++)
	{
		enemy[i]->Draw(shader, projection, view);
	}
	//===============================================
	text.Draw(fontShader, "Enemy : " + std::to_string(enemy.size()), 700.0f, 700.0f, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));
	text.Draw(fontShader, "Time : " + std::to_string(Game_Time), 25.0f, 700.0f, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));

	text.Draw(fontShader, SceneName, 25.0f, 25.0f, 1.0f, glm::vec3(0.5f, 0.1f, 0.5f));

	text.Draw(fontShader, cameraPos.x, 850.0f, 150.0f, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));
	text.Draw(fontShader, cameraPos.y, 850.0f, 100.0f, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));
	text.Draw(fontShader, cameraPos.z, 850.0f, 50.0f, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));
	//===============================================
}

void Game::Reset()
{
	MemoryFree();

	for (int i = 0; i < enermy_Index; i++)
	{
		enemy.push_back(new Enemy());
		enemy.back()->SetImage("texture/PngItem.png");
		enemy[i]->SetPosition(glm::vec3(0, 25, 0));
		enemy[i]->SetScale(glm::vec3(5, 5, 5));
	}

	Result = false;
	TimeOut = false;
	GameClear = false;

	Game_Time = MaxTime;
}

void Game::MemoryFree()
{
	//for (int i = 0; i < Wall.size(); i++)
	//{
	//	delete Wall[i];
	//	Wall.erase(Wall.begin() + i);
	//	Wall.clear();
	//}

	for (int i = 0; i < enemy.size(); i++)
	{
		delete enemy[i];
	}
	enemy.clear();
}

//collision chacke
//====================
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


