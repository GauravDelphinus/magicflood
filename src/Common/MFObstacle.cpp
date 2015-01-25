//
//  MFObstacle.cpp
//  Magic Flood
//
//  Created by Anukrity Jain on 22/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#include "MFObstacle.h"
#include "MFGrid.h"
#include "MFGridInterface.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

MFObstacle::MFObstacle(int level)
{
    mLevel = level;
}

/**
 Check if the grid has a closed loop considering the already
 placed obstacle in the grid, and checking with the boundary
 walls on all 4 sides.  This is required, as a valid game
 cannot have a closed loop as the loop will either become in accessible
 or unescapable.
 
 The logic in this function runs round the periphery of the grid,
 and in case two sequences of obstacle cells are found, it means a
 closed loop was found.
 **/
bool MFObstacle::gridHasClosedLoop(int **grid, int gridSize)
{
    bool obstacleStarted = false;
    bool obstacleEnded = false;
    for (int i = 0; i < gridSize; i++)
    {
        //first row
        if (grid[0][i] == GRID_OBSTACLE)
        {
            if (!obstacleEnded)
            {
                obstacleStarted = true;
            }
            else if (obstacleEnded)
            {
                //this is a closed loop!
                return true;
            }
        }
        else
        {
            if (obstacleStarted)
            {
                obstacleEnded = true;
            }
        }
    }
    for (int i = 1; i < gridSize; i++)
    {
        //last colum
        if (grid[i][gridSize - 1] == GRID_OBSTACLE)
        {
            if (!obstacleEnded)
            {
                obstacleStarted = true;
            }
            else if (obstacleEnded)
            {
                //this is a closed loop!
                return true;
            }
        }
        else
        {
            if (obstacleStarted)
            {
                obstacleEnded = true;
            }
        }
    }
    for (int i = gridSize-2; i >= 0; i--)
    {
        //last row
        if (grid[gridSize - 1][i] == GRID_OBSTACLE)
        {
            if (!obstacleEnded)
            {
                obstacleStarted = true;
            }
            else if (obstacleEnded)
            {
                //this is a closed loop!
                return true;
            }
        }
        else
        {
            if (obstacleStarted)
            {
                obstacleEnded = true;
            }
        }
    }
    for (int i = gridSize - 2; i > 0; i--)
    {
        //first colum
        if (grid[i][0] == GRID_OBSTACLE)
        {
            if (!obstacleEnded)
            {
                obstacleStarted = true;
            }
            else if (obstacleEnded)
            {
                //this is a closed loop!
                return true;
            }
        }
        else
        {
            if (obstacleStarted)
            {
                obstacleEnded = true;
            }
        }
    }
    return false;
}

/**
 Reset the grid with 0's.
 **/
void MFObstacle::resetGrid(int **grid, int gridSize)
{
    for (int i = 0; i < gridSize; i++)
    {
        memset(grid[i], 0, gridSize * sizeof(int));
    }
}