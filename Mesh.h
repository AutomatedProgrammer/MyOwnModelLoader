#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "Shader.h"

using namespace std;

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 tex_coord;
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
    Mesh();
    void draw(Shader& shader);

    private:
    unsigned int VAO, VBO, EBO;
    void setup_mesh();
};