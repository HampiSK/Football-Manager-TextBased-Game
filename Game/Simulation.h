#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include "pch.h"

class Simulation
{
    private:
        bool running = true;

        std::queue<std::string> event_log;

        void timer(int milliseconds)
        {
           auto start = std::chrono::steady_clock::now();
           while (true)
           {
               // ADD LINE: which enables to close program
               auto end = std::chrono::steady_clock::now();

               if (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() > milliseconds)
               break;
           }
        }    
        void team_stats(bool team)
        {
            std::string name = Stats.stats_getteam(team)->team_bio("name");
            std::vector<int> text_coord;

            int column = 0;
            int row = -9;

            if (team)
                text_coord = { -2,4,-32 }; // Coordinations for Team_A
            else
                text_coord = { 2,4,15 }; // Coordinations for Team_B

            // Assign coordinations of displayed text on screen
            int menu_goal  = text_coord[0];
            int menu_team  = text_coord[1];
            int menu_stats = text_coord[2];

            if (team)
            {
                column -= name.size();
                Main_Window.text(column - menu_team, -13, name, 7);
            } 
            else  
                Main_Window.text(menu_team, -13, name, 7);

            Main_Window.text(0 , -13, ":", 7);

            // Looping through nested maps
            std::map <bool, std::map <std::string, int> >::iterator outerit;
            std::map <std::string, int>::iterator innerit;

            for (outerit = Match_Stats::event_lib.begin(); outerit != Match_Stats::event_lib.end(); ++outerit)
            {             
                if (team == outerit->first)
                {
                    for (innerit = outerit->second.begin(); innerit != outerit->second.end(); ++innerit)
                    {
                        if (innerit->first == "goal" && outerit->first == team)
                        {
                            Main_Window.text(menu_goal, -13, innerit->second, 7);
                        }
                        else
                        {
                            Main_Window.text(menu_stats , row, innerit->first, 7);
                            Main_Window.text(menu_stats  + 12, row, innerit->second, 7);
                            row++;
                        }
                    }
                }
            }            
        }
        void event_viewer(std::string text)
        {
            int line = 4;

            system("cls");
            
            team_stats(true);
            team_stats(false);

            if (event_log.size() >= 8)
            {
                event_log.pop();
                event_log.push(text);
            }
            else
                event_log.push(text);
            
            std::queue<std::string> temp_log = event_log; //copy the original queue to the temporary queue

            while (!temp_log.empty())
            {            
                std::string q_element = temp_log.front();
                Main_Window.text(-32, line, q_element, 7);
                line++;
                temp_log.pop();
            }         
        }

        void sim_half(int time)
        {
            int minute = 0;
            int speed = 200;
            bool team;
            int extended_time;           

            if (time > 0)
                extended_time = rand() % 5;
            else
                extended_time = 0;

            while (minute != 46+extended_time)
            {                
                Main_Window.WindowBuffer();
                buttons();
                       
                if (Button.backspace_state)
                {
                    system("cls");    
                    running = false;           
                    return;
                }

                if (minute == 45 || minute == 90)
                    event_viewer("Match was extended for " + std::to_string(extended_time) + " minutes.");
                    
                team = EVMechanics.event_player(EVMechanics.event_possesion(true),EVMechanics.event_possesion(false));
                sim_event(team);
                event_viewer(std::to_string(minute+time) + "min: ");

                for (unsigned int i = 0; i < Match_Stats::waiting_comment.size(); i++)
                {
                    event_viewer(Match_Stats::waiting_comment[i]);
                }
                    
                Match_Stats::waiting_comment.clear();               
                minute++;
                timer(speed);
            }                 
        }
      
        void sim_event(bool team)
        {
            std::vector<int> tactic_P = Stats.stats_gettactic(team);
            std::vector<int> tactic_O = Stats.stats_gettactic(!team);

            int AT_passed = Stats.stats_geti("effectivity","AT",team);

            int DE_opponent = Stats.stats_geti("effectivity","DE",!team);
            int GK_opponent = Stats.stats_geti("effectivity","GK",!team);

            if (rand() % 101 <= 40)
                return;
            else if (Event.event_foul(tactic_O[7],!team))
                return;
            else if (EVMechanics.event_type() && team)
            {
//                 PEvent.event_special();
                return; //ADD: player event loop
            }
            else
            {
                std::string event = EVMechanics.event_auto(tactic_P[0],tactic_P[1],tactic_P[2],tactic_P[3],tactic_P[4],tactic_P[5],tactic_P[6]);
                if (event == "penalty")
                    Event.event_penalty(AT_passed,0, GK_opponent,team);
                else if (event == "cornerkick")
                    Event.event_cornerkick(AT_passed, DE_opponent, GK_opponent,team);
                else if (event == "attempt")           
                    Event.event_attempt(AT_passed, DE_opponent, GK_opponent,team);               
                else if (event == "shotongoal")            
                    Event.event_shotongoal(AT_passed, DE_opponent, GK_opponent,team);                
                else if (event == "injury")          
                    Event.event_injury(tactic_P[6],team);                
                else if (event == "offside")
                {        
                    Stats.stats_upload("upload",event,team);
                    Match_Stats::waiting_comment.push_back(Comment.comment_get("EVENT_OFFSIDE")); 
                }           
                else if (event == "out")
                {
                    Stats.stats_upload("upload",event,team);
                    Match_Stats::waiting_comment.push_back(Comment.comment_get("EVENT_OUT")); 
                }
            }
        }
    public:     
        void reset()
        {
            Team_A.reset();     
            Team_B.reset();
            while (!event_log.empty())
            {            
                std::string q_element = event_log.front();
                event_log.pop();
            }   
        } 

        void sim()
        {
            Render_State.load = true; 
            running = true;
            int time = 0;

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

                if (time < 46)
                {
                    sim_half(time);
                    if (time == 0)
                    {
                        event_viewer(" ");
                        event_viewer("HALFTIME");
                        event_viewer(" "); 
                        time += 45;               
                    }
                    else if (time == 45)
                    {
                        event_viewer(" ");
                        event_viewer("END OF THE MATCH");
                        event_viewer(" ");  
                        time += 45; 
                    }
                }                              
            }
        }
};

Simulation Sim;

#endif /* SIMULATION_H_INCLUDED */
