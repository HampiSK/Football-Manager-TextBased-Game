#ifndef PLAYEREVENT_H_INCLUDED
#define PLAYEREVENT_H_INCLUDED

#include "pch.h"

class Player_Event
{  
  private:  
      std::map<std::string,std::vector<std::string>> options = 
      {
        {"player_action", {"Shoot","Pass","Hold","Lets Player Decide"} },
        {"player_bonus",  {"Attack", "Midfield", "Defense", "Goalkeeper"} },
        {"player_style",  {"Play Aggresively", "Play For Posesion", "Play Defensively", "Play As Usual"} }
      };
      std::vector<std::string> event_type = {"player_action","player_bonus","player_style"};
      std::map<int,std::string> field = 
      {
          {0,"AT"},
          {1,"MI"},
          {2,"DE"},  
          {3,"GK"},
          {10,"ATTACK_PENALTY"},
          {11,"POSESION_PENALTY"},
          {12,"DEFENSIVE_PENALTY"},
          {13,"GOALKEEPER_PENALTY"},
          {20,"ATTACK_BONUS"},
          {21,"POSESION_BONUS"},
          {22,"DEFENSIVE_BONUS"},
          {23,"GOALKEEPER_BONUS"},              
      };  
      
      std::string translate_value(int value)
      {
          if (value >= 10)
              return "LIHTLY";
          else if (value >= 15)
              return "MODERATELY";
          else if (value >= 20)
              return "HIGHLY";
          else
              return "SIGNIFICANTLY"; 
      }
      
      void answer_action(std::string answer)
      {
          int bonus = rand() % 25 + 5; // 5 to 25

          if (answer == options["player_action"][0]) // "Shoot"
              Event.event_shotongoal(100,0,0,true); // higher chance to score
          else if (answer == options["player_action"][1]) // "Pass"
          {
              if (rand() % 11 <= 7)
              {
                  Stats.stats_upload("bonus", "MI", true, bonus);
                  Match_Stats::waiting_comment.push_back(Comment.comment_get("POSESION_BONUS",translate_value(bonus)));                
              }
              else
              {
                  Stats.stats_upload("penalty", "MI", true, bonus);
                  Match_Stats::waiting_comment.push_back(Comment.comment_get("POSESION_PENALTY",translate_value(bonus)));                
              }       
          }
          else if (answer == options["player_action"][2]) // "Hold"
          {
              if (rand() % 11 <= 7)
              {
                  Stats.stats_upload("bonus", "DE", true, bonus);
                  Match_Stats::waiting_comment.push_back(Comment.comment_get("DEFENSIVE_BONUS",translate_value(bonus)));               
              }
              else
              {
                  Stats.stats_upload("penalty", "DE", true, bonus);
                  Match_Stats::waiting_comment.push_back(Comment.comment_get("DEFENSIVE_BONUS",translate_value(bonus)));                 
              }      
          }  
          else if (answer == options["player_action"][3]) // "Lets Player Decide"
          {
              if (rand() % 10 <= 5)
                  Event.event_shotongoal(200,0,0,true); // highest chance to score
              else 
                  Event.event_shotongoal(200,0,0,false); 
          }
      }

      void answer_bonus(std::string answer)
      {
          int bonus = rand() % 15 + 5; // 5 to 15

          if (answer == options["player_bonus"][0]) // "Attack"
          {
              Stats.stats_upload("bonus", "AT", true, bonus); 
              Match_Stats::waiting_comment.push_back(Comment.comment_get("ATTACK_BONUS",translate_value(bonus))); 
          }
          else if (answer == options["player_bonus"][1]) // "Midfield"
          {      
              Stats.stats_upload("bonus", "MI", true, bonus);
              Match_Stats::waiting_comment.push_back(Comment.comment_get("POSESION_BONUS",translate_value(bonus)));                    
          }
          else if (answer == options["player_bonus"][2]) // "Defense"
          {      
              Stats.stats_upload("bonus", "DE", true, bonus);
              Match_Stats::waiting_comment.push_back(Comment.comment_get("DEFENSIVE_BONUS",translate_value(bonus)));                 
          }
          else if (answer == options["player_bonus"][3]) // "Goalkeeper"
          {      
              Stats.stats_upload("bonus", "GK", true, bonus); 
              Match_Stats::waiting_comment.push_back(Comment.comment_get("GOALKEEPER_BONUS",translate_value(bonus)));   
          }      
      }

