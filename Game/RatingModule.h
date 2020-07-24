#ifndef RATINGMODULE_H_INCLUDED
#define RATINGMODULE_H_INCLUDED

#include "pch.h"

class Classification
{
    private:
        std::map<int,int> bonus_attacker = 
        { {0,-100},
          {1,-10 },
          {2,0   },
          {3,10  },
          {4,20  },
          {5,30  },
          {6,40  },
          {7,50  },
          {8,60  },
          {9,70  },
          {10,80 },
          {11,90 } };
        std::map<int,int> bonus_midfielder = 
        { {0,-100},
          {1,-20 },
          {2,-10 },
          {3,0   },
          {4,10  },
          {5,20  },
          {6,30  },
          {7,40  },
          {8,50  },
          {9,60  },
          {10,70 },
          {11,80 } };
        std::map<int,int> bonus_deffender = 
        { {0,-100},
          {1,-20 },
          {2,-10 },
          {3,0   },
          {4,10  },
          {5,20  },
          {6,30  },
          {7,40  },
          {8,50  },
          {9,60  },
          {10,70 },
          {11,80 } };
        std::map<int,int> bonus_goalkeeper = 
        { {0,-100},
          {1,0   } };
          
        std::vector<int> player_attacker = {25,25,25,10,5,10,0,0,0,0};
        std::vector<int> player_midfielder = {10,20,20,10,20,20,0,0,0,0};
        std::vector<int> player_deffender = {10,5,5,30,30,10,2,2,2,4};
        std::vector<int> player_goalkeeper = {2,2,2,2,2,5,25,25,20,15};

    public:        
        int rating_player(std::string field, int pace, int dribbling, int shooting, int physical, int defending, int passing, int reflexes, int diving, int handling, int position)
        {
        /* Couting player skill on passed football field */
        
            int rating = 0;
            std::vector<int> rating_stats = {pace,dribbling,shooting,physical,defending,passing,reflexes,diving,handling,position};
            std::vector<int> stats;
            int equalizer;
                        
            if (field == "AT")
            {
                stats = player_attacker;
                equalizer = 94;
            }   
            else if (field == "MI")
            {
                stats = player_midfielder;
                equalizer = 94;
            } 
            else if (field == "DE")
            {
                stats = player_deffender;
                equalizer = 90;
            } 
            else if (field == "GK")
            {
                stats = player_goalkeeper;
                equalizer = 90;
            } 
                
            for (unsigned int i = 0; i < stats.size(); i++)
            {               
                rating += rating_stats[i]*stats[i]/100;
            }
            
            return rating*100/equalizer;
        }
        
        int rating_overall(std::string field,int toal_players,int average_skill)
        {
        /* Couting overall rating of passed football field */
        
            int bonus;
            
            if (field == "AT")
            {
                bonus = bonus_attacker[toal_players];
            }   
            else if (field == "MI")
            {
                bonus = bonus_midfielder[toal_players];
            } 
            else if (field == "DE")
            {
                bonus = bonus_deffender[toal_players];
            } 
            else if (field == "GK")
            {
                bonus = bonus_goalkeeper[toal_players];
            } 
            
            if (bonus == 0)
                return average_skill;
            else
                return average_skill / 100 * bonus + average_skill;
        }
             
};

Classification Rating;

