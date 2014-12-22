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
		mStartPaint.setColor(getResources().getColor(R.color.white));
		mStartPaint.setAntiAlias(true);
		mStartPaint.setStyle(Style.FILL);
		mStartPaint.setAlpha(255);
		mStartPaint.setStrokeWidth(1);
		
		mTestPaint = new Paint();
		mTestPaint.setColor(getResources().getColor(R.color.black));
		mTestPaint.setAlpha(255);
		mTestPaint.setStrokeWidth(2);
		
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
		drawStar(canvas, cellSize, hOffset, vOffset);
		
	}

	private void drawStar(Canvas canvas, int cellSize, int hOffset, int vOffset)
	{
		int left = hOffset + mStartPos[1] * cellSize;
		int top = vOffset + mStartPos[0] * cellSize;
		
		int d = cellSize; //diameter
		int r = d/2; //radius of star spikes
		int s = r/2; //radius of star troughs
		double theta = 72 * Math.PI / 180; //degrees
		double phi = 36 * Math.PI / 180; //degrees
		
		double costheta = Math.cos(theta);
		double cosphi = Math.cos(phi);
		double sintheta = Math.sin(theta);
		double sinphi = Math.sin(phi);
		
		int x1 = left + d;
		int y1 = top + r;
		int x3 = left + r + (int)(r * costheta);
		int y3 = top + r - (int)(r * sintheta);
		int x5 = left + r - (int)(r * cosphi);
		int y5 = top + r - (int)(r * sinphi);
		int x7 = left + r - (int)(r * cosphi);
		int y7 = top + r + (int)(r * sinphi);
		int x9 = left + r + (int)(r * costheta);
		int y9 = top + r + (int)(r * sintheta);
		int x2 = left + r + (int)(s * cosphi);
		int y2 = top + r - (int)(s * sinphi);
		int x4 = left + r - (int)(s * costheta);
		int y4 = top + r - (int)(s * sintheta);
		int x6 = left + r - s;
		int y6 = top + r;
		int x8 = left + r - (int)(s * costheta);
		int y8 = top + r + (int)(s * sintheta);
		int x10 = left + r + (int)(s * cosphi);
		int y10 = top + r + (int)(s * sinphi);
		
		canvas.drawPoint(left + r, top + r, mTestPaint);
		
		mCurrentAngleOfStartPosition += ROTATION_STEP_DEGREES;
		canvas.rotate(mCurrentAngleOfStartPosition % 360, left + r, top + r);
		//canvas.drawRect(l, t, r, b, startPaint);
		Path starPath = new Path();
		starPath.reset();
		starPath.moveTo(x1, y1);
		starPath.lineTo(x2, y2);
		starPath.lineTo(x3, y3);
		starPath.lineTo(x4, y4);
		starPath.lineTo(x5, y5);
		starPath.lineTo(x6, y6);
		starPath.lineTo(x7, y7);
		starPath.lineTo(x8, y8);
		starPath.lineTo(x9, y9);
		starPath.lineTo(x10, y10);
		starPath.lineTo(x1, y1);
		
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

	private Paint mStartPaint, mBorderPaint, mFillPaint, mTestPaint;
}
