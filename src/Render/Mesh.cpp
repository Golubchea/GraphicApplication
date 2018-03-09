#define GLEW_STATIC
#include <GL/glew.h>
#include "Mesh.h"
#include <SDL.h>
#include <math.h>
#include <vector>
#include <iostream>
#include "Shader.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Mesh::Mesh(std::string _name,MouseProperties *mousePtr1,glm::vec3 _position,std::vector<Vertex> _vertices, std::vector<GLuint> _indices,const char* image1):isSelect(false)
{
    this->name=_name;
    this->mousePtr=mousePtr1;
    this->mode=GL_TRIANGLES;
    this->position=_position;
    this->vertices=_vertices;
    this->indices=_indices;
    if(_name=="boundingBox"){

        const GLchar* vertexShaderSource = "#version 330 core\n"
                                           "layout (location = 0) in vec3 position;\n"
                                           "layout (location = 1) in vec3 color;\n"
                                           "layout (location = 2) in vec2 texCoord;\n"
                                           "uniform mat4 model;\n"
                                           "uniform mat4 view;\n"
                                           " uniform mat4 projection;\n"
                                           "out vec3 ourColor;\n"
                                           " out vec2 TexCoord;\n"
                                           "void main()\n"
                                           " {\n"
                                           "  gl_Position = projection * model * vec4(position, 1.0f);\n"
                                           "  ourColor = color;\n"
                                           "   TexCoord = vec2(0, 0);\n"
                                           " }\n\0";

        const GLchar* fragmentShaderSource = "#version 330 core\n"
                                             "in vec3 ourColor;\n"
                                             "in vec2 TexCoord;   \n"
                                             "out vec4 color;\n"
                                             "uniform sampler2D ourTexture;\n"
                                             "void main()\n"
                                             "{\n"
                                             "color = vec4(0.267f, 0.784f, 0.388f, 1.0f);\n"
                                             " }\n\0";




        Shader *ShaderProgram1=new Shader(vertexShaderSource,fragmentShaderSource,true);
        this->ShaderProgram=ShaderProgram1;
        model    = glm::mat4(1.0);

    }



/*
    if(_name=="minimize" ||_name=="resize" ||_name== "close")
    {
         model    = glm::mat4(1.0);
    }

    */
    if(_name!="boundingBox"){
        const GLchar* vertexShaderSource = "#version 330 core\n"
                                           "layout (location = 0) in vec3 position;\n"
                                           "layout (location = 1) in vec3 color;\n"
                                           "layout (location = 2) in vec2 texCoord;\n"
                                           "uniform mat4 model;\n"
                                           "uniform mat4 view;\n"
                                           " uniform mat4 projection;\n"
                                           "out vec3 ourColor;\n"
                                           " out vec2 TexCoord;\n"
                                           "void main()\n"
                                           " {\n"
                                           "  gl_Position = projection * view * model * vec4(position, 1.0f);\n"
                                           "  ourColor = color;\n"
                                           "   TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);\n"
                                           " }\n\0";

        const GLchar* fragmentShaderSource = "#version 330 core\n"
                                             "in vec3 ourColor;\n"
                                             "in vec2 TexCoord;   \n"
                                             "out vec4 color;\n"
                                             "uniform sampler2D ourTexture;\n"
                                             "void main()\n"
                                             "{\n"
                                             "color = texture(ourTexture, TexCoord);\n"
                                             " }\n\0";

        Shader *ShaderProgram1=new Shader(vertexShaderSource,fragmentShaderSource,true);
        this->ShaderProgram=ShaderProgram1;


        model =glm::translate(model,position);
    }




    //   glBufferData(GL_ARRAY_BUFFER,   vertices1.size() * sizeof(glm::vec3(ver2.x,  ver2.y, ver2.z)),
    // &vertices1[0], GL_DYNAMIC_DRAW);



    //this->vertices.size()*sizeof(glm::vec3(0.0f,  0.0f, 0.0f)

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex),
                 &this->vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint),
                 &this->indices[0], GL_STATIC_DRAW);

    // Vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (GLvoid*)0);
    // Vertex Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (GLvoid*)offsetof(Vertex, color));
    // Vertex Texture Coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (GLvoid*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
if(_name!="boundingBox")
{
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
    // Set our texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load, create texture and generate mipmaps
    int width=24, height=24;


    SDL_Surface * image = SDL_LoadBMP(image1);

    GLint colors = image->format->BytesPerPixel;
    GLenum texture_format;
    if (colors == 4) {   // alpha
        if (image->format->Rmask == 0x000000ff)
            texture_format = GL_RGBA;
        else
            texture_format = GL_BGRA;
    } else {             // no alpha
        if (image->format->Rmask == 0x000000ff)
            texture_format = GL_RGB;
        else
            texture_format = GL_BGR;
    }



    glTexImage2D(GL_TEXTURE_2D, 0, colors, width, height, 0, texture_format, GL_UNSIGNED_BYTE ,image->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    SDL_FreeSurface(image);

    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

}
else{

}
}

