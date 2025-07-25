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

    private:
    Assimp::Importer importer;
    vector<Mesh> meshes;
    const aiScene* scene = nullptr;
    void process_scene(const aiScene* scene);
    Mesh process_mesh(aiMesh* mesh);
    vector<Texture> load_material_textures(aiMaterial *mat, aiTextureType type, string type_name);

};