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
import android.graphics.Rect;
import android.graphics.RectF;
import android.graphics.Shader;
import android.support.v4.view.GestureDetectorCompat;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.GestureDetector;

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
	private static final int SHADOW_THICKNESS = 8;

	/**
	 Direction of Linear Gradient for Shadow
	 **/
	private static final int LINEAR_GRADIENT_DIRECTION_NORTH = 1;
	private static final int LINEAR_GRADIENT_DIRECTION_EAST = 2;
	private static final int LINEAR_GRADIENT_DIRECTION_SOUTH = 3;
	private static final int LINEAR_GRADIENT_DIRECTION_WEST = 4;

	/**
	 Direction of Radial Gradient (whether outward or inward) for Shadow
	 **/
	private static final int RADIAL_GRADIENT_DIRECTION_NORTH_EAST = 1;
	private static final int RADIAL_GRADIENT_DIRECTION_SOUTH_EAST = 2;
	private static final int RADIAL_GRADIENT_DIRECTION_SOUTH_WEST = 3;
	private static final int RADIAL_GRADIENT_DIRECTION_NORTH_WEST = 4;
	
	public MFGameView(Context context, AttributeSet attrs) 
	{
		super(context, attrs);
		
		mAnimationTimer = new Timer();
		mAnimationTimerTask = new AnimationTimerTask(this);
		mAnimationTimer.scheduleAtFixedRate(mAnimationTimerTask, ROTATION_SPEED_INTERVAL, ROTATION_SPEED_INTERVAL);
		
		mBorderPaint1 = new Paint();
		mBorderPaint1.setARGB(255, 255, 255, 255);
		mBorderPaint1.setAntiAlias(true);
		mBorderPaint1.setStyle(Style.STROKE);
		mBorderPaint1.setStrokeWidth(2);
		
		mBorderPaint2 = new Paint();
		mBorderPaint2.setARGB(255, 120, 120, 120);
		mBorderPaint2.setAntiAlias(true);
		mBorderPaint2.setStyle(Style.STROKE);
		mBorderPaint2.setStrokeWidth(2);
		
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
		mStartStrokePaint.setARGB(255, 120, 120, 120);
		mStartStrokePaint.setStyle(Style.STROKE);
		mStartStrokePaint.setAlpha(255);
		mStartStrokePaint.setStrokeWidth(1);
		
		mStarPath = new Path();
		
		mTestPaint = new Paint();
		mTestPaint.setColor(getResources().getColor(R.color.black));
		mTestPaint.setAlpha(255);
		mTestPaint.setStrokeWidth(2);
		
		mFillPaint = new Paint();
		
		mDetector = new GestureDetectorCompat(context, new MyGestureListener());
	}
	
	@Override 
    public boolean onTouchEvent(MotionEvent event){ 
        this.mDetector.onTouchEvent(event);
        return super.onTouchEvent(event);
    }
	
	protected void onDraw(Canvas canvas)
	{		
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
		int cellSize = gridSizePixels/mGridSize;
		gridSizePixels = cellSize * mGridSize; //remove the rounding off errors
		
		for (int i = 0; i < mGridSize; i++)
		{
			for (int j = 0; j < mGridSize; j++)
			{
				int left = hOffset + j * cellSize;
				int top = vOffset + i * cellSize;
				int right = left + cellSize;
				int bottom = top + cellSize;
				
				/**
				 * Correcting last cell size to compensate for precision
				 */
				if (i == mGridSize - 1)
				{
					bottom = vOffset + gridSizePixels;
				}
				if (j == mGridSize - 1)
				{
					right = hOffset + gridSizePixels;
				}
				
				mFillPaint.reset();
				mFillPaint.setAntiAlias(true);
				mFillPaint.setStyle(Style.FILL);
				mFillPaint.setColor(getColor(mGrid[i][j]));
				//fillPaint.setShader(new LinearGradient(0, top, 0, bottom, getColor(mGrid[i][j]), Color.WHITE, Shader.TileMode.MIRROR));
				if (mGrid[i][j] == MFGameConstants.GRID_OBSTACLE) //show a gradient for obstacles
				{
					mFillPaint.setShader(new RadialGradient((left + right)/2, (top + bottom)/2, (int)((right - left) / 2 * Math.sqrt(2)), getSecondaryColor(mGrid[i][j]), getColor(mGrid[i][j]), Shader.TileMode.MIRROR));
				}
				
				if (mGrid[i][j] != MFGameConstants.GRID_SPACE) //draw if this cell is not an empty space
				{
					canvas.drawRect(left, top, right, bottom, mFillPaint);
					canvas.drawLine(left + 1, top, left + 1, bottom - 1, mBorderPaint1);
					canvas.drawLine(left, top + 1, right - 1, top + 1, mBorderPaint1);
					canvas.drawLine(left + 1, bottom - 1, right, bottom - 1, mBorderPaint2);
					canvas.drawLine(right - 1, top + 1, right - 1, bottom, mBorderPaint2);
					//canvas.drawRect(left,  top, right, bottom, mBorderPaint);
				}
			}
		}
		
		//Start Position
		for (int i = 0; i < mNumStartPos; i++)
		{
			drawStar(canvas, cellSize, hOffset, vOffset, mStartPos[i][0], mStartPos[i][1]);
		}
		
		/**
		 * Draw the grid shadows
		 */
		drawGridShadow(canvas, hOffset, vOffset, gridSizePixels, cellSize);
	}

	/**
	 * Draw all the grid shadows
	 * @param canvas
	 * @param left grid left
	 * @param top grid top
	 * @param gridLenth grid width/height
	 * @param cellSize size of each cell
	 */
	private void drawGridShadow(Canvas canvas, int left, int top, int gridLenth, int cellSize)
	{
		for (int i = 0; i < mGridSize; i++)
	    {
	        for (int j = 0; j < mGridSize; j++)
	        {
	            if (isEmptyAt(j, i)) //only draw shadow around a real colored cell
	            {
	                continue;
	            }
	            
	            int cellLeft = left + j * cellSize;
	            int cellTop = top + i * cellSize;
	            int cellRight = cellLeft + cellSize;
	            int cellBottom = cellTop + cellSize;
	            
	            if (isEmptyAt(j, i+1)) //below cell is empty
	            {
	                if (!isEmptyAt(j-1, i)) //left cell is not empty, so just draw the bottom shadow
	                {
	                    //bottom shadow with full cell width
	                    Rect shadowRect = new Rect(cellLeft, cellTop + cellSize, cellRight, cellBottom + SHADOW_THICKNESS);
	                    drawLinearGradient(canvas, shadowRect, LINEAR_GRADIENT_DIRECTION_SOUTH);
	                }
	                else //left cell is empty, so the shadow starts here.  so draw the bottom shadow but
	                    //with a rounded offset
	                {
	                    //bottom left corner shadow
	                    Rect cornerRect = new Rect(cellLeft, cellTop + cellSize, cellLeft + SHADOW_THICKNESS, cellBottom + SHADOW_THICKNESS);
	                    drawRadialGradient(canvas, cornerRect, RADIAL_GRADIENT_DIRECTION_SOUTH_WEST, true);
	                    
	                    //bottom shadow offsetted by the shadow thickness
	                    Rect shadowRect = new Rect(cellLeft + SHADOW_THICKNESS, cellTop + cellSize, cellRight, cellBottom + SHADOW_THICKNESS);
	                    drawLinearGradient(canvas, shadowRect, LINEAR_GRADIENT_DIRECTION_SOUTH);
	                }
	            }
	            
	            if (isEmptyAt(j+1, i)) //right cell is empty
	            {
	                if (!isEmptyAt(j, i-1)) //upper cell is not empty, so just draw the right shadow
	                {
	                    //right shadow with full height
	                    Rect shadowRect = new Rect(cellLeft + cellSize, cellTop, cellRight + SHADOW_THICKNESS, cellBottom);
	                    drawLinearGradient(canvas, shadowRect, LINEAR_GRADIENT_DIRECTION_EAST);
	                }
	                else //upper cell is empty, so the shadow starts here.  So draw the offsetted shadow
	                    //with rounded corner
	                {
	                    //top right corner shadow
	                    Rect cornerRect = new Rect(cellLeft + cellSize, cellTop, cellRight + SHADOW_THICKNESS, cellTop + SHADOW_THICKNESS);
	                    drawRadialGradient(canvas, cornerRect, RADIAL_GRADIENT_DIRECTION_NORTH_EAST, true);
	                    
	                    //right shadow offsetted by shadow thickness's height
	                    Rect shadowRect = new Rect(cellLeft + cellSize, cellTop + SHADOW_THICKNESS, cellRight + SHADOW_THICKNESS, cellBottom);
	                    drawLinearGradient(canvas, shadowRect, LINEAR_GRADIENT_DIRECTION_EAST);
	                }
	            }
	            
	            if (isEmptyAt(j, i+1) && isEmptyAt(j+1, i)) //bottom right corner
	            {
	                /**
	                 the right and bottom shadows would have been drawn already (above), so just draw
	                 the bottom right radial shadow.
	                 **/
	                Rect cornerRect = new Rect(cellLeft + cellSize, cellTop + cellSize, cellRight + SHADOW_THICKNESS, cellBottom + SHADOW_THICKNESS);
	                drawRadialGradient(canvas, cornerRect, RADIAL_GRADIENT_DIRECTION_SOUTH_EAST, true);
	            }
	        }
	    }

	}
	
	/**
	 Check if the cell at this position is "empty".
	 **/
	boolean isEmptyAt(int x, int y)
	{
	    if (x < 0 || y < 0 || x >= mGridSize || y >= mGridSize)
	        return true;
	    
	    if (mGrid[y][x] == MFGameConstants.GRID_SPACE)
	    {
	        return true;
	    }
	    
	    return false;
	}
	
	/**
	 Draw a linear gradient in the given rect with the given direction.
	 See direction values at the top of this file.
	 **/
	private void drawLinearGradient(Canvas canvas, Rect rect, int direction)
	{
		Shader shadowShader = null;
		if (direction == LINEAR_GRADIENT_DIRECTION_EAST)
		{
			shadowShader = new LinearGradient(rect.left, rect.top, rect.right, rect.top, getResources().getColor(R.color.grid_background_gradient_start_color), getResources().getColor(R.color.transparent), Shader.TileMode.MIRROR);
		}
		else if (direction == LINEAR_GRADIENT_DIRECTION_WEST)
		{
			shadowShader = new LinearGradient(rect.right, rect.top, rect.left, rect.top, getResources().getColor(R.color.grid_background_gradient_start_color), getResources().getColor(R.color.transparent), Shader.TileMode.MIRROR);
		}
		else if (direction == LINEAR_GRADIENT_DIRECTION_NORTH)
		{
			shadowShader = new LinearGradient(rect.left, rect.bottom, rect.left, rect.top, getResources().getColor(R.color.grid_background_gradient_start_color), getResources().getColor(R.color.transparent), Shader.TileMode.MIRROR);
		}
		else if (direction == LINEAR_GRADIENT_DIRECTION_SOUTH)
		{
			shadowShader = new LinearGradient(rect.left, rect.top, rect.left, rect.bottom, getResources().getColor(R.color.grid_background_gradient_start_color), getResources().getColor(R.color.transparent), Shader.TileMode.MIRROR);
		}
		mShadowPaint.setShader(shadowShader);
		canvas.drawRect(rect.left, rect.top, rect.right, rect.bottom, mShadowPaint); 
	}
	
	/**
	 Draw an radial gradient with the given direction
	 in the given rect.  Refer direction values at the top of this file.
	 Outward means from dark to clear.  Inward means from clear to dark.
	 **/
	private void drawRadialGradient(Canvas canvas, Rect rect, int direction, boolean isOutward)
	{
		int rectW = rect.right - rect.left;
		int rectH = rect.bottom - rect.top;
		
		Shader cornerShader = null;
		if (direction == RADIAL_GRADIENT_DIRECTION_SOUTH_WEST)
		{
			cornerShader = new RadialGradient(rect.right, rect.top, SHADOW_THICKNESS, getResources().getColor(R.color.grid_background_gradient_start_color), getResources().getColor(R.color.transparent), Shader.TileMode.MIRROR);
			mShadowPaint.setShader(cornerShader);
			RectF rectF = new RectF(rect.left, rect.top - rectH, rect.right + rectW, rect.bottom);
			canvas.drawArc(rectF, 90, 90, true, mShadowPaint);
		}
		else if (direction == RADIAL_GRADIENT_DIRECTION_SOUTH_EAST)
		{
			cornerShader = new RadialGradient(rect.left, rect.top, SHADOW_THICKNESS, getResources().getColor(R.color.grid_background_gradient_start_color), getResources().getColor(R.color.transparent), Shader.TileMode.MIRROR);
			mShadowPaint.setShader(cornerShader);
			RectF rectF = new RectF(rect.left - rectW, rect.top - rectH, rect.right, rect.bottom);
			canvas.drawArc(rectF, 0, 90, true, mShadowPaint);
		}
		else if (direction == RADIAL_GRADIENT_DIRECTION_NORTH_WEST)
		{
			cornerShader = new RadialGradient(rect.right, rect.bottom, SHADOW_THICKNESS, getResources().getColor(R.color.grid_background_gradient_start_color), getResources().getColor(R.color.transparent), Shader.TileMode.MIRROR);
			mShadowPaint.setShader(cornerShader);
			RectF rectF = new RectF(rect.left, rect.top, rect.right + rectW, rect.bottom + rectH);
			canvas.drawArc(rectF, 180, 90, true, mShadowPaint);
		}
		else if (direction == RADIAL_GRADIENT_DIRECTION_NORTH_EAST)
		{
			cornerShader = new RadialGradient(rect.left, rect.bottom, SHADOW_THICKNESS, getResources().getColor(R.color.grid_background_gradient_start_color), getResources().getColor(R.color.transparent), Shader.TileMode.MIRROR);
			mShadowPaint.setShader(cornerShader);
			RectF rectF = new RectF(rect.left - rectW, rect.top, rect.right, rect.bottom + rectH);
			canvas.drawArc(rectF, 270, 90, true, mShadowPaint);
		}
	}
	
	private void drawStar(Canvas canvas, int cellSize, int hOffset, int vOffset, int x, int y)
	{
		int left = hOffset + y * cellSize;
		int top = vOffset + x * cellSize;
		int right = left + cellSize;
		int bottom = top + cellSize;
		
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
		canvas.drawPath(mStarPath, mStartStrokePaint);
		canvas.restore();
		
	}
	
	public void initializeGameData(int [][]grid, int size, int[][] startPos, int numStartPos, int maxMoves)
	{
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
	
	public void setTapHandler(GameViewTapHandler handler)
	{
		mTapHandler = handler;
	}
	
	public interface GameViewTapHandler
	{
		public void handleGameViewTap(int x, int y);
	}
	
	class MyGestureListener extends GestureDetector.SimpleOnGestureListener 
	{        
		@Override
		public boolean onDown(MotionEvent event)
		{
			return true;
		}
		
        @Override
        public boolean onSingleTapConfirmed(MotionEvent event) 
        {     		
    			int x = (int) event.getX();
    			int y = (int) event.getY();
    			
    			int screenWidth = getWidth();
    			int screenHeight = getHeight();
    			
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
    			
    			int gridSizePixels = Math.min(screenWidth, screenHeight) - SHADOW_THICKNESS;
    			int cellSize = gridSizePixels/mGridSize;
    			
    			int xOffset = x - hOffset;
    			int yOffset = y - vOffset;
    			
    			int gridy = xOffset / cellSize;
    			int gridx = yOffset / cellSize;
    			
    			mTapHandler.handleGameViewTap(gridx, gridy);
    			return true;
    		
    		
        }
    }

	private GestureDetectorCompat mDetector; 
	private GameViewTapHandler mTapHandler;
	private Paint mStartPaint, mBorderPaint1, mBorderPaint2, mFillPaint, mTestPaint, mStartStrokePaint, mShadowPaint;
	private Path mStarPath;
}