class Effectivity
{
        std::vector<int> calculate_effectivity(bool team, std::string operation)
        {
        /* Calculate field effectivity for "AT", "MI", "DE" and "GK"  
         * actual = actual effectivity of players on football field
         * default = effectivity of players on football field without bonuses and penalties 
         * normalized = effectivity of players on football field without bonuses and penalties bud effectivity is "normalized"
         *              for player on scale 0-100 */
        
            std::string field;
            int pace;
            int dribbling;
            int shooting;
            int physical;
            int defending;
            int passing;
            int reflexes;
            int diving;
            int handling;
            int position;

            int attack = 0;
            int midfield = 0;
            int defend = 0;
            int goalkeeper = 0;

            std::shared_ptr<Team> Team_Temp = Stats.stats_getteam(team);      
            std::vector<Player> field_Temp = Team_Temp->team_team("field");

            // calculate player skill on field
            for (Player & player : field_Temp)
            {      
                field = player.getplayer_s("position");
                pace = player.getplayer_i("pace");
                dribbling = player.getplayer_i("dribbling");
                shooting = player.getplayer_i("shooting");
                physical = player.getplayer_i("physical");
                defending = player.getplayer_i("defending");
                passing = player.getplayer_i("passing");
                reflexes = player.getplayer_i("reflexes");
                diving = player.getplayer_i("diving");
                handling = player.getplayer_i("handling");
                position = player.getplayer_i("position");

                if (field == "AT")
                    attack += Rating.rating_player(field,pace,dribbling,shooting,physical,defending,passing,reflexes,diving,handling,position);
                else if (field == "MI")
                    midfield += Rating.rating_player(field,pace,dribbling,shooting,physical,defending,passing,reflexes,diving,handling,position);
                else if (field == "DE")
                    defend += Rating.rating_player(field,pace,dribbling,shooting,physical,defending,passing,reflexes,diving,handling,position);
                else if (field == "GK")
                    goalkeeper += Rating.rating_player(field,pace,dribbling,shooting,physical,defending,passing,reflexes,diving,handling,position);
            }
            
            
            if (operation == "default" || operation == "normalized")
            {
                // Calculate overall field effectivity without added bonuses and penalties
                attack     = (Rating.rating_overall("AT",field_Temp.size(),attack));
                midfield   = (Rating.rating_overall("MI",field_Temp.size(),midfield));
                defend     = (Rating.rating_overall("DE",field_Temp.size(),defend));
                goalkeeper = (Rating.rating_overall("GK",field_Temp.size(),goalkeeper));  

                if (operation == "normalized")
                {
                    attack = (attack*100) / 2090; // maximum effectivity which you can get in attacking field
                    midfield = (midfield*100) / 1980; // maximum effectivity which you can get in midfield field
                    defend = (defend*100) / 1980; // maximum effectivity which you can get in defending field
                    goalkeeper = (goalkeeper*100) / 100; // maximum effectivity which you can get as a goalkeeper
                }
                return std::vector<int> {attack,midfield,defend,goalkeeper};
            }
            else if (operation == "actual")
            {
                std::vector<int> tactic = Stats.stats_gettactic(team);
                
                // Calculate overall field effectivity as well ASS add bonus and substrac penalty
                attack     = (Rating.rating_overall("AT",field_Temp.size(),attack))     + (Stats.stats_geti("bonus","AT",team)) - (Stats.stats_geti("penalty","AT",team)) + (tactic[8]);
                midfield   = (Rating.rating_overall("MI",field_Temp.size(),midfield))   + (Stats.stats_geti("bonus","MI",team)) - (Stats.stats_geti("penalty","MI",team)) + (tactic[9]);
                defend     = (Rating.rating_overall("DE",field_Temp.size(),defend))     + (Stats.stats_geti("bonus","DE",team)) - (Stats.stats_geti("penalty","DE",team)) + (tactic[10]);
                goalkeeper = (Rating.rating_overall("GK",field_Temp.size(),goalkeeper)) + (Stats.stats_geti("bonus","GK",team)) - (Stats.stats_geti("penalty","GK",team)) + (tactic[11]);
                return std::vector<int> {attack,midfield,defend,goalkeeper};
            }      
        }
    public:
        std::vector<int> get_default_effectivity(bool team, std::string operation = "default")
        {
        /* Return field effectivity of "AT", "MI", "DE" and "GK" on football field without bonuses.
         * Default effectivity is calculated withoud passing any second parameter.
         * Use "Stats.stats_setteam" before using this mehthod as it needs to be uploaded. */      
            return calculate_effectivity(team, operation);
        }
        
        void update_effectivity(bool team)
        {
        /* Update field effectivity for "AT", "MI", "DE" and "GK" on football field
         * Use "Stats.stats_setteam" before using this mehthod as it needs to be uploaded. */
            std::vector<int> effectivity = calculate_effectivity(team, "actual");

            // upload new data            
            Stats.stats_upload("effectivity","AT",team,effectivity[0]);
            Stats.stats_upload("effectivity","MI",team,effectivity[1]);
            Stats.stats_upload("effectivity","DE",team,effectivity[2]);
            Stats.stats_upload("effectivity","GK",team,effectivity[3]);
        }
};

Effectivity Effect;
#endif /* RATINGMODULE_H_INCLUDED */
