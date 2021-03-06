//
//  Practice_openGL.cpp
//  Practice_openGL
//
//  Created by 60947071s on 2020/8/18.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float vertices[] = {
   //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标(UV) -
    0.6f,  0.3f, 0.0f,   0.6f, 0.4f, 0.0f,    1.0f,  0.5f,   //
     0.4f, -0.4f, 0.0f,   0.0f, 0.7f, 0.0f,   0.7f, -1.0f,   //
    -0.4f, -0.4f, 0.0f,   0.0f, 0.0f, 0.7f,  -0.7f, -1.0f,   //
     0.0f,  0.7f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f,  1.0f,   //
    -0.6f,  0.3f, 0.0f,   0.6f, 0.0f, 0.4f,  -1.0f,  0.5f,   //
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3,
    2, 4, 3
};

/*
//vertexShader in GLSL (Shading Language)
const char* vertexShaderSource =
"#version 330 core                                                \n"
"layout (location = 0) in vec3 aPos;                              \n"

"layout (location = 1) in vec3 aColor;                            \n"
"out vec3 ourColor;                                                \n"

"void main(){                                                     \n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);              \n"
"    ourColor = aColor;                                            \n"
"           }             \n";

//fragmentShader in GLSL (Shading Language)
const char* fragmentShaderSource =
"#version 330 core                                                \n"
"out vec4 FragColor;                                              \n"

"in vec3 ourColor;                                                \n"

"void main(){                                                     \n"
"    FragColor = vec4(ourColor, 1.0);}                   \n";
*/

int main()
{
    //init GLFW
    glfwInit();
    //Config GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    //Create winodw & Bind context
    GLFWwindow *window = glfwCreateWindow(400, 400, "Practice_openGL", NULL, NULL);
    if(window == NULL)
    {
        printf("Failed to create window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Bind window and context
    
    //init GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        printf("Failed init GLEW");
        glfwTerminate();
        return -1;
    }
    
    Shader* loadShader = new Shader("vertexSource.txt", "fragmentSource.txt");
    
    unsigned int VAO;
    glGenVertexArrays(1, &VAO); //Gen
    glBindVertexArray(VAO); //Bind VAO
    
    unsigned int VBO;
    glGenBuffers(1, &VBO); //Gen
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Bind VBO on VAO
    
    //Bind vertices to buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // load and create a texture
    unsigned int texture;
    glGenTextures(1, &texture); //Gen
    glBindTexture(GL_TEXTURE_2D, texture);
      
    int width, height, nrChannels;
    unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data); //release data
    
    /*
    // Create shader -> GLSL Souce -> Compile
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    // Create shader program -> Attach -> Link
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    */
    
    // Vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // vertex index = 0
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1); // vertex index = 1
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2); // vertex index = 2
    
    // Show on the screen
    // 1. Give location & window size
    glViewport(0, 0, 800, 600);
    // 2. Rander loop & Event process
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //glUseProgram(shaderProgram);
        loadShader->use();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(window); //color buffer process
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}


