//
//  MFGrid.cpp
//  Magic Flood
//
//  Created by Anukrity Jain on 20/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "MFGrid.h"
#include "MFObstacle.h"
#include "MFGridInterface.h"
#include "MFIAPInterface.h"
#include "MFGlobalInterface.h"
#include <stdio.h>
#include <vector>
#include <map>
#include "MFNativeLog.h"

extern const char *sGridData[];

/*************************** Public Functions *****************************
 ***************************************************************************
 **************************************************************************/

MFGrid::MFGrid (int level)
{
    this->level = level;
    this->currMove = 0;
    this->startPos = NULL;
    
    initializeGrid();
    
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

int **MFGrid::getStartPos()
{
    return startPos;
}

int MFGrid::getNumStartPos()
{
    return numStartPos;
}

int MFGrid::addStartPos(int x, int y)
{
    if (mGameGrid[x][y] == GRID_OBSTACLE)
    {
        return 0; //invalid selection
    }
    
    int selectedX = x;
    int selectedY = y;
    
    int newNumStartPos = numStartPos + 1;
    int **newStartPosArray = (int **) malloc (newNumStartPos * sizeof(int *));
    for (int i = 0; i < newNumStartPos; i++)
    {
        newStartPosArray[i] = (int *) malloc (2 * sizeof(int));
    }
    
    for (int i = 0; i < numStartPos; i++)
    {
        newStartPosArray[i][0] = startPos[i][0];
        newStartPosArray[i][1] = startPos[i][1];
        
        free(startPos[i]);
    }
    free(startPos);
    startPos = NULL;
    
    newStartPosArray[numStartPos][0] = selectedX;
    newStartPosArray[numStartPos][1] = selectedY;
    
    startPos = newStartPosArray;
    numStartPos = newNumStartPos;
    
    return 1;
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
int* MFGrid::playMove(int color)
{
    int *retVal = (int *) malloc (2 * sizeof(int));
    
    //initialize a 2-d boolean array to mark cells that have already been checked for neighbor density
    bool **alreadyCheckedFlags = (bool **) calloc (gridSize, sizeof(bool *));
    for (int i = 0; i < gridSize; i++)
    {
        alreadyCheckedFlags[i] = (bool *) calloc (gridSize, sizeof (bool));
    }
    
    int numUpdated = 0;
    for (int k = 0; k < numStartPos; k++)
    {
        int startx = startPos[k][0];
        int starty = startPos[k][1];
        
        numUpdated += checkNeighborDensityForColor(mGameGrid[startx][starty], color, startx, starty, mGameGrid, alreadyCheckedFlags);
    }
    
    for (int k = 0; k < numStartPos; k++)
    {
        int startx = startPos[k][0];
        int starty = startPos[k][1];
        
        for (int i = 0; i < gridSize; i++)
        {
            for (int j = 0; j < gridSize; j++)
            {
                alreadyCheckedFlags[i][j] = false;
            }
        }
        
        updateNeighbors(mGameGrid[startx][starty], color, startx, starty, mGameGrid, alreadyCheckedFlags);
    }
    
    //Free the memroy that's no longer required
    for (int i = 0; i < gridSize; i++)
    {
        free(alreadyCheckedFlags[i]);
    }
    free(alreadyCheckedFlags);
    alreadyCheckedFlags = NULL;
    
    currMove ++;
    fprintf(stderr, "curr move = %d", currMove);
    
    if (gridCompleted(color, mGameGrid))
    {
        retVal[0] = RESULT_SUCCESS;
        retVal[1] = numUpdated;
        int currCoins = getCoins();
        currCoins += currMove + (maxMoves-currMove)*COINS_EARNED_FACTOR_ON_REMAINING_MOVES;
       // setCoins(currCoins);
    }
    else if (currMove >= maxMoves)
    {
        retVal[0] = RESULT_FAILED;
        retVal[1] = numUpdated;
    }
    else
    {
        retVal[0] = RESULT_CONTINUE;
        retVal[1] = numUpdated;
    }
    
    return retVal;
}

int MFGrid::getMaxMoves()
{
    return maxMoves;
}

void MFGrid::setMaxMoves(int newMaxMoves)
{
    maxMoves = newMaxMoves;
}

int MFGrid::getCurrMoves()
{
    return currMove;
}

/*************************** Private Functions *****************************
***************************************************************************
**************************************************************************/

void MFGrid::shuffleArray(int array[], int size)
{
    srand((unsigned int)time(NULL));
    
        //int randColor = rand() % GRID_NUM_COLORS + 1;

    for (int i = 0; i < size; i++)
    {
        int randIndex = rand() % size;
        int temp = array[i];
        array[i] = array[randIndex];
        array[randIndex] = temp;
    }
}

void MFGrid::initializeGrid()
{
    char *inputStr = strdup(sGridData[level - 1]);
        char *token = strtok(inputStr, "#");
    
    if (token)
    {
        //move on to skip the level #
        token = strtok(NULL, "#");
        
        numStartPos = atoi(token);
        startPos = (int **) malloc (numStartPos * sizeof(int *));
        for (int i = 0; i < numStartPos; i++)
        {
            startPos[i] = (int *) malloc (2 * sizeof(int));

            token = strtok(NULL, "#");
            if (!token)
                return;
            startPos[i][0] = atoi(token);
            token = strtok(NULL, "#");
            if (!token)
                return;
            startPos[i][1] = atoi(token);
        }
        
        token = strtok(NULL, "#");
        
        if (token)
        {
            gridSize = atoi(token);
            
            token = strtok(NULL, "#");
            if (token)
            {
                int k = 0; //index into the value
                //allocate the grid
                mGameGrid = (int **)calloc(gridSize, sizeof(int *));
                
                for (int i = 0; i < gridSize; i++)
                {
                    mGameGrid[i] = (int *)calloc(gridSize, sizeof(int));
                    for (int j = 0; j < gridSize; j++)
                    {
                        if (token[k] == '^')
                        {
                            mGameGrid[i][j] = token[k];
                        }
                        else
                        {
                            mGameGrid[i][j] = token[k] - '0';
                        }
                        k++;
                    }
                }
                
            }
        }
    }
    
    free(inputStr);
}

void MFGrid::computeMaxMoves()
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
        
        for (int k = 0; k < numStartPos; k++)
        {
            int startx = startPos[k][0];
            int starty = startPos[k][1];
            updateNeighbors(mMeasureGrid[startx][starty], randColor, startx, starty, mMeasureGrid, NULL);
        }
        numMoves ++;
        
        if (gridCompleted(randColor, mMeasureGrid))
        {
            break;
        }
    }
    
    maxMoves = numMoves;
    if (level <= GRACE_MOVES_TILL_LEVEL)
    {
        maxMoves += NUM_GRACE_MOVES;
    }
    else if (level >= REDUCE_MOVES_FROM_LEVEL)
    {
        maxMoves -= NUM_REDUCED_MOVES;
    }
    
    releaseGrid(mMeasureGrid);
    mMeasureGrid = NULL;
}

