#ifndef MORALE_H_INCLUDED
#define MORALE_H_INCLUDED

//Create Game_Stats class which will hold game stats data. W/L ratio, team rank etc..
class Team_Morale
{

    private:
        static int ef_player;
        static int ef_opponent;
        static std::string weather;
 
    public:
//         int morale_fan()
//         {
//             //crowd effectivity
//             //weather
//             //team rank
//             //W/L ratio
            
//         }
         
           void morale_init()
           {
               /* Update "default" effectivity (raw effectivity of team without bonuses and penalties) before simulation. */
               // finish this method with weather init crowd effectivity init as well as W/L ratio
               std::vector<int> effectivity_P = Effect.get_default_effectivity(true);
               ef_player = effectivity_P[0] + effectivity_P[1] + effectivity_P[2] + effectivity_P[3];
               
               std::vector<int> effectivity_O = Effect.get_default_effectivity(false);
               ef_opponent = effectivity_O[0] + effectivity_O[1] + effectivity_O[2] + effectivity_O[3];               
           } 
           
           int morale_get_ef(bool team)
           {
               /* Return default effectivity.
                * - when true  -> ef_player (Team_A)
                * - when false -> ef_opponent (Team_B) */
                
               if (team)
                   return ef_player;
               else
                   return ef_opponent;
           }
           
           int morale(bool team)
           {
               /* Calculate and return morale as int. */ //Add description after this class will be finished
               
               int team_rating;
               
               if (team)
                   team_rating = ef_player;
               else if (team == false)
                   team_rating = ef_opponent;
                   
               //fanMorale = (capacity)/1000 * (1+adMult)*(weatherMult) + 100 * (leagueid+1) +  (score+attempts)*10
               int morale_foul = (Stats.stats_geti("stats","foul",!team) * -3) + (Stats.stats_geti("stats","yellow",team) * -8) + (Stats.stats_geti("stats","red",team) * -20); 
               int morale_injury = (Stats.stats_geti("stats","injury",team) * -5);
               int morale_score = (Stats.stats_geti("stats","goal",team) - Stats.stats_geti("stats","goal",!team))*100; 
               
               int morale = morale_foul + morale_injury + morale_score + team_rating;
               
               //Morale = (fans+TeamScore)/2 
                              
               if (morale <= team_rating * 70 / 100)
               {
                   Stats.stats_upload("penalty", "AT", team, 30);
                   Stats.stats_upload("penalty", "MI", team, 30);
                   Stats.stats_upload("penalty", "DE", team, 30);
                   Stats.stats_upload("penalty", "GK", team, 30);
               }
               else if (morale >= team_rating * 130 / 100)
               {
                   Stats.stats_upload("bonus", "AT", team, 30);
                   Stats.stats_upload("bonus", "MI", team, 30);
                   Stats.stats_upload("bonus", "DE", team, 30);
                   Stats.stats_upload("bonus", "GK", team, 30);
               }      

               return morale;
           }

};

Team_Morale Morale;

int Team_Morale::ef_player;
int Team_Morale::ef_opponent;
std::string Team_Morale::weather;

#endif /* MORALE_H_INCLUDED */