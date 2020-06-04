#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include "pch.h"

class Simulation
{
    private:
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
        void sim_half(int time)
        {
            int minute = 0;
            bool team;
            int extended_time;
            
            if (time > 0)
                extended_time = rand() % 5;
            else
                extended_time = 0;

            while (minute != 46+extended_time)
            {                
                if (minute == 45 || minute == 90)
                    std::cout<<"Match was extended for "<<extended_time<<" minutes."<<std::endl; 
                    
                team = EVMechanics.event_player(EVMechanics.event_possesion(true),EVMechanics.event_possesion(false));
                sim_event(team);
                std::cout<<minute+time<<"min: "<<std::endl;

                for (unsigned int i = 0; i < Match_Stats::waiting_comment.size(); i++)
                {
                    std::cout<<Match_Stats::waiting_comment[i]<<std::endl;
                }
                    
                Match_Stats::waiting_comment.clear();               
                minute++;
                timer(200);
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
                PEvent.event_special();
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
        void sim()
        {
            sim_half(0);
            std::cout<<"\n"<<"HALFTIME"<<"\n"<<std::endl;
            sim_half(45);
            std::cout<<"\n"<<"END RESULTS"<<"\n"<<std::endl;
            
            // Looping through nested maps
            std::map <bool, std::map <std::string, int> >::iterator outerit;
            std::map <std::string, int>::iterator innerit;

            for (outerit = Match_Stats::event_lib.begin(); outerit != Match_Stats::event_lib.end(); ++outerit)
            {
                std::cout<<outerit->first<<std::endl;
                for (innerit = outerit->second.begin(); innerit != outerit->second.end(); ++innerit)
                {
                    std::cout<<innerit->first<<": "<<innerit->second<<" | ";
                }
                std::cout<<""<<std::endl;
            }
        }
};

Simulation Sim;

#endif /* SIMULATION_H_INCLUDED */
