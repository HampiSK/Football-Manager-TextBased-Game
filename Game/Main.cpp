#include "pch.h"


int main()
{
    srand (time(0));
    int counter = 0;
    int num = 0;
    std::vector<int> tactic;
    
    Stats.stats_setteam(true, Liverpool);
    Stats.stats_setteam(false, Arsenal);
    
    tactic = Tactic.tactic_get("tst");  
    Stats.stats_upload("tactic","none",true,0,tactic);
    Stats.stats_upload("tactic","none",false,0,tactic);
      
    Morale.morale_init();
    Effect.update_effectivity(true);
    Effect.update_effectivity(false);
    
    std::map <int,std::string> logo;
    for (unsigned int team = 0; team < all_teams.size(); team++)
    {
        std::map <int,std::string> logo;
        for (unsigned int i = 0; i < 16; i++)
        {
            logo = all_teams[team]->team_trademark();
            std::cout<<logo[i]<<std::endl;
        }
    }
//    std::cout<<EVMechanics.event_possesion(false)<<std::endl;
    //std::cin >> num;
    
    return 0;
}
