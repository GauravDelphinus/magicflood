//
//  MFGrid.cpp
//  Magic Flood
//
//  Created by Anukrity Jain on 20/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#include <time.h>
#include <stdlib.h>
#include "MFGrid.h"
#include "MFObstacle.h"
#include "MFGridInterface.h"
#include <list>

/*************************** Public Functions *****************************
 ***************************************************************************
 **************************************************************************/

MFGrid::MFGrid (int level)
{
    this->level = level;
    this->currMove = 0;
    this->startPos = NULL;
 
    //now compute all the constants for this game, based on the level
    computeSize();
    
    //now initialize the grid
    initializeGrid();
    
    //now compute the max moves and the start position (accounting for obstacles, if any)
    computeMaxMoves();
    initializeStartPos();
}

int MFGrid::getGridSize()
{
    return gridSize;
}

int ** MFGrid::getFullGrid()
{
    return grid;
}

int *MFGrid::getStartPos()
{
    return startPos;
}

bool MFGrid::isObstacle(int x, int y)
{
    if (x < 0 || y < 0)
        return true;
    if (x >= gridSize || y >= gridSize)
        return true;
    if (grid[x][y] == GRID_OBSTACLE)
        return true;
    return false;
}

void MFGrid::updateNeighbors(int oldColor, int newColor, int x, int y)
{
    //end condition of the recursion
    if ((isObstacle(x,y)) || (grid[x][y] == newColor) || (grid[x][y] != oldColor))
    {
        return;
    }
    
    //update the new color on self, and add to the incremental grid array
    grid[x][y] = newColor;
    /*int *changeArray = (int *)malloc(2 * sizeof(int));
    changeArray[0] = x;
    changeArray[1] = y;
    changeList->push_back(changeArray);
    */
    
    //updateNeighbors(oldColor, newColor, x-1, y-1, changeList);
    updateNeighbors(oldColor, newColor, x, y-1);
    //updateNeighbors(oldColor, newColor, x+1, y-1, changeList);
    updateNeighbors(oldColor, newColor, x-1, y);
    updateNeighbors(oldColor, newColor, x+1, y);
    //updateNeighbors(oldColor, newColor, x-1, y+1, changeList);
    updateNeighbors(oldColor, newColor, x, y+1);
    //updateNeighbors(oldColor, newColor, x+1, y+1, changeList);
}

bool MFGrid::gridCompleted(int color)
{
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            if (grid[i][j] != GRID_OBSTACLE && grid[i][j] != color)
            {
                return false;
                break;
            }
        }
    }
    
    return true;
}
int MFGrid::playMove(int color) //, int ***incrementalGrid)
{
    //TODO
    int startx = startPos[0];
    int starty = startPos[1];
    
//    std::list<int*> *changeList = new std::list<int*>();
    updateNeighbors(grid[startx][starty], color, startx, starty);
    
    //convert the changeList to a incremental Grid (array type)
   /*
    *incrementalGrid = (int **)malloc(changeList->size() * sizeof(int *));
    std::list<int *>::iterator iter = changeList->begin();
    int i = 0;
    while (iter != changeList->end())
    {
        (*incrementalGrid)[i] = *iter;
        i++;
        iter++;
    }
    */
    currMove ++;
    fprintf(stderr, "curr move = %d", currMove);
    if (currMove >= maxMoves)
    {
        return RESULT_FAILED;
    }
    else if (gridCompleted(color))
    {
        return RESULT_SUCCESS;
    }
    
    return RESULT_CONTINUE;
}

int MFGrid::getMaxMoves()
{
    return maxMoves;
}

int MFGrid::getCurrMoves()
{
    return currMove;
}

/*************************** Private Functions *****************************
***************************************************************************
**************************************************************************/

void MFGrid::computeSize() {
    if (level == GAME_LEVEL_EASY) {
        gridSize = EASYGRIDSIZE;
    }
    else if (level == GAME_LEVEL_MEDIUM) {
        gridSize = MEDIUMGRIDSIZE;
    }
    else {
        gridSize = HARDGRIDSIZE;
    }
}

