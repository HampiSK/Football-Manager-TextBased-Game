#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include "pch.h"
//     std::vector<std::string> attacking = {"LS", "CS", "CF", "RS", "LW", "RW", "ST", "LM", "RM"};
//     std::vector<std::string> midfielding = {"LAM", "CAM", "RAM", "LCM", "CM", "RCM", "LDM", "CDM", "RDM"};
//     std::vector<std::string> defending = {"LWB", "CDM", "RWB", "LB", "LCB", "CB", "RCB", "RB", "SW"};

//////////////////
/* Team Arsenal */
//////////////////

std::map <int,std::string> ArsenalLogo = 
{
    { 0,"   MNmdhhyyyyssyyyyyhhhdN    "},
    { 1,"  yyy+yyyyyyyyyhhhhhhhhh+yy  "},
    { 2," msm+ysoyyyyyyyhhhhhhhhss+ms "},
    { 3," yhd:s.`o///:o://:+:s+/:+:dh "},
    { 4," sdh/:+::.o+::-:o.s.::./:/hd "},
    { 5," oms+yyyyyyyyyyhhhhhhhhhhosm "},
    { 6," omsoyssssssoo++ossssssss+sd "},
    { 7," ydh/+oooo/+/++++/++oooooooo "},
    { 8," mym:ysss//++//////++osyy:dy "},
    { 9,"  yhsoyyy+/++o++ooo+shhhosh  "},
    {10,"   yd+so+o+/os++so+shhhyod   "},
    {11,"    yssoyyyysooosshhhhsoh    "},
    {12,"     myyoyyyyyyhhhhhhsyy     "},
    {13,"       dyssyyyyhhhhssyd      "},
    {14,"        inmhosyyhyssh        "},
    {15,"            ssshh            "}
};
std::vector<Player> ArsenalField
{
    {"P. Aubameyang","Gabon",30,187,80,14,"AT",94,85,75,80,37,69,20,20,20,20,0},
    {"A. Lacazette","France",28,175,73,9,"AT",82,85,75,86,40,74,20,20,20,20,0},
    {"B. Leno","Germany",27,190,83,1,"GK",20,20,20,20,20,20,85,83,81,84,0},
    {"Sokratis","Greek",31,180,85,5,"DE",72,51,52,60,84,83,20,20,20,20,0},
    {"M. Ozil","Germany",30,180,76,10,"MI",70,72,86,84,24,56,20,20,20,20,0},
    {"N. Pepe","Ivory Coast",24,183,73,19,"AT",91,81,75,85,33,67,20,20,20,20,0},
    {"David Luiz","Brazil",32,189,86,23,"DE",61,65,74,70,82,77,20,20,20,20,0},
    {"L. Torreira","Uruguay",23,168,64,11,"MI",75,67,77,80,81,75,20,20,20,20,0},
    {"G. Xhaka","Switzerland",26,185,82,34,"MI",51,67,81,71,69,78,20,20,20,20,0},
    {"Nacho Monreal","Spain",33,180,77,18,"DE",63,61,71,74,80,68,20,20,20,20,0},
    {"A.Maitland-Niles","England",21,177,71,15,"DE",85,59,70,76,68,67,20,20,20,20,0}
};
std::vector<Player> ArsenalSub
{
    {"Dani Ceballos","Spain",22,179,70,8,"SUB",69,67,79,84,68,68,20,20,20,20,0},
    {"H. Mkhitaryan","Armenia",30,177,75,7,"SUB",78,76,78,83,55,66,20,20,20,20,0},
    {"Hector Bellerín","Spain",24,178,74,2,"SUB",92,51,70,78,76,66,20,20,20,20,0},
    {"S. Kolašinac","Bosnia Herzegovina",26,183,85,31,"SUB",75,62,72,73,75,87,20,20,20,20,0},
    {"S. Mustafi","Germany",27,184,82,20,"SUB",60,57,63,61,77,77,20,20,20,20,0},
    {"K. Tierney","Scotland",22,178,78,3,"SUB",88,59,70,74,71,81,20,20,20,20,0},
    {"R. Holding","England",23,189,75,16,"SUB",60,34,59,64,77,73,20,20,20,20,0} 
};
std::vector<Player> ArsenalSuspended;
std::shared_ptr<Team> Arsenal = std::make_shared<Team>("Arsenal F.C", "Premier League", "Mikel Arteta", ArsenalLogo, ArsenalField, ArsenalSub, ArsenalSuspended);

