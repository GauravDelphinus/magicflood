//
//  MFGlobalInterface.cpp
//  Magic Flood
//
//  Created by Anukrity Jain on 31/1/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#include "MFGlobalInterface.h"
static int totalCoins = INITIAL_COINS_ALLOCATED;

extern "C" void setCoins(int coins)
{
    totalCoins = coins;
}

extern "C" int getCoins()
{
    return totalCoins;
}

extern "C" int getNumCoinsForMoves()
{
    return COINS_TO_ADD_5_MOVES;
}

extern "C" int getNumCoinsForStar()
{
    return COINS_TO_ADD_A_STAR;
}

extern "C" int getNumCoinsForHurdleSmasher()
{
    return COINS_TO_ADD_A_HURDLE_SMASHER;
}