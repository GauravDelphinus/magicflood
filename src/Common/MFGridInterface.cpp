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

static MFGrid *mGrid = NULL;

extern "C" {
    
long createNewGrid(int level)
{
    if (mGrid == NULL)
    {
        mGrid = new MFGrid(level);
    }
    
    return (long)mGrid;
}

void deleteGrid(long handle)
{
    if (mGrid != NULL)
    {
        delete mGrid;
        mGrid = NULL;
    }
}

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
int* getStartPos(long handle)
{
    MFGrid *grid = reinterpret_cast<MFGrid*>(handle);
    if (grid != NULL)
    {
        int *internalStartPos = grid->getStartPos();
        int *startPos = (int *) malloc (2 * sizeof(int));
        startPos[0] = internalStartPos[0];
        startPos[1] = internalStartPos[1];
        
        return startPos;
    }
    
    return NULL;
}
    
/**
 Free the memory in startPos that was allocated by a previous
 getStartPos API.
 **/
void freeStartPos(long handle, int *startPos)
{
    fprintf(stderr, "freeStartPos called with handle = %lx, startPos = %p\n", handle, startPos);
    MFGrid *grid = reinterpret_cast<MFGrid*>(handle);
    if (grid != NULL)
    {
        if (startPos != NULL)
        {
            free(startPos);
        }
    }
}
    
int getMaxMoves(long handle)
{
    MFGrid *grid = reinterpret_cast<MFGrid*>(handle);
    if (grid != NULL)
    {
        return grid->getMaxMoves();
    }
    
    return -1;
}
    
int getCurrMove(long handle)
{
    MFGrid *grid = reinterpret_cast<MFGrid*>(handle);
    if (grid != NULL)
    {
        return grid->getCurrMoves();
    }
    
    return -1;
}
    
int playMove(long handle, int color)
{
    int result = -1;
    
    MFGrid *grid = reinterpret_cast<MFGrid*>(handle);
    if (grid != NULL)
    {
        result = grid->playMove(color);
    }
    
    return result;
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
        
            fprintf(stderr, "getGridData, return gridData = %p\n", gridData);
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
    fprintf(stderr, "freeGridData called with handle = %lx, gridData = %p\n", handle, gridData);
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

}