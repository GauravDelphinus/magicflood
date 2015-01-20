package com.ezeeideas.magicflood;

import java.util.Random;
import java.util.Timer;
import java.util.TimerTask;

import android.content.Context;
import android.graphics.Canvas;

import android.graphics.LinearGradient;
import android.graphics.Paint;
import android.graphics.Paint.Style;
import android.graphics.Path;
import android.graphics.RadialGradient;
import android.graphics.RectF;
import android.graphics.Shader;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;

public class MFGameView extends View 
{
	int[][] mGrid;
	int mGridSize;
	int[][] mStartPos;
	int mNumStartPos;
	int mMaxMoves;
	private Timer mAnimationTimer = null;
	private TimerTask mAnimationTimerTask = null;
	private int mCurrentAngleOfStartPosition = 0;
	private static final int ROTATION_STEP_DEGREES = 5;
	private static final int ROTATION_SPEED_INTERVAL = 200; //milliseconds
	private static final int SHADOW_THICKNESS = 20;
	
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
		mStartPaint.setAntiAlias(true);
		mStartPaint.setStyle(Style.FILL);
		mStartPaint.setAlpha(255);
		mStartPaint.setStrokeWidth(1);
		mStartPaint.setColor(getResources().getColor(R.color.white));
		
		mShadowPaint = new Paint();
		mShadowPaint.setAntiAlias(true);
		mShadowPaint.setStyle(Style.FILL);
		mShadowPaint.setAlpha(255);
		mShadowPaint.setStrokeWidth(1);
		mShadowPaint.setColor(getResources().getColor(R.color.game_grid_shadow_color));
		
		mStartStrokePaint = new Paint();
		mStartStrokePaint.setARGB(255, 0, 0, 0);
		mStartStrokePaint.setStyle(Style.STROKE);
		mStartStrokePaint.setAlpha(255);
		mStartStrokePaint.setStrokeWidth(1);
		
		mStarPath = new Path();
		
		mTestPaint = new Paint();
		mTestPaint.setColor(getResources().getColor(R.color.black));
		mTestPaint.setAlpha(255);
		mTestPaint.setStrokeWidth(2);
		
