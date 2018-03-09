#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H
#include <SDL.h>
#include "../Render/MeshGroup.h"
#include "MouseProperties.h"
#include "../imgui/fontstash.h"
#define c(msg) do { std::cout << msg << std::endl; } while (0)

class SystemManager
{
public:
    SystemManager();
    ~SystemManager();
    void loop(SDL_Window* window1);

    SDL_Event event;
    bool running;

    MeshGroup *meshes=nullptr;
    MouseProperties *mousePtr=nullptr;
  SDL_DisplayMode dm;






};

#endif // INPUTMANAGER_H
