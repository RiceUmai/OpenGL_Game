#include "Cube.h"

Cube::Cube()
{
	Position = glm::vec3(0, 0, 0);
	Rotation = glm::vec3(1.0f, 1.0f, 1.0f);
	Scale = glm::vec3(1.0f, 1.0f, 1.0f);
    Color = glm::vec3(1.0f, 1.0f, 1.0f);
    angle = 0;
    Init();
}

Cube::Cube(glm::vec3 pos)
{
	Position = pos;
	Rotation = glm::vec3(1.0f, 1.0f, 1.0f);
	Scale = glm::vec3(1.0f, 1.0f, 1.0f);
    Color = glm::vec3(1.0f, 1.0f, 1.0f);
    angle = 0;
    Init();
}

Cube::Cube(float x, float y, float z)
{
	Position.x = x;
	Position.y = y;
	Position.z = z;
	Rotation = glm::vec3(1.0f, 1.0f, 1.0f);
	Scale = glm::vec3(1.0f, 1.0f, 1.0f);
    Color = glm::vec3(1.0f, 1.0f, 1.0f);
    angle = 0;
    Init();
}

Cube::~Cube()
{
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &VBO);
}

void Cube::Updata(float DeltaTime)
{
    Collision_Update();
}

void Cube::Draw(Shader shader, glm::mat4 projection, glm::mat4 view)
{
    glBindVertexArray(cubeVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    

    shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, Position);
    model = glm::rotate(model, angle, Rotation);
    model = glm::scale(model, Scale);
    
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    shader.setMat4("model", model);
    shader.setVec3("Color", Color);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Cube::SetImage(char const* path)
{
    Image image(path);
    texture = image.getTextureID();
}




//private function
//========================================
//========================================
void Cube::Init()
{
    //maxX = 0.5f * Scale.x;
    //maxY = 0.5f * Scale.y;
    //maxZ = 0.5f * Scale.z;
    
    //minX = -(0.5f * Scale.x);
    //minY = -(0.5f * Scale.y);
    //minZ = -(0.5f * Scale.z);

    maxPos.x = 0.5f * Scale.x;
    maxPos.y = 0.5f * Scale.y;
    maxPos.z = 0.5f * Scale.z;

    minPos.x = -(0.5f * Scale.x);
    minPos.y = -(0.5f * Scale.y);
    minPos.z = -(0.5f * Scale.z);

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Cube::Collision_Update()
{
    maxPos.x = Position.x + 0.5 * Scale.x;
    maxPos.y = Position.y + 0.5 * Scale.y;
    maxPos.z = Position.z + 0.5 * Scale.z;

    minPos.x = Position.x  - (0.5 * Scale.x);
    minPos.y = Position.y  - (0.5 * Scale.y);
    minPos.z = Position.z  - (0.5 * Scale.z);
 }
