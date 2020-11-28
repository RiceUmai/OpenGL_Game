#pragma once
#include "Game.h"
#include "Title.h"
#include "Setting.h"

using namespace std;

#pragma comment(lib, "glfw3.lib")
#pragma comment (lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#pragma comment(lib, "assimp-vc142-mt.lib")   
#pragma comment(lib, "freetype.lib")

Game* game;
Title* title;

//callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scencode, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;

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

	//callback setup
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//==========================
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Assimp::Importer importer;
	//==============================
	//==============================
	Shader ourShader("Shader/model_loading.vs", "Shader/model_loading.fs");
	//Shader LineShader("Shader/Line.vs", "Shader/Line.fs");

	//Model ourModel("newell_teaset/teapot.obj");

	Shader shader("Shader/font.vs", "Shader/font.fs");
	glm::mat4 projection = glm::ortho(0.0f, (float)Setting::SCR_WIDTH, 0.0f, (float)Setting::SCR_HEIGHT);
	shader.use();
	//glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	shader.setMat4("projection", projection);
	Text text("font/arial.ttf");

	Shader cube("Shader/Cube.vs", "Shader/Cube.fs");
	//==================================
	Line* line = new Line();

	//Scene Add
	 //=================================
	Game* game = new Game();
	Title* title = new Title();
	//=================================
	
	//=================================
	//=================================
	Shader Screen_frame("Shader/framebuffers_screen.vs", "Shader/framebuffers_screen.fs");
	float quadVertices[] = 
	{
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	unsigned int quadVAO, wquadVBO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &wquadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, wquadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	//frame buffer
   //======================================================


	Screen_frame.use();
	Screen_frame.setInt("screenTexture", 0);
   //======================================================
	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	unsigned int textureColorbuffer;
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Setting::SCR_WIDTH, Setting::SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	//======================================================
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Setting::SCR_WIDTH, Setting::SCR_HEIGHT);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Setting::SCR_WIDTH, Setting::SCR_HEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//======================================================
	//======================================================

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		gametime.Time_Measure();
		// render
	
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

		// ------
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);


		////========================================
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)Setting::SCR_WIDTH / (float)Setting::SCR_HEIGHT, 0.1f, 100.0f);
		////========================================

		
		// Line
		//line->SetWidth(100);
		//line->SetScals(glm::vec3(100,5,5));
		//line->SetColor(glm::vec3(0.5, 0.5, 0.5));
		//line->Draw(LineShader, projection, view);
		//==============
		//TeaPort Renderer
		//
		//ourShader.use();
		//ourShader.setMat4("projection", projection);
		//ourShader.setMat4("view", view);
		//
		//model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//
		//ourShader.setMat4("model", model);
		//ourShader.setFloat("Color", glfwGetTime());
		//ourModel.Draw(ourShader);
		//================


		if (is_SceneName == "Game")
		{
			game->SetCameraPos(camera.Position);
			game->Update(gametime.GetDeltaTime());
			game->Draw(projection, view);


		}

		else if (is_SceneName == "Title")
		{
			title->Update(gametime.GetDeltaTime());
			title->Draw(projection, view);
			text.Draw(shader, title->GetSceneName(), 25.0f, 25.0f, 1.0f, glm::vec3(0.5f, 0.1f, 0.5f));
		}

		//==============================
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Screen_frame.use();
		glBindVertexArray(quadVAO);
		glDisable(GL_DEPTH_TEST);
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
		Screen_frame.setFloat("Time", sin(glfwGetTime()));
		glDrawArrays(GL_TRIANGLES, 0, 6);

		gametime.DeltaTime_Update();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}


//CallBack function============================================
//============================================
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scencode, int action, int mods)
{
	float CameraSpeed = 5.0f;
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
	case GLFW_KEY_R:
		camera.Position = glm::vec3(0, 0, 0);

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
		camera.reset();
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		cout << "Mouse Clicked right left" << endl;
		is_SceneName = "Title";
		camera.reset();
	}
}
//==========================================================