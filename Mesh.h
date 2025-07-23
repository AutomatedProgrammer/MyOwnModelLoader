#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>

using namespace std;

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoord;
};

struct Texture
{
    unsigned int id;
    string type;
    string path;
};

class Mesh
{
    public:
    vector<Vertex> vertices;
    vector<Texture> textures;
    vector<unsigned int> indices;

    Mesh(const vector<Vertex>& vertices, const vector<Texture>& textures, const vector<unsigned int>& indices);
    

    private:
    unsigned int VAO, VBO, EBO;
};