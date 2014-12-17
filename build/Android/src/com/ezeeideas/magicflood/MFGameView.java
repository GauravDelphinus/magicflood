package com.ezeeideas.magicflood;

import java.util.Random;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.LinearGradient;
import android.graphics.Paint;
import android.graphics.Paint.Style;
import android.graphics.RadialGradient;
import android.graphics.Shader;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;

public class MFGameView extends View 
{
	int[][] mGrid;
	int mGridSize;
	int[] mStartPos;
	int mMaxMoves;
	
	public MFGameView(Context context, AttributeSet attrs) {
		super(context, attrs);
		// TODO Auto-generated constructor stub
	}

	protected void onDraw(Canvas canvas)
	{
		Log.d("magicfloord", "MFGameView.onDraw called");
		int horizontalGap = 20;
		int vOffset = 80;
		int screenWidth = this.getWidth();
		int screenHeight = this.getHeight();
		int cellSize = (Math.min(screenWidth, screenHeight) - horizontalGap)/mGridSize;
		int hOffset = horizontalGap / 2;
		
		Paint borderPaint = new Paint();
		borderPaint.setARGB(255, 255, 255, 255);
		borderPaint.setAntiAlias(true);
		borderPaint.setStyle(Style.STROKE);
		borderPaint.setStrokeWidth(2);
		
		Paint startPaint = new Paint();
		startPaint.setARGB(255, 0, 0, 0);
		startPaint.setAntiAlias(true);
		startPaint.setStyle(Style.STROKE);
		startPaint.setStrokeWidth(4);
		
		Paint fillPaint = new Paint();
		fillPaint.setAntiAlias(true);
		fillPaint.setStyle(Style.FILL);
		
		for (int i = 0; i < mGridSize; i++)
		{
			for (int j = 0; j < mGridSize; j++)
			{
				int left = hOffset + i * cellSize;
				int top = vOffset + j * cellSize;
				int right = left + cellSize;
				int bottom = top + cellSize;
				
				fillPaint.setColor(getColor(mGrid[i][j]));
				//fillPaint.setShader(new LinearGradient(0, top, 0, bottom, getColor(mGrid[i][j]), Color.WHITE, Shader.TileMode.MIRROR));
				fillPaint.setShader(new RadialGradient((left + right)/2, (top + bottom)/2, (int)((right - left) / 2 * Math.sqrt(2)), getSecondaryColor(mGrid[i][j]), getColor(mGrid[i][j]), Shader.TileMode.MIRROR));
				canvas.drawRect(left, top, right, bottom, fillPaint);
				canvas.drawRect(left,  top, right, bottom, borderPaint);
			}
		}
		canvas.drawRect(hOffset + mStartPos[0] * cellSize,  vOffset + mStartPos[1] * cellSize, hOffset + mStartPos[0] *cellSize + cellSize, vOffset + mStartPos[1] * cellSize + cellSize, startPaint);
		
	}

	public void initializeGameData(int [][]grid, int size, int[] startPos, int maxMoves)
	{
		Log.d("magicflood", "initializeGameData");
		mGrid = new int[size][size];
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				mGrid[i][j] = grid[i][j];
			}
		}
		mGridSize = size;
		
		mStartPos = new int[2];
		mStartPos[0] = startPos[0];
		mStartPos[1] = startPos[1];
		
		mMaxMoves = maxMoves;
	}
	
	public void updateGameData(int [][]grid)
	{
		for (int i = 0; i < mGridSize; i++)
		{
			for (int j = 0; j < mGridSize; j++)
			{
				mGrid[i][j] = grid[i][j];
			}
		}

	}
	
	public static int randInt(int min, int max) {

	    // NOTE: Usually this should be a field rather than a method
	    // variable so that it is not re-seeded every call.
	    Random rand = new Random();

	    // nextInt is normally exclusive of the top value,
	    // so add 1 to make it inclusive
	    int randomNum = rand.nextInt((max - min) + 1) + min;

	    return randomNum;
	}
	
	int getColor(int colorValue)
	{
		switch (colorValue)
		{
		case MFGameConstants.GRID_COLOR_RED:
			return getContext().getResources().getColor(R.color.red);
		case MFGameConstants.GRID_COLOR_GREEN:
			return getContext().getResources().getColor(R.color.green);
		case MFGameConstants.GRID_COLOR_BLUE:
			return getContext().getResources().getColor(R.color.blue);
		case MFGameConstants.GRID_COLOR_YELLOW:
			return getContext().getResources().getColor(R.color.yellow);
		case MFGameConstants.GRID_COLOR_ORANGE:
			return getContext().getResources().getColor(R.color.orange);
		case MFGameConstants.GRID_COLOR_CYAN:
			return getContext().getResources().getColor(R.color.cyan);
		case MFGameConstants.GRID_OBSTACLE:
			return getContext().getResources().getColor(R.color.gray);
		}
		
		return -1;
	}
	
	int getSecondaryColor(int colorValue)
	{
		switch (colorValue)
		{
		case MFGameConstants.GRID_COLOR_RED:
			return getContext().getResources().getColor(R.color.red2);
		case MFGameConstants.GRID_COLOR_GREEN:
			return getContext().getResources().getColor(R.color.green2);
		case MFGameConstants.GRID_COLOR_BLUE:
			return getContext().getResources().getColor(R.color.blue2);
		case MFGameConstants.GRID_COLOR_YELLOW:
			return getContext().getResources().getColor(R.color.yellow2);
		case MFGameConstants.GRID_COLOR_ORANGE:
			return getContext().getResources().getColor(R.color.orange2);
		case MFGameConstants.GRID_COLOR_CYAN:
			return getContext().getResources().getColor(R.color.cyan2);
		case MFGameConstants.GRID_OBSTACLE:
			return getContext().getResources().getColor(R.color.gray2);
		}
		
		return -1;
	}
}
