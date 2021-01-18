# OpenGLプロジェット

## 使用言語, ツール
C++, GLSL
Visual Studio 2019, VS Code

## 使用ライブラリ
[GLFW3](https://www.glfw.org/),
[glad](https://glad.dav1d.de/),
[glm](https://github.com/g-truc/glm),
[std_image](https://github.com/nothings/stb),
[FreeType](https://www.freetype.org/)

## 参考サイト
[Learn opengl](https://learnopengl.com/)

# ゲーム画面
<center>
   <img src="./ScreenShot/gameScene1.gif" width="40%">
</center>

## 説明
1. W,S,A,Sでカメラ移動
2. マウス移動でカメラ回転
3. Time(左上)が0になったらゲームオーバー
4. Enemy(右上)キューブの数
5. 右下(Canera position) 上からｘ、ｙ、ｚ
6. キューブに当たったらキューブは消える。（Enemyの数字が減少する）

# cube生成と行列変換
## Cube.cpp(constructor)
<details>
<summary>Source codeを見る</summary>

```cpp
Cube::Cube(glm::vec3 pos)
{
	Position = pos;
	Rotation = glm::vec3(1.0f, 1.0f, 1.0f);
	Scale = glm::vec3(1.0f, 1.0f, 1.0f);
    Color = glm::vec3(1.0f, 1.0f, 1.0f);
    angle = 0;
    Init();
}

void Cube::Init()
{
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
```
</details>

## cube.cpp(座標、回転、スケール)
```cpp
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, Position); //オブジェクトの座標(World Position)
    model = glm::rotate(model, angle, Rotation); //回転(角度,方向)
    model = glm::scale(model, Scale); // スケール設定
```
# 当たり判定
## game.cpp
```cpp
bool Game::CollisionAABB(Cube* Target, Cube* box)
{
	return (Target->GetMinPos().x <= box->GetMaxPos().x && Target->GetMaxPos().x >= box->GetMinPos().x) &&
		(Target->GetMinPos().y <= box->GetMaxPos().y && Target->GetMaxPos().y >= box->GetMinPos().y) &&
		(Target->GetMinPos().z <= box->GetMaxPos().z && Target->GetMaxPos().z >= box->GetMinPos().z);
}
```
# post processing
<center><img src="./ScreenShot/Shader1.gif" width="40%"></center>

## 説明
マウス右左クリックでShaderを変更
## 適用の流れ
1. FrameBuffer生成
2. Sceneを描く場所を指定(**生成したFrameBuffer**)
3. 指定したFrameBufferにGameSceneを描いて保存
4. **生成**したFrameBufferを**default** FrameBufferに変更
5. PostProcessingを適用したいなオブジェクト生成（四角形）
6. 四角形にTexture(**別のFrameBuffer保存されているScene**)適用する
7. そしてShaderを適用する

## ScreenRender.Cpp(FrameBuffers生成)
```cpp
ScreenRender::ScreenRender()
{
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Setting::SCR_WIDTH, Setting::SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	//=============================================
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	//=============================================
	//=============================================
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Setting::SCR_WIDTH, Setting::SCR_HEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	//=============================================
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
```
## quad.h.cpp(四角形生成)
```cpp
void quad::Init()
{
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

	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}
//=========================	
//中略
//=========================	
//shader適用
	Shaders.push_back(Shader("Shader/framebuffers_screen.vs", "Shader/framebuffers_screen.fs"));
	Shaders[Shaders_indice].setFloat("Time", glfwGetTime());
	Shaders[Shaders_indice].use();
}
```

## Main.cpp
```cpp
#include "ScreenRender.h"
#include "Game.h"
#include "quad.h"

//=========================	
//中略
//=========================	

	game = new Game();
	scrennRender = new ScreenRender();
	_quad = new quad();
	while (!glfwWindowShouldClose(window))
	{
		gametime.Time_Measure();
   		scrennRender->use();

		game->SetCameraPos(camera.Position);
		game->Update(gametime.GetDeltaTime());
		game->Draw(projection, view);
		
		scrennRender->free();
		_quad->SetTexture(scrennRender->GetTextureColorbuffer());
		_quad->Draw();

		gametime.DeltaTime_Update();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
```

## vertex shader
```glsl
#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float Time;

void main()
{
    vec2 temp = TexCoords;
    temp.x += 0.5f;
    vec3 col = texture(screenTexture, TexCoords + sin(Time)).rgb;

    FragColor = vec4(col, 1.0f);
}
```

## fragmant shader
```glsl
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = vec4(aPos.x, aPos.y, 0.0f, 1.0f);
}
```

# その外(post processing)
## 画面分割
<center><img src="./ScreenShot/postshader2.JPG" width="40%"></center>

## モザイク
<center><img src="./ScreenShot/postshader3.JPG" width="40%"></center>

## グレースケール
<center><img src="./ScreenShot/postshader4.JPG" width="40%"></center>