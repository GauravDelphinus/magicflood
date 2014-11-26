package com.ezeeideas.magicflood;

import java.util.Random;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Paint.Style;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;

public class MFGameView extends View 
{
	int[][] grid;
	int gridSize;
	int[] startPos;
	int maxMoves;
	
	public MFGameView(Context context, AttributeSet attrs) {
		super(context, attrs);
		// TODO Auto-generated constructor stub
		
		gridSize = 8;
		grid = new int[gridSize][];
		for (int i = 0; i < gridSize; i++)
		{
			grid[i] = new int[gridSize];
		}
		
		for (int i = 0; i < gridSize; i++)
		{
			for (int j = 0; j < gridSize; j++)
			{
				grid[i][j] = randInt(1, 6);
			}
		}
	}

	protected void onDraw(Canvas canvas)
	{
		Log.d("magicfloord", "MFGameView.onDraw called");
		int horizontalGap = 20;
		int vOffset = 80;
		int screenWidth = this.getWidth();
		int cellSize = (screenWidth - horizontalGap)/gridSize;
		int hOffset = horizontalGap / 2;
		
		Paint borderPaint = new Paint();
		borderPaint.setARGB(255, 255, 255, 255);
		borderPaint.setAntiAlias(true);
		borderPaint.setStyle(Style.STROKE);
		borderPaint.setStrokeWidth(2);
		
		Paint fillPaint = new Paint();
		fillPaint.setAntiAlias(true);
		fillPaint.setStyle(Style.FILL);
		
		for (int i = 0; i < gridSize; i++)
		{
			for (int j = 0; j < gridSize; j++)
			{
				int left = hOffset + i * cellSize;
				int top = vOffset + j * cellSize;
				int right = left + cellSize;
				int bottom = top + cellSize;
				
				fillPaint.setColor(getColor(grid[i][j]));
				canvas.drawRect(left, top, right, bottom, fillPaint);
				canvas.drawRect(left,  top, right, bottom, borderPaint);
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
		case 1:
			return getContext().getResources().getColor(R.color.red);
		case 2:
			return getContext().getResources().getColor(R.color.green);
		case 3:
			return getContext().getResources().getColor(R.color.blue);
		case 4:
			return getContext().getResources().getColor(R.color.yellow);
		case 5:
			return getContext().getResources().getColor(R.color.orange);
		case 6:
			return getContext().getResources().getColor(R.color.cyan);
		}
		
		return -1;
	}
}
