#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <iostream>

class Texture
{
private:

public:
	unsigned int loadTexture(char const* path);
};