      void answer_style(std::string answer, std::string player_name)
      {
          int bonus = rand() % 20 + 5; // 5 to 20
          std::shared_ptr<Team> pointer_team = Stats.stats_getteam(true);
          
          //Get player position
          std::string player_position = pointer_team->team_gets("name","none","getrandom");         

          if (answer == options["player_style"][0]) // "Play Aggresively"
          {
              if (player_position == "AT")
              {
                   Stats.stats_upload("bonus", "AT", true, bonus);
                   Match_Stats::waiting_comment.push_back(Comment.comment_get("ATTACK_BONUS",translate_value(bonus))); 
              }
              else
              {
                   Stats.stats_upload("penalty", "AT", true, bonus);
                   Match_Stats::waiting_comment.push_back(Comment.comment_get("ATTACK_PENALTY",translate_value(bonus)));            
              }
          }
          else if (answer == options["player_style"][1]) // "Play For Posesion"
          {      
                if (player_position == "MI")
                {
                    Stats.stats_upload("bonus", "MI", true, bonus);
                    Match_Stats::waiting_comment.push_back(Comment.comment_get("POSESION_BONUS",translate_value(bonus)));                    
                }
                else
                {
                    Stats.stats_upload("penalty", "MI", true, bonus);
                    Match_Stats::waiting_comment.push_back(Comment.comment_get("POSESION_PENALTY",translate_value(bonus)));                  
                }
          }
          else if (answer == options["player_style"][2]) // "Play Defensively"
          {      
                if (player_position == "DE")
                {
                    Stats.stats_upload("bonus", "DE", true, bonus);
                    Match_Stats::waiting_comment.push_back(Comment.comment_get("DEFENSIVE_BONUS",translate_value(bonus)));
                } 
                else
                {
                    Stats.stats_upload("penalty", "DE", true, bonus);
                    Match_Stats::waiting_comment.push_back(Comment.comment_get("DEFENSIVE_BONUS",translate_value(bonus)));                 
                }
          }
          else if (answer == options["player_style"][3]) // "Play As Usual"
          {      
              int random = rand() % 4;
              if (player_position == "GK")
              {
                  Stats.stats_upload("bonus", "GK", true, bonus);
                  Match_Stats::waiting_comment.push_back(Comment.comment_get("GOALKEEPER_BONUS",translate_value(bonus)));               
              }
              else if (rand() % 11 <= 7)
              {
                  Stats.stats_upload("bonus", field[random], true, bonus);
                  Match_Stats::waiting_comment.push_back(Comment.comment_get(field[random+20],translate_value(bonus)));   
              }
              else
              {
                  Stats.stats_upload("penalty", field[random], true, bonus);
                  Match_Stats::waiting_comment.push_back(Comment.comment_get(field[random+10],translate_value(bonus))); 
              }
          }
      }      
           
      void upload_question(std::string player_name)
      {
          std::string type = event_type[rand() % 3];
          std::map<std::string,std::vector<std::string>> questions = 
          {
            {"player_action", { "Your team is kicking free kick. What is their next move?",
                                player_name + " has a ball and you are screaming “JUST DO IT!“, but what do you mean by that?",
                                player_name + " has a ball what he should do?",
                                "You can see benefitial opportunity for your team. You tell " + player_name + " to:" } },
            {"player_bonus",  { "It seems that your team needs to focus more on one type of possesion? Which one should it be?",
                                "Opposition is pressuring you, which area should you focus on?",
                                "Your team is holding back, where on the field will you reinforce?",
                                "You believe that one of the positions needs a boost, which one do you want to strengthen?"} },
            {"player_style",  { player_name + " wants to play more defensively, what do you think?",
                                player_name + " wants to play more aggresive, what do you think?",
                                player_name + " is asking you what he should do.",
                                player_name + " wants to play more for posesion, what do you think? "} }
          };

          Stats.stats_upload("player_event_option_A",options[type][0]);
          Stats.stats_upload("player_event_option_B",options[type][1]);
          Stats.stats_upload("player_event_option_C",options[type][2]);
          Stats.stats_upload("player_event_option_D",options[type][3]);    
          Stats.stats_upload("player_event_question",questions[type][rand() % 4]); 
          Stats.stats_upload("player_event_type",type);      
      }
      
      void check_answer(std::string type, std::string answer, std::string player_name = "none")
      {
          if (event_type[0] == type)
              answer_action(answer);
          else if (event_type[1] == type)
              answer_bonus(answer);
          else if (event_type[2] == type)
              answer_style(answer,player_name);
      }
      
    public:      
      void event_special()
      {
          // temp
          std::string answer;
          std::shared_ptr<Team> pointer_team = Stats.stats_getteam(true);            
           // Get random name
          std::string name = pointer_team->team_gets("name","none","getrandom"); 
          upload_question(name);
          std::cout<<Stats.stats_gets("player_event_question")<<"\n"<<"A) " + Stats.stats_gets("player_event_option_A")<<"\n"<<"B) " + Stats.stats_gets("player_event_option_B")<<"\n"<<"C) " + Stats.stats_gets("player_event_option_C")<<"\n"<<"D) " + Stats.stats_gets("player_event_option_D")<<std::endl;
          std::cin >> answer;
          check_answer(Stats.stats_gets("player_event_type"),answer,name);
      }
      
};

Player_Event PEvent;

#endif /* PLAYEREVENT_H_INCLUDED */
