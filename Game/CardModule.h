#ifndef CARDMODULE_H_INCLUDED
#define CARDMODULE_H_INCLUDED

#include "pch.h"

class Card
{

private:
    static std::map<bool,std::vector<std::string> > card_yellow;
    static std::map<bool,std::vector<std::string> > card_doubleyellow;
    static std::map<bool,std::vector<std::string> > card_red;

    std::map<bool,std::vector<std::string>> card_temp(std::string card)
    {
      /* Return specified map */
      
      if (card == "yellow")
          return card_yellow;
      else if (card == "doubleyellow")
          return card_doubleyellow;
      else if (card == "red")
          return card_red;
    }

    void card_delete(std::string card_map,  bool team, std::string name)
    {  
        /* Delete player from "original" map based on parameters */
        
        // Assign copy of card map based on attribute
        std::map<bool,std::vector<std::string>> cards = card_temp(card_map);

        // Looping through "cards" map
        for (std::pair<bool,std::vector<std::string>> element : cards) 
        {
            // Accessing KEY from element
            bool key = element.first;
            // Accessing VALUE from temp_element.
            std::vector<std::string> vec = element.second;    

            if (team == key)
            {
                //Deletion process
                auto itr = std::find(vec.begin(), vec.end(), name);
                if (itr != vec.end()) 
                    vec.erase(itr);
                //Upload map
                cards[team] = vec;
                break;
            }  
        }
        
        //Upload original map
        if (card_map == "yellow")
            card_yellow = cards;
        else if (card_map == "doubleyellow")
            card_doubleyellow = cards;
        else if (card_map == "red") 
            card_red = cards;
    }

    void card_add(std::string card_map,  bool team, std::string name)
    {   
        /* Add player to "original" map based on parameters */
        
        // Assign copy of card map based on argument
        std::map<bool,std::vector<std::string>> cards = card_temp(card_map);

        // Looping through "cards" map
        for (std::pair<bool,std::vector<std::string>> element : cards) 
        {
            // Accessing KEY from element
            bool key = element.first;
            // Accessing VALUE from temp_element.
            std::vector<std::string> vec = element.second;    

            if (team == key)
            {
                //Adding process
                vec.push_back(name);
                cards[team] = vec; 
                break;
            }  
        } 
        
        //Upload original map
        if (card_map == "yellow")
            card_yellow = cards;
        else if (card_map == "doubleyellow")
            card_doubleyellow = cards;
        else if (card_map == "red") 
            card_red = cards;
    }
    
    public: 
    
    std::map<bool,std::vector<std::string>> card_get(std::string card)
    {
        /* Returns specified map */
        return card_temp(card);
    }
    
    void card_module(std::string card,bool team,std::string name) 
    {  
        /* Card logic of card football system. When red card is shown by a refere as well as player gets
         * second yellow card,  player (name variable) is suspended for whole match and its also moved to
         * "card_doubleyellow" or "card_red" map. When player was in "card_yellow" map before, player gets
         * deleted. 
         * 
         * Comments are also uploaded from this method */
         
        if (card == "yellow")
        {
            if (card_yellow[team].size() == 0)
            {
               // Upload comment
               Match_Stats::waiting_comment.push_back(Comment.comment_get("FOUL_YELLOW",name));   
               card_add("yellow",team,name);
            }
            else
            {
                for(unsigned int i = 0; i < card_yellow[team].size(); i++ )
                {
                    if (card_yellow[team][i] == name)
                    {
                        card_add("doubleyellow",team,name);
                        card_delete("yellow",team,name);
                        
                        // Upload comment
                        Match_Stats::waiting_comment.push_back(Comment.comment_get("FOUL_DOUBLE_YELLOW",name));
                        
                        // Suspend player
                        std::shared_ptr<Team> modify_team = Stats.stats_getteam(team);
                        modify_team->team_operation("suspend",name,10000);
                        return;
                    }
                }               
                Match_Stats::waiting_comment.push_back(Comment.comment_get("FOUL_YELLOW",name));
                card_add("yellow",team,name);
            }
        }
        else
        {
            card_add("red",team,name);

            if (card_yellow[team].size() != 0)
            {
                for(unsigned int i = 0; i < card_yellow[team].size(); i++ )
                {
                    if (card_yellow[team][i] == name)
                    {             
                        // Upload comment
                        Match_Stats::waiting_comment.push_back(Comment.comment_get("FOUL_DOUBLE_YELLOW",name));
                        card_delete("yellow",team,name);
                        break;
                    }
                }
            }     
            else
            {
               // Upload comment
               Match_Stats::waiting_comment.push_back(Comment.comment_get("FOUL_RED",name));
            }
            // Suspend player
            std::shared_ptr<Team> modify_team = Stats.stats_getteam(team);
            modify_team->team_operation("suspend",name,10000);
        }
    }
};

std::map<bool,std::vector<std::string> > Card::card_yellow =
{
 {true,  {} },
 {false, {} }
};
std::map<bool,std::vector<std::string> > Card::card_doubleyellow =
{
 {true,  {} },
 {false, {} }
};
std::map<bool,std::vector<std::string> > Card::card_red =
{
 {true,  {} },
 {false, {} }
}; 

Card Cards;

#endif /* CARDMODULE_H_INCLUDED */