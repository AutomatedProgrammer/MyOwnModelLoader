#pragma once
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <string>
#include <vector>
#include "Mesh.h"
using namespace std;


class Model
{
    public:
    Model();
    Model(string file_path);
    void draw(Shader& shader);

    private:
    string directory;
    Assimp::Importer importer;
    vector<Mesh> meshes;
    vector<Texture> loaded_textures;
    const aiScene* scene = nullptr;
    void process_scene(const aiScene* scene);
    Mesh process_mesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> load_material(aiMaterial *mat, aiTextureType type);
    unsigned int load_texture(string file_path);
};