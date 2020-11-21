#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <math.h>
#include <vector>

#include "Camera.h"
#include "Shader.h"
#include "GameTIme.h"
#include "Model.h"
#include "Text.h"
#include "Image.h"
#include "Line.h"

#include "Enemy.h"
#include "Plane.h"

#include "Setting.h"


class Game
{
private:
	std::string SceneName = "Game";
	
	std::vector<Plane*> Wall;
	std::vector<Enemy*> enemy;

	glm::vec3 cameraPos;

	Shader shader;
	int Wall_Index = 6;
	int enermy_Index = 50;

	//============================================
	glm::mat4 view;
	glm::mat4 projection;
public:
	Game();
	~Game();
	void Update(float DeltaTime);
	void Draw(glm::mat4 projection, glm::mat4 view);

	std::string GetSceneName() { return SceneName; };
	void SetCameraPos(glm::vec3 pos) { cameraPos = pos; };

	void Reset();

private:
	void MemoryFree();
	bool CollisionAABB(Cube* Target, Cube* box);
	bool CollisionAABB(glm::vec3 Target, Cube* box);
};