/**
 Recursively update all neighbors of the current cell with the color.
 Returns the total number of cells that were updated.
 **/
int MFGrid::updateNeighbors(int oldColor, int newColor, int x, int y, int *grid[], bool *alreadyCheckedFlags[])
{
    int numUpdated = 0;
    
    if (isObstacle(x, y, grid))
    {
        return 0;
    }
    
    if (grid[x][y] == newColor)
    {
        checkDensity(newColor, x, y, grid, &numUpdated, alreadyCheckedFlags);
        return numUpdated;
    }
    
    //end condition of the recursion
    if (grid[x][y] != oldColor)
    {
        return 0;
    }
    
    //update the new color on self, and add to the incremental grid array
    grid[x][y] = newColor;
    
    numUpdated += updateNeighbors(oldColor, newColor, x, y-1, grid, alreadyCheckedFlags);
    numUpdated += updateNeighbors(oldColor, newColor, x-1, y, grid, alreadyCheckedFlags);
    numUpdated += updateNeighbors(oldColor, newColor, x+1, y, grid, alreadyCheckedFlags);
    numUpdated += updateNeighbors(oldColor, newColor, x, y+1, grid, alreadyCheckedFlags);
    
    return numUpdated;
}

/**
 Calculate the number of NEW cells that will be updated if we drop the newColor
 in the grid at the position x, y.
 **/
int MFGrid::checkNeighborDensityForColor(int oldColor, int newColor, int x, int y, int *grid[], bool *alreadyCheckedFlags[])
{
    int numUpdated = 0;
    
    if (isObstacle(x, y, grid) || alreadyCheckedFlags[x][y])
    {
        return 0;
    }
    
    if (grid[x][y] == newColor)
    {
        checkDensity(newColor, x, y, grid, &numUpdated, alreadyCheckedFlags);
        return numUpdated;
    }
    
    //end condition of the recursion
    if (grid[x][y] != oldColor)
    {
        return 0;
    }
    
    alreadyCheckedFlags[x][y] = true;
    
    numUpdated += checkNeighborDensityForColor(oldColor, newColor, x, y-1, grid, alreadyCheckedFlags);
    numUpdated += checkNeighborDensityForColor(oldColor, newColor, x-1, y, grid, alreadyCheckedFlags);
    numUpdated += checkNeighborDensityForColor(oldColor, newColor, x+1, y, grid, alreadyCheckedFlags);
    numUpdated += checkNeighborDensityForColor(oldColor, newColor, x, y+1, grid, alreadyCheckedFlags);
    
    return numUpdated;
}

/**
 Check the density of the given color starting at the position x, y.
 **/
