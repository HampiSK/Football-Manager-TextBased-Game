#ifndef BUILDER_H_INCLUDED
#define BUILDER_H_INCLUDED

#include "pch.h"

class Player
{
private:
    static int counter;

    //PLAYER BIO
    std::string bio_name;
    std::string bio_nationality;
    int bio_age;
    int bio_height;
    double bio_weight;
    int bio_number;
    std::string bio_position;

    //PLAYER SKILLS
    int skill_pace;
    int skill_shooting;
    int skill_passing;
    int skill_dribbling;
    int skill_defending;
    int skill_physical;
    int skill_reflexes;
    int skill_diving;
    int skill_handling;
    int skill_position;
    
    //PLAYER DYNAMIC
    int dynamic_suspended;
    
    std::map <std::string,int> player_idata;
    std::map <std::string,std::string> player_sdata;
    std::map <std::string,double> player_ddata; 

public:
    int Player_ID;
    Player(std::string name, std::string nationality, int age, int height,double weight, int number, std::string player_position,
           int pace, int shooting, int passing, int dribbling, int defending, int physical, int reflexes, int diving, int handling, int position,
           int suspended)
           {
                Player_ID = counter;
                counter++;
                
                bio_name = name;
                bio_nationality = nationality;
                bio_age = age;
                bio_height = height;
                bio_weight = weight;
                bio_number = number;
                bio_position = player_position;
                skill_pace = pace;
                skill_shooting = shooting;
                skill_passing = passing;
                skill_dribbling = dribbling;
                skill_defending = defending;
                skill_physical = physical;
                skill_reflexes = reflexes;
                skill_diving = diving;
                skill_handling = handling;
                skill_position = position;
                dynamic_suspended = suspended;
           }
           
     void player_data(std::string data) const
     {
         if(data == "ALL")
         {
             std::cout << 
             "PLAYER BIO"       << "\n" <<
             "Name: "           << bio_name           << "\n" <<
             "Nationality: "    << bio_nationality    << "\n" <<
             "Age: "            << bio_age            << "\n" <<
             "Height: "         << bio_height         << "\n" <<
             "Weight: "         << bio_weight         << "\n" <<
             "Number: "         << bio_number         << "\n" <<
             "Position: "       << bio_position       << "\n" <<
             "PLAYER SKILLS"    << "\n" <<
             "Pace: "           << skill_pace         << "\n" <<
             "Shooting: "       << skill_shooting     << "\n" <<
             "Passing: "        << skill_passing      << "\n" <<
             "Dribbling: "      << skill_dribbling    << "\n" <<
             "Defending: "      << skill_defending    << "\n" <<
             "Physical: "       << skill_physical     << "\n" <<
             "Reflexes: "       << skill_reflexes     << "\n" <<
             "Driving: "        << skill_diving       << "\n" <<
             "Handling: "       << skill_handling     << "\n" <<
             "Position: "       << skill_position     << "\n" <<
             "PLAYER DYNAMICS" << "\n" <<
             "Suspended: "      << dynamic_suspended << "\n" <<
             std::endl;
          }
     }
     
      std::string getplayer_s(std::string key) const
      {     
           std::map <std::string,std::string> player_data = 
           { 
               {"name",bio_name},
               {"nationality",bio_nationality},
               {"position",bio_position}
           }; 
               //std::string information = player_data[key];
               return player_data[key];
      }
      
      void setplayer_s(std::string key,std::string val)
      {     
          if (key == "name") bio_name = val;
          else if (key == "nationality") bio_nationality = val;
          else if (key == "position") bio_position = val;
      }
      
      int getplayer_i(std::string key) const
      {     
          std::map <std::string,int> player_data = 
          {
              {"age",bio_age},
              {"height",bio_height},
              {"number",bio_number},
              {"pace",skill_pace},
              {"shooting",skill_shooting},
              {"passing",skill_passing},
              {"dribbling",skill_dribbling},
              {"defending",skill_defending},
              {"physical",skill_physical},
              {"reflexes",skill_reflexes},
              {"diving",skill_diving},
              {"handling",skill_handling},
              {"position",skill_position},
              {"suspended",dynamic_suspended}
          };
              //int information = player_data[key];
              return player_data[key];
      }
      