////////////////////
/* Team Liverpool */
////////////////////

std::map <int,std::string> LiverpoolLogo =  
{
    { 0,"         ``.::::::.`          "},
    { 1,"   `--./|-+:-/::-/::/-./:.    "},
    { 2,"  `-.-.--::-/+/+::::----.-.   "},
    { 3,"  ++/++++/++/o+o++/++/+/++/.  "},
    { 4,"  `-o/-...-/+oo//-...-:+//`   "},
    { 5,"   -ooyo+ooosysooooooos+/-    "},
    { 6,"   .o+y++o+o/++ss+++s/so/.    "},
    { 7," ``.o:::/::::-:::--::/-+:.``  "},
    { 8," -/-+:```` `````` ````-o.+/-  "},
    { 9," ::++-+`    `:o::+:   /|+/`:  "},
    {10," +++`//|    :oos+/`  -+ ++//  "},
    {11," `+-- `+:   :+ss/.  -+. .++`  "},
    {12," ./|//+o+/`  -/+.-`:+o+/:+--  "},
    {13," ` ssoo+o++--:.:-./+o+ooso.`  "},
    {14,"  `.`. -+o/+++o/+/|o+:``.``   "},
    {15,"       ./::::---::/|-.        "} 
};

std::vector<Player> LiverpoolField
{
    {"V. van Dijk","Netherlands",27,193,92,4,"MI",77,60,70,71,90,86,20,20,20,20,0},
    {"M. Salah","Egypt",27,175,71,11,"AT",93,86,81,89,45,74,20,20,20,20,0},
    {"Alisson","Brazil",26,191,91,1,"GK",20,20,20,20,20,20,89,85,84,90,0},
    {"S. Mane","Senegal",27,175,69,10,"AT",94,83,77,89,44,74,20,20,20,20,0},
    {"Roberto Firmino","Brazil",27,181,76,9,"AT",77,82,80,87,61,78,20,20,20,20,0},
    {"Fabinho","Brazil",25,188,78,3,"DE",68,69,78,77,85,83,20,20,20,20,0},
    {"A. Robertson","Scotland",25,178,64,26,"DE",85,62,77,79,80,75,20,20,20,20,0},
    {"G. Wijnaldum","Netherlands",28,175,69,5,"MI",77,73,78,84,76,78,20,20,20,20,0},
    {"T. Alexander-Arnold","England",20,180,69,66,"DE",80,62,82,78,78,70,20,20,20,20,0},
    {"J. Henderson","England",29,182,80,14,"MI",64,70,83,77,78,80,20,20,20,20,0},
    {"J. Gomez","England",22,188,77,12,"MI",81,30,64,68,79,76,20,20,20,20,0}
};
std::vector<Player> LiverpoolSub
{
    {"N. Keita","Guinea",24,172,64,8,"SUB",71,73,76,88,65,66,20,20,20,20,0},
    {"J. Matip","Cameroon",27,194,90,32,"SUB",61,46,68,67,83,76,20,20,20,20,0},
    {"X. Shaqiri","Switzerland",27,169,72,23,"SUB",80,77,81,85,46,69,20,20,20,20,0},
    {"J. Milner","England",33,175,70,7,"SUB",61,70,82,77,77,78,20,20,20,20,0},
    {"A. Oxlade-Chamberlain","England",25,175,70,15,"SUB",82,73,78,84,66,73,20,20,20,20,0},
    {"D. Lovren","Croatia",29,188,84,6,"SUB",54,40,59,62,80,78,20,20,20,20,0},
    {"A. Lallana","England",31,178,73,20,"SUB",67,71,79,82,62,65,20,20,20,20,0}
};
std::vector<Player> LiverpoolSuspended;
std::shared_ptr<Team> Liverpool = std::make_shared<Team>("Liverpool F.C", "Premier League", "Jorgen Klopp", LiverpoolLogo, LiverpoolField, LiverpoolSub, LiverpoolSuspended);

