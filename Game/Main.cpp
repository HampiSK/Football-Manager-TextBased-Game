#include "pch.h"

static bool running = true;

std::string mainmenu(int &x, int &y)
{     
    /* Create main menu and return choosen menu */

    const std::vector<std::string> options = {"Campaign","Normal Game","Tutorial","Options","Quit"};
    y = Main_Window.checker(y, options.size());

    int center_y = -10;
    for (unsigned int i = 0; i < options.size(); i++)
    {
        int option_size = options[i].size();
        if (y == i)
        {
            Main_Window.text(0 - option_size / 2, center_y, options[i], 4);
            if(Button.confirm_state)
                return options[i];
        }
        else
            Main_Window.text(0 - option_size / 2, center_y, options[i], 7);
        
        center_y += 5;
    }

    return "none"; 
}

int main()
{
    /* Initialize game window, set seed for random values and run main menu of the game */

    srand(time(NULL));
    Main_Window.WindowInit();
    std::string run_menu;

    while (running)
    {
        Main_Window.WindowBuffer();
        buttons();
        
        run_menu = mainmenu(Render_State.x, Render_State.y);

        if (run_menu == "Campaign")
            Main_Window.text(10,0, "empty", 10);
        else if (run_menu == "Normal Game")
            Normal_Game.run(Render_State.x, Render_State.y); // create dropdown for NPC Player vs PLayer Player Events ON/OFF, create unique pointer for new team
        else if (run_menu == "Tutorial")
            Main_Window.text(10,0, "empty", 10);
        else if (run_menu == "Options")
            Main_Window.text(10,0, "empty", 10);
        else if (run_menu == "Quit")
            running = false;
    }

    return 0;
}