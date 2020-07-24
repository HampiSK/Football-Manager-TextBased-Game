#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "pch.h"

struct Buttons
{
    short unsigned int button_left       = 37;
    short unsigned int button_up         = 38;
    short unsigned int button_right      = 39;
    short unsigned int button_down       = 40;
    short unsigned int button_escape     = 27;
    short unsigned int button_backspace  = 8;
    short unsigned int button_enter      = 13;

    bool confirm_state = false;
    bool escape_state = false;
    bool backspace_state = false;
    bool button_state = false;
};

static Buttons Button;

void buttons()
{
    int key = 0;
    for(int i = 8; i <= 256; i++)
    {           
        if(GetAsyncKeyState(i) & 0x7FFF)             
            key = i;
    }

    if (key == Button.button_left)
    {
        Render_State.x--;
        Button.button_state = true;            
    }
    else if (key == Button.button_up)
    {
        Render_State.y--;
        Button.button_state = true;            
    }
    else if (key == Button.button_right)
    {
        Render_State.x++;
        Button.button_state = true;            
    }
    else if (key == Button.button_down)
    {
        Render_State.y++;
        Button.button_state = true;            
    }
    else if (key == Button.button_enter)
    {
        Button.confirm_state = true;
        Button.button_state = true;
    }
    else if (key == Button.button_escape)
    {
        Button.escape_state = true;
        Button.button_state = true;
    }
    else if (key == Button.button_backspace)
    {
        Button.backspace_state = true;
        Button.button_state = true;
    }
    else
    {
        Button.backspace_state = false;
        Button.confirm_state = false;
        Button.escape_state = false;
        Button.button_state = false;
    }
}

#endif /* BUTTON_H_INCLUDED */