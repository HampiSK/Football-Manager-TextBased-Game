#ifndef COMMENTATORMODULE_H_INCLUDED
#define COMMENTATORMODULE_H_INCLUDED

#include "pch.h"

class Commentator
{
    public:
    std::string comment_get(std::string key,std::string word = "none")    
    {   
        std::map<std::string, std::vector<std::string> > comments = {
        { "GOAL_AT", { "GOOOAL!","Its been decided! The GOAL has been given counts!","GOAL! What a strike Alan." } },
        { "GOAL_NOAT", { "That's a shame, ball hits construction!","Ball hits the bar!","Who puts the bar there? It should be a goal!" } },

        { "SERIOUS_INJURY", { "It's seems like really serious injury for "+word+".","That looked horrific to me Martin. "+word+" seems to be seriously injured.","Ooh, very serious foul that is. "+word+" wont be playing any longer." } },
        { "TEMPORARY_INJURY", { word+" should be back in few minutes after his injury.","That doesn't look as bad as it seems. "+word+" will be playing soon.",word+" was injured! He will be back soon." } },
        { "LIGHT_INJURY", { word+" was lightly injured! But it doesn't look as bad as it seems.",word+" was lightly injured!","Fairly light one that is for "+word+"." } },
        
        { "PENALTY", { "Surely that's a penalty.","Penalty has been given to attacking team.","Referee announces penalty!" } },
        { "PENALTY_GOAL", { "And it's GOAL! Goalkeeper didn't stand a chance.","SCORE! Goalkeeper was in opposite side!","GOAL!!! It looked so easy to score!" } },
        { "PENALTY_DEFF", { "What a beautiful save by goalkeeper.","Goalkeeper manages with penalty easily!","Tremendous reflexes! Penalty was saved by goalkeeper." } },    

        { "CORNERKICK_AT", { "Corner was taken beuatifully.","It's a cornerkick!","Referee signals corner for attacking team." } },
        { "CORNERKICK_DEFF_PENALTY", { "Look at that! From cornerkick to penalty.","Unbelievable, it looks like a foul in the center after cornerkick.","Hold on Alan, what happend in the center? It was just a cornerkick." } },
        { "CORNERKICK_DEFF", { "It was a well defended cornerkick.","Corner has been given and ball was cleared comfortably under the pressure.","Deffenders managed a cornerkick easily." } },

        { "SHOTONGOAL_AT", { "What a shot on goal!","Beautifull strike!","Shoot was on target!" } }, 
        { "SHOTONGOAL_DEFF_CORNERKICK", { "Ball was cleared away by goalkeeper.","Goalkeeper barely defended that shot!","The goalkeeper bounced the ball." } },
        { "SHOTONGOAL_DEFF", { "Defenders were there before the shot!","Seconds after the shot, they were nearly into scoring.","Ball was cleared out of bounds." } },

        { "ATTEMPT_DEFF_PENALTY", { "That's catastrophe, did you see that slide in front of goalkeeper Martin?","What they were thinking? You cannot foul players like that in front of goalkeeper!","No way Alan! It look like a penalty for attacking team!" } },
        { "ATTEMPT_DEFF", { "This slide was on spot and prevented a shot!","Defenders prevented chance to score!","Huge shout out to defenders, another saved attempt." } },
        { "ATTEMPT_AT", { "That was worth the shot.","If he'd taken the shot a little earlier.","This attempt nearly stood a chance." } },
        { "ATTEMPT_DEFF_CORNERKICK", { "They almost got away with it, but defendeders prevented a catastrophe","Another save by defenders, but luckily it's a cornerkick for attacking team.","Ball just went off for a corner after defendeders blocked it." } }, 

        { "ATTACK_PENALTY", { "Attack was decreased "+word+".","Your effectivity of attackers was "+word+" decreased.","Attackers are "+word+" less effective." } },
        { "POSESION_PENALTY", { "Possesion was decreased "+word+".","Your effectivity of midfielders was "+word+" decreased.","Midfielders are "+word+" less effective." } },
        { "DEFENSIVE_PENALTY", { "Defensive was decreased "+word+".","Your effectivity of defenders was "+word+" decreased.","Defenders are "+word+" less effective." } },
        { "GOALKEEPER_PENALTY", { "Goalkeepers effectivity was decreased "+word+".","Your effectivity of goalkeeper was "+word+" decreased.","Goalkeeper is "+word+" less effective." } },
        { "ATTACK_BONUS", { "Attack was increased "+word+".","Your effectivity of attackers was "+word+" increased.","Attackers are "+word+" more effective." } },
        { "POSESION_BONUS", { "Possesion was increased "+word+".","Your effectivity of midfielders was "+word+" increased.","Midfielders are "+word+" more effective." } },
        { "DEFENSIVE_BONUS", { "Defensive was increased "+word+".","Your effectivity of defenders was "+word+" increased.","Defenders are "+word+" more effective." } },
        { "GOALKEEPER_BONUS", { "Goalkeepers effectivity was increased "+word+".","Your effectivity of goalkeeper was "+word+" increased.","Goalkeepers is "+word+" more effective." } },

        { "EVENT_OFFSIDE", { "And that's the offside.","Referee signals the offside.","Correct decision! That was clear offside." } },
        { "EVENT_OUT", { "Out!","And that's the out.","Ball went outside from football field. Referee signals the out." } },

        { "FOUL", { "Clear slide that was!","They are lucky as they stopped another opportunity to score by this clear slide","That's beautiful slide right from the book of slides!" } },
        { "FOUL_YELLOW", { "That's yellow card for "+word+".","Referee punished "+word+" with card. He is lucky for that yellow card I must say.","What a nasty foul. "+word+" was punished with yellow card!" } },
        { "FOUL_DOUBLE_YELLOW", { "It's a day off for "+word+" as he recieved another yellow card.",word+" should be more careful. But he wasn't and it's another yellow card.",word+" was send to the dressing room as he saw yellow card again." } },
        { "FOUL_RED", { "Terrible foul! That's red card for "+word+".","Referee punished "+word+" with red card.","Foul from the back! That's red card for "+word+"." } }
        };

        return comments.at(key)[rand() % 3]; 
    }
};

Commentator Comment;

#endif /* COMMENTATORMODULE_H_INCLUDED */
