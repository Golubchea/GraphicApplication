#ifndef MESH_H
#define MESH_H
#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#include "Shader.h"
#include "../System/MouseProperties.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define co(msg) do { std::cout << msg << std::endl; } while (0)

struct Vertex {
    glm::vec3 Position;
    glm::vec3 color;
    glm::vec2 TexCoords;
};
class MouseProperties;
class Mesh
{
public:
    Mesh(std::string, MouseProperties *mousePtr,glm::vec3 _position,std::vector<Vertex> vertices, std::vector<GLuint> indices,const char* image);

    void draw();
    void setVertices(glm::vec3,glm::vec3);
    ~Mesh();




    GLuint VBO;
    GLuint VAO;
    GLuint EBO;
    GLuint texture1;
    Shader *ShaderProgram=nullptr;

    glm::mat4 model;
    glm::vec3 position;

    std::vector<Vertex> vertices;
     std:: vector<GLuint> indices;


    MouseProperties *mousePtr=nullptr;
    GLenum mode;

    std::string name;
    void isSelected();
    void isDeselected();
    bool isSelect;
private:

};

#endif 
