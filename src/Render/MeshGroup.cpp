
#include "MeshGroup.h"
#include "Mesh.h"
#include <memory>
#include <iostream>
#include <SDL.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/closest_point.hpp>

using namespace std;
MeshGroup::MeshGroup()
{
    this->camera=new Camera(glm::vec3(0.0f, 0.0f, 1.0f));
    this->Meshes=new std::vector<Mesh*>();
    this->selectedMeshes=new std::vector<Mesh*>();
    this->selectedGui=new std::vector<Mesh*>();
    this->Gui=new std::vector<Mesh*>();
}

void MeshGroup::addMesh(std::string name)
{
    glm::vec3 wincoord = glm::vec3( (GLfloat)this->mousePtr->mouse_x,(GLfloat)this->mousePtr->WindowHeight - (GLfloat)this->mousePtr->mouse_y- 1.0f ,  0.99);
    glm::vec4 viewport = glm::vec4(0, 0, (GLfloat)this->mousePtr->WindowWidth, (GLfloat)this->mousePtr->WindowHeight);

    std::vector<Vertex>_vertices;
    Vertex v1={glm::vec3(0.1f,  0.1f, 0.0f),  glm::vec3(0.267f, 0.784f, 0.388f),glm::vec2(1.0f, 1.0f)};
    Vertex v2={glm::vec3(0.1f,  -0.1f, 0.0f),  glm::vec3(0.267f, 0.784f, 0.388f),glm::vec2(1.0f, 0.0f)};
    Vertex v3={glm::vec3(-0.1f, -0.1f, 0.0f),glm::vec3(0.267f, 0.784f, 0.388f),glm::vec2(0.0f, 0.0f)};
    Vertex v4={glm::vec3( -0.1f, 0.1f, 0.0f), glm::vec3(0.267f, 0.784f, 0.388f),glm::vec2(0.0f, 1.0f)};
    _vertices.push_back(v1);
    _vertices.push_back(v2);
    _vertices.push_back(v3);
    _vertices.push_back(v4);
    std::vector <GLuint> _indices= {  // Note that we start from 0!
                                      0, 1, 3, // First Triangle
                                      1, 2, 3  // Second Triangle
                                   };

    //Mesh()
    Meshes->push_back(new Mesh(name,this->mousePtr,glm::unProject(wincoord, view, projection, viewport),_vertices,_indices,"image.bmp"));
    //  co(Meshes->size());
}

