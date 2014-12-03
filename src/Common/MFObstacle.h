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

#endif /* defined(__Magic_Flood__MFObstacle__) */
