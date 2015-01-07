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
#include "MFGridData.h"
#include "MFNativeLog.h"

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

void MFGrid::initializeGrid()
{
    logPrint("gaurav", "MFGrid::initializeGrid *********, level = %d\n", level);
    
    numLevels = sizeof(sGridData) / sizeof(const char *);
    logPrint("gaurav", "numLevels = %d\n", numLevels);
    
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
