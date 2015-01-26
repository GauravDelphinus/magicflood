package com.ezeeideas.magicflood;

import android.app.Activity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.ViewGroup.LayoutParams;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.AnimationUtils;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ViewFlipper;

public abstract class MFViewFlipperActivity extends Activity implements AnimationListener
{
    protected void onCreate(Bundle savedInstanceState, int rootLayoutId) 
	{
        super.onCreate(savedInstanceState);
        setContentView(rootLayoutId);
        
        mViewFlipper = getViewFlipper();
        setupViewFlipper();
        
        mIndicatorLayout = getIndicatorLayout();
        int startScreen = getStartScreen();
        setupIndicatorLayout(startScreen);
	}
    
    /**
     * Add the children, etc. in the ViewFlipper
     */
    protected abstract void setupViewFlipper();
    
    /**
     * returns the ViewFlipper object
     */
    protected abstract ViewFlipper getViewFlipper();
    
    /**
     * returns a LinearLayout that contains the indicator view (usually at the bottom
     * of the screen with horizontal orientation)
     * @return
     */
    protected abstract LinearLayout getIndicatorLayout();
    
    /**
     * Returns the number of screens controlled by the view flipper
     * @return
     */
    protected abstract int getNumScreens();
    
    /**
     * Return the starting screen index.
     * @return
     */
    protected abstract int getStartScreen();
    
    private void setupIndicatorLayout(int startScreen)
    {
    	 /**
         * Add the indicator image (circle) for each screen
         */
    	for (int i = 0; i < mNumScreens; i++)
    	{
	        ImageView indicatorView = new ImageView(this);
	        if (i == startScreen)
	        {
	        	indicatorView.setImageResource(R.drawable.ic_viewflipper_indicator_selected);
	        }
	        else
	        {
	        	indicatorView.setImageResource(R.drawable.ic_viewflipper_indicator_unselected);
	        }
	        
	        LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
	        params.setMargins(10, 0, 10, 0);
	        indicatorView.setLayoutParams(params);
	        indicatorView.setId(i);
	        mIndicatorLayout.addView(indicatorView);
    	}
    }
    
    private void updateIndicatorLayout(int selectedScreen)
    {
    	for (int i = 0; i < mNumScreens; i++)
		{
			ImageView indicatorView = (ImageView) mIndicatorLayout.findViewById(i);
			if (selectedScreen == i)
			{
				indicatorView.setImageResource(R.drawable.ic_viewflipper_indicator_selected);
			}
			else
			{
				indicatorView.setImageResource(R.drawable.ic_viewflipper_indicator_unselected);
			}
		}
    }
    
	@Override
	public void onAnimationEnd(Animation arg0) 
	{		
		updateIndicatorLayout(mViewFlipper.getDisplayedChild());
	}

	@Override
	public void onAnimationRepeat(Animation arg0) 
	{
	}

	@Override
	public void onAnimationStart(Animation arg0) 
	{
	}
	
	@Override
	public boolean dispatchTouchEvent(MotionEvent touchevent) 
	{
		switch (touchevent.getAction())
    	{
    	// when user first touches the screen to swap
    	case MotionEvent.ACTION_DOWN: 
    	{
    		lastX = touchevent.getX();
    		break;
    	}
    	case MotionEvent.ACTION_UP: 
    	{
    		float currentX = touchevent.getX();

    		// if left to right swipe on screen
    		if (lastX < currentX && (currentX - lastX) > SWIPE_DISPLACEMENT_THRESHOLD) 
    		{
    			if (mViewFlipper.getDisplayedChild() > 0)
    			{
	    			// set the required Animation type to ViewFlipper
	    			// The Next screen will come in form Left and current Screen will go OUT from Right 
	    			Animation inFromLeftAnimation = AnimationUtils.loadAnimation(this, R.anim.in_from_left);
	    			inFromLeftAnimation.setAnimationListener(this);
	    			mViewFlipper.setInAnimation(inFromLeftAnimation);
	
	    			Animation outToRightAnimation = AnimationUtils.loadAnimation(this, R.anim.out_to_right);
	    			outToRightAnimation.setAnimationListener(this);
	    			mViewFlipper.setOutAnimation(outToRightAnimation);
	
	    			// Show the previous Screen
	    			mViewFlipper.showPrevious();
    			}
    			
    			return true;
    		}

    		// if right to left swipe on screen
    		else if (lastX > currentX && (lastX - currentX) > SWIPE_DISPLACEMENT_THRESHOLD)
    		{
    			if (mViewFlipper.getDisplayedChild() < (mViewFlipper.getChildCount() - 1))
    			{
	    			// set the required Animation type to ViewFlipper
	    			// The Next screen will come in form Right and current Screen will go OUT from Left 
	    			Animation inFromLeftAnimation = AnimationUtils.loadAnimation(this, R.anim.in_from_right);
	    			inFromLeftAnimation.setAnimationListener(this);
	    			mViewFlipper.setInAnimation(inFromLeftAnimation);
	
	    			Animation outToRightAnimation = AnimationUtils.loadAnimation(this, R.anim.out_to_left);
	    			outToRightAnimation.setAnimationListener(this);
	    			mViewFlipper.setOutAnimation(outToRightAnimation);
	
	
	    			// Show The next Screen
	    			mViewFlipper.showNext();
    			}
    			return true;
    		}

    		break;
    	}
    	}
		return super.dispatchTouchEvent(touchevent);
	}
	
	protected ViewFlipper mViewFlipper;
	protected LinearLayout mIndicatorLayout; //LinearLayout at the bottom of hte screen that contains the indicator images
	protected int mNumScreens;
	private float lastX;
	
	private static final int SWIPE_DISPLACEMENT_THRESHOLD = 10; //no. of pixels to displace, to recognize a "swipe" gesture
}