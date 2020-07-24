#ifndef MATCHSTATS_H_INCLUDED
#define MATCHSTATS_H_INCLUDED

#include "pch.h"

class Match_Stats
{
    private:
     
    static std::map<bool,std::map<std::string,int>> effectivity_penalty;
    static std::map<bool,std::map<std::string,int>> effectivity_bonus;    
    static std::map<bool,std::map<std::string,int>> effectivity_fields;
    static std::map<std::string,std::map<bool,std::vector<std::string>>> card_lib;  
    static std::map<bool,std::shared_ptr<Team>> play_team;   
    
    static std::map<bool,std::vector<int>> tactic;
    
    static std::string player_event_option_A;
    static std::string player_event_option_B;
    static std::string player_event_option_C;
    static std::string player_event_option_D;
    static std::string player_event_question;
    static std::string player_event_type;

    void modify_map(std::map<bool,std::map<std::string,int>> &passed_map, std::string key, bool team, int effectivity = 0)
    {
        /* Modify one of the following maps: event_lib, effectivity_bonus, effectivity_penalty, effectivity_fields
         * with new values */
        
        // Looping through nested maps
        std::map <bool, std::map <std::string, int> >::iterator outerit;
        std::map <std::string, int>::iterator innerit;
        
        for (outerit = passed_map.begin(); outerit != passed_map.end(); ++outerit)
        {
            if (outerit->first == team)
            { 
                for (innerit = outerit->second.begin(); innerit != outerit->second.end(); ++innerit)
                {
                    if (innerit->first == key)
                    {
                        if (effectivity == 0)
                            innerit->second++; 
                        else
                            innerit->second+= effectivity;
                        effectivity_upload = true;
                        break;
                    }   
                }
            }
        }  
    }
    
    int get_map(std::map<bool,std::map<std::string,int>> &passed_map, std::string key, bool team)
    {
        /* Get data from  one of the following maps: event_lib, effectivity_bonus, effectivity_penalty, effectivity_fields */
        
        // Looping through nested maps
        std::map <bool, std::map <std::string, int> >::iterator outerit;
        std::map <std::string, int>::iterator innerit;
        
        for (outerit = passed_map.begin(); outerit != passed_map.end(); ++outerit)
        {
            if (outerit->first == team)
            { 
                for (innerit = outerit->second.begin(); innerit != outerit->second.end(); ++innerit)
                {
                    if (innerit->first == key)
                    {
                        return innerit->second;
                    }   
                }
            }
        }  
    }   
    
    public: 
    static std::map<bool,std::map<std::string,int>> event_lib;
    static std::vector<std::string> waiting_comment;
    static bool effectivity_upload;

    void stats_setteam(bool key, std::shared_ptr<Team> playing_team)
    {
        /* Insert value to the map of playing teams. 
         * TRUE is always Team_A/PLayer
         * FALSE is always Team_B/"NPC" */
         
        play_team[key] = playing_team;
    }
  
    std::shared_ptr<Team> stats_getteam(bool key)
    {
        /* Get smart pointer pointing at the team from "play_team" map based on key */    
      
        return play_team[key];
    }  
 
    void stats_upload(std::string operation, std::string key = "none", bool team = true, int value = 0, std::vector<int> vec = {})
    {
        /* OPERATIONS:
         * upload      - Couting generated events while football match simulation is running. 
         * penalty     - Add penalty for team, positive value
         * bonus       - Add bonus for team,  positive value 
         * effectivity - Update field effectivity */  
         
        if (operation == "upload")
            modify_map(event_lib,key,team);
        else if (operation == "penalty")
            modify_map(effectivity_penalty,key,team,value);
        else if (operation == "bonus")
            modify_map(effectivity_bonus,key,team,value);
        else if (operation == "effectivity")
            modify_map(effectivity_fields,key,team,value); 
        else if (operation == "player_event_option_A")          
            player_event_option_A = key;           
        else if (operation == "player_event_option_B")
            player_event_option_B = key;
        else if (operation == "player_event_option_C")
            player_event_option_C = key;
        else if (operation == "player_event_option_D")
            player_event_option_D = key;
        else if (operation == "player_event_question")
            player_event_question = key;
        else if (operation == "player_event_type")
            player_event_type = key;
        else if (operation == "tactic")
            tactic[team] = vec;
        else if (operation == "tt")
        {
            // Looping through nested maps
            std::map <bool, std::map <std::string, int> >::iterator outerit;
            std::map <std::string, int>::iterator innerit;

            for (outerit = effectivity_fields.begin(); outerit != effectivity_fields.end(); ++outerit)
            {
                std::cout << "Team: "<<outerit->first<<std::endl;

                    for (innerit = outerit->second.begin(); innerit != outerit->second.end(); ++innerit)
                    {
                        std::cout << innerit->first << " | " << innerit->second << std::endl;
                    }
            }          
        }
     }
     
