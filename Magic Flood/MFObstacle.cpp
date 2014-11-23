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

MFObstacle::MFObstacle()
{
}

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

void MFObstacle::setObstacle(int **grid, int gridSize, int shape, bool useRandom)
{
    int shapeWidth = 0, shapeHeight = 0, xoffset = 0, yoffset = 0;
    switch (shape)
    {
        case SHAPE_SQUARE:
            grid[gridSize/2 - 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            break;
        case SHAPE_LINE_VERTICAL:
            grid[gridSize/2 - 1][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 + 1] = GRID_OBSTACLE;
            break;
        case SHAPE_LINE_HORIZONTAL:
            grid[gridSize/2 - 2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 + 1][gridSize/2 - 1] = GRID_OBSTACLE;
            break;
        case SHAPE_ELL_UPRIGHT:
            grid[gridSize/2 - 1][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            break;
        case SHAPE_ELL_RIGHT:
            grid[gridSize/2 - 2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 1] = GRID_OBSTACLE;
            break;
        case SHAPE_ELL_INVERTED:
            grid[gridSize/2 - 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 + 1] = GRID_OBSTACLE;
            break;
        case SHAPE_ELL_LEFT:
            grid[gridSize/2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            break;
        case SHAPE_JAY_UPRIGHT:
            grid[gridSize/2][gridSize/2 - 2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2] = GRID_OBSTACLE;
            break;
        case SHAPE_JAY_LEFT:
            grid[gridSize/2 - 2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            break;
        case SHAPE_JAY_INVERTED:
            grid[gridSize/2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 + 1] = GRID_OBSTACLE;
            break;
        case SHAPE_JAY_RIGHT:
            grid[gridSize/2 - 2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2 - 1][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2 - 1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            break;
        case SHAPE_TEE_UPRIGHT:
            grid[gridSize/2-2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2+1][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            break;
        case SHAPE_TEE_RIGHT:
            grid[gridSize/2][gridSize/2-2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2+1] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2] = GRID_OBSTACLE;
            break;
        case SHAPE_TEE_INVERTED:
            grid[gridSize/2-1][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2+1][gridSize/2] = GRID_OBSTACLE;
            break;
        case SHAPE_TEE_LEFT:
            grid[gridSize/2-1][gridSize/2-2] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2+1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            break;
        case SHAPE_ESS_UPRIGHT:
            grid[gridSize/2-1][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2] = GRID_OBSTACLE;
            break;
        case SHAPE_ESS_TILTED:
            grid[gridSize/2-1][gridSize/2-2] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            break;
        case SHAPE_ZED_UPRIGHT:
            grid[gridSize/2-1][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2] = GRID_OBSTACLE;
            grid[gridSize/2-2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2-1] = GRID_OBSTACLE;
            break;
        case SHAPE_ZED_TILTED:
            grid[gridSize/2][gridSize/2-2] = GRID_OBSTACLE;
            grid[gridSize/2][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2-1] = GRID_OBSTACLE;
            grid[gridSize/2-1][gridSize/2] = GRID_OBSTACLE;
            break;
        case SHAPE_HARD_A:
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
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 8] = GRID_OBSTACLE;
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
        case SHAPE_HARD_CIRCLE:
            shapeWidth = 8;
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
            grid[yoffset + 5][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 0] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 10] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 11] = GRID_OBSTACLE;
            break;
        case SHAPE_HARD_SPIRAL:
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
            grid[yoffset + 11][xoffset + 1] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 3] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 4] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 5] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 6] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 5][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 7] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 8] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 2][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 3][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 4][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 6][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 7][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 8][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 9][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 11][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 0][xoffset + 10] = GRID_OBSTACLE;
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
        case SHAPE_HARD_C:
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
            grid[yoffset + 1][xoffset + 1] = GRID_OBSTACLE;
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
            grid[yoffset + 9][xoffset + 2] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 2] = GRID_OBSTACLE;
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
            grid[yoffset + 9][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 10][xoffset + 9] = GRID_OBSTACLE;
            grid[yoffset + 1][xoffset + 10] = GRID_OBSTACLE;
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
            break;
        default:
            break;
    }

}

void MFObstacle::resetGrid(int **grid, int gridSize)
{
    for (int i = 0; i < gridSize; i++)
    {
        memset(grid[i], 0, gridSize * sizeof(int));
    }
}

int ** MFObstacle::createGrid(int shape, int gridSize)
{
    //allocate the grid
    int **grid = (int **)calloc(gridSize, sizeof(int *));
    for (int i = 0; i < gridSize; i++)
    {
        grid[i] = (int *)calloc(gridSize, sizeof(int));
    }
    
    int count = 1;
    while (count > 0)
    {
        setObstacle(grid, gridSize, shape, true);
        if (!gridHasClosedLoop(grid, gridSize))
        {
            break;
        }
        resetGrid(grid, gridSize);
        count --;
    }
    
    if (count == 0)
    {
        fprintf(stderr, "in count == 0 case\n");
        setObstacle(grid, gridSize, shape, false);
    }
    
    return grid;
}