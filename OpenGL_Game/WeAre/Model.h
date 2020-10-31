#pragma once
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <stb_image.h>

#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "Shader.h"
#include "Mesh.h"

class Model
{
public:
	Model(std::string const &path, bool gamma =false) { loadModel(path); };
	void Draw(Shader shader);
private:
	std::vector<Mesh> meshes;
	std::vector<Texture> textures_loaded;
	std::string directory;

	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *sceme);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(const char* path, const std::string &directory, bool gamma = false);
};

