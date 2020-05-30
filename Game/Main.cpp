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
    
    Sim.sim();

    return 0;
}
