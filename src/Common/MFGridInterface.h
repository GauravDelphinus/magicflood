//
//  MFGridInterface.h
//  Magic Flood
//
//  Created by Anukrity Jain on 23/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#ifndef Magic_Flood_MFGridInterface_h
#define Magic_Flood_MFGridInterface_h

extern "C" {
int getNumLevels();
long createNewGrid(int level);
void deleteGrid(long handle);
int getGridSize(long handle);
    int getNumStartPos(long handle);
int** getStartPos(long handle);
void freeStartPos(long handle, int **startPos);
    int addStartPos(long handle, int x, int y);
int getMaxMoves(long handle);
    void setMaxMoves(long handle, int maxMoves);
int getCurrMove(long handle);
int* playMove(long handle, int color);
void freePlayMove(long handle, int *result);
int** getGridData(long handle);
void freeGridData(long handle, int **gridData);
    int smashHurdle(long handle, int x, int y);
    bool hasHurdles(long handle);
    int buildBridge(long handle, int startx, int starty, int endx, int endy);
    int ** checkBridgeValid(long handle, int startrow, int startcol, int endrow, int endcol);
    void freeBridgeExtremes(long handle, int **bridgeExtremes);
    int isBridgeEndpointValid(long handle, int row, int col);
    bool hasSpaces(long handle);
}

/**
 Result of a Move
 **/
#define RESULT_CONTINUE 0
#define RESULT_SUCCESS 1
#define RESULT_FAILED 2

/**
 Color values that are stored in the Grid.
 Note that 0 indicates color cannot be filled in that cell.
 Please add colors in increasing order, and update the NUM_COLORS macro.
 **/
#define GRID_OBSTACLE 0
#define GRID_SPACE  '.'

#define GRID_COLOR_RED 1
#define GRID_COLOR_GREEN 2
#define GRID_COLOR_BLUE 3
#define GRID_COLOR_YELLOW 4
#define GRID_COLOR_ORANGE 5
#define GRID_COLOR_CYAN 6

#define GRID_NUM_COLORS 6

#endif
