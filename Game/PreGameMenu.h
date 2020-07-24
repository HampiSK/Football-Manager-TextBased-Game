#ifndef PREGAMEMENU_H_INCLUDED
#define PREGAMEMENU_H_INCLUDED

#include "pch.h"

struct PreGameMenu
{
        bool running = true;
        int option_overview;
        std::string tactic_A;
        std::string tactic_B;
        int menu_main(int &x, int &y)
        {
            /* Display main menu which is menu on top of the screen as well as return choosen option as an intiger:
             * 0 = Start Match
             * 1 = Team_A
             * 2 = Team_B */
            
            const std::map <int, std::vector<std::string>> menu =
            {
                {0, {"Start Match"}                                    },
                {1, {Team_A->team_bio("name"), Team_B->team_bio("name")} }
            };      

            // Prevent segmentation fault error
            y = Main_Window.checker(y, menu.size());
            x = Main_Window.checker(x, menu.at(y).size());
            
            int row = -14; 
            int choosen_option = 0;   

            for (unsigned int level = 0; level < menu.size(); level++)
            {
                std::vector<std::string> options = menu.at(level);
                int column = 0;              
                for(unsigned int option = 0; option < options.size(); option++)
                {       
                    // Calculate console X cursor postion if:
                    if (options.size() == 2 && option == 0)
                        column -= options[option].size();
                    else if (options.size() == 1)
                        column -= options[option].size() / 2 - 1;
                    // Tracking cursor position
                    if (y == level && x == option)
                    {
                        Main_Window.text(column, row, options[option], 4); 
                        choosen_option = y + x; // "Converting" string as an intiger      
                    }
                    else
                        Main_Window.text(column, row, options[option], 7);  

                    column += options[option].size() + 2;                                        
                }               
                row++;
            }
            return choosen_option;
        }

        int menu_options(int &x, int &y)
        {
            int column = -57;            
            const std::vector<std::string> menu = {"Squad","Tactic"};
            int option = menu.size();

            x = Main_Window.checker(x, menu.size());
               
            for (unsigned int i = 0; i < menu.size(); i++)
            {
                int option_size = menu[i].size();
                if (x == i && y == 2)
                {
                    Main_Window.text(column, -11, menu[i], 12); //12
                    option = i;
                }
                else
                    Main_Window.text(column, -11, menu[i], 7);
                
                column += menu[0].size() + 3;
            }   

            return option;           
        }
        
        void menu_squad(int &y, bool team)
        {
            std::shared_ptr<Team> Team_Squad = Stats.stats_getteam(team);  
            std::vector<Player> field = Team_Squad->team_team("field");
            std::vector<Player> sub = Team_Squad->team_team("sub");
            y -= 2;
            
            y = Main_Window.checker(y, 1 + field.size() ); // + sub.size() 
            //x = Main_Window.checker(x, 1);
            int i = 1;
            Main_Window.text(-57,-9,"    PLAYERS ON FIELD    ",7);           
            Main_Window.text(-57,-9,"NUM - POS - SKILL - NAME",7); 
            for (Player & player :  field)
            { 
                std::string player_name = player.getplayer_s("name");               
                std::string player_position = player.getplayer_s("position");
                std::string player_number = std::to_string(player.getplayer_i("number"));  
                if (player_number.size() == 1)
                    player_number = player_number + " ";   
                std::string skill = std::to_string( Rating.rating_player(player.getplayer_s("position"), player.getplayer_i("pace"), 
                                                    player.getplayer_i("dribbling"), player.getplayer_i("shooting"), 
                                                    player.getplayer_i("physical"), player.getplayer_i("defending"), 
                                                    player.getplayer_i("passing"), player.getplayer_i("reflexes"), 
                                                    player.getplayer_i("diving"), player.getplayer_i("handling"), 
                                                    player.getplayer_i("position") 
                                                   ));

                std::string player_info = player_number + "  - " + player_position + "  -  " + skill + "   - " + player_name;
                if (y == i)  
                {
                    Main_Window.text(-57,-9 + i,player_info,12); 
                    menu_info(player);
                }
                else
                    Main_Window.text(-57,-9 + i,player_info,7);                  
                i++;               
            }           
          
            y += 2;
           
        }