      void setplayer_i(std::string key,int val)
      {     
          if (key == "age") bio_age = val;
          else if (key == "height") bio_height = val;
          else if (key == "number") bio_number = val;
          else if (key == "pace") skill_pace = val;
          else if (key == "shooting") skill_shooting = val;
          else if (key == "passing") skill_passing  = val;
          else if (key == "dribbling") skill_dribbling = val;
          else if (key == "defending") skill_defending = val;
          else if (key == "physical") skill_physical = val;
          else if (key == "reflexes") skill_reflexes = val;
          else if (key == "diving") skill_diving = val;
          else if (key == "handling") skill_handling = val;
          else if (key == "position") skill_position = val;
          else if (key == "suspended") dynamic_suspended = val;
      }    
      
      double getplayer_d(std::string key) const
      {
          std::map <std::string,double> player_data = 
          { 
              {"weight",bio_weight}
          };
              return player_data[key];
      }
      
      void setplayer_d(std::string key, double val)
      {
          if (key == "weight") bio_weight = val;
      }      
};

class Team
{
private:
    static int counter;
    std::string team_name;
    std::string team_league;
    std::string team_manager;
    std::vector<Player> team_field;
    std::vector<Player> team_sub;
    std::vector<Player> team_suspended;
    std::map <int,std::string> team_logo;
     
public:
    int Team_ID;
    Team(std::string name, std::string league, std::string manager, std::map <int,std::string> logo, std::vector<Player> &field, std::vector<Player> &sub, std::vector<Player> &suspended)
    {
        Team_ID = counter;
        counter++;
        
        team_name = name;
        team_league = league;
        team_manager = manager;
        team_field = field;
        team_sub = sub;
        team_suspended = suspended;
        team_logo = logo;
    }
        
    void team_pdelete(std::vector<Player> &team_passed, std::string name )
    {
        for (std::vector<Player>::iterator it = team_passed.begin(); it != team_passed.end(); ++it) 
        {
            if (it->getplayer_s("name") == name)
            {
                team_field.erase(it);   
                break;
            }
        }
    }
    
    std::string team_gets(std::string key, std::string name, std::string operation = "get")
    {    
        if (operation == "getrandom")
        {
            int counter = 0;
            int random = rand() % team_field.size();
            for (Player & player : team_field)
            {
                if (counter >= random)
                    return player.getplayer_s(key);
                counter++;
            }
        }
        else if (operation == "get")
        {
            for (Player & player : team_field)
            {
                if (player.getplayer_s("name") == name)
                    return player.getplayer_s(key);                   
            }
        }
    }
    
    int team_geti(std::string key, std::string name)
    {    
          for (Player & player : team_field)
          {
              if (player.getplayer_s("name") == name)
                  return player.getplayer_i(key);                   
          }
    }    
    
    int team_getd(std::string key, std::string name)
    {    
          for (Player & player : team_field)
          {
              if (player.getplayer_s("name") == name)
                  return player.getplayer_d(key);                   
          }
    }
    
    std::string team_bio(std::string bio) const
    {
        if (bio == "name") return team_name;
        else if (bio == "league") return team_league;
        else if (bio == "manager") return team_manager;        
    }
    
    std::map <int,std::string> team_trademark()
    {
        return team_logo;
    }
    
    std::vector<Player> team_team(std::string team) const
    {
        if (team == "field") return team_field;
        else if (team == "sub") return team_sub;
        else if (team == "suspended") return team_suspended;
    }
    
   
    void team_operation(std::string operation, std::string val1 = "none",int val2 = 0)
    {
        if (operation == "suspend")
        {
            for (Player & player : team_field)
            {
                if (player.getplayer_s("name") == val1)
                {           
                    player.setplayer_i("suspended",val2);             
                    team_suspended.push_back(player);
                    team_pdelete(team_field,val1 );
                    break;
                }
            }        
        }
    }
};

int Player::counter = 0;
int Team::counter = 0;

#endif /* BUILDER_H_INCLUDED */