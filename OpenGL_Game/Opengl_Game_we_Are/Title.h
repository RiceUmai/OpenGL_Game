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

class Title
{
private:
	std::string SceneName = "Title";
public:
	Title();
	~Title();
	void Update(float DeltaTime);
	void Draw(glm::mat4 projection, glm::mat4 view);

	std::string GetSceneName() { return SceneName; };

	void Reset();
};

