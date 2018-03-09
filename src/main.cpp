#include <SDL.h>
#include "System/SystemManager.h"
#include "System/window.h"


int main(int argc, char* argv[]) {
    Window Window1(500 ,600,argv[0],false);
    SystemManager SystemManager1;






    while(SystemManager1.running)
    {
        SystemManager1.loop(Window1.window);
    }
    return 0;
}