void MeshGroup::addMesh(std::string name,int x,int y,const char* image,int mode)
{

    //Mesh()
    if(mode==1)
    {
        glm::vec3 wincoord = glm::vec3( (GLfloat)x,(GLfloat)this->mousePtr->WindowHeight - (GLfloat)y- 1.0f ,  0.99);
        glm::vec4 viewport = glm::vec4(0, 0, (GLfloat)this->mousePtr->WindowWidth, (GLfloat)this->mousePtr->WindowHeight);
        //glm::mat4 view1=glm::mat4(1.0);
        std::vector<Vertex>_vertices;
        Vertex v1={glm::vec3(0.1f,  0.1f, 0.0f),  glm::vec3(1.0f, 0.0f, 0.0f),glm::vec2(1.0f, 1.0f)};
        Vertex v2={glm::vec3(0.1f,  -0.1f, 0.0f),  glm::vec3(0.0f, 1.0f, 0.0f),glm::vec2(1.0f, 0.0f)};
        Vertex v3={glm::vec3(-0.1f, -0.1f, 0.0f),glm::vec3(0.0f, 0.0f, 1.0f),glm::vec2(0.0f, 0.0f)};
        Vertex v4={glm::vec3( -0.1f, 0.1f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f),glm::vec2(0.0f, 1.0f)};
        _vertices.push_back(v1);
        _vertices.push_back(v2);
        _vertices.push_back(v3);
        _vertices.push_back(v4);
        std::vector <GLuint> _indices= {  // Note that we start from 0!
                                          0, 1, 3, // First Triangle
                                          1, 2, 3  // Second Triangle
                                       };
        Meshes->push_back(new Mesh(name,this->mousePtr,glm::unProject(wincoord, view, projection, viewport),_vertices,_indices,image));
    }
    //gui
    if(mode==2)
    {
        glm::vec3 wincoord = glm::vec3( (GLfloat)x,(GLfloat)this->mousePtr->WindowHeight - (GLfloat)y- 1.0f ,  0.99);
        glm::vec4 viewport = glm::vec4(0, 0, (GLfloat)this->mousePtr->WindowWidth, (GLfloat)this->mousePtr->WindowHeight);
        //glm::mat4 view1=glm::mat4(1.0);
        std::vector<Vertex>_vertices;
        Vertex v1={glm::vec3(0.1f,  0.1f, 0.0f),  glm::vec3(1.0f, 0.0f, 0.0f),glm::vec2(1.0f, 1.0f)};
        Vertex v2={glm::vec3(0.1f,  -0.1f, 0.0f),  glm::vec3(0.0f, 1.0f, 0.0f),glm::vec2(1.0f, 0.0f)};
        Vertex v3={glm::vec3(-0.1f, -0.1f, 0.0f),glm::vec3(0.0f, 0.0f, 1.0f),glm::vec2(0.0f, 0.0f)};
        Vertex v4={glm::vec3( -0.1f, 0.1f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f),glm::vec2(0.0f, 1.0f)};
        _vertices.push_back(v1);
        _vertices.push_back(v2);
        _vertices.push_back(v3);
        _vertices.push_back(v4);
        std::vector <GLuint> _indices= {  // Note that we start from 0!
                                          0, 1, 3, // First Triangle
                                          1, 2, 3  // Second Triangle
                                       };
        Gui->push_back(new Mesh(name,this->mousePtr,glm::unProject(wincoord, view, projection, viewport),_vertices,_indices,image));
    }
    //obj
    if(mode==3)
    {

        glm::vec3 wincoord = glm::vec3( (GLfloat)x,(GLfloat)this->mousePtr->WindowHeight - (GLfloat)y- 1.0f ,  0.99);
        glm::vec4 viewport = glm::vec4(0, 0, (GLfloat)this->mousePtr->WindowWidth, (GLfloat)this->mousePtr->WindowHeight);
        //glm::mat4 view1=glm::mat4(1.0);
        std::vector<Vertex>_vertices;

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<GLuint> elements;


        this->load_obj("box.obj", vertices, normals, elements);
        for(size_t i=0;i<vertices.size();i++)
        {
            Vertex v4={vertices[i], normals[i],glm::vec2(vertices[i].x,vertices[i].y)};
            _vertices.push_back(v4);
            std::cout<<normals[i].x<<normals[i].y<<normals[i].z<<std::endl;
        }
        std::cout<<"elements.size()"<<std::endl;
        std::cout<<elements.size()<<std::endl;


        Meshes->push_back(new Mesh(name,this->mousePtr,glm::unProject(wincoord, view, projection, viewport),_vertices,elements,image));
    }

}

void MeshGroup::load_obj(const char* filename, vector<glm::vec3> &vertices, vector<glm::vec3> &normals, vector<GLuint> &elements)
{
    ifstream in(filename, ios::in);
    if (!in)
    {
        cerr << "Cannot open " << filename << endl; exit(1);
    }

    string line;
    while (getline(in, line))
    {
        if (line.substr(0,2) == "v ")
        {
            istringstream s(line.substr(2));
            glm::vec3 v; s >> v.x; s >> v.y; s >> v.z;
            vertices.push_back(v);
        }
        else if (line.substr(0,2) == "f ")
        {
            istringstream s(line.substr(2));
            GLuint a,b,c;
            s >> a; s >> b; s >> c;
            a--; b--; c--;
            elements.push_back(a); elements.push_back(b); elements.push_back(c);
        }
        else if (line[0] == '#')
        {
            /* ignoring this line */
        }
        else
        {
            /* ignoring this line */
        }
    }

    normals.resize(vertices.size(), glm::vec3(0.0, 0.0, 0.0));
    for (GLuint i = 0; i < elements.size(); i+=3)
    {
        GLuint ia = elements[i];
        GLuint ib = elements[i+1];
        GLuint ic = elements[i+2];
        glm::vec3 normal = glm::normalize(glm::cross(
                                              glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
                                              glm::vec3(vertices[ic]) - glm::vec3(vertices[ia])));
        normals[ia] = normals[ib] = normals[ic] = normal;
    }
}








