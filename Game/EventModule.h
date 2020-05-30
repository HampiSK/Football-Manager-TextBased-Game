#ifndef EVENTMODULE_H_INCLUDED
#define EVENTMODULE_H_INCLUDED

#include "pch.h"

class Events
{
    /* List of events: 
     * event_foul
     * event_injury
     * event_penalty
     * event_cornerkick
     * event_offside
     * event_out
     * event_attempt
     * event_shotongoal
     * event_player */
    private:
        void eventor(std::string comment = "none", std::string upload = "none", bool team = true, std::string event = "none",
                     int attackers_effectivity = 0, int deffenders_effectivity = 0, int goalkeepers_effectivity = 0, std::string name = "none")
        {
          /* This function can upload comment, stats as well as run another Event method. */

            // Upload comment
            if (comment != "none")
                Match_Stats::waiting_comment.push_back(Comment.comment_get(comment,name));            
            // Upload stats
            if (upload != "none")
                Stats.stats_upload("upload",upload,team);
            // Run event
            if(event != "none")
            {
                if(event == "shotongoal")
                    event_shotongoal(attackers_effectivity, deffenders_effectivity, goalkeepers_effectivity, team);
                else if(event == "attempt")
                    event_attempt(attackers_effectivity, deffenders_effectivity, goalkeepers_effectivity, team);
                else if(event == "cornerkick")
                    event_cornerkick(attackers_effectivity, deffenders_effectivity, goalkeepers_effectivity, team);
                else if(event == "penalty")
                    event_penalty(attackers_effectivity, deffenders_effectivity, goalkeepers_effectivity, team);                          
            }
        }
    
    public:     
        bool event_foul(int bonus_foul,bool team)
        {      
        /* When output from this method is true, it will stop event generation process 
         * Player can foul and get:
         * Yellow card
         * Red card
         * Nothing
         * Card logic is programmed in "card_module" which can suspend player and uploading comments */

            std::vector<int> val = {5 + bonus_foul, rand() % 101}; 
            std::shared_ptr<Team> pointer_team = Stats.stats_getteam(team);
            
            // Get random name
            std::string name = pointer_team->team_gets("name","none","getrandom");

            if (val[1] <= 101 * val[0] / 100)
            {
                if (val[1] <= 101 * 70 / 100)
                {
                    Stats.stats_upload("upload","foul",team);
                    return true;
                }
                else if(val[1] <= 101 * 90 / 100) 
                {
                    Stats.stats_upload("upload","foul",team);
                    Stats.stats_upload("upload","yellow",team); 
                    Cards.card_module("yellow",team,name);
                    return true;
                }
                else
                {
                    Stats.stats_upload("upload","foul",team);
                    Stats.stats_upload("upload","red",team);
                    Cards.card_module("red",team,name);
                    return true;
                }
            }
            else
                return false;
        }

        void event_injury(int injury_bonus,bool team)
        {
            /* Player can be injured while playing:
             * Serious injury = random player will be suspend for 1-10 days
             * Temporary injury = random player will be suspend for max 4 min
             * Light injury = does nothing right now */

            std::vector<int> val = {5 + injury_bonus, 15 + injury_bonus, rand() % 101};
            std::shared_ptr<Team> pointer_team = Stats.stats_getteam(team);
            std::string name;
   
            while (true)
            {
                // Get random name except goalkeeper
                name = pointer_team->team_gets("name","none","getrandom");
                if (pointer_team->team_gets("position",name) != "GK")
                    break;
            }

            if (val[2] <= 101 * val[0] / 100)
            {
                // Suspend random player (except goalkeeper) for whole match
                // Right now time is multiplied by 10000 but maybe in future 10000 will be 1 day. Max 9 days           
                pointer_team->team_operation("suspend",name,(rand() % 10 + 1) * 10000);
                eventor("SERIOUS_INJURY","injury",team,"none",0,0,0,name);
            }
            else
            {
                if (val[2] <= 101 * val[1] / 100)
                {
                    eventor("TEMPORARY_INJURY","injury",team,"none",0,0,0,name); 
                    // Suspend random player (except goalkeeper) for random time. Max 4 min
                    pointer_team->team_operation("suspend",name,rand() % 5);                
                }
                else
                {
                    eventor("LIGHT_INJURY","injury",team,"none",0,0,0,name); 
                    // ADD LINE: add some penalty for injured player NOT SURE
                }
            }
        }

        void event_penalty(int attackers_effectivity,int deffenders_effectivity, int goalkeepers_effectivity,bool team)
        {
            /* When attacking team is kicking a penalty following situations can happen:
             * Attacking team socred a goal
             * Attacking team did not socre a goal */

            std::vector<int> val = {attackers_effectivity + 500, rand() % ((attackers_effectivity + 500) + (goalkeepers_effectivity + 500) + 1)};
            eventor("PENALTY");
            
            if (val[1] <= val[0])
            {
                eventor("none","penalty",team); //  add PENALTY comment ? not sure
                eventor("PENALTY_GOAL","goal",team);
            }
            else
                eventor("PENALTY_DEFF","penalty",team);
        }

