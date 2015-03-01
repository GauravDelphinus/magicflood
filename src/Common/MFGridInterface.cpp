//
//  MFGridInterface.c
//  Magic Flood
//
//  Created by Anukrity Jain on 23/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "MFGrid.h"
#include "MFGridData.h"
#include "MFGridInterface.h"

/**
 The Grid object.
 **/
static MFGrid *mGrid = NULL;

extern "C" {

/**
 Get the number of levels.
 **/
int getNumLevels()
{
    return sizeof(sGridData) / sizeof(const char *);
}

/**
 Create/allocate a new Grid.
 **/
long createNewGrid(int level)
{
    if (mGrid == NULL)
    {
        mGrid = new MFGrid(level);
    }
    
    return (long)mGrid;
}

/**
 Delete/free up the grid.
 **/
void deleteGrid(long handle)
{
    if (mGrid != NULL)
    {
        delete mGrid;
        mGrid = NULL;
    }
}

/**
 Return the size of the Grid.
 **/
int getGridSize(long handle)
{
    MFGrid *grid = reinterpret_cast<MFGrid*>(handle);
    if (grid != NULL)
    {
        return grid->getGridSize();
    }
    
    return -1;
}
    
/*
 Return the start position for this game.
 NOTE: The returned array must be freed by the caller by calling freeStartPos API.
 */
int** getStartPos(long handle)
{
    MFGrid *grid = reinterpret_cast<MFGrid*>(handle);
    if (grid != NULL)
    {
        int **internalStartPos = grid->getStartPos();
        int numStartPos = grid->getNumStartPos();
        int **startPos = (int **) malloc (numStartPos * sizeof(int*));
        for (int i = 0; i < numStartPos; i++)
        {
            startPos[i] = (int *) malloc (2 * sizeof(int));
            startPos[i][0] = internalStartPos[i][0];
            startPos[i][1] = internalStartPos[i][1];
        }
        
        return startPos;
    }
    
    return NULL;
}
    
/**
 Free the memory in startPos that was allocated by a previous
 getStartPos API.
 **/
void freeStartPos(long handle, int **startPos)
{
    MFGrid *grid = reinterpret_cast<MFGrid*>(handle);
    if (grid != NULL)
    {
        if (startPos != NULL)
        {
            int numStartPos = grid->getNumStartPos();
            for (int i = 0; i < numStartPos; i++)
            {
                free(startPos[i]);
            }
            free(startPos);
        }
    }
}
    
/**
 Return the number of Start Positions in the game.
 **/
int getNumStartPos(long handle)
{
    MFGrid *grid = reinterpret_cast<MFGrid *>(handle);
    if (grid != NULL)
    {
        return grid->getNumStartPos();
    }
    
    return 0;
}
    
int addStartPos(long handle, int x, int y)
{
    MFGrid *grid = reinterpret_cast<MFGrid*>(handle);
    if (grid != NULL)
    {
        return grid->addStartPos(x, y);
    }
    
    return 0;
}

/**
 Return the maximum number of moves for this game.
 **/
int getMaxMoves(long handle)
{
    MFGrid *grid = reinterpret_cast<MFGrid*>(handle);
    if (grid != NULL)
    {
        return grid->getMaxMoves();
    }
    
    return -1;
}

/**
 Set the maximum moves for this game.
 **/
void setMaxMoves(long handle, int maxMoves)
{
    MFGrid *grid = reinterpret_cast<MFGrid*>(handle);
    if (grid != NULL)
    {
        return grid->setMaxMoves(maxMoves);
    }
}

/**
 Return the current move.
 **/
int getCurrMove(long handle)
{
    MFGrid *grid = reinterpret_cast<MFGrid*>(handle);
    if (grid != NULL)
    {
        return grid->getCurrMoves();
    }
    
    return -1;
}

/**
 Play the move after extracting th MFGrid object.
 NOTE: The returned array must be freed by the caller by calling freePlayMove API.
 **/
int* playMove(long handle, int color)
{
    int *result = NULL;
    
    MFGrid *grid = reinterpret_cast<MFGrid*>(handle);
    if (grid != NULL)
    {
        result = grid->playMove(color);
    }
    
    return result;
}

/**
 Free the memory in result that was allocated by a previous
 playMove API.
 **/
void freePlayMove(long handle, int *result)
{
    MFGrid *grid = reinterpret_cast<MFGrid*>(handle);
    if (grid != NULL)
    {
        if (result != NULL)
        {
            free(result);
        }
    }
}
  
/**
 Return the full grid data to the calling routine.
 NOTE: This function allocates a 2-D array, and must be freed after use
 by calling the freeGridData API.
 **/
int** getGridData(long handle)
{
    MFGrid *grid = reinterpret_cast<MFGrid*>(handle);
    if (grid != NULL)
    {
        int **internalGridData = grid->getFullGrid();
        if (internalGridData != NULL)
        {
            int size = grid->getGridSize();
            int **gridData = (int **) malloc(size * sizeof(int *));
            for (int i = 0; i < size; i++)
            {
                gridData[i] = (int *) malloc (size * sizeof(int));
                for (int j = 0; j < size; j++)
                {
                    gridData[i][j] = internalGridData[i][j];
                }
            }
        
            return gridData;
        }
    }
    
    return NULL;
}
    
/**
 Free the grid data that was previously returned by the getGridData API.
 **/
void freeGridData(long handle, int **gridData)
{
    MFGrid *grid = reinterpret_cast<MFGrid*>(handle);
    if (grid != NULL)
    {
        if (gridData != NULL)
        {
            int size = grid->getGridSize();
            for (int i = 0; i < size; i++)
            {
                free(gridData[i]);
            }
            free(gridData);
        }
    }
}

/**
 Smash the hurdle near the position x, y in the grid.
 Return 1 in case of success, 0 in case of failure
 **/
int smashHurdle(long handle, int x, int y)
{
    MFGrid *grid = reinterpret_cast<MFGrid*>(handle);
    if (grid != NULL)
    {
        return grid->smashHurdle(x, y);
    }
    
    return 0;
}
    
bool hasHurdles(long handle)
{
    MFGrid *grid = reinterpret_cast<MFGrid *>(handle);
    if (grid != NULL)
    {
        return grid->hasHurdles();
    }
    
    return false;
}

}