void MeshGroup::removeMesh(std::string name)
{


    GLuint i =0;
    while (i < Meshes->size())
    {
        if((this->Meshes->at(i))->name==name)
        {
            (this->Meshes->at(i))->~Mesh();
            Meshes->erase(Meshes->begin()+i);
        }
        else
        {
            ++i;
        }
    }
}

glm::vec3 MeshGroup::setBorders(GLuint mode)
{
    glm::mat4 view1=glm::mat4(1.0);
    glm::vec3 wincoord = glm::vec3( (GLfloat)this->mousePtr->mouse_x,(GLfloat)this->mousePtr->WindowHeight -(GLfloat)this->mousePtr->mouse_y- 1.0f ,  1.00);
    glm::vec4 viewport = glm::vec4(0, 0, (GLfloat)this->mousePtr->WindowWidth, (GLfloat)this->mousePtr->WindowHeight);
    if (mode==1){
        return glm::unProject(wincoord, view1, projection, viewport);
    }
    else
    {
        return glm::unProject(wincoord, view, projection, viewport);
    }
}

void MeshGroup::draw()
{
    view = camera->GetViewMatrix();
    projection = glm::perspective(camera->Zoom, (GLfloat)this->mousePtr->WindowWidth/(GLfloat)this->mousePtr->WindowHeight, 0.1f, 200.0f);
    //projection =glm::ortho(0.0f,(GLfloat)this->mousePtr->WindowWidth,(GLfloat)this->mousePtr->WindowWidth,0.0f,-1.0f,1.0f);
    for (size_t i =0; i < Meshes->size(); i++)
    {
        viewLoc = glGetUniformLocation((((this->Meshes->at(i))->ShaderProgram->Program)), "view");
        projLoc = glGetUniformLocation((((this->Meshes->at(i))->ShaderProgram->Program)), "projection");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        (this->Meshes->at(i))->draw();
    }
    for (size_t i =0; i < Gui->size(); i++)
    {
        viewLoc = glGetUniformLocation((((this->Gui->at(i))->ShaderProgram->Program)), "view");
        projLoc = glGetUniformLocation((((this->Gui->at(i))->ShaderProgram->Program)), "projection");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        (this->Gui->at(i))->draw();
    }

}

void MeshGroup::selected(){
    float closest_distance = 1.0 / 0.0; // infinity

    glm::vec3 wincoord = glm::vec3( (GLfloat)this->mousePtr->mouse_x,(GLfloat)this->mousePtr->WindowHeight - (GLfloat)this->mousePtr->mouse_y - 1.0f,  1.0f);
    glm::vec4 viewport = glm::vec4(0, 0, (GLfloat)this->mousePtr->WindowWidth, (GLfloat)this->mousePtr->WindowHeight);

    glm::vec3 point1 = camera->Position;
    glm::vec3 point2 = glm::unProject(wincoord, view, projection, viewport);

    for (size_t i =0; i < Meshes->size(); i++)
    {
        glm::vec3 cpol = glm::closestPointOnLine((this->Meshes->at(i))->position, point1, point2);
        float dtol = glm::distance((this->Meshes->at(i))->position, cpol);
        float distance = glm::distance((this->Meshes->at(i))->position, camera->Position);
        if(dtol < 0.2 * sqrtf(1.0) && distance < closest_distance)
        {
            (this->Meshes->at(i))->isSelected();

            this->selectedMeshes->push_back((this->Meshes->at(i)));
        }
        else
        {
            (this->Meshes->at(i))->isDeselected();
        }
    }
    for (size_t i =0; i < Gui->size(); i++)
    {
        glm::vec3 cpol = glm::closestPointOnLine((this->Gui->at(i))->position, point1, point2);
        float dtol = glm::distance((this->Gui->at(i))->position, cpol);
        float distance = glm::distance((this->Gui->at(i))->position, camera->Position);
        if(dtol < 0.2 * sqrtf(1.0) && distance < closest_distance)
        {
            (this->Gui->at(i))->isSelected();

            this->selectedGui->push_back((this->Gui->at(i)));
        }
        else
        {
            (this->Gui->at(i))->isDeselected();
        }
    }
}

