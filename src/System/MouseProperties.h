#ifndef MOUSEPROPERTIES_H
#define MOUSEPROPERTIES_H


class MouseProperties
{
public:
    int WindowWidth;
    int WindowHeight;

    int mouse_x;
    int mouse_y;

    int mouse_x_globalSpace;
    int mouse_x_old; //for window offset then moving
    int mouse_y_old; //for window offset then moving
    int mouse_y_globalSpace;
    unsigned char mousebutton ;
    bool firstMouse;
    bool dragWindow=false;
    MouseProperties * getPtr(){
        return this;
    }
}  ;

#endif 