///////////////////////
/* Manchester United */
///////////////////////

std::map <int,std::string> ManchesterLogo = 
{   
    { 0,"                             "},
    { 1,"      ::/sooysoss/::-::      "},
    { 2,"    -:+syyyhsyysyys+:::--    "},
    { 3,"  -:/:osyosossossosossso/--  "},
    { 4," :+osooooso+/////osoo++oso+: "},
    { 5," -oo+/+//+o+//////o+//o+/oo- "},
    { 6," -+so+- -::::///::::- -/++/. "},
    { 7," -++-o:  |:+o/o+:/.|  '.:+-. "},
    { 8," -+++o:  |:+o+o+:/-|  ..:--. "},
    { 9," :+++o.  |//+shyo+.|  .---:- "},
    {10,"  -/ys+-:///shyso//:-+sys:-  "},
    {11,"  .:yhhhyo++++/+o++syhhhs:.  "},
    {12,"   -+yhossoyssysyoyosyy+-.   "},
    {13,"    -/osyssyohsshsys+/-..    "},
    {14,"       ..-/++osos+o+-.       "},
    {15,"                             "},
}; 
 
std::vector<Player> ManchesterField
{
    {"De Gea","Spain",28,192,82,1,"GK",20,20,20,20,20,20,92,90,84,85,0},
    {"P. Pogba","France",26,191,84,6,"MI",74,81,86,85,66,86,20,20,20,20,0},
    {"A. Martial","France",23,184,76,9,"AT",89,81,72,86,41,71,20,20,20,20,0},
    {"M. Rashford","England",21,186,70,10,"AT",92,82,73,84,45,77,20,20,20,20,0},
    {"H. Maguire","England",26,194,100,5,"DE",50,53,64,69,81,84,20,20,20,20,0},
    {"J. Lingard","England",26,175,62,14,"MI",80,78,76,83,58,72,20,20,20,20,0},
    {"V. Lindelof","Sweden",24,187,80,2,"DE",74,50,72,72,82,78,20,20,20,20,0},
    {"L. Shaw","England",23,181,75,23,"DE",82,54,75,80,80,78,20,20,20,20,0},
    {"A. Wan-Bissaka","England",21,183,72,29,"DE",87,50,63,78,80,72,20,20,20,20,0},
    {"S. McTominay","Scotland",22,193,88,39,"MI",61,65,72,72,74,80,20,20,20,20,0},
    {"Andreas Pereira","Brazil",23,178,71,15,"AT",73,74,78,78,66,69,20,20,20,20,0},
};
std::vector<Player> ManchesterSub
{
    {"Juan Mata","Spain",31,170,63,8,"SUB",62,74,83,83,36,47,20,20,20,20,0},
    {"A. Sanchez","Chile",30,169,62,7,"SUB",81,78,77,85,44,73,20,20,20,20,0},
    {"S. Romero","Argentina",32,192,86,22,"SUB",20,20,20,20,20,20,83,79,76,79,0},
    {"C. Smalling","England",29,194,81,12,"SUB",69,47,58,58,79,81,20,20,20,20,0},
    {"Fred","Brazil",26,169,64,17,"SUB",76,73,75,80,74,69,20,20,20,20,0},
    {"A. Young","England",33,175,65,18,"SUB",70,66,74,75,73,71,20,20,20,20,0}
};
std::vector<Player> ManchesterSuspended;
std::shared_ptr<Team> Manchester = std::make_shared<Team>("Manchester United F.C.", "Premier League", "Ole Gunnar Solskjaer", ManchesterLogo, ManchesterField, ManchesterSub, ManchesterSuspended);


