package com.ezeeideas.magicflood;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.AnimationUtils;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ViewFlipper;

public class MFViewFlipperActivity extends Activity implements AnimationListener
{
    protected void onCreate(Bundle savedInstanceState, int rootLayoutId) 
	{
        super.onCreate(savedInstanceState);
        setContentView(rootLayoutId);
        
        mViewFlipper = (ViewFlipper) findViewById(R.id.view_flipper_id);
	}
        
	@Override
	public void onAnimationEnd(Animation arg0) 
	{
		int childIndex = mViewFlipper.getDisplayedChild();
		
		LinearLayout indicatorRowLayout = (LinearLayout) findViewById(R.id.indicator_row_layout_id);
		
		int numChildren = mViewFlipper.getChildCount();
	
		for (int i = 0; i < numChildren; i++)
		{
			ImageView indicatorView = (ImageView) indicatorRowLayout.findViewById(i);
			if (childIndex == i)
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
	public void onAnimationRepeat(Animation arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onAnimationStart(Animation arg0) {
		// TODO Auto-generated method stub
		
	}
	
	@Override
	public boolean dispatchTouchEvent(MotionEvent touchevent) 
	{
		Log.d("gaurav", "dispatchTouchEvent called for Activity");
		switch (touchevent.getAction())
    	{
    	// when user first touches the screen to swap
    	case MotionEvent.ACTION_DOWN: 
    	{
    		Log.d("gaurav", "dispatchTouchEvent, ACTION_DOWN");
    		lastX = touchevent.getX();
    		break;
    	}
    	case MotionEvent.ACTION_UP: 
    	{
    		float currentX = touchevent.getX();
    		Log.d("gaurav", "dispatchTouchEvent, lastX = " + lastX + ", currentX = " + currentX);

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
	    			Log.d("gaurav", "set the animation listener 1");
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
	    			Log.d("gaurav", "set the animation listener 2");
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

	/*
	@Override
	public boolean onTouch(View v, MotionEvent touchevent) 
	{
		Log.d("gaurav", "onTouch, action = " + touchevent.getAction());
    	switch (touchevent.getAction())
    	{
    	// when user first touches the screen to swap
    	case MotionEvent.ACTION_DOWN: 
    	{
    		Log.d("gaurav", "onTouchEvent, ACTION_DOWN");
    		lastX = touchevent.getX();
    		break;
    	}
    	case MotionEvent.ACTION_UP: 
    	{
    		float currentX = touchevent.getX();
    		Log.d("gaurav", "onTouchEvent, lastX = " + lastX + ", currentX = " + currentX);

    		// if left to right swipe on screen
    		if (lastX < currentX && (currentX - lastX) > SWIPE_DISPLACEMENT_THRESHOLD) 
    		{
    			// set the required Animation type to ViewFlipper
    			// The Next screen will come in form Left and current Screen will go OUT from Right 
    			Animation inFromLeftAnimation = AnimationUtils.loadAnimation(this, R.anim.in_from_left);
    			inFromLeftAnimation.setAnimationListener(this);
    			mViewFlipper.setInAnimation(inFromLeftAnimation);

    			Animation outToRightAnimation = AnimationUtils.loadAnimation(this, R.anim.out_to_right);
    			outToRightAnimation.setAnimationListener(this);
    			Log.d("gaurav", "set the animation listener 1");
    			mViewFlipper.setOutAnimation(outToRightAnimation);

    			// Show the previous Screen
    			mViewFlipper.showPrevious();
    			
    			return true;
    		}

    		// if right to left swipe on screen
    		else if (lastX > currentX && (lastX - currentX) > SWIPE_DISPLACEMENT_THRESHOLD)
    		{
    			
    			// set the required Animation type to ViewFlipper
    			// The Next screen will come in form Right and current Screen will go OUT from Left 
    			Animation inFromLeftAnimation = AnimationUtils.loadAnimation(this, R.anim.in_from_right);
    			inFromLeftAnimation.setAnimationListener(this);
    			mViewFlipper.setInAnimation(inFromLeftAnimation);

    			Animation outToRightAnimation = AnimationUtils.loadAnimation(this, R.anim.out_to_left);
    			outToRightAnimation.setAnimationListener(this);
    			Log.d("gaurav", "set the animation listener 2");
    			mViewFlipper.setOutAnimation(outToRightAnimation);


    			// Show The next Screen
    			mViewFlipper.showNext();
    			
    			return true;
    		}

    		break;
    	}
    	}
    	return true;
	}
	*/
	
	private ViewFlipper mViewFlipper;
	private float lastX;
	
	private static final int SWIPE_DISPLACEMENT_THRESHOLD = 10; //no. of pixels to displace, to recognize a "swipe" gesture
}