        void menu_info(Player &player)
        {
            Main_Window.text(0,-8,"PLAYER BIO",7);
            Main_Window.text(0,-7,"Name:        " + player.getplayer_s("name"),7); 
            Main_Window.text(0,-6,"Nationality: " + player.getplayer_s("nationality"),7); 
            Main_Window.text(0,-5,"Age:         " + std::to_string(player.getplayer_i("age")),7); 
            Main_Window.text(0,-4,"Height:      " + std::to_string(player.getplayer_i("height")),7); 
            Main_Window.text(0,-3,"Weight:      " + std::to_string( player.getplayer_d("weight") * 1000.0  / 1000.0),7); 
            Main_Window.text(0,-2,"Number:      " + std::to_string(player.getplayer_i("number")),7); 
            Main_Window.text(0,-1,"Position:    " + player.getplayer_s("position"),7); 
            Main_Window.text(0,1,"PLAYER SKILLS",7);
            Main_Window.text(0,2,"Dribbling: " + std::to_string(player.getplayer_i("dribbling")),7); 
            Main_Window.text(0,3,"Shooting:  " + std::to_string(player.getplayer_i("shooting")),7); 
            Main_Window.text(0,4,"Physical:  " + std::to_string(player.getplayer_i("physical")),7); 
            Main_Window.text(0,5,"Defending: " + std::to_string(player.getplayer_i("defending")),7); 
            Main_Window.text(0,6,"Passing:   " + std::to_string(player.getplayer_i("passing")),7); 
            Main_Window.text(0,7,"Reflexes:  " + std::to_string(player.getplayer_i("reflexes")),7); 
            Main_Window.text(0,8,"Diving:    " + std::to_string(player.getplayer_i("diving")),7); 
            Main_Window.text(0,9,"Handling:  " + std::to_string(player.getplayer_i("handling")),7); 
            Main_Window.text(0,10,"Position:  " + std::to_string(player.getplayer_i("position")),7); 
        }
        void menu_tactic(int &y, bool team)
        {
            std::vector<std::string> options = { "Aggresive","Balanced","Defensive","Counter","Possesion","Random","None" };
            std::string tactic;
            y -= 2; 

            for (int i = 0; i < options.size(); i++)
            {
                if (y == i)
                {
                    Main_Window.text(-57, i-8, options[i], 12); //12
                    if (Button.confirm_state)
                    {
                        tactic = options[i];
                        if (team)
                            tactic_A = tactic;
                        else
                            tactic_B = tactic;      
                    }
                }
                else
                    Main_Window.text(-57, i-8, options[i], 7);

                if (team)
                    Main_Window.text(-57, -10, "Team tactic: "+ tactic_A, 7);
                else
                    Main_Window.text(-57, -10, "Team tactic: "+ tactic_B, 7);
                
            }   
            y += 2; 
        }
        void menu_overview(int &x, int &y, bool team)
        {
            int lock_x;
            int lock_y;           
            bool info = false;
            if (team)
                menu_main(lock_x = 0, lock_y = 1);
            else
                menu_main(lock_x = 1, lock_y = 1);

            if (y <= 2)
                option_overview = menu_options(x, y);

            if (option_overview == 0) //Squad
            {
                menu_options(lock_x = 0, lock_y = 2);         
                menu_squad(y,team);
            }
            else if (option_overview == 1) // Tactic
            {
                menu_options(lock_x = 1, lock_y = 2); 
                menu_tactic(y,team);
            }
            
            info = false;
        }

    void normalmenu(int &x, int &y)
    {
        int option_up;
        Render_State.load = true;      
        Render_State.cord_clear();
        tactic_A = "None";
        tactic_B = "None";

        while (running)
        {
            Main_Window.WindowBuffer();                
            buttons();
                       
            if (Button.backspace_state)
            {
                system("cls");   
                running = false;          
                return;
            }

            if (Button.button_state || Render_State.load)
            {                   
                system("cls");
                Render_State.load = false; 
                
                if (y <= 1)
                    option_up = menu_main(x, y);

                if (option_up == 0) // Start Match
                {
                    if (Button.confirm_state)
                    {
                        system("cls");
                        std::vector<int> tactic_bonuses_A;
                        std::vector<int> tactic_bonuses_B;

                        Stats.stats_setteam(true, Team_A);
                        Stats.stats_setteam(false, Team_B);

                        tactic_bonuses_A = Tactic.tactic_get(tactic_A);  
                        tactic_bonuses_B = Tactic.tactic_get(tactic_B); 
                        Stats.stats_upload("tactic","none",true,0,tactic_bonuses_A);
                        Stats.stats_upload("tactic","none",false,0,tactic_bonuses_B);

                        Morale.morale_init();

                        Effect.update_effectivity(true);
                        Effect.update_effectivity(false);

                        Sim.sim();
                        Sim.reset();
                        return;
                    }
                }
                else if (option_up == 1) // Team_A / true
                    menu_overview(x, y, true);
                else if (option_up == 2) // Team_B / false
                    menu_overview(x, y, false);
                             
            }    
        }   
    }
};

PreGameMenu Pre_Game_Menu;

#endif /* PREGAMEMENU_H_INCLUDED */