		mFillPaint = new Paint();
	}

	protected void onDraw(Canvas canvas)
	{
		int horizontalGap = 0;
		
		int screenWidth = this.getWidth();
		int screenHeight = this.getHeight();
		
		int hOffset = 0;
		int vOffset = 0;
		/**
		 * figure out the hOffset and the vOffset, in trying to center the grid in the given area.
		 */
		if (screenHeight > screenWidth)
		{
			hOffset = 0;
			vOffset = (screenHeight - screenWidth) / 2;
		}
		else
		{
			vOffset = 0;
			hOffset = (screenWidth - screenHeight) / 2;
		}
		
		/**
		 * Draw a shadown behind the grid to one x and one y direction.  Calculate the size of the grid
		 * after accounting for the shadow thickness
		 */
		int gridSizePixels = Math.min(screenWidth, screenHeight) - SHADOW_THICKNESS;
		
		/**
		 * Draw the shadow rect.
		 */
		
		//bottom shadow
		Shader shadowShader = new LinearGradient(hOffset, vOffset + gridSizePixels, hOffset, vOffset + gridSizePixels + SHADOW_THICKNESS, getResources().getColor(R.color.grid_background_gradient_start_color), getResources().getColor(R.color.transparent), Shader.TileMode.MIRROR);
		mShadowPaint.setShader(shadowShader);
		canvas.drawRect(hOffset + SHADOW_THICKNESS, vOffset + gridSizePixels, hOffset + gridSizePixels, vOffset + gridSizePixels + SHADOW_THICKNESS, mShadowPaint);
		
		//right shadow
		shadowShader = new LinearGradient(hOffset + gridSizePixels, vOffset + SHADOW_THICKNESS, hOffset + gridSizePixels + SHADOW_THICKNESS, vOffset + SHADOW_THICKNESS, getResources().getColor(R.color.grid_background_gradient_start_color), getResources().getColor(R.color.transparent), Shader.TileMode.MIRROR);
		mShadowPaint.setShader(shadowShader);
		canvas.drawRect(hOffset + gridSizePixels, vOffset + SHADOW_THICKNESS, hOffset + SHADOW_THICKNESS + gridSizePixels, vOffset + gridSizePixels, mShadowPaint);
		
		//bottom right corner
		Shader cornerShader = new RadialGradient(hOffset + gridSizePixels, vOffset + gridSizePixels, SHADOW_THICKNESS, getResources().getColor(R.color.grid_background_gradient_start_color), getResources().getColor(R.color.transparent), Shader.TileMode.MIRROR);
		mShadowPaint.setShader(cornerShader);
		RectF rectF = new RectF(hOffset + gridSizePixels - SHADOW_THICKNESS, vOffset + gridSizePixels - SHADOW_THICKNESS, hOffset + gridSizePixels + SHADOW_THICKNESS, vOffset + gridSizePixels + SHADOW_THICKNESS);
		canvas.drawArc(rectF, 0, 90, true, mShadowPaint);
		
		//bottom left corner
		cornerShader = new RadialGradient(hOffset + SHADOW_THICKNESS, vOffset + gridSizePixels, SHADOW_THICKNESS, getResources().getColor(R.color.grid_background_gradient_start_color), getResources().getColor(R.color.transparent), Shader.TileMode.MIRROR);
		mShadowPaint.setShader(cornerShader);
		rectF = new RectF(hOffset, vOffset + gridSizePixels - SHADOW_THICKNESS, hOffset + 2 * SHADOW_THICKNESS, vOffset + gridSizePixels + SHADOW_THICKNESS);
		canvas.drawArc(rectF, 90, 180, true, mShadowPaint);
		
		//top right corner
		cornerShader = new RadialGradient(hOffset + gridSizePixels, vOffset + SHADOW_THICKNESS, SHADOW_THICKNESS, getResources().getColor(R.color.grid_background_gradient_start_color), getResources().getColor(R.color.transparent), Shader.TileMode.MIRROR);
		mShadowPaint.setShader(cornerShader);
		rectF = new RectF(hOffset + gridSizePixels - SHADOW_THICKNESS, vOffset, hOffset + gridSizePixels + SHADOW_THICKNESS, vOffset  + 2 * SHADOW_THICKNESS);
		canvas.drawArc(rectF, 0, -90, true, mShadowPaint);
		
		int cellSize = gridSizePixels/mGridSize;
		
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
		for (int i = 0; i < mNumStartPos; i++)
		{
			drawStar(canvas, cellSize, hOffset, vOffset, mStartPos[i][0], mStartPos[i][1]);
		}
		
	}

	private void drawStar(Canvas canvas, int cellSize, int hOffset, int vOffset, int x, int y)
	{
		int left = hOffset + y * cellSize;
		int top = vOffset + x * cellSize;
		int right = left + cellSize;
		int bottom = top + cellSize;
		
		/**
		 * Draw the background cell with gradient, before you draw the star on it.
		 */
		mFillPaint.reset();
		mFillPaint.setAntiAlias(true);
		mFillPaint.setStyle(Style.FILL);
		mFillPaint.setColor(getColor(mGrid[x][y]));

		mFillPaint.setShader(new RadialGradient((left + right)/2, (top + bottom)/2, (int)((right - left) / 2 * Math.sqrt(2)), getResources().getColor(R.color.star_background_gradient_start_color), getColor(mGrid[x][y]), Shader.TileMode.MIRROR));
		
		canvas.drawRect(left, top, right, bottom, mFillPaint);
		
		/**
		 * Now draw the star
		 */
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
		
		//canvas.drawPoint(left + r, top + r, mTestPaint);
		
		mCurrentAngleOfStartPosition += ROTATION_STEP_DEGREES;
		canvas.save();
		canvas.rotate(mCurrentAngleOfStartPosition % 360, left + r, top + r);
		mStarPath.reset();
		mStarPath.moveTo(x1, y1);
		mStarPath.lineTo(x2, y2);
		mStarPath.lineTo(x3, y3);
		mStarPath.lineTo(x4, y4);
		mStarPath.lineTo(x5, y5);
		mStarPath.lineTo(x6, y6);
		mStarPath.lineTo(x7, y7);
		mStarPath.lineTo(x8, y8);
		mStarPath.lineTo(x9, y9);
		mStarPath.lineTo(x10, y10);
		mStarPath.lineTo(x1, y1);
		
		//set gradient fill in the paint
		//mStartPaint.setShader(new RadialGradient(left + r, top + r, r, getResources().getColor(R.color.white), 
			//	getResources().getColor(R.color.gray), Shader.TileMode.MIRROR));

		//finally, draw the star!
		canvas.drawPath(mStarPath, mStartPaint);
		canvas.restore();
		//canvas.drawPath(starPath, mStartStrokePaint);
	}
	
	public void initializeGameData(int [][]grid, int size, int[][] startPos, int numStartPos, int maxMoves)
	{
		Log.d("gaurav", "initializeGameData, size =" + size + ", numStartPos = " + numStartPos);
		for (int i = 0; i < numStartPos; i++)
		{
			Log.d("gaurav", "startPos index = " + i + ", x = " + startPos[i][0] + ", y = " + startPos[i][1]);
		}
		mGrid = new int[size][size];
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				mGrid[i][j] = grid[i][j];
			}
		}
		mGridSize = size;
		
		mStartPos = new int[numStartPos][2];
		for (int i = 0; i < numStartPos; i++)
		{
			mStartPos[i][0] = startPos[i][0];
			mStartPos[i][1] = startPos[i][1];
		}
		mNumStartPos = numStartPos;
		
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
	
	public void updateStartPos(int [][]startPos, int numStartPos)
	{
		mStartPos = new int[numStartPos][2];
		for (int i = 0; i < numStartPos; i++)
		{
			mStartPos[i][0] = startPos[i][0];
			mStartPos[i][1] = startPos[i][1];
		}
		mNumStartPos = numStartPos;
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

	private Paint mStartPaint, mBorderPaint, mFillPaint, mTestPaint, mStartStrokePaint, mShadowPaint;
	private Path mStarPath;
}
