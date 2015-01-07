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
#include "MFIAPInterface.h"
#include <stdio.h>
#include <vector>
#include <map>

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
    initializeStartPos();
    computeMaxMoves();
}

int MFGrid::getGridSize()
{
    return gridSize;
}

int ** MFGrid::getFullGrid()
{
    return mGameGrid;
}

int *MFGrid::getStartPos()
{
    return startPos;
}

bool MFGrid::gridCompleted(int color, int *grid[])
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

/**
 Play the move for the given color.
 **/
int MFGrid::playMove(int color)
{
    int startx = startPos[0];
    int starty = startPos[1];
    
    updateNeighbors(mGameGrid[startx][starty], color, startx, starty, mGameGrid);
    
    currMove ++;
    fprintf(stderr, "curr move = %d", currMove);
    
    if (gridCompleted(color, mGameGrid))
    {
        return RESULT_SUCCESS;
    }
    else if (currMove >= maxMoves)
    {
        return RESULT_FAILED;
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

void MFGrid::computeMaxMoves()
{
    if (level == GAME_LEVEL_EASY)
    {
        maxMoves = EASYMAXMOVES;
    }
    else
    {
        //allocate a temp grid and copy from the game grid
        mMeasureGrid = (int **)calloc(gridSize, sizeof(int *));
        for (int i = 0; i < gridSize; i++)
        {
            mMeasureGrid[i] = (int *)calloc(gridSize, sizeof(int));
        }
        for (int i = 0; i < gridSize; i++)
        {
            for (int j = 0; j < gridSize; j++)
            {
                mMeasureGrid[i][j] = mGameGrid[i][j];
            }
        }
        
        int numMoves = 0;
        srand((unsigned int)time(NULL));
        while (true)
        {
            //int randColor = rand() % GRID_NUM_COLORS + 1;
            int randColor = findMostDenseColor(mMeasureGrid);
            
            updateNeighbors(mMeasureGrid[startPos[0]][startPos[1]], randColor, startPos[0], startPos[1], mMeasureGrid);
            numMoves ++;
            
            if (gridCompleted(randColor, mMeasureGrid))
            {
                break;
            }
        }
        
        //int offset = (numMoves + 10) % 5;
        //maxMoves = (numMoves + 10) - offset;
        maxMoves = numMoves;
        
        releaseGrid(mMeasureGrid);
        mMeasureGrid = NULL;
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
            
            if (mGameGrid[startPos[0]][startPos[1]] != GRID_OBSTACLE)
                break;
        }
        
        if (mGameGrid[startPos[0]][startPos[1]] == GRID_OBSTACLE)
        {
            if (mGameGrid[0][0] != GRID_OBSTACLE)
            {
                startPos[0] = 0;
                startPos[1] = 0;
            }
            else if (mGameGrid[0][gridSize-1] != GRID_OBSTACLE)
            {
                startPos[0] = 0;
                startPos[1] = gridSize - 1;
            }
            else if (mGameGrid[gridSize-1][gridSize-1] != GRID_OBSTACLE)
            {
                startPos[0] = gridSize - 1;
                startPos[1] = gridSize - 1;
            }
            else if (mGameGrid[gridSize-1][0] != GRID_OBSTACLE)
            {
                startPos[0] = gridSize - 1;
                startPos[1] = 0;
            }
        }
        
    }
}

void MFGrid::initializeGrid()
{
    
    MFObstacle *obstacle = new MFObstacle(level);
    
    if (level == GAME_LEVEL_EASY)
    {
        hurdleType = SHAPE_NONE;
        mGameGrid = obstacle->createGrid(hurdleType, gridSize);
    }
    else if (level == GAME_LEVEL_MEDIUM)
    {
        srand(time(0));
        hurdleType = random() % NUM_MEDIUM_SHAPES + 1;

        mGameGrid = obstacle->createGrid(hurdleType, gridSize);
    }
    else if (level == GAME_LEVEL_HARD)
    {
        srand(time(0));
        
        hurdleType = selectObstacle();
        mGameGrid = obstacle->createGrid(hurdleType, gridSize);
    }
    
    int prevColor = 1;
    srand(time(0));
    
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            if (mGameGrid[i][j] != GRID_OBSTACLE)
            {
                prevColor = random() % GRID_NUM_COLORS + 1;
                mGameGrid[i][j] = prevColor;
            }
        }
    }
    
    fprintf(stderr, "initializeGridData, created grid = %p\n", mGameGrid);
}

/**
 Select a random obstacle from the list of available obstacles
 that may be free or provisioned (bought) by the user.
 **/
