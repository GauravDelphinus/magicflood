//
//  MFGrid.h
//  Magic Flood
//
//  Created by Anukrity Jain on 20/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#ifndef __Magic_Flood__MFGrid__
#define __Magic_Flood__MFGrid__

class MFGrid
{
private:
    int **grid;
    int gridSize;
    int level;
    int *startPos;
    int maxMoves;
    int currMove;
    
    void computeSize();
    void initializeStartPos();
    void computeMaxMoves();
    void initializeGrid();
    
    bool isObstacle(int x, int y);
    void updateNeighbors(int oldColor, int newColor, int x, int y);
    bool gridCompleted(int color);
    int selectObstacle();
    
public:
    MFGrid (int level);
    int getGridSize();
    int ** getFullGrid();
    int * getStartPos();
    int getMaxMoves();
    int getCurrMoves();
    int playMove(int color);
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