     int stats_geti(std::string operation, std::string key, bool team)
     {
        /* OPERATIONS:
         * stats       - Get event
         * penalty     - Get penalty of team
         * bonus       - Get bonus of team
         * effectivity - Get field effectivity */  

         if (operation == "stats")
             return get_map(event_lib,key,team);
         else if (operation == "penalty")
             return get_map(effectivity_penalty,key,team);
         else if (operation == "bonus")
             return get_map(effectivity_bonus,key,team);
         else if (operation == "effectivity")
             return get_map(effectivity_fields,key,team);      
     }
     std::string stats_gets(std::string var)
     {
        if (var == "player_event_option_A")          
            return player_event_option_A;           
        else if (var == "player_event_option_B")
            return player_event_option_B;
        else if (var == "player_event_option_C")
            return player_event_option_C;
        else if (var == "player_event_option_D")
            return player_event_option_D;
        else if (var == "player_event_question")
            return player_event_question;
        else if (var == "player_event_type")
            return player_event_type;
     }
     std::vector<int> stats_gettactic(bool team)
     {
         return tactic[team];
     }

     void reset()
     {
        event_lib =
        {
            { true, {{"penalty", 0},
                    {"cornerkick", 0},
                    {"offside", 0},
                    {"out", 0},
                    {"attempt", 0},
                    {"shotongoal", 0},
                    {"injury", 0},
                    {"goal", 0},
                    {"foul", 0},
                    {"yellow", 0},
                    {"red", 0}}
            },
            { false,{{"penalty", 0},
                    {"cornerkick", 0},
                    {"offside", 0},
                    {"out", 0},
                    {"attempt", 0},
                    {"shotongoal", 0},
                    {"injury", 0},
                    {"goal", 0},
                    {"foul", 0},
                    {"yellow", 0},
                    {"red", 0}}
            }
        };

        card_lib =
        {
            {"yellow",  {{true,  {} },
                        {false, {} }}
            },
            {"red",     {{true,  {} },
                        {false, {} }}
            }
        };  

        play_team = {};
        effectivity_bonus = 
        { 
            {true, {{"AT",0},
                    {"MI",0},
                    {"DE",0},
                    {"GK",0}}
            },
            {false,{{"AT",0},
                    {"MI",0},
                    {"DE",0},
                    {"GK",0}}
            }
        };

        effectivity_penalty = 
        { 
            {true, {{"AT",0},
                    {"MI",0},
                    {"DE",0},
                    {"GK",0}}
            },
            {false,{{"AT",0},
                    {"MI",0},
                    {"DE",0},
                    {"GK",0}}
            }
        };
        effectivity_fields =
        { 
            {true, {{"AT",0},
                    {"MI",0},
                    {"DE",0},
                    {"GK",0}}
            },
            {false,{{"AT",0},
                    {"MI",0},
                    {"DE",0},
                    {"GK",0}}
            }
        };
        tactic = 
        {
            {true,  {}},
            {false, {}}
        };
        waiting_comment = {};
     }
};

std::map< bool, std::map <std::string, int> > Match_Stats::event_lib =
{
    { true, {{"penalty", 0},
             {"cornerkick", 0},
             {"offside", 0},
             {"out", 0},
             {"attempt", 0},
             {"shotongoal", 0},
             {"injury", 0},
             {"goal", 0},
             {"foul", 0},
             {"yellow", 0},
             {"red", 0}}
    },
    { false,{{"penalty", 0},
             {"cornerkick", 0},
             {"offside", 0},
             {"out", 0},
             {"attempt", 0},
             {"shotongoal", 0},
             {"injury", 0},
             {"goal", 0},
             {"foul", 0},
             {"yellow", 0},
             {"red", 0}}
    }
};

std::map<std::string,std::map<bool,std::vector<std::string>>> Match_Stats::card_lib =
{
    {"yellow",  {{true,  {} },
                 {false, {} }}
    },
    {"red",     {{true,  {} },
                 {false, {} }}
    }
};  

std::map<bool,std::shared_ptr<Team>> Match_Stats::play_team;
std::map<bool,std::map<std::string,int>> Match_Stats::effectivity_bonus = 
{ 
    {true, {{"AT",0},
            {"MI",0},
            {"DE",0},
            {"GK",0}}
    },
    {false,{{"AT",0},
            {"MI",0},
            {"DE",0},
            {"GK",0}}
    }
};
std::map<bool,std::map<std::string,int>> Match_Stats::effectivity_penalty = 
{ 
    {true, {{"AT",0},
            {"MI",0},
            {"DE",0},
            {"GK",0}}
    },
    {false,{{"AT",0},
            {"MI",0},
            {"DE",0},
            {"GK",0}}
    }
};
std::map<bool,std::map<std::string,int>> Match_Stats::effectivity_fields =
{ 
    {true, {{"AT",0},
            {"MI",0},
            {"DE",0},
            {"GK",0}}
    },
    {false,{{"AT",0},
            {"MI",0},
            {"DE",0},
            {"GK",0}}
    }
};
std::map<bool,std::vector<int>> Match_Stats::tactic = 
{
    {true,  {}},
    {false, {}}
};
std::vector<std::string> Match_Stats::waiting_comment;
bool Match_Stats::effectivity_upload = false;
std::string Match_Stats::player_event_option_A;
std::string Match_Stats::player_event_option_B;
std::string Match_Stats::player_event_option_C;
std::string Match_Stats::player_event_option_D;
std::string Match_Stats::player_event_question;
std::string Match_Stats::player_event_type;

Match_Stats Stats;
 
#endif /* MATCHSTATS_H_INCLUDED */