void Mesh::setVertices(glm::vec3 ver2,glm::vec3 ver1)
{





    std::vector<glm::vec3> vertices1;
    vertices1.push_back(glm::vec3(ver2.x,  ver2.y, ver2.z));
    vertices1.push_back(glm::vec3(ver2.x,  ver1.y, ver2.z));
    vertices1.push_back(glm::vec3(ver1.x,  ver1.y, ver2.z));
    vertices1.push_back(glm::vec3(ver1.x,  ver2.y, ver2.z));
    vertices1.push_back(glm::vec3(ver2.x,  ver2.y, ver2.z));





    this->mode=GL_LINE_STRIP ;

    glBindVertexArray(VAO);


    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,   vertices1.size() * sizeof(glm::vec3(ver2.x,  ver2.y, ver2.z)),
                 &vertices1[0], GL_DYNAMIC_DRAW);
    // Position attribute
     glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  3*sizeof(GLfloat), (GLvoid*)0);



    // Vertex Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (GLvoid*)offsetof(Vertex, color));

  glBindVertexArray(0);
}

void Mesh::draw()
{
    this->ShaderProgram->Use();
    GLint modelLoc = glGetUniformLocation(this->ShaderProgram->Program, "model");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Bind Textures using texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glUniform1i(glGetUniformLocation(this->ShaderProgram->Program, "ourTexture"), 0);
    glBindVertexArray(VAO);
    if (mode==GL_LINE_STRIP||mode==GL_LINE_LOOP){
        glLineWidth(1);
        glDrawArrays(mode, 0, 5);
    }
    else
    {
        glLineWidth(1);
        glDrawElements(mode, this->indices.size()+1, GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(0);
}


void Mesh::isSelected()
{
    this->ShaderProgram->~Shader();
    delete this->ShaderProgram;
    const GLchar* vertexShaderSource = "#version 330 core\n"
                                       "layout (location = 0) in vec3 position;\n"
                                       "layout (location = 1) in vec3 color;\n"
                                       "layout (location = 2) in vec2 texCoord;\n"
                                       "uniform mat4 model;\n"
                                       "uniform mat4 view;\n"
                                       " uniform mat4 projection;\n"
                                       "out vec3 ourColor;\n"
                                       " out vec2 TexCoord;\n"
                                       "void main()\n"
                                       " {\n"
                                       "  gl_Position = projection * view * model * vec4(position, 1.0f);\n"
                                       "  ourColor = color;\n"
                                       "   TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);\n"
                                       " }\n\0";


    const GLchar* fragmentShaderSourceSelected = "#version 330 core\n"
                                                 "in vec3 ourColor;\n"
                                                 "in vec2 TexCoord;   \n"
                                                 "out vec4 color;\n"
                                                 "uniform sampler2D ourTexture;\n"
                                                 "void main()\n"
                                                 "{\n"
                                                 "color = vec4(ourColor, 1.0f);\n"
                                                 " }\n\0";


    Shader *ShaderProgram1=new Shader(vertexShaderSource,fragmentShaderSourceSelected,true);
    this->ShaderProgram=ShaderProgram1;
    this->isSelect=true;

}


void Mesh::isDeselected(){
    this->ShaderProgram->~Shader();
    delete this->ShaderProgram;
    const GLchar* vertexShaderSource = "#version 330 core\n"
                                       "layout (location = 0) in vec3 position;\n"
                                       "layout (location = 1) in vec3 color;\n"
                                       "layout (location = 2) in vec2 texCoord;\n"
                                       "uniform mat4 model;\n"
                                       "uniform mat4 view;\n"
                                       " uniform mat4 projection;\n"
                                       "out vec3 ourColor;\n"
                                       " out vec2 TexCoord;\n"
                                       "void main()\n"
                                       " {\n"
                                       "  gl_Position = projection * view * model * vec4(position, 1.0f);\n"
                                       "  ourColor = color;\n"
                                       "   TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);\n"
                                       " }\n\0";

    const GLchar* fragmentShaderSource = "#version 330 core\n"
                                         "in vec3 ourColor;\n"
                                         "in vec2 TexCoord;   \n"
                                         "out vec4 color;\n"
                                         "uniform sampler2D ourTexture;\n"
                                         "void main()\n"
                                         "{\n"
                                         "color = texture(ourTexture, TexCoord);\n"
                                         " }\n\0";




    Shader *ShaderProgram1=new Shader(vertexShaderSource,fragmentShaderSource,true);
    this->ShaderProgram=ShaderProgram1;
    this->isSelect=false;
}

Mesh::~Mesh()
{

    this->ShaderProgram->~Shader();
    delete this->ShaderProgram;

    glDeleteVertexArrays(1, &VAO);

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &VAO);
    //glDeleteBuffers(1, &ibo_cube_elements);
    glDeleteTextures(1, &this->texture1);
}




