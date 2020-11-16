#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <string>

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "assimp-vc142-mt.lib")   
#pragma comment(lib, "freetype.lib")
#pragma comment (lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

static GLFWwindow* aWindow;
static int          aWidth = 640;
static int          aHeight = 480;
static std::string  aTitle = "Modeling transformation";

// キューブの頂点情報。
static const GLdouble aCubeVertex[][3] = {
    { 0.0, 0.0, 0.0 },
    { 1.0, 0.0, 0.0 },
    { 1.0, 1.0, 0.0 },
    { 0.0, 1.0, 0.0 },
    { 0.0, 0.0, 1.0 },
    { 1.0, 0.0, 1.0 },
    { 1.0, 1.0, 1.0 },
    { 0.0, 1.0, 1.0 }
};
// キューブの面。
static const int aCubeFace[][4] = {
    { 0, 1, 2, 3 },
    { 1, 5, 6, 2 },
    { 5, 4, 7, 6 },
    { 4, 0, 3, 7 },
    { 4, 5, 1, 0 },
    { 3, 2, 6, 7 }
};
// キューブに対する法線ベクトル。
static const GLdouble aCubeNormal[][3] = {
  { 0.0, 0.0,-1.0 },
  { 1.0, 0.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  {-1.0, 0.0, 0.0 },
  { 0.0,-1.0, 0.0 },
  { 0.0, 1.0, 0.0 }
};
// キューブの材質。
static const GLfloat aCube0Material[] = { 0.8, 0.2, 0.2, 1.0 };
static const GLfloat aCube1Material[] = { 0.2, 0.8, 0.2, 1.0 };
// 光源。
static const GLfloat aLightColor[] = { 0.1, 0.1, 0.8, 1.0 };// 光源の色。
static const GLfloat aLight0pos[] = { 0.0, 6.0, 8.0, 1.0 };// 光源0の位置。
static const GLfloat aLight1pos[] = { 8.0, 6.0, 0.0, 1.0 };// 光源1の位置。

// キューブを描画する関数。
static void drawCube(const GLfloat material[]);
// GLFW3に渡すコールバック関数。
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{
    /* GLFW3の初期化 */
    if (!glfwInit())
    {
        std::cerr << "glfwInit failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    aWindow = glfwCreateWindow(aWidth, aHeight, aTitle.c_str(), nullptr, nullptr);
    if (!aWindow)
    {
        std::cerr << "glfwCreateWindow failed." << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(aWindow);
    // キー入力を処理するコールバック関数を設定。
    glfwSetKeyCallback(aWindow, keyCallback);
    /* OpenGLの初期化  */
    glEnable(GL_DEPTH_TEST);// デプスバッファの有効化。
    glEnable(GL_CULL_FACE);// カリングの有効化。
    glEnable(GL_LIGHTING);// ライティングの有効化。
    glEnable(GL_LIGHT0);// 光源0 を有効化。
    glEnable(GL_LIGHT1);// 光源1 を有効化。
    glCullFace(GL_FRONT);// カリング。
    glLightfv(GL_LIGHT1, GL_DIFFUSE, aLightColor);// 光源1の色を設定。
    glLightfv(GL_LIGHT1, GL_SPECULAR, aLightColor);// 光源1の色を設定。
    glClearColor(1, 1, 1, 1);// glClear() で使用する色（RGBA）

    // メインループ。
    while (!glfwWindowShouldClose(aWindow))
    {
        /* 初期化 */
        // 画面をクリア。
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // 変換行列の初期化。
        glLoadIdentity();

        /* 更新 */
        // 現在のウィンドウの大きさを取得。
        int width, height;
        glfwGetFramebufferSize(aWindow, &width, &height);
        // ビューポートの更新。
        glViewport(0, 0, width, height);
        // 透視投影。
        gluPerspective(30.0, (double)width / (double)height, 1.0, 100.0);
        // 視点設定前の行列をすべて平行移動（視界に収める）。
        glTranslated(0.0, 0.0, 1.0);
        // 視点の設定。
        gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        // 光源の位置設定 （＊重要 視点の位置を設定した後に行う） 
        glLightfv(GL_LIGHT0, GL_POSITION, aLight0pos);
        glLightfv(GL_LIGHT1, GL_POSITION, aLight1pos);

        /* 描画 */
        glPushMatrix();// モデルビュー変換行列の保存。
        glRotated(-10, 0.0, 1.0, 0.0);// すべてのキューブを少し回転。
        // 1つ目のキューブ（1段目）を描画。
        glPushMatrix();
        drawCube(aCube0Material);// キューブを描画。
        glPopMatrix();
        // 2つ目のキューブ（2段目）を描画。
        glPushMatrix();
        glTranslated(0.0, 1.0, 0.0);// 初期位置（1つ目のキューブの位置から上に移動）。
        glTranslated(0.5, 0.0, 0.5);// 回転と拡大縮小のために原点をずらす。
        glRotated(30, 0.0, 1.0, 0.0);// 回転。
        glScaled(0.5, 0.5, 1.0);// 縮小。
        glTranslated(-0.5, 0.0, -0.5);// 原点を元に戻す。
        drawCube(aCube1Material);// モデリング変換したキューブを描画。
        glPopMatrix();
        // 3つ目のキューブ（3段目）を描画。
        glPushMatrix();
        glTranslated(0.0, 1.5, 0.0);// 初期位置（1つ目のキューブから上に移動）。
        glTranslated(0.5, 0.0, 0.5);
        glScaled(0.5, 0.25, 0.25);
        glTranslated(-0.5, 0.0, -0.5);
        drawCube(aCube0Material);
        glPopMatrix();
        glPopMatrix();// モデルビュー変換行列の復帰。

        /* ダブルバッファのスワップとイベントのポーリング */
        glfwSwapBuffers(aWindow);
        glfwPollEvents();
    }
    // GLFW3 の終了。
    glfwTerminate();
    return EXIT_SUCCESS;
}

static void drawCube(const GLfloat material[])
{
    // キューブの材質パラメータを設定。
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material);
    // キューブの頂点を描画。
    glBegin(GL_QUADS);
    for (size_t i = 0; i < 6; ++i)
    {
        glNormal3dv(aCubeNormal[i]);// 法線ベクトルをキューブに当てる。
        for (size_t j = 0; j < 4; ++j)
        {
            glVertex3dv(aCubeVertex[aCubeFace[i][j]]);
        }
    }
    glEnd();
}

/*
typedef void(* GLFWkeyfun)(GLFWwindow *, int, int, int, int)
This is the function signature for keyboard key callback functions.

Parameters
    [in]    window  The window that received the event.
    [in]    key The keyboard key that was pressed or released.
    [in]    scancode    The system-specific scancode of the key.
    [in]    action  GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
    [in]    mods    Bit field describing which modifier keys were held down.
*/
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // ESCキーでウィンドウのクローズフラグを設定。
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        // Sets the close flag of the specified window.
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}