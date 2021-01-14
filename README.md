# OpenGLプロジェット

## 使用言語, ツール
C++, GLSL  
Visual Studio 2019, VS Code

## 使用ライブラリ
GLFW3(https://www.glfw.org/)  
glad(https://glad.dav1d.de/)  
glm(https://github.com/g-truc/glm)  
std_image(https://github.com/nothings/stb)  
FreeType(https://www.freetype.org/)

## 参考サイト
Learn opengl(https://learnopengl.com/)

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

## 目的
ゲームシーン内にあるキューブを全て消えさせばゲームクリア

# 当たり判定
```cpp
bool Game::CollisionAABB(Cube* Target, Cube* box)
{
	return (Target->GetMinPos().x <= box->GetMaxPos().x && Target->GetMaxPos().x >= box->GetMinPos().x) &&
		(Target->GetMinPos().y <= box->GetMaxPos().y && Target->GetMaxPos().y >= box->GetMinPos().y) &&
		(Target->GetMinPos().z <= box->GetMaxPos().z && Target->GetMaxPos().z >= box->GetMinPos().z);
}

bool Game::CollisionAABB(glm::vec3 Target, Cube* box)
{
	return  (Target.x <= box->GetMaxPos().x && Target.x >= box->GetMinPos().x) &&
		(Target.y <= box->GetMaxPos().y && Target.y >= box->GetMinPos().y) &&
		(Target.z <= box->GetMaxPos().z && Target.z >= box->GetMinPos().z);
}
```

# post processing
<center><img src="./ScreenShot/Shader1.gif" width="40%"></center>

## 説明
マウス右左クリックでShaderを変更
## vertex shader
```Cpp
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
```Cpp
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
##その外(post processing)

<center>
<p>
  <img src="./ScreenShot/postshader2.jpg" width="30%">
  <img src="./ScreenShot/postshader3.jpg" width="30%">
  <img src="./ScreenShot/postshader4.jpg" width="30%">
</p>
</center>