        void event_cornerkick(int attackers_effectivity,int deffenders_effectivity,int goalkeepers_effectivity,bool team)
        {
            /* During the the cornerkick event following situations can happen:
             * Ball was passed to attacking player who is shooting on goal
             * Ball was passed to attacking player who is attempting to score
             * Ball was passed to attacking player but he was fauled. Attacking team is kicking penalty
             * Cornerkick was deffended by deffender team */

            std::vector<int> val = {attackers_effectivity + 500, deffenders_effectivity + 500, rand() % ((attackers_effectivity + 500) + (deffenders_effectivity + 500) + 1)};

            if (val[2] <= val[0])
            {
                int shotongoal = val[0] * 20 / 100;
                if (val[2] <= shotongoal)
                    eventor("CORNERKICK_AT","cornerkick",team,"shotongoal",attackers_effectivity,deffenders_effectivity,goalkeepers_effectivity);
                else
                {      
                    eventor("CORNERKICK_AT","cornerkick",team);
                    eventor("ATTEMPT_AT","attempt",team);
                }
            }
            else
            {
                int penalty = val[1] * 1 / 100 + val[1];
                if (val[2] <= penalty)
                    eventor("CORNERKICK_DEFF_PENALTY","cornerkick",team,"penalty",attackers_effectivity,deffenders_effectivity,goalkeepers_effectivity);            
                else
                    eventor("CORNERKICK_DEFF","cornerkick",team);
            }
        }

        void event_shotongoal(int attackers_effectivity, int deffenders_effectivity, int goalkeepers_effectivity, bool team)
        {
            /* When football player is shooting ball on goal following situations can happen: 
             * Shot is successfull and attacking team scored the goal
             * Shot is successfull but attacking team did not score the goal
             * Ball was bounced on goalkeeper out of the field and attacking team gets cornerkick
             * Shot was caught by goalkeeper */

            std::vector<int> val = {attackers_effectivity + 500, goalkeepers_effectivity + 500, rand() % ((attackers_effectivity + 500) + (goalkeepers_effectivity + 500) + 1)};

            if (val[2] <= val[0])
            {
                int goal = val[0] * 25 / 100;
                if (val[2] <= goal)
                {
                    eventor("SHOTONGOAL_AT","shotongoal",team);
                    eventor("GOAL_AT","goal",team);
                }
                else
                {
                    eventor("SHOTONGOAL_AT","shotongoal",team);
                    eventor("GOAL_NOAT","none",team);
                }
            }
            else
            {
                int cornerkick = val[1] * 10 / 100 + val[1];
                if (val[2] <= cornerkick )
                    eventor("SHOTONGOAL_DEFF_CORNERKICK","shotongoal",team,"cornerkick",attackers_effectivity,deffenders_effectivity,goalkeepers_effectivity);
                else
                    eventor("SHOTONGOAL_DEFF","shotongoal",team);
            }
        }

        void event_attempt(int attackers_effectivity, int deffenders_effectivity, int goalkeepers_effectivity, bool team)
        {
            /* When football player is attemting to score following situations can happen: 
             * Attempt is successfull and ball is aiming on goal
             * Attempt is successfull, but ball is not aiming on goal
             * Attempt was deffended, but attacking player was fauled
             * Attempt was deffended and ball was kicked out of football field by deffender
             * Attempt was deffended  */

            std::vector<int> val = {attackers_effectivity + 500, deffenders_effectivity + 500, rand() % ((attackers_effectivity + 500) + (deffenders_effectivity + 500) + 1)};

            if(val[2] <= val[0])
            {         
                int shotongoal = val[0] * 25 / 100;
                if(val[2] <= shotongoal)
                    event_shotongoal(attackers_effectivity, deffenders_effectivity, goalkeepers_effectivity, team);
                else
                    eventor("ATTEMPT_AT","attempt",team);
            }
            else
            {
                int penalty = val[1] * 1 / 100 + val[1];
                if(val[2] <= penalty)
                    eventor("ATTEMPT_DEFF_PENALTY","attempt",team,"penalty",attackers_effectivity,deffenders_effectivity,goalkeepers_effectivity);
                else
                {
                    int cornerkick = val[1] * 10 / 100 + penalty;
                    if(val[2] <= cornerkick)   
                        eventor("ATTEMPT_DEFF_CORNERKICK","attempt",team,"cornerkick",attackers_effectivity,deffenders_effectivity,goalkeepers_effectivity);
                    else
                        eventor("ATTEMPT_DEFF","attempt",team);
                }
            }
        }
};

Events Event;

#endif /* EVENTMODULE_H_INCLUDED */