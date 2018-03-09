#include "SystemManager.h"
#include <GL/glew.h>
#include <math.h>
#include <string>
#include "../Render/Mesh.h"
#include "../Render/MeshGroup.h"
#include "../Render/Camera.h"

#include "../imgui/imgui.h"
#include "../imgui/imguiRenderGL3.h"
//#include "../imgui/fontstash.h"


SystemManager::SystemManager():running(true)
{
    MouseProperties *mousePtr1 =new MouseProperties();
    this->mousePtr=mousePtr1;
    this->mousePtr->firstMouse=true;
    this->mousePtr->WindowWidth=500;
    this->mousePtr->WindowHeight=600;
    this->meshes=new MeshGroup();
    this->meshes->mousePtr=this->mousePtr;


    ////////////////////////////////////////////////////////////
    if (!imguiRenderGLInit("DroidSans.ttf"))
    {
        fprintf(stderr, "Could not init GUI renderer.\n");
        exit(EXIT_FAILURE);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);


}

SystemManager::~SystemManager()
{
    delete mousePtr;
    delete meshes;
    running=false;
    imguiRenderGLDestroy();
}

void SystemManager::loop(SDL_Window* window1)
{
    GLfloat lastX=250;
    GLfloat lastY=300;
    GLfloat xoffset=0;
    GLfloat yoffset=0;
    bool created_window_buttons=false;
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;
    std::string inputText = "Some Text";
    int scrollarea1 = 0;
    while (running)
    {
        GLfloat currentFrame = SDL_GetTicks()/250.0f;
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        int value1 = 2;
        int mscroll = 0;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEMOTION:
                //loop



                //drag window
                if(this->mousePtr->dragWindow==true)
                {
                    int align=0;
                    if(this->mousePtr->mouse_x_globalSpace<=10)
                    {
                        align=1;
                    }
                    if(  this->mousePtr->mouse_x_globalSpace>dm.w-10)
                    {
                        align=2;
                    }
                    if(  this->mousePtr->mouse_y_globalSpace<=10 && this->mousePtr->mouse_x_globalSpace>dm.w/2-100 && this->mousePtr->mouse_x_globalSpace<dm.w/2+100)
                    {
                        align=3;
                    }

                    switch (align) // начало оператора switch
                    {
                    case 1: //left
                    {
                        SDL_SetWindowPosition(window1,0,0);
                        SDL_SetWindowSize(window1,dm.w/2,dm.h-35);
                        break;
                    }
                    case 2: //right
                    {
                        SDL_SetWindowPosition(window1,dm.w/2,0);
                        SDL_SetWindowSize(window1,dm.w/2,dm.h-35);
                        break;
                    }
                    case 3: // top
                    {
                        SDL_SetWindowPosition(window1,0,0);
                        SDL_SetWindowSize(window1,dm.w,dm.h-35);
                        break;
                    }
                    default: // если count равно любому другому значению
                        SDL_SetWindowPosition(window1,this->mousePtr->mouse_x_globalSpace-this->mousePtr->mouse_x_old,this->mousePtr->mouse_y_globalSpace);
                    }
                }

                //for Camera class
                xoffset = this->mousePtr->mouse_x - lastX;
                yoffset = lastY - this->mousePtr->mouse_y;  // Reversed since y-coordinates go from bottom to left

                lastX = this->mousePtr->mouse_x;
                lastY = this->mousePtr->mouse_y;

                if(event.button.button==SDL_BUTTON_MIDDLE){
                    if(this->mousePtr->firstMouse)
                    {
                        this->mousePtr->firstMouse = false;
                    }
                    this->meshes->camera->ProcessMouseMovement(xoffset, yoffset,true);
                }
                this->mousePtr->mouse_x= event.motion.x;
                this->mousePtr->mouse_y = event.motion.y;
                if(!this->meshes->Meshes->empty()&&this->meshes->Meshes->back()->name=="boundingBox")//&&event.button.button==SDL_BUTTON_RIGHT)
                {
                    this->meshes->Meshes->back()->setVertices(this->meshes->setBorders(1),this->meshes->oldBorder);
                }
                SDL_GetGlobalMouseState(&this->mousePtr->mouse_x_globalSpace,&this->mousePtr->mouse_y_globalSpace);
                if(created_window_buttons==false)
                {
                    /////////////////////////////////////////////////
                    this->meshes->addMesh("minimize",this->mousePtr->WindowWidth-50,5,"minimize.bmp",2);
                    this->meshes->addMesh("resize",this->mousePtr->WindowWidth-25,5,"resize.bmp",2);
                    this->meshes->addMesh("close",this->mousePtr->WindowWidth-5,5,"close.bmp",2);
                    created_window_buttons=true;
                }


                break;
            case SDL_MOUSEBUTTONDOWN:
                if( event.button.button == SDL_BUTTON_LEFT  && this->mousePtr->mouse_y>10)
                {
                    this->meshes->selected();
                    this->meshes->addMesh("boundingBox");
                    this->mousePtr->mouse_x_old=event.motion.x;
                    this->mousePtr->mouse_y_old=event.motion.y;
                    this->meshes->oldBorder=this->meshes->setBorders(1);

                    this->mousePtr->mousebutton = IMGUI_MBUT_LEFT;
                    if(!this->meshes->selectedGui->empty())
                    {
                        if(this->meshes->selectedGui->back()->name=="minimize")
                        {
                            SDL_MinimizeWindow(window1);
                            //    this->meshes->selectedGui->back()=nullptr;
                        }
                        if(this->meshes->selectedGui->back()->name=="resize")
                        {
                            SDL_SetWindowPosition(window1,0,0);
                            SDL_SetWindowSize(window1,dm.w,dm.h-35);
                            //  this->meshes->selectedGui->back()=nullptr;
                        }
                        if(this->meshes->selectedGui->back()->name=="close")
                        {
                            //  this->meshes->selectedGui->back()=nullptr;
                            running = false;
                            SDL_Quit();
                        }
                    }
                }
                if( event.button.button == SDL_BUTTON_LEFT && this->mousePtr->mouse_y<=10 )
                {
                    SDL_GetCurrentDisplayMode(0, &this->dm);
                    this->mousePtr->mouse_x_old= event.motion.x;
                    this->mousePtr->dragWindow=true;
                }else
                {
                    this->mousePtr->dragWindow=false;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if( event.button.button == SDL_BUTTON_LEFT ){
                    this->meshes->removeMesh("boundingBox");
                    this->meshes->selectedBorder (this->mousePtr->mouse_x_old,this->mousePtr->mouse_y_old);
                    this->meshes->drawBB();
                    this->mousePtr->dragWindow=false;
                }
                this->mousePtr->mousebutton= 0;
                break;
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:

                // SDL_StopTextInput();

                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = false;
                    SDL_Quit();
                }
                if (event.key.keysym.sym == SDLK_1)
                {
                    this->meshes->addMesh("1");
                    value1 =2;

                }
                if (event.key.keysym.sym == SDLK_2)
                {

                    this->meshes->removeMesh("boundingBox3d");
                }
                if (event.key.keysym.sym == SDLK_3)
                {

                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

                }
                if (event.key.keysym.sym == SDLK_4)
                {

                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

                }
                if (event.key.keysym.sym == SDLK_5)
                {
                    this->meshes->addMesh("boundingBox");
                }
                if (event.key.keysym.sym == SDLK_f)
                {
                    this->meshes->addMesh("box",this->mousePtr->mouse_x,this->mousePtr->mouse_y,"minimize.bmp",3);


                }
                if (event.key.keysym.sym == SDLK_7)
                {
                    this->meshes->Meshes->back()->isDeselected();
                }
                if (event.key.keysym.sym == SDLK_7)
                {
                    this->meshes->Meshes->back()->isSelected();
                }

                if (event.key.keysym.sym == SDLK_w)
                {
                    this->meshes->camera->ProcessKeyboard(FORWARD, deltaTime);
                }
                if (event.key.keysym.sym == SDLK_s)
                {
                    this->meshes->camera->ProcessKeyboard(BACKWARD, deltaTime);
                }
                if (event.key.keysym.sym == SDLK_d)
                {
                    this->meshes->camera->ProcessKeyboard(RIGHT, deltaTime);
                }
                if (event.key.keysym.sym == SDLK_a)
                {
                    this->meshes->camera->ProcessKeyboard(LEFT, deltaTime);
                }
                if (event.key.keysym.sym == SDLK_q)
                {
                    this->meshes->selected();
                }
                if( event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
                {
                    //lop off character
                    inputText.pop_back();

                }
                //Handle copy
                else if( event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
                {
                    SDL_SetClipboardText( inputText.c_str() );
                }
                //Handle paste
                else if( event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
                {
                    inputText = SDL_GetClipboardText();

                }

                if (event.key.keysym.sym == SDLK_9)
                {

                }
                break;
            case SDL_TEXTINPUT:
            {
                //Not copy or pasting
                if( !( ( event.text.text[ 0 ] == 'c' || event.text.text[ 0 ] == 'C' ) && ( event.text.text[ 0 ] == 'v' || event.text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) )
                {
                   // inputText += event.text.text;
                }
            }
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                {
                    running = false;
                }
                if(event.window.event==SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    this->mousePtr->WindowWidth=event.window.data1;


                    this->mousePtr->WindowHeight= event.window.data2;
                    glViewport(0, 0, event.window.data1, event.window.data2);
                }
                break;

            default:
                break;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 0.7f);
        meshes->draw();


        imguiBeginFrame(this->meshes->mousePtr->mouse_x,this->meshes->mousePtr->WindowHeight- this->meshes->mousePtr->mouse_y,this->mousePtr->mousebutton, mscroll);

        if(value1 ==2){
            imguiDrawText(this->meshes->mousePtr->mouse_x,this->meshes->mousePtr->WindowHeight- this->meshes->mousePtr->mouse_y, IMGUI_ALIGN_LEFT, inputText.c_str(),  imguiRGBA(32,192, 32,192));
        }


        imguiBeginScrollArea("MENU", 0, 35, this->meshes->mousePtr->WindowWidth / 5, this->meshes->mousePtr->WindowHeight - 20, &scrollarea1);
        imguiSeparatorLine();
        imguiSeparator();
        //imguiSlider("Slider", &value1, 0.f, 100.f, 1.f);
        imguiButton("Open");

        imguiButton("Save",true);
        imguiItem("Item");
        imguiItem("Item");
        imguiItem("Disabled item", false);
        imguiEndScrollArea();
        imguiRenderGLDraw(this->meshes->mousePtr->WindowWidth, this->meshes->mousePtr->WindowHeight);
        imguiEndFrame();




        value1 =1;
        SDL_GL_SwapWindow(window1);
    }
}




