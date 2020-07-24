#ifndef PCH_H_INCLUDED
#define PCH_H_INCLUDED

/* This is PRE COMPILED HEADER with all files included.
 * To create precompiled file use command: g++ -std=c++11 pch.h
*/

#include <iostream>
#include <algorithm>
#include <chrono>
#include <memory>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <vector>
#include <map>
#include <windows.h>
#include <queue> 

#include "MainWindow.h"
#include "Button.h"

#include "Builder.h"
#include "Data.h"
#include "MatchStats.h"
#include "Tactic.h"
#include "CommentatorModule.h"
#include "CardModule.h"
#include "EventModule.h"
#include "PlayerEvent.h" 
#include "RatingModule.h"
#include "Morale.h"
#include "EventMechanic.h"
#include "Simulation.h"

#include "PreGameMenu.h"
#include "NormalGame.h"

#endif /* PCH_H_INCLUDED */
