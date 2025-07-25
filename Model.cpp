#include "Model.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Model::Model(string file_path)
{
    scene = importer.ReadFile(file_path, aiProcess_Triangulate | aiProcess_FlipUVs);
    directory = file_path.substr(0, file_path.find_last_of('/'));
    process_scene(scene);
}


void Model::process_scene(const aiScene* scene)
{
    for (unsigned int i = 0; i < scene->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[i];
        meshes.push_back(process_mesh(mesh, scene));
    }
}

Mesh Model::process_mesh(aiMesh* mesh, const aiScene* scene)
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

    vector<unsigned int> indices;
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace* face = &mesh->mFaces[i];
        for (unsigned int j = 0; j < face->mNumIndices; j++)
            indices.push_back(face->mIndices[j]);
    }
    vector<Texture> textures;
    //Todo: TEXTURES
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];
        vector<Texture> diffuse_textures = load_material(mat, aiTextureType_DIFFUSE);
        textures.insert(textures.end(), diffuse_textures.begin(), diffuse_textures.end());
    }
    return Mesh(vertices, textures, indices);
}

void Model::draw(Shader& shader)
{
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i].draw(shader);
    }
}

unsigned int Model::load_texture(string file_path)
{
    string filename = string(file_path);
    filename = directory + '/' + filename;
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    return texture;
}

vector<Texture> Model::load_material(aiMaterial *mat, aiTextureType type)
{
    vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for (unsigned int j = 0; j < loaded_textures.size(); j++)
        {
            if (strcmp(str.C_Str(), loaded_textures[j].path.c_str()) == 0)
            {
                skip = true;
                textures.push_back(loaded_textures[j]);
                break;
            }
        }

        if (!skip)
        {
            Texture texture;
            if (type == aiTextureType_DIFFUSE)
                texture.type = "texture_diffuse";
            else
                texture.type = "unknown";
            texture.id = load_texture(str.C_Str());
            texture.path = str.C_Str();

            textures.push_back(texture);
            loaded_textures.push_back(texture);
        }
        
    }

    return textures;
    
}