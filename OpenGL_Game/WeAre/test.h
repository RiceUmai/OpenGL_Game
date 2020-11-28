#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

class test{
public:
	void input(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_A && action == GLFW_PRESS)
        {
            std::cout << "test" << std::endl;
        }
	}
};