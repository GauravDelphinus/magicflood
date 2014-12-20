package com.ezeeideas.magicflood;

import java.util.Random;
import java.util.Timer;
import java.util.TimerTask;

import android.content.Context;
import android.graphics.Canvas;

import android.graphics.Paint;
import android.graphics.Paint.Style;
import android.graphics.Path;
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
	private Timer mAnimationTimer = null;
	private TimerTask mAnimationTimerTask = null;
	private int mCurrentAngleOfStartPosition = 0;
	private static final int ROTATION_STEP_DEGREES = 10;
	private static final int ROTATION_SPEED_INTERVAL = 100; //milliseconds
	
	public MFGameView(Context context, AttributeSet attrs) 
	{
		super(context, attrs);
		
		mAnimationTimer = new Timer();
		mAnimationTimerTask = new AnimationTimerTask(this);
		mAnimationTimer.scheduleAtFixedRate(mAnimationTimerTask, ROTATION_SPEED_INTERVAL, ROTATION_SPEED_INTERVAL);
		
		mBorderPaint = new Paint();
		mBorderPaint.setARGB(255, 255, 255, 255);
		mBorderPaint.setAntiAlias(true);
		mBorderPaint.setStyle(Style.STROKE);
		mBorderPaint.setStrokeWidth(2);
		
		mStartPaint = new Paint();
		mStartPaint.setColor(getResources().getColor(R.color.gray));
		mStartPaint.setAntiAlias(true);
		mStartPaint.setStyle(Style.FILL_AND_STROKE);
		mStartPaint.setAlpha(150);
		mStartPaint.setStrokeWidth(1);
		
		mFillPaint = new Paint();
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

		
		for (int i = 0; i < mGridSize; i++)
		{
			for (int j = 0; j < mGridSize; j++)
			{
				int left = hOffset + j * cellSize;
				int top = vOffset + i * cellSize;
				int right = left + cellSize;
				int bottom = top + cellSize;
				
				mFillPaint.reset();
				mFillPaint.setAntiAlias(true);
				mFillPaint.setStyle(Style.FILL);
				mFillPaint.setColor(getColor(mGrid[i][j]));
				//fillPaint.setShader(new LinearGradient(0, top, 0, bottom, getColor(mGrid[i][j]), Color.WHITE, Shader.TileMode.MIRROR));
				if (mGrid[i][j] == MFGameConstants.GRID_OBSTACLE) //show a gradient for obstacles
				{
					mFillPaint.setShader(new RadialGradient((left + right)/2, (top + bottom)/2, (int)((right - left) / 2 * Math.sqrt(2)), getSecondaryColor(mGrid[i][j]), getColor(mGrid[i][j]), Shader.TileMode.MIRROR));
				}

				canvas.drawRect(left, top, right, bottom, mFillPaint);
				canvas.drawRect(left,  top, right, bottom, mBorderPaint);
			}
		}
		
		//Start Position
		int left = hOffset + mStartPos[1] * cellSize;
		int top = vOffset + mStartPos[0] * cellSize;
		int right = hOffset + mStartPos[1] * cellSize + cellSize;
		int bottom = vOffset + mStartPos[0] * cellSize + cellSize;
		int l = left + (right - left) / 4;
		int t = top + (bottom - top) / 4;
		int r = l + (right - left) / 2;
		int b = t + (bottom - top) / 2;
		int w = (r - l);
		int h = (b - t);
		mCurrentAngleOfStartPosition += ROTATION_STEP_DEGREES;
		canvas.rotate(mCurrentAngleOfStartPosition % 360, (l + r)/2, (t + b)/2);
		//canvas.drawRect(l, t, r, b, startPaint);
		Path starPath = new Path();
		starPath.reset();
		starPath.moveTo((l + r)/2, t);
		starPath.lineTo(l + 2 * w / 3, t + h / 3);
		starPath.lineTo(r, (t + b)/2);
		starPath.lineTo(l + 2 * w / 3, t + 2 * h / 3);
		starPath.lineTo((l + r)/2, b);
		starPath.lineTo(l + w / 3, t + 2 * h/3);
		starPath.lineTo(l, (t + b) /2);
		starPath.lineTo(l + w /3, t + h/3);
		starPath.lineTo((l + r)/2, t);
		
		//set gradient fill in the paint
		//mStartPaint.setShader(new RadialGradient((l + r)/2, (t + b)/2, w/2, getColor(mGrid[mStartPos[0]][mStartPos[1]]), 
		//		getResources().getColor(R.color.white), Shader.TileMode.MIRROR));

		//finally, draw the star!
		canvas.drawPath(starPath, mStartPaint);
		canvas.restore();
		
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
	
	public class AnimationTimerTask extends TimerTask
	{
		private View mView;
		
		public AnimationTimerTask(View view)
		{
			mView = view;
		}
		
		@Override
	    public void run()
		{
			mView.postInvalidate();
		}
	}

	private Paint mStartPaint, mBorderPaint, mFillPaint;
}
