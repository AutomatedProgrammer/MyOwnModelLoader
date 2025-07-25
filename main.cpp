
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Shader.h"
#include "Model.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Model Loader", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    /*
    std::vector<unsigned int> cube_indices = {
        0, 1, 2, 2, 3, 0, // back
        4, 5, 6, 6, 7, 4, // front
        8, 9, 10, 10, 11, 8, // bottom
        12, 13, 14, 14, 15, 12, // top
        16, 17, 18, 18, 19, 16, // left
        20, 21, 22, 22, 23, 20  // right
    };
    
    std::vector<glm::vec3> cube_pos = 
    {
        glm::vec3(-0.5f, -0.5f, -0.5f),  
        glm::vec3(0.5f, -0.5f, -0.5f),  
        glm::vec3(0.5f,  0.5f, -0.5f),  
        glm::vec3(-0.5f,  0.5f, -0.5f), 

        glm::vec3(-0.5f, -0.5f,  0.5f), 
        glm::vec3(0.5f, -0.5f,  0.5f),  
        glm::vec3(0.5f,  0.5f,  0.5f),  
        glm::vec3(-0.5f,  0.5f,  0.5f), 
        
        glm::vec3(-0.5f, -0.5f, -0.5f),  
        glm::vec3(0.5f, -0.5f, -0.5f),  
        glm::vec3(0.5f, -0.5f,  0.5f),  
        glm::vec3(-0.5f, -0.5f,  0.5f), 

        glm::vec3(-0.5f,  0.5f, -0.5f),  
        glm::vec3(0.5f,  0.5f, -0.5f),  
        glm::vec3(0.5f,  0.5f,  0.5f),  
        glm::vec3(-0.5f,  0.5f,  0.5f),  

        glm::vec3(-0.5f, -0.5f, -0.5f),   
        glm::vec3(-0.5f,  0.5f, -0.5f),  
        glm::vec3(-0.5f,  0.5f,  0.5f),  
        glm::vec3(-0.5f, -0.5f,  0.5f),  

        glm::vec3(0.5f, -0.5f, -0.5f),  
        glm::vec3(0.5f,  0.5f, -0.5f),  
        glm::vec3(0.5f,  0.5f,  0.5f),  
        glm::vec3(0.5f, -0.5f,  0.5f)  
    };

    std::vector<Vertex> cube_vertices;

    Texture ex;
    ex.id = 0;
    ex.path = "";
    ex.type = "";
    std::vector<Texture> blank;
    blank.push_back(ex);

    for(int i = 0; i < cube_pos.size(); i++)
    {
        Vertex vertex;
        vertex.position = cube_pos[i];
        vertex.normal = glm::vec3(0.0f);
        vertex.tex_coord = glm::vec2(0.0f);
        cube_vertices.push_back(vertex);
    }

    */
    //Mesh cube(cube_vertices, blank, cube_indices);
    Shader shader("cube.vert", "cube.frag");
    Model backpack("backpack/backpack.obj");
    
    glEnable(GL_DEPTH_TEST);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);
        

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        model = glm::rotate(model, (float)glfwGetTime()*glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 1.0f, 0.5f));	// it's a bit too big for our scene, so scale it down
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        shader.setMat4("model", model);
        backpack.draw(shader);
        
        //cube.draw(shader);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

