#include "Model.h"

Model::Model(string file_path)
{
    scene = importer.ReadFile(file_path, aiProcess_Triangulate | aiProcess_FlipUVs);
    process_scene(scene);
}


void Model::process_scene(const aiScene* scene)
{
    for (unsigned int i = 0; i < scene->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[i];
        meshes.push_back(process_mesh(mesh));
    }
}

Mesh Model::process_mesh(aiMesh* mesh)
{
    vector<Vertex> vertices;
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        vertex.position.x = mesh->mVertices[i].x;
        vertex.position.y = mesh->mVertices[i].y;
        vertex.position.z = mesh->mVertices[i].z;

        vertex.normal.x = mesh->mNormals[i].x;
        vertex.normal.y = mesh->mNormals[i].y;
        vertex.normal.z = mesh->mNormals[i].z;

        vertex.tex_coord.x = mesh->mTextureCoords[0][i].x;
        vertex.tex_coord.y = mesh->mTextureCoords[0][i].y;
        vertices.push_back(vertex);
    }

    vector<unsigned int> faces;
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace* face = &mesh->mFaces[i];
        faces.push_back(face->mIndices[i]);
    }

    //Todo: TEXTURES
}
