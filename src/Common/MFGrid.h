//
//  MFGrid.h
//  Magic Flood
//
//  Created by Anukrity Jain on 20/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#ifndef __Magic_Flood__MFGrid__
#define __Magic_Flood__MFGrid__

#include <map>

class MFGrid
{
private:
    int **mGameGrid;
    int **mMeasureGrid; //not the real grid for lay, but just used for measurement of moves, etc.
    int gridSize;
    int level;
    int *startPos;
    int maxMoves;
    int currMove;
    
    void computeSize();
    void initializeStartPos();
    void computeMaxMoves();
    void initializeGrid();
    void releaseGrid(int *grid[]);
    
    bool isObstacle(int x, int y, int *grid[]);
    bool gridCompleted(int color, int *grid[]);
    int selectObstacle();
    int playMoveInternal(int color, int *grid[]);
    void checkNeighborDensity(int startColor, int x, int y, int *grid[], std::map<int, int> *map, bool *alreadyCheckedFlags[]);
    int findMostDenseColor(int *grid[]);
    
public:
    MFGrid (int level);
    int getGridSize();
    int ** getFullGrid();
    int * getStartPos();
    int getMaxMoves();
    int getCurrMoves();
    int playMove(int color);
    void updateNeighbors(int oldColor, int newColor, int x, int y, int *grid[]);
    ~MFGrid();
};

/**
 Grid Sizes, depending on Level.
 **/
#define EASYGRIDSIZE 8
#define MEDIUMGRIDSIZE 16
#define HARDGRIDSIZE 24

/**
 Maximum Moves, depending on level.
 **/
#define EASYMAXMOVES 20
#define MEDIUMMAXMOVES 50
#define HARDMAXMOVES 80

#endif /* defined(__Magic_Flood__MFGrid__) */

