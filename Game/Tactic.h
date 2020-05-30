#ifndef TACTIC_H_INCLUDED
#define TACTIC_H_INCLUDED

#include "pch.h"

class Tactics
{
    /* Class tactic affects events generation as well as raise or decrease AT,MI,DE,GK effectivity. */
    private:
        std::map<std::string,std::vector<int>> tactic = 
        {
            //0:penalty_bonus, 1:cornerkick_bonus, 2:offside_bonus, 3:out_bonus, 4:attempt_bonus,
            //5:shotongoal_bonus, 6:injury_bonus, 7:foul_bonus, 8:AT, 9:MI, 10:DE, 11:GK
            {"tst"      ,{ 0 , 0 , 0 , 0  , 0 , 0 , 0 , 0 , 0  , 0   , 0 , 0   }},
            {"aggresive",{ 1 , 15 , 15 , 5  , 25 , 13 , 5 , 10 , 100  , 10   , -100 , 0   }},
            {"balanced" ,{ 0 , 7  , 2  , 5  , 7  , 3  , 0 , 0  , 20   , 20   , 20   , 40  }},
            {"defensive",{ 0 , 0  , 0  , 17 , 0  , 0  , 2 , 7  , -100 , 0    , 100  , 100 }},
            {"counter"  ,{ 1 , 5  , 5  , 5  , 10 , 15 , 2 , 10 , 80   , -100 , 10   , 10  }},
            {"possesion",{ 0 , 4  , 2  , 5  , 5  , 3  , 1 , 5  , -10  , 100  , -10  , 0   }},
            {"random"   ,{rand() % 3, rand() % 11, rand() % 11, rand() % 11, rand() % 11, rand() % 11,
                          rand() % 3, rand() % 5, rand() % 30, rand() % 30, rand() % 30, rand() % 30}}
        };
    
    public:
        std::vector<int> tactic_get(std::string key)
        {
            /* Return vector with int values which represents:
             * penalty_bonus, cornerkick_bonus, offside_bonus, out_bonus, attempt_bonus, shotongoal_bonus, injury_bonus,AT,MI,DE,GK */
             
            return tactic[key];
        }
};

Tactics Tactic;

#endif /* TACTIC_H_INCLUDED */