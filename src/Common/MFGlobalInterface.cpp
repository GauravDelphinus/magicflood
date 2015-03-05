//
//  MFGlobalInterface.cpp
//  Magic Flood
//
//  Created by Anukrity Jain on 31/1/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#include "MFGlobalInterface.h"
static int totalCoins = 0;

/**
 Num Coins you can buy
 **/
#define COINS_IAP_COINS_FIRST   500
#define COINS_IAP_COINS_SECOND  1000
#define COINS_IAP_COINS_THIRD   2500
#define COINS_IAP_COINS_FOURTH  5000


#define MOVES_ADD_INCREMENT 5

#define COINS_EARNED_FACTOR_ON_GAME_COMPLETION 20
#define COINS_EARNED_FACTOR_ON_EACH_MOVE 1
#define COINS_EARNED_FACTOR_ON_REMAINING_MOVES 5
#define LEVEL_INTERVAL_REQUIRING_COIN_REDEMPTION 5 //interval between levels after which you must redeem coins to move forward
#define MIN_LEVEL_TO_ADD_STARS 27
#define MIN_LEVEL_TO_ADD_HURDLE_SMASHER 48
#define MIN_LEVEL_TO_ADD_BRIDGE 81



/**
 * Redeeming Coins for Lifelines
 */
#define COINS_TO_ADD_5_MOVES 500
#define COINS_TO_ADD_A_STAR 1000
#define COINS_TO_ADD_A_HURDLE_SMASHER 1500
#define COINS_TO_ADD_A_BRIDGE   2000

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

extern "C" int getNumCoinsForBridge()
{
    return COINS_TO_ADD_A_BRIDGE;
}

extern "C" int getMinLevelToAddStars()
{
    return MIN_LEVEL_TO_ADD_STARS;
}

extern "C" int getMinLevelToAddHurdleSmasher()
{
    return MIN_LEVEL_TO_ADD_HURDLE_SMASHER;
}

extern "C" int getMinLevelToAddBridge()
{
    return MIN_LEVEL_TO_ADD_BRIDGE;
}

extern "C" int getNumCoinsIAPFirst()
{
    return COINS_IAP_COINS_FIRST;
}

extern "C" int getNumCoinsIAPSecond()
{
    return COINS_IAP_COINS_SECOND;
}

extern "C" int getNumCoinsIAPThird()
{
    return COINS_IAP_COINS_THIRD;
}

extern "C" int getNumCoinsIAPFourth()
{
    return COINS_IAP_COINS_FOURTH;
}

extern "C" int getNumCoinsForSuccessfulGame(int currMove, int maxMoves)
{
    return (COINS_EARNED_FACTOR_ON_GAME_COMPLETION + COINS_EARNED_FACTOR_ON_EACH_MOVE * currMove + COINS_EARNED_FACTOR_ON_REMAINING_MOVES * (maxMoves - currMove));
}