void MFGrid::computeMaxMoves() {
    if (level == GAME_LEVEL_EASY)
    {
        maxMoves = EASYMAXMOVES;
    }
    else if (level == GAME_LEVEL_MEDIUM)
    {
        maxMoves = MEDIUMMAXMOVES;
    }
    else
    {
        maxMoves = HARDMAXMOVES;
    }
}

void MFGrid::initializeStartPos()
{
    if (startPos == NULL)
    {
        startPos = (int *)malloc(2 * sizeof(int));
    }
    
    if (level == GAME_LEVEL_EASY)
    {
        /**
         Always initialize to top-left corner
         **/
        startPos[0] = 0;
        startPos[1] = 0;
    }
    else if (level == GAME_LEVEL_MEDIUM)
    {
        /**
         Initialize randomly to one of the four corners
         **/
        srand((unsigned int)time(NULL));
        int randNum = rand() % 4 + 1;
        switch (randNum)
        {
            case 1: //top-left corner
                startPos[0] = 0;
                startPos[1] = 0;
                break;
            case 2: //top-right corner
                startPos[0] = MEDIUMGRIDSIZE - 1;
                startPos[1] = 0;
                break;
            case 3: //bottom-right corner
                startPos[0] = MEDIUMGRIDSIZE - 1;
                startPos[1] = MEDIUMGRIDSIZE - 1;
                break;
            case 4: //bottom-left corner
                startPos[0] = 0;
                startPos[1] = MEDIUMGRIDSIZE - 1;
                break;
        }
    }
    else //hard
    {
        /**
         Initialize to a RANDOM cell in the entire array.
         **/
        srand((unsigned int)time(NULL));
        int count = 2;
        while (count --)
        {
            startPos[0] = rand() % HARDGRIDSIZE;
            startPos[1] = rand() % HARDGRIDSIZE;
            
            if (grid[startPos[0]][startPos[1]] != GRID_OBSTACLE)
                break;
        }
        
        if (grid[startPos[0]][startPos[1]] == GRID_OBSTACLE)
        {
            if (grid[0][0] != GRID_OBSTACLE)
            {
                startPos[0] = 0;
                startPos[1] = 0;
            }
            else if (grid[0][gridSize-1] != GRID_OBSTACLE)
            {
                startPos[0] = 0;
                startPos[1] = gridSize - 1;
            }
            else if (grid[gridSize-1][gridSize-1] != GRID_OBSTACLE)
            {
                startPos[0] = gridSize - 1;
                startPos[1] = gridSize - 1;
            }
            else if (grid[gridSize-1][0] != GRID_OBSTACLE)
            {
                startPos[0] = gridSize - 1;
                startPos[1] = 0;
            }
        }
        
    }
}

void MFGrid::initializeGrid()
{
    
    MFObstacle *obstacle = new MFObstacle();
    
    if (level == GAME_LEVEL_EASY)
    {
        grid = obstacle->createGrid(SHAPE_NONE, gridSize);
    }
    else if (level == GAME_LEVEL_MEDIUM)
    {
        srandom(time(0));
        int shape = random() % NUM_MEDIUM_SHAPES + 1;

        fprintf(stderr, "shape = %d", shape);
        grid = obstacle->createGrid(shape, gridSize);
    }
    else if (level == GAME_LEVEL_HARD)
    {
        srandom(time(0));
        int shape = random() % NUM_HARD_SHAPES + SHAPE_HARD_A;
        
        fprintf(stderr, "shape = %d", shape);
        grid = obstacle->createGrid(shape, gridSize);
    }
    
    int prevColor = 1;
    srandom(time(0));
    
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            if (grid[i][j] != GRID_OBSTACLE)
            {
                prevColor = random() % GRID_NUM_COLORS + 1;
                grid[i][j] = prevColor;
            }
        }
    }
}

MFGrid::~MFGrid()
{
    if (grid != NULL)
    {
        for (int i = 0; i < gridSize; i++)
        {
            free(grid[i]);
        }
        free(grid);
    }
    
    if (startPos != NULL)
    {
        free(startPos);
    }
}
