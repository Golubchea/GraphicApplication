#define GLEW_STATIC
#include"window.h"


Window::Window(int window_width ,int window_height,const char *programName,bool fullScreen):modernGLEnabled(false)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) < 0)
        co("Failed to initialize SDL");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1); //antialiasing
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);


    auto x = SDL_WINDOWPOS_CENTERED;
    auto y = SDL_WINDOWPOS_CENTERED;
    auto flags = SDL_WINDOW_OPENGL |SDL_WINDOW_RESIZABLE|SDL_WINDOW_BORDERLESS;
    if (fullScreen)
        flags |= SDL_WINDOW_FULLSCREEN;

    window = SDL_CreateWindow(programName, x, y, window_width, window_height, flags);
    context = SDL_GL_CreateContext(window);

    SDL_bool enabled=SDL_TRUE;   //для смещения окна
    SDL_CaptureMouse(enabled);  //для смещения окна

    glewExperimental = true;
    glewInit();

    SDL_GL_SetSwapInterval(1);

    if (glewIsSupported("GL_VERSION_3_2"))
    {
        co("gl3.3 support");
        this->modernGLEnabled=true;
    }
}





Window::~Window()
{
    if (context)
        SDL_GL_DeleteContext(context);
    if (window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}
