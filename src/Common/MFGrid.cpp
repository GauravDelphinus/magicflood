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
 
    //allocate resources
    if (startPos == NULL)
    {
        startPos = (int *)malloc(2 * sizeof(int));
    }
    
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
int* MFGrid::playMove(int color)
{
    int *retVal = (int *) malloc (2 * sizeof(int));
    
    int startx = startPos[0];
    int starty = startPos[1];
    
    //initialize a 2-d boolean array to mark cells that have already been checked for neighbor density
    bool **alreadyCheckedFlags = (bool **) calloc (gridSize, sizeof(bool *));
    for (int i = 0; i < gridSize; i++)
    {
        alreadyCheckedFlags[i] = (bool *) calloc (gridSize, sizeof (bool));
    }

    int numUpdated = checkNeighborDensityForColor(mGameGrid[startx][starty], color, startx, starty, mGameGrid, alreadyCheckedFlags);
    
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            alreadyCheckedFlags[i][j] = false;
        }
    }
    updateNeighbors(mGameGrid[startx][starty], color, startx, starty, mGameGrid, alreadyCheckedFlags);
   
    
    
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
        retVal[1] = 0;
    }
    else if (currMove >= maxMoves)
    {
        retVal[0] = RESULT_FAILED;
        retVal[1] = 0;
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

void MFGrid::initializeGrid()
{
    logPrint("gaurav", "MFGrid::initializeGrid *********, level = %d\n", level);
        
    logPrint("gaurav", "arg to strtok [%s]\n", sGridData[level-1]);
    char *inputStr = strdup(sGridData[level - 1]);
        char *token = strtok(inputStr, "#");
    logPrint("gaurav", "token is %p\n", token);
    
    if (token)
    {
        startPos[0] = atoi(token);
        logPrint("gaurav", "setting the startPos[0] to %d\n", startPos[0]);
        
        token = strtok(NULL, "#");
        if (token)
        {
            startPos[1] = atoi(token);
            logPrint("gaurav", "setting the startPos[1] to %d\n", startPos[1]);
            
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
                    logPrint("gaurav", "setting the gridSize to %d\n", gridSize);
                    
                    for (int i = 0; i < gridSize; i++)
                    {
                        mGameGrid[i] = (int *)calloc(gridSize, sizeof(int));
                        for (int j = 0; j < gridSize; j++)
                        {
                            mGameGrid[i][j] = token[k] - '0';
                            logPrint("gaurav", "setting mGameGrid[%d][%d] to value[%d] - '0'\n", i, j, k);
                            k++;
                        }
                    }

                }
            }
        }
    }
    /*
        while (token)
        {
            logPrint("gaurav", "top of while loop, token [%s]", token);
            char *key = strtok(token, "=");
            if (key != NULL && strcmp(key, START_POSX_TOKEN_KEY) == 0)
            {
                char *value = strtok(NULL, "=");
                if (value != NULL)
                {
                    startPos[0] = atoi(value);
                    logPrint("gaurav", "setting the startPos[0] to %d\n", startPos[0]);
                }
                value = strtok(NULL, "=");
            }
            else if (key != NULL && strcmp(key, START_POSY_TOKEN_KEY) == 0)
            {
                char *value = strtok(NULL, "=");
                if (value != NULL)
                {
                    startPos[1] = atoi(value);
                    logPrint("gaurav", "setting the startPos[1] to %d\n", startPos[1]);
                }
            }
            else if (key != NULL && strcmp(key, GRIDSIZE_TOKEN_KEY) == 0)
            {
                char *value = strtok(NULL, "=");
                if (value != NULL)
                {
                    gridSize = atoi(value);
                    logPrint("gaurav", "setting the gridSize to %d\n", gridSize);
                }
            }
            else if (key != NULL && strcmp(key, GRIDDATA_TOKEN_KEY) == 0)
            {
                char *value = strtok(NULL, "=");
                if (value != NULL)
                {
                    int k = 0; //index into the value
                    //allocate the grid
                    mGameGrid = (int **)calloc(gridSize, sizeof(int *));
                    for (int i = 0; i < gridSize; i++)
                    {
                        mGameGrid[i] = (int *)calloc(gridSize, sizeof(int));
                        for (int j = 0; j < gridSize; j++)
                        {
                            mGameGrid[i][j] = value[k] - '0';
                            logPrint("gaurav", "setting mGameGrid[%d][%d] to value[%d] - '0'\n", i, j, k);
                            k++;
                        }
                    }
                }
            }
            token = strtok(NULL, "#");
        }
     */
    
    free(inputStr);
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
            
            updateNeighbors(mMeasureGrid[startPos[0]][startPos[1]], randColor, startPos[0], startPos[1], mMeasureGrid, NULL);
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

/*
void MFGrid::checkDensity(int color, int x, int y, int *grid[], std::map<int, int> *map, bool *alreadyCheckedFlags[])
{
    if (isObstacle(x, y, grid) || grid[x][y] != color || alreadyCheckedFlags == NULL || alreadyCheckedFlags[x][y])
    {
        return;
    }
    
    alreadyCheckedFlags[x][y] = true;
    (*map)[color] ++;
    logPrint("gaurav", "checkDesntiy, x = %d, y = %d, added value for color %d to %d\n", x, y, color, (*map)[color]);
    
    checkDensity(color, x, y-1, grid, map, alreadyCheckedFlags);
    checkDensity(color, x, y+1, grid, map, alreadyCheckedFlags);
    checkDensity(color, x-1, y, grid, map, alreadyCheckedFlags);
    checkDensity(color, x+1, y, grid, map, alreadyCheckedFlags);
}
 */

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
        logPrint("gaurav", "findMostDenseCOlor, color count for %d is %d\n", color, colorCount);
        iter++;
    }
    
    logPrint("gaurav", "findMostDenseColor returning %d\n", mostDenseColor);
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
