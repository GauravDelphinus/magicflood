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
    int **startPos;
    int numStartPos;
    int maxMoves;
    int currMove;
    
    void computeSize();
    void initializeStartPos();
    void computeMaxMoves();
    void initializeGrid();
    void releaseGrid(int *grid[]);
    
    bool isBoundary(int x, int y, int *grid[]); //is this cell a grid boundary? (not color and not hurdle)
    bool isFillable(int x, int y, int *grid[]); //is this cell fillable with a color? (not hurdle and within boundary)
    bool isHurdle(int x, int y, int *grid[]); //is this cell a legal hurdle? (GRID_OBSTACLE)
    bool isInside(int x, int y); //is within the bounds of the grid
    bool isValidBridgeEndpoint(int x, int y, int *grid[]); //check to see if this point is a valid end point for a bridge under construction
    bool gridCompleted(int color, int *grid[]);
    int selectObstacle();
    int playMoveInternal(int color, int *grid[]);
    void checkNeighborDensity(int startColor, int x, int y, int *grid[], std::map<int, int> *map, bool *alreadyCheckedFlags[]);
    void checkDensity(int color, int x, int y, int *grid[], int *count, bool *alreadyCheckedFlags[]);
    void checkDensity(int color, int x, int y, int *grid[], std::map<int, int> *map, bool *alreadyCheckedFlags[]);
    int checkNeighborDensityForColor(int oldColor, int newColor, int x, int y, int *grid[], bool *alreadCheckedFlags[]);
    int findMostDenseColor(int *grid[]);
    int updateNeighbors(int oldColor, int newColor, int x, int y, int *grid[], bool *alreadyCheckedFlags[]);
    int getQuadrant(int x, int y);
    void placeStarInQuadrant(int q);
    void placeStarInGrid();
    void placeStarInRect(int xmin, int xmax, int ymin, int ymax);
    bool quadrantContainsStar(int q, int x, int y);
    int getFartherQuadrant(int q);
    void shuffleArray(int array[], int size);
    bool notTooNearAnotherStar(int x, int y);
    bool findNearestHurdle(int x, int y, int *hurdleX, int *hurdleY);
    bool checkNeighboringHurdles(int x, int y, int *hurdleX, int *hurdleY, int depth);
    void smashThisHurdle(int x, int y);
    void smashNeighboringHurdles(int x, int y, int depth);
public:
    MFGrid (int level);
    int getGridSize();
    int ** getFullGrid();
    int ** getStartPos();
    int getNumStartPos();
    int addStartPos(int x, int y);
    int getMaxMoves();
    void setMaxMoves(int maxMoves);
    int getCurrMoves();
    int* playMove(int color);
    int smashHurdle(int x, int y);
    bool hasHurdles(); //has at least 1 hurdle
    int buildBridge(int startx, int starty, int endx, int endy);
    int ** checkBridgeValid(int startrow, int startcol, int endrow, int endcol);
    int isBridgeEndpointValid(int row, int col);
    bool hasSpaces();
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

#define MAX_DEPTH_TO_CHECK_FOR_HURDLES  2

#define ADJUST_MOVES_UPTO_LEVEL_A 4
#define NUM_ADJUSTED_MOVES_A 3

#define ADJUST_MOVES_UPTO_LEVEL_B 16
#define NUM_ADJUSTED_MOVES_B -1

#define ADJUST_MOVES_UPTO_LEVEL_C 27
#define NUM_ADJUSTED_MOVES_C -2

#define ADJUST_MOVES_UPTO_LEVEL_D 48
#define NUM_ADJUSTED_MOVES_D -3

#define NUM_ADJUSTED_MOVES_REMAINING    -5

#endif /* defined(__Magic_Flood__MFGrid__) */