void MFGrid::checkDensity(int color, int x, int y, int *grid[], int *count, bool *alreadyCheckedFlags[])
{
    if (isObstacle(x, y, grid) || grid[x][y] != color || alreadyCheckedFlags == NULL
        || alreadyCheckedFlags[x][y])
    {
        return;
    }
    
    alreadyCheckedFlags[x][y] = true;
    (*count) ++;
    
    checkDensity(color, x, y-1, grid, count, alreadyCheckedFlags);
    checkDensity(color, x, y+1, grid, count, alreadyCheckedFlags);
    checkDensity(color, x-1, y, grid, count, alreadyCheckedFlags);
    checkDensity(color, x+1, y, grid, count, alreadyCheckedFlags);
}

void MFGrid::checkNeighborDensity(int startColor, int x, int y, int *grid[], std::map<int, int> *map, bool *alreadyCheckedFlags[])
{
    if (isObstacle(x, y, grid) || alreadyCheckedFlags[x][y])
    {
        return;
    }
    
    if (grid[x][y] != startColor)
    {
        int count = 0;
        checkDensity(grid[x][y], x, y, grid, &count, alreadyCheckedFlags);
        (*map)[grid[x][y]] += count;
        return;
    }
    
    alreadyCheckedFlags[x][y] = true;

    checkNeighborDensity(startColor, x, y-1, grid, map, alreadyCheckedFlags);
    checkNeighborDensity(startColor, x, y+1, grid, map, alreadyCheckedFlags);
    checkNeighborDensity(startColor, x-1, y, grid, map, alreadyCheckedFlags);
    checkNeighborDensity(startColor, x+1, y, grid, map, alreadyCheckedFlags);
}

int MFGrid::findMostDenseColor(int *grid[])
{
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
    
    for (int k = 0; k < numStartPos; k++)
    {
        int startx = startPos[k][0];
        int starty = startPos[k][1];
        int startColor = grid[startx][starty];
        for (int i = 0; i < gridSize; i++)
        {
            for (int j = 0; j < gridSize; j++)
            {
                alreadyCheckedFlags[i][j] = false;
            }
        }
        checkNeighborDensity(startColor, startx, starty, grid, &neighborDensityMap, alreadyCheckedFlags);
    }
    
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
    releaseGrid(mGameGrid);
    mGameGrid = NULL;

    if (startPos != NULL)
    {
        free(startPos);
        startPos = NULL;
    }
}

void MFGrid::smashNeighboringHurdles(int x, int y, int depth)
{
    depth ++;
    
    if (depth > MAX_DEPTH_TO_CHECK_FOR_HURDLES)
    {
        return;
    }
    
    if (x < 0 || y < 0 || x >= gridSize || y >= gridSize)
    {
        //reached a boundary.
        return;
    }
    
    if (mGameGrid[x][y] != GRID_OBSTACLE)
    {
        return; //end as soon as you are no longer in the obstacle
    }
    
    //smash this cell by setting to a non-obstacle random color
    int randColor = rand() % GRID_NUM_COLORS + 1;
    mGameGrid[x][y] = randColor;
    
    smashNeighboringHurdles(x, y+1, depth);
    smashNeighboringHurdles(x, y-1, depth);
    smashNeighboringHurdles(x+1, y, depth);
    smashNeighboringHurdles(x-1, y, depth);
}

void MFGrid::smashThisHurdle(int x, int y)
{
    srand((unsigned int)time(NULL));
    
    smashNeighboringHurdles(x, y, 0);
}

bool MFGrid::checkNeighboringHurdles(int x, int y, int *hurdleX, int *hurdleY, int depth)
{
    depth ++;
    
    if (depth > MAX_DEPTH_TO_CHECK_FOR_HURDLES)
    {
        return false;
    }
    
    if (x < 0 || y < 0 || x >= gridSize || y >= gridSize)
    {
        //reached a boundary.
        return false;
    }
    
    if (mGameGrid[x][y] == GRID_OBSTACLE)
    {
        *hurdleX = x;
        *hurdleY = y;
        return true;
    }
    
    int found = false;
    
    found = checkNeighboringHurdles(x, y-1, hurdleX, hurdleY, depth);
    if (found)
        return found;
    
    found = checkNeighboringHurdles(x, y+1, hurdleX, hurdleY, depth);
    if (found)
        return found;
    
    found = checkNeighboringHurdles(x-1, y, hurdleX, hurdleY, depth);
    if (found)
        return found;
    
    found = checkNeighboringHurdles(x+1, y, hurdleX, hurdleY, depth);
    if (found)
        return found;
    
    return false;
}

bool MFGrid::findNearestHurdle(int x, int y, int *hurdleX, int *hurdleY)
{
    bool found = checkNeighboringHurdles(x, y, hurdleX, hurdleY, 0);
    
    return found;
}

int MFGrid::smashHurdle(int x, int y)
{
    int hurdleX, hurdleY;
    bool found = findNearestHurdle(x, y, &hurdleX, &hurdleY);
    if (!found)
    {
        return 0;
    }
    
    smashThisHurdle(hurdleX, hurdleY);
    
    return 1;
}