int MFGrid::selectObstacle()
{
    std::vector<int> *obstacles = new std::vector<int>();
    
    /**
     Add the first two hurdles (which are free) by default
     **/
    for (int i = 1; i < 1 + NUM_FREE_HURDLES; i++)
    {
        obstacles->push_back(i);
    }
    
    char **provisionedInAppProducts = getProvisionedInAppProducts();
    int num = getNumProvisionedInAppProducts();
    for (int i = 0; i < num; i++)
    {
        const char *pid = provisionedInAppProducts[i];
        int *obstacleIDs = getObstaclesInInAppProduct(pid);
        int numObstacles = getNumObstaclesInInAppProduct(pid);
        for (int j = 0; j < numObstacles; j++)
        {
            obstacles->push_back(obstacleIDs[j]);
        }
    }
    
    srand(time(0));
    int obstacleIndex = random() % obstacles->size();
    
    return (*obstacles)[obstacleIndex];
}


void MFGrid::updateNeighbors(int oldColor, int newColor, int x, int y, int *grid[])
{
    //end condition of the recursion
    if ((isObstacle(x,y, grid)) || (grid[x][y] == newColor) || (grid[x][y] != oldColor))
    {
        return;
    }
    
    //update the new color on self, and add to the incremental grid array
    grid[x][y] = newColor;
    
    updateNeighbors(oldColor, newColor, x, y-1, grid);
    updateNeighbors(oldColor, newColor, x-1, y, grid);
    updateNeighbors(oldColor, newColor, x+1, y, grid);
    updateNeighbors(oldColor, newColor, x, y+1, grid);
}

void MFGrid::checkNeighborDensity(int startColor, int x, int y, int *grid[], std::map<int, int> *map, bool *alreadyCheckedFlags[])
{
    if (isObstacle(x, y, grid) || alreadyCheckedFlags[x][y])
    {
        return;
    }
    
    alreadyCheckedFlags[x][y] = true;
    
    if (grid[x][y] != startColor)
    {
        (*map)[grid[x][y]] ++;
    }
    else
    {
        checkNeighborDensity(startColor, x, y-1, grid, map, alreadyCheckedFlags);
        checkNeighborDensity(startColor, x, y+1, grid, map, alreadyCheckedFlags);
        checkNeighborDensity(startColor, x-1, y, grid, map, alreadyCheckedFlags);
        checkNeighborDensity(startColor, x+1, y, grid, map, alreadyCheckedFlags);
    }
}

int MFGrid::findMostDenseColor(int *grid[])
{
    /*
    int **neighborDensityArray = (int **) malloc (GRID_NUM_COLORS * sizeof(int *));
    for (int i = 0; i < GRID_NUM_COLORS; i++)
    {
        neighborDensityArray[i] = (int *) malloc (2 * sizeof(int));
    }
     */
    std::map<int, int> neighborDensityMap;
    neighborDensityMap[GRID_COLOR_BLUE] = 0;
    neighborDensityMap[GRID_COLOR_CYAN] = 0;
    neighborDensityMap[GRID_COLOR_GREEN] = 0;
    neighborDensityMap[GRID_COLOR_ORANGE] = 0;
    neighborDensityMap[GRID_COLOR_RED] = 0;
    neighborDensityMap[GRID_COLOR_YELLOW] = 0;
    
    //initialize a 2-d boolean array to mark cells that have already been checked for neighbor density
    bool **alreadyCheckedFlags = (bool **) calloc (gridSize, sizeof(bool *));
    for (int i = 0; i < gridSize; i++)
    {
        alreadyCheckedFlags[i] = (bool *) calloc (gridSize, sizeof (bool));
    }
    
    int startColor = grid[startPos[0]][startPos[1]];
    checkNeighborDensity(startColor, startPos[0], startPos[1], grid, &neighborDensityMap, alreadyCheckedFlags);
    
    //Free the memroy that's no longer required
    for (int i = 0; i < gridSize; i++)
    {
        free(alreadyCheckedFlags[i]);
    }
    free(alreadyCheckedFlags);
    alreadyCheckedFlags = NULL;
    
    //now figure out the neighbor with the highest density
    int mostDenseColor = -1;
    int mostDenseColorCount = 0;
    std::map<int, int>::iterator iter = neighborDensityMap.begin();
    while (iter != neighborDensityMap.end())
    {
        int color = iter->first;
        int colorCount = iter->second;
        if (colorCount > mostDenseColorCount)
        {
            mostDenseColorCount = colorCount;
            mostDenseColor = color;
        }
        
        iter++;
    }
    
    return mostDenseColor;
}

bool MFGrid::isObstacle(int x, int y, int *grid[])
{
    if (x < 0 || y < 0)
        return true;
    if (x >= gridSize || y >= gridSize)
        return true;
    if (grid[x][y] == GRID_OBSTACLE)
        return true;
    return false;
}

void MFGrid::releaseGrid(int *grid[])
{
    if (grid != NULL)
    {
        for (int i = 0; i < gridSize; i++)
        {
            free(grid[i]);
        }
        free(grid);
    }
}

MFGrid::~MFGrid()
{
    fprintf(stderr, "~MFGrid, freeing grid = %p and startPos = %p\n", mGameGrid, startPos);

    releaseGrid(mGameGrid);
    mGameGrid = NULL;

    if (startPos != NULL)
    {
        free(startPos);
        startPos = NULL;
    }
}
