//
//  MFGlobalInterface.h
//  Magic Flood
//
//  Created by Anukrity Jain on 31/1/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#ifndef __Magic_Flood__MFGlobalInterface__
#define __Magic_Flood__MFGlobalInterface__


/**
 * Game Constants
 */

extern "C" {
    void setCoins(int coins);
    int getCoins();
    int getNumCoinsIAPFirst();
    int getNumCoinsIAPSecond();
    int getNumCoinsIAPThird();
    int getNumCoinsIAPFourth();
    int getNumCoinsForMoves();
    int getNumCoinsForStar();
    int getNumCoinsForHurdleSmasher();
    int getNumCoinsForBridge();
    int getMinLevelToAddStars();
    int getMinLevelToAddHurdleSmasher();
    int getMinLevelToAddBridge();
    int getNumCoinsForSuccessfulGame(int currMove, int maxMoves);
}



#endif /* defined(__Magic_Flood__MFGlobalInterface__) */
