//======================================================
//参考サイト　
//https://learnopengl.com/

#pragma once
#include "Game.h"
#include "Setting.h"
#include "ScreenRender.h"
#include "quad.h"

using namespace std;

#pragma comment(lib, "glfw3.lib")
#pragma comment (lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#pragma comment(lib, "assimp-vc142-mt.lib")   
#pragma comment(lib, "freetype.lib")

Game* game;
ScreenRender* scrennRender;
quad *_quad;

//callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scencode, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

Camera camera(glm::vec3(0.0f, 10.0f, 0.0f));
float _lastX = 800;
float _lastY = 600;
bool firstMouse = true;

float zoom = -3.0f;

GameTime gametime;

std::string is_SceneName = "Game";
int main()
{
	// glfw initialize
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creat
	// --------------------
	GLFWwindow* window = glfwCreateWindow(Setting::SCR_WIDTH, Setting::SCR_HEIGHT, "We Are Tech", NULL, NULL);
	glfwSwapInterval(1); //FPS 60 set
	glfwSetWindowPos(window, 800, 100);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//===========================
	//===========================
	//callback setup
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	//===========================
	//===========================

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	//==========================
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Assimp::Importer importer;
	//==============================
	printf("%s\n", glGetString(GL_VERSION));

	//Scene Add
	 //=================================
	game = new Game();
	//=================================

	scrennRender = new ScreenRender();
	_quad = new quad();

	//=================================

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		gametime.Time_Measure();
		// render (Scene Draw)
		//------Set Drawing Screen Targer(FrameBuffer)
		scrennRender->use();
		
		//Camre Propertys
		//========================================
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)Setting::SCR_WIDTH / (float)Setting::SCR_HEIGHT, 0.1f, 500.0f);
		//========================================
		if (is_SceneName == "Game")
		{
			game->SetCameraPos(camera.Position);
			game->Update(gametime.GetDeltaTime());
			game->Draw(projection, view);
		}
		//======================================
		//======================================
		//Post Processing main
		scrennRender->free(); //Set default FrameBuffer
		_quad->SetTexture(scrennRender->GetTextureColorbuffer());
		_quad->Draw();
		//==================
		//==================

		gametime.DeltaTime_Update();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}



//============================================
//CallBack function============================================
//============================================
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scencode, int action, int mods)
{
	float CameraSpeed = 10.0f;
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, true);
		break;
		//===============
		//Camera movement
	case GLFW_KEY_W:
		camera.ProcessKeyboard(FORWARD, CameraSpeed * gametime.GetDeltaTime());
		break;
	case GLFW_KEY_S:
		camera.ProcessKeyboard(BACKWARD, CameraSpeed * gametime.GetDeltaTime());
		break;
	case GLFW_KEY_A:
		camera.ProcessKeyboard(LEFT, CameraSpeed * gametime.GetDeltaTime());
		break;
	case GLFW_KEY_D:
		camera.ProcessKeyboard(RIGHT, CameraSpeed * gametime.GetDeltaTime());
		break;
		//===============
	case GLFW_KEY_SPACE:
		//camera.Position = glm::vec3(0, 0, 0);
		game->Reset();
		break;

	default:
		cout << "Pressed default Key " << endl;
		break;
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		_lastX = xpos;
		_lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - _lastX;
	float yoffset = _lastY - ypos;

	_lastX = xpos;
	_lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//camera.ProcessMouseScroll(yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		cout << "Mouse Clicked right button" << endl;
		is_SceneName = "Game";
		_quad->Previous_Shaders_indice();
		//camera.reset();
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		cout << "Mouse Clicked Left left" << endl;
		//is_SceneName = "Title";
		_quad->Next_Shaders_indice();
		//camera.reset();
	}
}
//==========================================================
//==========================================================
//==========================================================