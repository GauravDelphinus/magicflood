//
//  MFObstacle.h
//  Magic Flood
//
//  Created by Anukrity Jain on 22/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#ifndef __Magic_Flood__MFObstacle__
#define __Magic_Flood__MFObstacle__

class MFObstacle
{
private:
    int mLevel; //easy, medium or hard
    int getWidth();
    int getHeight();
    bool gridHasClosedLoop(int **grid, int gridSize);
    void setObstacle(int **grid, int gridSize, int shape, bool useRandom);
    void setMediumObstacle(int **grid, int gridSize, int shape);
    void setHardObstacle(int **grid, int gridSize, int shape, bool useRandom);
    void resetGrid(int **grid, int gridSize);

public:
    MFObstacle(int level);
    int **createGrid(int shape, int gridSize);
};

/**
 Shapes
 **/
#define SHAPE_NONE 0 //no obstacle
#define SHAPE_SQUARE    1 // []
#define SHAPE_LINE_VERTICAL 2 // |
#define SHAPE_LINE_HORIZONTAL 3 // -
#define SHAPE_ELL_UPRIGHT 4 // L
#define SHAPE_ELL_RIGHT 5   //
#define SHAPE_ELL_INVERTED 6 // 7
#define SHAPE_ELL_LEFT 7
#define SHAPE_JAY_UPRIGHT 8 // J
#define SHAPE_JAY_RIGHT 9
#define SHAPE_JAY_INVERTED 10
#define SHAPE_JAY_LEFT 11
#define SHAPE_TEE_UPRIGHT 12 //T
#define SHAPE_TEE_RIGHT 13
#define SHAPE_TEE_INVERTED 14
#define SHAPE_TEE_LEFT 15
#define SHAPE_ESS_UPRIGHT 16 // S
#define SHAPE_ESS_TILTED 17
#define SHAPE_ZED_UPRIGHT 18 // Z
#define SHAPE_ZED_TILTED 19

#define NUM_MEDIUM_SHAPES 19


#define NUM_HARD_SHAPES 9

/**
 Hurdles used in Hard Game
 **/
/**
 Hurdle index or ID starts at 1.
 First two hurdles, IDs 1 and 2, are Free.
 Next 5 hurdles, Ids 3 to 7, are IAP A-la-carte hurdles.
 Next 5 hurldes, Ids 8 to 12, are part of IAP combo 1
 Next 10 hurldes, Ids 13 to 22, are part of IAP combo 2
 Next 25 hurdles, Ids 23 to 47, are part of IAP combo 3
 Next 50 hurldes, Ids 48 to 97, are part of IAP combo 4
 **/

#define NUM_FREE_HURDLES 2
#define NUM_IAP_ALACARTE_HURDLES    5
#define NUM_IAP_COMBO1_HURDLES  5
#define NUM_IAP_COMBO2_HURLDES  10
#define NUM_IAP_COMBO3_HURDLES  25
#define NUM_IAP_COMBO4_HURLDES  50

#endif /* defined(__Magic_Flood__MFObstacle__) */
