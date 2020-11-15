#pragma once
#include "Game.h"
#include "Title.h"
#include "Setting.h"

using namespace std;


#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "assimp-vc142-mt.lib")   
#pragma comment(lib, "freetype.lib")

//callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scencode, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float _lastX = 800;
float _lastY = 600;
bool firstMouse = true;

float mixValue = 0.2f;
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
    Shader lightingShader("Shader/Multiple_light.vs", "Shader/Multiple_light.fs");
    Shader lightCubeShader("Shader/light_cube.vs", "Shader/light_cube.fs");
    Shader ourShader("Shader/model_loading.vs", "Shader/model_loading.fs");
    Shader LineShader("Shader/Line.vs", "Shader/Line.fs");

    Model ourModel("newell_teaset/teapot.obj");

    Shader shader("Shader/font.vs", "Shader/font.fs");
    glm::mat4 projection = glm::ortho(0.0f, (float)Setting::SCR_WIDTH, 0.0f, (float)Setting::SCR_HEIGHT);
    shader.use();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    Text text("font/arial.ttf");

    Shader cube("Shader/Cube.vs", "Shader/Cube.fs");
    //==================================
    Cube* cubes = new Cube;
    cubes->SetImage("texture/container2.png");
    //==================================
    Line* line = new Line();


    //Scene Add
     //=================================
    Game* game = new Game();
    Title* title = new Title();
     //=================================

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        ////glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        gametime.Time_Measure();
        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ////========================================
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)Setting::SCR_WIDTH / (float)Setting::SCR_HEIGHT, 0.1f, 100.0f);
        ////========================================
        // cubes
        //cubes->SetPosition(glm::vec3(1,2,1));
        //cubes->Draw(cube, projection, view);
        //
        // Line
        //line->SetWidth(100);
        //line->SetScals(glm::vec3(100,5,5));
        //line->SetColor(glm::vec3(0.5, 0.5, 0.5));
        //line->Draw(LineShader, projection, view);
        //==============
        //TeaPort Renderer

        //ourShader.use();
        //ourShader.setMat4("projection", projection);
        //ourShader.setMat4("view", view);

        //model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
        //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

        //ourShader.setMat4("model", model);
        //ourShader.setFloat("Color", glfwGetTime());
        //ourModel.Draw(ourShader);
        //================
        //Text Draw
        //================
        text.Draw(shader, camera.Position.x, 400.0f, 300.0f, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));
        text.Draw(shader, camera.Position.y, 400.0f, 250.0f, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));
        text.Draw(shader, camera.Position.z, 400.0f, 200.0f, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));
        //================
        if (is_SceneName == "Game")
        {
            game->Update();
            game->Draw(projection, view);
            text.Draw(shader, game->GetSceneName(), 25.0f, 25.0f, 1.0f, glm::vec3(0.5f, 0.1f, 0.5f));
        }

        else if (is_SceneName == "Title")
        {
            title->Update();
            title->Draw(projection, view);
            text.Draw(shader, title->GetSceneName(), 25.0f, 25.0f, 1.0f, glm::vec3(0.5f, 0.1f, 0.5f));
        }

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
    case GLFW_KEY_UP:
        mixValue += 0.1f;
        break;
    case GLFW_KEY_DOWN:
        mixValue -= 0.1f;
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
    camera.ProcessMouseScroll(yoffset);
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