#ifndef MESHGROUP_H
#define MESHGROUP_H
#include <vector>
#include <string>
#include "Mesh.h"
#include "../System/MouseProperties.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Mesh;
class MouseProperties;
class MeshGroup
{
public:
    MeshGroup();

    ~MeshGroup();
    void addMesh(std::string);
    void addMesh(std::string name,int x,int y,const char* image,int mode);
    void removeMesh(std::string);
    glm::vec3 setBorders(GLuint mode);
    void selected();
    void selectedBorder(int x1,int y1);
    void load_obj(const char* filename, std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<GLuint> &elements);


    void drawBB();
    void draw();
    std::vector<Mesh*> *Meshes;
    std::vector<Mesh*> *selectedMeshes;
    std::vector<Mesh*> *Gui;
    std::vector<Mesh*> *selectedGui;
    MouseProperties *mousePtr=nullptr;

    Camera *camera;

    glm::mat4 view;




    glm::mat4 projection;


    glm::vec3 oldBorder;
    GLint viewLoc;
    GLint projLoc;

private:



};

#endif 