std::vector<std::shared_ptr<Team>> all_teams = {Arsenal,Liverpool,Manchester};

std::shared_ptr<Team> Team_A;     
std::shared_ptr<Team> Team_B;   


#endif /* DATA_H_INCLUDED */


// ///////////////////////
// /* Manchester United */
// ///////////////////////

// std::map <int,std::string> ManchesterLogo = 
// {   
//     { 0,"                             "},
//     { 1,"      ::/sooysoss/::-::      "},
//     { 2,"    -:+syyyhsyysyys+:::--    "},
//     { 3,"  -:/:osyosossossosossso/--  "},
//     { 4," :+osooooso+/////osoo++oso+: "},
//     { 5," -oo+/+//+o+//////o+//o+/oo- "},
//     { 6," -+so+- -::::///::::- -/++/. "},
//     { 7," -++-o:  |:+o/o+:/.|  '.:+-. "},
//     { 8," -+++o:  |:+o+o+:/-|  ..:--. "},
//     { 9," :+++o.  |//+shyo+.|  .---:- "},
//     {10,"  -/ys+-:///shyso//:-+sys:-  "},
//     {11,"  .:yhhhyo++++/+o++syhhhs:.  "},
//     {12,"   -+yhossoyssysyoyosyy+-.   "},
//     {13,"    -/osyssyohsshsys+/-..    "},
//     {14,"       ..-/++osos+o+-.       "},
//     {15,"                             "},
// }; 
 
// std::vector<Player> ManchesterField
// {
//     {"De Gea","Spain",28,192,82,1,"DE",99,99,99,99,99,99,99,99,99,99,0},
//     {"P. Pogba","France",26,191,84,6,"DE",99,99,99,99,99,99,99,99,99,99,0},
//     {"A. Martial","France",23,184,76,9,"DE",99,99,99,99,99,99,99,99,99,99,0},
//     {"M. Rashford","England",21,186,70,10,"DE",99,99,99,99,99,99,99,99,99,99,0},
//     {"H. Maguire","England",26,194,100,5,"DE",99,99,99,99,99,99,99,99,99,99,0},
//     {"J. Lingard","England",26,175,62,14,"DE",99,99,99,99,99,99,99,99,99,99,0},
//     {"V. Lindelof","Sweden",24,187,80,2,"DE",99,99,99,99,99,99,99,99,99,99,0},
//     {"L. Shaw","England",23,181,75,23,"DE",99,99,99,99,99,99,99,99,99,99,0},
//     {"A. Wan-Bissaka","England",21,183,72,29,"DE",99,99,99,99,99,99,99,99,99,99,0},
//     {"S. McTominay","Scotland",22,193,88,39,"DE",99,99,99,99,99,99,99,99,99,99,0},
//     {"Andreas Pereira","Brazil",23,178,71,15,"DE",99,99,99,99,99,99,99,99,99,99,0},
// };
// std::vector<Player> ManchesterSub
// {
//     {"Juan Mata","Spain",31,170,63,8,"SUB",62,74,83,83,36,47,20,20,20,20,0},
//     {"A. Sanchez","Chile",30,169,62,7,"SUB",81,78,77,85,44,73,20,20,20,20,0},
//     {"S. Romero","Argentina",32,192,86,22,"SUB",20,20,20,20,20,20,83,79,76,79,0},
//     {"C. Smalling","England",29,194,81,12,"SUB",69,47,58,58,79,81,20,20,20,20,0},
//     {"Fred","Brazil",26,169,64,17,"SUB",76,73,75,80,74,69,20,20,20,20,0},
//     {"A. Young","England",33,175,65,18,"SUB",70,66,74,75,73,71,20,20,20,20,0}
// };
// std::vector<Player> ManchesterSuspended;
// std::shared_ptr<Team> Manchester = std::make_shared<Team>("Manchester United F.C.", "Premier League", "Ole Gunnar Solskjaer", ManchesterLogo, ManchesterField, ManchesterSub, ManchesterSuspended);
