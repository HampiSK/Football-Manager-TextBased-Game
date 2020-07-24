#ifndef EVENTMECHANIC_H_INCLUDED
#define EVENTMECHANIC_H_INCLUDED

#include "pch.h"

class Event_Mechanics
{
    public:
        std::string event_auto(int penalty_bonus = 0, int cornerkick_bonus = 0, int offside_bonus = 0,
                               int out_bonus = 0, int attempt_bonus = 0,int shotongoal_bonus = 0,
                               int injury_bonus = 0)
        { 
            /* Events are randomized, based on simple weighing algorithm. Bonuses are set in tactic and used here. 

               List of generated events: 
               penalty
               cornerkick
               offside
               out
               attempt
               shotongoal
               injury  */

            std::map<std::string,int> events = { { "penalty", 1 + penalty_bonus },
                                                 { "cornerkick", 50 + cornerkick_bonus },
                                                 { "offside", 10 + offside_bonus},
                                                 { "out", 50 + out_bonus},
                                                 { "attempt", 160 + attempt_bonus},
                                                 { "shotongoal", 30 + shotongoal_bonus},
                                                 { "injury", 2 + injury_bonus}
                                               };

            int total = events["penalty"] + events["cornerkick"] + events["offside"] + events["out"] + events["attempt"] + events["shotongoal"] + events["injury"];
            int random_event = rand() % total; // From 0 to total-1
            int track = 0;

            for (std::pair<std::string,int> element : events) 
            {           
                std::string item = element.first; // Accessing ITEM from element      
                int weight = element.second; // Accessing WEIGHT from element

                track += weight;
                if(track > random_event)
                    return item;
            }	
        }

        bool event_type()
        {
            /* Decide if event will be randomized by event_auto method,
             or by special player event mechanics */

            int event = rand() % 101; // From 0 to 100  
            if (event <= 1) 
                return true; // event_player
            return false; // event_auto
        }
        
        int event_possesion(bool team)
        {
            // working on
            return Morale.morale_get_ef(team) + Morale.morale(team) + Stats.stats_geti("effectivity","MI",team) + rand() % 151;
        }
        
        bool event_player(int PLAYER_A_possesion, int PLAYER_B_possesion)
        {
            /* Choose PLAYER who will get an event, based on randomized number.
               Number is randomized from total possesion. */

            int total_possesion = PLAYER_A_possesion + PLAYER_B_possesion;
            int random_possesion = rand() % total_possesion;

            if (random_possesion <= PLAYER_A_possesion)
                return true; // Event for Team_A
            return false; // Event for Team_B
        }
};

Event_Mechanics EVMechanics;

#endif /* EVENTMECHANIC_H_INCLUDED */
