#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include "pch.h"

struct RenderState
{
    int width;
    int height;
    int size;
    int x = 0;
    int y = 0;
    bool load;

    void cord_clear()
    {
        x,y = 0;
    }
};

static RenderState Render_State;

struct MainWindow
{
    int window_width() 
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int columns;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        
        return columns;
    }

    int window_height() 
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int rows;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        
        return rows;
    }

    void ShowConsoleCursor(bool showFlag)
    {
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);

        // set the cursor visibility
        cursorInfo.bVisible = showFlag; 

        SetConsoleCursorInfo(out, &cursorInfo);
    } 

    int center(int pointA, int pointB, std::string text)
    {
        int letters = text.size();
        int half =  (pointA - pointB - letters) / 2;
        return pointB + half + 1;
    }

    int clamp(int min, int val, int max)
    {
        if (val < min) return min;
        if (val > max) return max;
        return val;
    }

    template< typename TYPE >
    void draw_onScreen(int x, int y, TYPE message, int text_color)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coord;

        //x = clamp(0, x, Render_State.width); // width
        //y = clamp(0, y, Render_State.height);       
        coord.X = x;
        coord.Y = y;

        SetConsoleCursorPosition(hConsole, coord); 
        SetConsoleTextAttribute(hConsole, text_color);
        std::cout<< message <<std::endl;  
    }

    template< typename TYPE >
    void text(float x, float y, TYPE message, int text_color)
    {
        // x *= Render_State.width * 0.01f;
        // y *= Render_State.height * 0.01f;
        x += Render_State.width / 2.f;
        y += Render_State.height / 2.f;
        draw_onScreen(x, y, message, text_color);
    }

    void WindowInit() 
    {
        system("cls");
        HANDLE hOut;
        CONSOLE_SCREEN_BUFFER_INFO SBInfo;
        COORD NewSBSize;

        SetConsoleTitleA("Football Manager");
        ShowConsoleCursor(false);   

        Render_State.width = window_width();
        Render_State.height = window_height();          
        Render_State.size = Render_State.width * Render_State.height * sizeof(unsigned int); 

        hOut = GetStdHandle(STD_OUTPUT_HANDLE);

        GetConsoleScreenBufferInfo(hOut, &SBInfo);
        NewSBSize.X = Render_State.width;
        NewSBSize.Y = Render_State.height;

        SetConsoleScreenBufferSize(hOut, NewSBSize);
    }

    void WindowBuffer() 
    {        
        if (Render_State.width != window_width() || Render_State.height != window_height())
        {
            system("cls");
            Render_State.load = true;
            ShowConsoleCursor(false);  

            HANDLE hOut;
            CONSOLE_SCREEN_BUFFER_INFO SBInfo;
            COORD NewSBSize;

            Render_State.width = window_width();
            Render_State.height = window_height(); 
            hOut = GetStdHandle(STD_OUTPUT_HANDLE);

            NewSBSize.X = Render_State.width;
            NewSBSize.Y = Render_State.height;
            SetConsoleScreenBufferSize(hOut, NewSBSize);
        }
    } 

    int checker(int &cord, int size_cord)
    {
    if (cord < 0)
        return cord = 0;       
    else if (cord >= size_cord)
        return cord = size_cord - 1;
    else      
        return cord;
    }   
};

MainWindow Main_Window;

#endif /* MAINWINDOW_H_INCLUDED */