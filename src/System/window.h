#ifndef WINDOW_H
#define WINDOW_H
#define co(msg) do { std::cout << msg << std::endl; } while (0)

#include <SDL.h>
#include <cstdlib>
#include <iostream>

//#define GLEW_STATIC
#include <GL/glew.h>

using namespace std;

class Window{
public:
    Window(int screen_width ,int screen_height,const char *programName,bool fullScreen);
    ~Window();

    SDL_Window* window = nullptr;
    SDL_GLContext context = nullptr;

	bool modernGLEnabled;
	
};







#endif // WINDOW_H

