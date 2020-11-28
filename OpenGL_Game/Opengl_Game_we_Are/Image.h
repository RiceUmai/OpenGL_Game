#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <iostream>

class Image
{
private:
	unsigned int textureID;
public:
	Image(char const* path);
	~Image();
	unsigned int getTextureID() { return textureID; };
};

