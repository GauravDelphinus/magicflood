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
 Genereate and place a medium obstacle in the grid, at the center.
 **/
void MFObstacle::setMediumObstacle(int **grid, int gridSize, int shape)
{
    switch (shape)
    {
        case SHAPE_SQUARE:
            grid[gridSize/2 - 2][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 + 1] = GRID_OBSTACLE;
            break;
        case SHAPE_LINE_VERTICAL:
            grid[gridSize/2 - 1][gridSize/2 - 4] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 3] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 + 2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 + 3] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 4] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 3] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 + 2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 + 3] = GRID_OBSTACLE;
            break;
        case SHAPE_LINE_HORIZONTAL:
            grid[gridSize/2 - 4][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 3][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 3][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 4][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 3][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 + 2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 + 3][gridSize/2] = GRID_OBSTACLE;
            break;
        case SHAPE_ELL_UPRIGHT:
            grid[gridSize/2 - 2][gridSize/2 - 4] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 4] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2 - 3] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 3] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 + 1] = GRID_OBSTACLE;
            break;
        case SHAPE_ELL_RIGHT:
            grid[gridSize/2 - 2][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 + 2][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 + 3][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 3][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 + 1] = GRID_OBSTACLE;
            break;
        case SHAPE_ELL_INVERTED:
            grid[gridSize/2 - 2][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 + 2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 + 2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 + 3] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 + 3] = GRID_OBSTACLE;
            break;
        case SHAPE_ELL_LEFT:
            grid[gridSize/2][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 4][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 3][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 4][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 3][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 + 1] = GRID_OBSTACLE;
            break;
        case SHAPE_JAY_UPRIGHT:
            grid[gridSize/2][gridSize/2 - 4] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 - 4] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 3] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 - 3] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 + 1] = GRID_OBSTACLE;
            break;
        case SHAPE_JAY_LEFT:
            grid[gridSize/2 - 2][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 + 2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 + 3][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 2][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 3][gridSize/2 + 1] = GRID_OBSTACLE;
            break;
        case SHAPE_JAY_INVERTED:
            grid[gridSize/2 - 2][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2 + 2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 + 2] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2 + 3] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 + 3] = GRID_OBSTACLE;
            break;
        case SHAPE_JAY_RIGHT:
            grid[gridSize/2 - 4][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 - 3][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 - 4][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 3][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 + 1] = GRID_OBSTACLE;
            break;
        case SHAPE_TEE_UPRIGHT:
            grid[gridSize/2 - 3][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 + 2][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2-3][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2+1][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2+2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 + 1] = GRID_OBSTACLE;
            break;
        case SHAPE_TEE_RIGHT:
            grid[gridSize/2][gridSize/2-3] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2-2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2+1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2+2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2-3] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2-2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2+1] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2+2] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2-2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-2][gridSize/2] = GRID_OBSTACLE;
            break;
        case SHAPE_TEE_INVERTED:
            grid[gridSize/2-1][gridSize/2-2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2-2] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-3][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2-2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2+1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2+2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2-3][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2-2][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2+1][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2+2][gridSize/2 + 1] = GRID_OBSTACLE;
            break;
        case SHAPE_TEE_LEFT:
            grid[gridSize/2-2][gridSize/2-3] = GRID_OBSTACLE;
            grid[gridSize/2-2][gridSize/2-2] = GRID_OBSTACLE;
            grid[gridSize/2-2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2-2][gridSize/2+1] = GRID_OBSTACLE;
            grid[gridSize/2-2][gridSize/2+2] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2-3] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2-2] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2+1] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2+2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2] = GRID_OBSTACLE;
            break;
        case SHAPE_ESS_UPRIGHT:
            grid[gridSize/2-1][gridSize/2-2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2-2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2-2] = GRID_OBSTACLE;
            grid[gridSize/2 + 2][gridSize/2-2] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2 + 2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-3][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2-2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2-3][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2-2][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 + 1] = GRID_OBSTACLE;
            break;
        case SHAPE_ESS_TILTED:
            grid[gridSize/2 - 2][gridSize/2 - 3] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 3] = GRID_OBSTACLE;
            grid[gridSize/2-2][gridSize/2-2] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2-2] = GRID_OBSTACLE;
            grid[gridSize/2-2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 + 2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 + 2] = GRID_OBSTACLE;
            break;
        case SHAPE_ZED_UPRIGHT:
            grid[gridSize/2-3][gridSize/2-2] = GRID_OBSTACLE;
            grid[gridSize/2-2][gridSize/2-2] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2-2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2-2] = GRID_OBSTACLE;
            grid[gridSize/2-3][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 + 2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 2][gridSize/2 + 1] = GRID_OBSTACLE;
            break;
        case SHAPE_ZED_TILTED:
            grid[gridSize/2-2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2-2][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2-2][gridSize/2 + 2] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2 + 1] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2 + 2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2-3] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2-2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2-3] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2-2] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2] = GRID_OBSTACLE;
            break;
        default:
            break;
    }

}