void MeshGroup::selectedBorder(int x1,int y1){
    float closest_distance = 1.0 / 0.0; // infinity
    glm::vec4 viewport = glm::vec4(0, 0, (GLfloat)this->mousePtr->WindowWidth, (GLfloat)this->mousePtr->WindowHeight);
    glm::vec3 point1 = camera->Position;
    int n=10;// point count of rays on one side of rectangle . all = 16

    GLfloat hx= ((GLfloat)this->mousePtr->mouse_x-(GLfloat)x1)/(GLfloat)n;
    GLfloat hy=((GLfloat)this->mousePtr->mouse_y-(GLfloat)y1)/(GLfloat)n;

    for(int k=0;k<=n;k++)
    {
        for(int j=0;j<=n;j++){
            glm::vec3 wincoord = glm::vec3( x1+hx*j,(GLfloat)this->mousePtr->WindowHeight- (y1+hy*k) - 1.0f,  1.0f);

            glm::vec3 point2 = glm::unProject(wincoord, view, projection, viewport);

            for (size_t i =0; i < Meshes->size(); i++)
            {
                glm::vec3 cpol = glm::closestPointOnLine((this->Meshes->at(i))->position, point1, point2);
                float dtol = glm::distance((this->Meshes->at(i))->position, cpol);
                float distance = glm::distance((this->Meshes->at(i))->position, camera->Position);
                if(dtol < 0.2 * sqrtf(3.0) && distance < closest_distance)
                {
                    (this->Meshes->at(i))->isSelected();
                    this->selectedMeshes->push_back((this->Meshes->at(i)));
                }

            }


        }
    }

}



void MeshGroup::drawBB() {
    /*
  if (this->selectedMeshes->size() == 0)
    return;


  GLfloat
    min_x, max_x,
    min_y, max_y,
    min_z, max_z;
  for (GLuint j = 0; j <  this->selectedMeshes->size(); j++) {
  min_x = max_x = this->selectedMeshes->at(j)->vertices[0].Position.x;
  min_y = max_y = this->selectedMeshes->at(j)->vertices[0].Position.y;
  min_z = max_z = this->selectedMeshes->at(j)->vertices[0].Position.z;
  for (GLuint i = 0; i <  this->selectedMeshes->at(0)->vertices.size(); i++) {
    if ( this->selectedMeshes->at(j)->vertices[i].Position.x < min_x) min_x = this->selectedMeshes->at(j)->vertices[i].Position.x;
    if ( this->selectedMeshes->at(j)->vertices[i].Position.x > max_x) max_x = this->selectedMeshes->at(j)->vertices[i].Position.x;
    if ( this->selectedMeshes->at(j)->vertices[i].Position.y < min_y) min_y = this->selectedMeshes->at(j)->vertices[i].Position.y;
    if ( this->selectedMeshes->at(j)->vertices[i].Position.y > max_y) max_y = this->selectedMeshes->at(j)->vertices[i].Position.y;
    if ( this->selectedMeshes->at(j)->vertices[i].Position.z < min_z) min_z = this->selectedMeshes->at(j)->vertices[i].Position.z;
    if ( this->selectedMeshes->at(j)->vertices[i].Position.z > max_z) max_z = this->selectedMeshes->at(j)->vertices[i].Position.z;

    glm::vec3 size = glm::vec3(max_x-min_x, max_y-min_y, max_z-min_z);
    glm::vec3 center = glm::vec3((min_x+max_x)/2, (min_y+max_y)/2, (min_z+max_z)/2);
    glm::mat4 transform =  glm::translate(glm::mat4(1), center)* glm::scale(glm::mat4(1), size);

    this->selectedMeshes->at(j)->model = this->selectedMeshes->at(j)->model * transform;
  }
  }




*/
}

MeshGroup::~MeshGroup()
{
    delete camera;
    for (std::vector<Mesh*>::iterator it =  Meshes->begin(); it !=  Meshes->end(); ++it)
    {
        //   (*it)->~Mesh();
        delete (*it);
    }
    //  for (std::vector<Mesh*>::iterator it =  selectedMeshes->begin(); it !=  selectedMeshes->end(); ++it)
    //  {
    //   (*it)->~Mesh();
    //      delete (*it);
    //  }
    for (std::vector<Mesh*>::iterator it =  Gui->begin(); it !=  Gui->end(); ++it)
    {
        //   (*it)->~Mesh();
        delete (*it);
    }
    delete Meshes;
    delete selectedMeshes;
    delete Gui;
}
