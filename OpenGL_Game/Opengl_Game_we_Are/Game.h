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
#include "Cube.h"
#include "Line.h"
#include "Plane.h"

class Game
{
private:
	std::string SceneName = "Game";
	Cube* cube = new Cube();
	
	Shader shader;

public:
	Game();
	~Game();
	void Update();
	void Draw(glm::mat4 view, glm::mat4 projection);

	std::string GetSceneName() { return SceneName; };
};

