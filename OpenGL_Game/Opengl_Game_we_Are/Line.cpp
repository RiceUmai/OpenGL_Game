#include "Line.h"

Line::Line()
{
    Position = glm::vec3(0, 0, 0);
    Rotation = glm::vec3(1.0f, 1.0f, 1.0f);
    Scals = glm::vec3(1.0f, 1.0f, 1.0f);
    angle = 0;
    Width = 5;
   
    Init();
}

Line::Line(glm::vec3 position)
{
    Position = position;
    Rotation = glm::vec3(1.0f, 1.0f, 1.0f);
    Scals = glm::vec3(1.0f, 1.0f, 1.0f);
    angle = 0;
    Width = 5;

    Init();
}

void Line::Draw(Shader shader, glm::mat4 projection, glm::mat4 view)
{
    glBindVertexArray(LineVAO);

    shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, Position);
    model = glm::rotate(model, angle, Rotation);
    model = glm::scale(model, Scals);

    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    shader.setMat4("model", model);
    shader.setVec3("color", color);
    glLineWidth(Width);

    glDrawArrays(GL_LINES, 0, 3);

    glBindVertexArray(0);
}

void Line::Init()
{
    float verices[] = {
        // positions       
         -0.5f, 0.0f,  0.0f,
          0.5f, 0.0f,  0.0f
    };

    glGenVertexArrays(1, &LineVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verices), verices, GL_STATIC_DRAW);

    glBindVertexArray(LineVAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}