/**
 Placed a Hard Obstacle.  The code that is inside each switch/case
 statement can be auto-generated using the script genHurdleCode in the
 scripts folder.
 **/
void MFObstacle::setHardObstacle(int **grid, int gridSize, int shape, bool useRandom)
{
    int shapeWidth = 0, shapeHeight = 0, xoffset = 0, yoffset = 0;
    switch (shape)
    {
        case 1: /* Free Hurdle */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 2: /* Free Hurdle */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 3: /* IAP A-la-carte 1 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 4: /* IAP A-la-carte 2 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 5: /* IAP A-la-carte 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 6: /* IAP A-la-carte 4 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 7: /* IAP A-la-carte 5 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 8: /* Part of IAP Combo 1 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 9: /* Part of IAP Combo 1 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 10: /* Part of IAP Combo 1 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 11: /* Part of IAP Combo 1 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 12: /* Part of IAP Combo 1 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 13: /* Part of IAP Combo 2 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 14: /* Part of IAP Combo 2 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 15: /* Part of IAP Combo 2 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 16: /* Part of IAP Combo 2 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 17: /* Part of IAP Combo 2 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 18: /* Part of IAP Combo 2 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 19: /* Part of IAP Combo 2 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 20: /* Part of IAP Combo 2 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 21: /* Part of IAP Combo 2 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 22: /* Part of IAP Combo 2 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 23: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 24: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 25: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 26: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 27: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 28: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 29: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 30: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 31: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 32: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 33: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 34: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 35: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 36: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 37: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 38: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 39: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 40: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 41: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 42: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 43: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 44: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 45: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 46: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 11] = GRID_OBSTACLE;
            break;
        case 47: /* Part of IAP Combo 3 */
            shapeWidth = 12;
            shapeHeight = 12;
            if (useRandom)
            {
                xoffset = random() % (gridSize - shapeWidth + 1);
                yoffset = random() % (gridSize - shapeHeight + 1);
            }
            else
            {
                xoffset = yoffset = 1;
            }
            grid[yoffset + 0][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 11] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 11] = GRID_OBSTACLE;
            break;
        }
    
}

/**
 Place the obstacle/hurdle in the grid.  If useRandom is true,
 place the hurdle at a random position.  Otherwise, place at a fixed
 position.
 **/
void MFObstacle::setObstacle(int **grid, int gridSize, int shape, bool useRandom)
{
    if (mLevel == GAME_LEVEL_MEDIUM)
    {
        setMediumObstacle(grid, gridSize, shape);
    }
    else if (mLevel == GAME_LEVEL_HARD)
    {
        setHardObstacle(grid, gridSize, shape, useRandom);
    }
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

/**
 Create/Allocate a new grid of the given Shape and Size.
 **/
int ** MFObstacle::createGrid(int shape, int gridSize)
{
    //allocate the grid
    int **grid = (int **)calloc(gridSize, sizeof(int *));
    for (int i = 0; i < gridSize; i++)
    {
        grid[i] = (int *)calloc(gridSize, sizeof(int));
    }
    
    /**
     Try fixing the hurdle at a random location in the grid.
     **/
    int count = 1;
    while (count > 0)
    {
        setObstacle(grid, gridSize, shape, true);
        
        //check for closed loops
        if (!gridHasClosedLoop(grid, gridSize))
        {
            break;
        }
        
        //the grid had closed loop(s), so reset it
        resetGrid(grid, gridSize);
        count --;
    }
    
    /**
     Grid had closed loop(s).  Place at a fixed position (see
     setObstacle for details).
     **/
    if (count == 0)
    {
        setObstacle(grid, gridSize, shape, false);
    }
    
    return grid;
}