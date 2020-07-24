#ifndef NORMALGAME_H_INCLUDED
#define NORMALGAME_H_INCLUDED

#include "pch.h"

struct NormalGameMenu
{
    void display_logo(std::map <int,std::string> &logo, int x, int row, int color)
    {
        /* Draw team logo on screen */

        for (unsigned int i = 0; i < logo.size(); i++)
        {
            Main_Window.text(x, row, logo[i], color);
            row += 1;
        } 
    }

    void bar_borders(int &x, int left, int right, int row)
    {
        /* Create simple borders around displayed team. 
        * Borders may change if they are at the end/start of the list of all teams */

        //Left border
        if (x == 0)
            Main_Window.text(left, row, '|', 7);
        else
            Main_Window.text(left, row, '<', 7);

        //Right border
        if (x == all_teams.size() - 1)
            Main_Window.text(right, row, '|', 7);
        else
            Main_Window.text(right, row, '>', 7);
    }

    bool choose_team(bool team, int &x, int color, int color_confirm)
    {
        /* Display data about choosen team from the list of all teams */
        
        // Prepared for initialisation          
        std::vector<int> text_coord;

        if (team)
            text_coord = { -57,-13,-31,-49,8,-60,10,-58,-10 }; // Coordinations for Team_A
        else
            text_coord = { 29,-13,55,37,8,26,10,28,-10 }; // Coordinations for Team_B

        // Assign coordinations of displayed text on screen
        int menu_left  = text_coord[0];
        int menu_row   = text_coord[1];
        int menu_right = text_coord[2];
        int overall_x  = text_coord[3];
        int overall_y  = text_coord[4];
        int stats_x    = text_coord[5];
        int stats_y    = text_coord[6];
        int logo_x     = text_coord[7];
        int row        = text_coord[8];

        for (unsigned int i = 0; i < all_teams.size(); i++)
        { 
            bar_borders(x, menu_left, menu_right, menu_row); // Create borders around team name
        
            std::map <int,std::string> logo = all_teams[i]->team_trademark(); // Copy team logo

            if (x == i)
            {              
                Stats.stats_setteam(team, all_teams[i]); // To calculate effectivity team must be initialized in Stats
                
                std::vector<int> team_stats = Effect.get_default_effectivity(team,"normalized"); // Get team effectivity
                std::string text_team_stats = "AT: "+std::to_string(team_stats[0])+" - MI: "+std::to_string(team_stats[1])+" - DE: "+std::to_string(team_stats[2])+" - GK: "+std::to_string(team_stats[3]);
                std::string text_team_overall = "OVERALL: "+std::to_string((team_stats[0]+team_stats[1]+team_stats[2]+team_stats[3]) / 4);
                
                std::string team_name = all_teams[i]->team_bio("name"); // Get team name
                int centerer = Main_Window.center(menu_left+2, menu_right-2, team_name);
                

                if (Button.confirm_state) // Draw team information
                {                                  
                    display_logo(logo, logo_x, row, color_confirm);
                    
                    Main_Window.text(centerer, menu_row, team_name, color_confirm);                   
                    Main_Window.text(stats_x, stats_y, text_team_stats, color_confirm);
                    Main_Window.text(overall_x, overall_y, text_team_overall, color_confirm);  

                    if(team)
                        Team_A = all_teams[i];
                    else 
                        Team_B = all_teams[i];
                    return true;                  
                }
                else // Draw team information
                {                   
                    display_logo(logo, logo_x, row, color);
                    
                    Main_Window.text(centerer, menu_row, team_name, color);                   
                    Main_Window.text(stats_x, stats_y, text_team_stats, color);
                    Main_Window.text(overall_x, overall_y, text_team_overall, color); 
                }
            }                                            
        }
        return false;  
    }

    void menu(int &x)
    {              
        Render_State.load = true;
        x = 0;

        bool lock_A = false;
        bool lock_B = false;
        int selected_A = 0;
        int selected_B = 0;

        while (true)
        {
            Main_Window.WindowBuffer();                
            buttons();
            x = Main_Window.checker(x, all_teams.size());

            if (Button.backspace_state)
            {
                system("cls"); 
                if (lock_B)
                {
                    lock_B = false;
                    Render_State.load = true;
                    x = selected_B;
                    selected_B = 0;                  
                    continue;
                }
                else if (lock_A)
                {
                    lock_A = false;
                    Render_State.load = true;
                    x = selected_A;
                    selected_A = 0;                   
                    continue;
                }             
                return;
            }

            if (Button.button_state || Render_State.load)
            {                   
                system("cls");
                Render_State.load = false;

                if (lock_A == false)
                {
                    lock_A = choose_team(true, x, 4, 10);
                    choose_team(false, selected_B, 4, 4);
                    if (lock_A)
                    {
                        selected_A = x;
                        x = 0;
                    }                        
                }
                else if (lock_B == false)
                {
                    lock_B = choose_team(false, x, 4, 10);
                    choose_team(true, selected_A, 10, 10);
                    if (lock_B)
                    {
                        selected_B = x;
                        x = 0;
                    }        
                }
                else
                {
                    choose_team(true, selected_A, 10, 10);
                    choose_team(false, selected_B, 10, 10);
                    if (Button.confirm_state)
                    {
                        system("cls");
                        x = 0;
                        return;
                    }
                }
                
                Main_Window.text(-14, 12, "<Press ENTER key to continue>", 7);
                Main_Window.text(-16, 13, "<Press BACKSPACE key to go back>", 7);
            }
        }
    }   
};

NormalGameMenu Normal_Game_Menu;

class NormalGame
{
    public:
        void run(int &x, int &y)
        {
            while (true)
            {
                Normal_Game_Menu.menu(x);
                Pre_Game_Menu.normalmenu(x,y);
                system("cls");
                Render_State.cord_clear();
                return;
            }
        }
};

NormalGame Normal_Game;
#endif /* NORMALGAME_H_INCLUDED */

