package com.ezeeideas.magicflood;

import com.ezeeideas.magicflood.iabutil.IabHelper;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.AnimationUtils;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ViewFlipper;

public class MFStoreActivity extends Activity implements MFInAppPurchaseManager.IAPPurchaseInterface, View.OnClickListener, AnimationListener
{
	@Override
    protected void onCreate(Bundle savedInstanceState) 
	{
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_store);
        
        mIAPManager = new MFInAppPurchaseManager(this);
        mIAPManager.addPurchaseListener(this);
        
        mViewFlipper = (ViewFlipper) findViewById(R.id.view_flipper_id);
        
        mFirstChildIndicatorView = (ImageView) findViewById(R.id.viewflipper_child1_indicator_id);
        mSecondChildIndicatorView = (ImageView) findViewById(R.id.viewflipper_child2_indicator_id);
        mThirdChildIndicatorView = (ImageView) findViewById(R.id.viewflipper_child3_indicator_id);
        
        String detailsArray[];
        boolean isProvisioned = false;
        MFInAppProductLayout iapLayout;
        
        //First Free Product
        iapLayout = (MFInAppProductLayout) findViewById(R.id.alacarte_layout_1_id);
        iapLayout.setProperties(getResources().getString(R.string.free_product_detail_string), getResources().getString(R.string.free_product_price_string), true);
        iapLayout.setEnabled(false);
        
        //Second Free Product
        iapLayout = (MFInAppProductLayout) findViewById(R.id.alacarte_layout_2_id);
        iapLayout.setProperties(getResources().getString(R.string.free_product_detail_string), getResources().getString(R.string.free_product_price_string), true);
        iapLayout.setEnabled(false);
        
        //Third Free Product
        iapLayout = (MFInAppProductLayout) findViewById(R.id.alacarte_layout_3_id);
        iapLayout.setProperties(getResources().getString(R.string.free_product_detail_string), getResources().getString(R.string.free_product_price_string), true);
        iapLayout.setEnabled(false);
        
        //IAP 1
        detailsArray = mIAPManager.getProductDetails(MFGameConstants.IAP_ALACARTE_HURDLE_1);
        isProvisioned = mIAPManager.getProductProvisioned(MFGameConstants.IAP_ALACARTE_HURDLE_1);
        iapLayout = (MFInAppProductLayout) findViewById(R.id.alacarte_layout_4_id);
        iapLayout.setProperties(detailsArray[0], detailsArray[2], isProvisioned);
        iapLayout.setEnabled(!isProvisioned);
        iapLayout.setOnClickListener(this);
     
        //IAP 2
        detailsArray = mIAPManager.getProductDetails(MFGameConstants.IAP_ALACARTE_HURDLE_2);
        isProvisioned = mIAPManager.getProductProvisioned(MFGameConstants.IAP_ALACARTE_HURDLE_2);
        iapLayout = (MFInAppProductLayout) findViewById(R.id.alacarte_layout_5_id);
        iapLayout.setProperties(detailsArray[0], detailsArray[2], isProvisioned);
        iapLayout.setEnabled(!isProvisioned);
        iapLayout.setOnClickListener(this);
        
        //IAP 3
        detailsArray = mIAPManager.getProductDetails(MFGameConstants.IAP_ALACARTE_HURDLE_3);
        isProvisioned = mIAPManager.getProductProvisioned(MFGameConstants.IAP_ALACARTE_HURDLE_3);
        iapLayout = (MFInAppProductLayout) findViewById(R.id.alacarte_layout_6_id);
        iapLayout.setProperties(detailsArray[0], detailsArray[2], isProvisioned);
        iapLayout.setEnabled(!isProvisioned);
        iapLayout.setOnClickListener(this);
        
        //IAP 4
        detailsArray = mIAPManager.getProductDetails(MFGameConstants.IAP_ALACARTE_HURDLE_4);
        isProvisioned = mIAPManager.getProductProvisioned(MFGameConstants.IAP_ALACARTE_HURDLE_4);
        iapLayout = (MFInAppProductLayout) findViewById(R.id.alacarte_layout_7_id);
        iapLayout.setProperties(detailsArray[0], detailsArray[2], isProvisioned);
        iapLayout.setEnabled(!isProvisioned);
        iapLayout.setOnClickListener(this);
     
        //IAP 5
        detailsArray = mIAPManager.getProductDetails(MFGameConstants.IAP_ALACARTE_HURDLE_5);
        isProvisioned = mIAPManager.getProductProvisioned(MFGameConstants.IAP_ALACARTE_HURDLE_5);
        iapLayout = (MFInAppProductLayout) findViewById(R.id.alacarte_layout_8_id);
        iapLayout.setProperties(detailsArray[0], detailsArray[2], isProvisioned);
        iapLayout.setEnabled(!isProvisioned);
        iapLayout.setOnClickListener(this);
        
        //IAP 6
        detailsArray = mIAPManager.getProductDetails(MFGameConstants.IAP_ALACARTE_HURDLE_6);
        isProvisioned = mIAPManager.getProductProvisioned(MFGameConstants.IAP_ALACARTE_HURDLE_6);
        iapLayout = (MFInAppProductLayout) findViewById(R.id.alacarte_layout_9_id);
        iapLayout.setProperties(detailsArray[0], detailsArray[2], isProvisioned);
        iapLayout.setEnabled(!isProvisioned);
        iapLayout.setOnClickListener(this);
        
        //Combo 1
        detailsArray = mIAPManager.getProductDetails(MFGameConstants.IAP_COMBO_HURDLES_1);
        isProvisioned = mIAPManager.getProductProvisioned(MFGameConstants.IAP_COMBO_HURDLES_1);
        iapLayout = (MFInAppProductLayout) findViewById(R.id.combo_layout_1_id);
        iapLayout.setProperties(detailsArray[0], detailsArray[2], isProvisioned);
        iapLayout.setEnabled(!isProvisioned);
        iapLayout.setOnClickListener(this);
        
        //Combo 2
        detailsArray = mIAPManager.getProductDetails(MFGameConstants.IAP_COMBO_HURDLES_2);
        isProvisioned = mIAPManager.getProductProvisioned(MFGameConstants.IAP_COMBO_HURDLES_2);
        iapLayout = (MFInAppProductLayout) findViewById(R.id.combo_layout_2_id);
        iapLayout.setProperties(detailsArray[0], detailsArray[2], isProvisioned);
        iapLayout.setEnabled(!isProvisioned);
        iapLayout.setOnClickListener(this);
        
        //Combo 3
        detailsArray = mIAPManager.getProductDetails(MFGameConstants.IAP_COMBO_HURDLES_3);
        isProvisioned = mIAPManager.getProductProvisioned(MFGameConstants.IAP_COMBO_HURDLES_3);
        iapLayout = (MFInAppProductLayout) findViewById(R.id.combo_layout_3_id);
        iapLayout.setProperties(detailsArray[0], detailsArray[2], isProvisioned);
        iapLayout.setEnabled(!isProvisioned);
        iapLayout.setOnClickListener(this);
        
        //Combo 4
        detailsArray = mIAPManager.getProductDetails(MFGameConstants.IAP_COMBO_HURDLES_4);
        isProvisioned = mIAPManager.getProductProvisioned(MFGameConstants.IAP_COMBO_HURDLES_4);
        iapLayout = (MFInAppProductLayout) findViewById(R.id.combo_layout_4_id);
        iapLayout.setProperties(detailsArray[0], detailsArray[2], isProvisioned);
        iapLayout.setEnabled(!isProvisioned);
        iapLayout.setOnClickListener(this);
	}
	
    @Override
    public void onDestroy() 
    {
        super.onDestroy();
        
        //Unbind the service manager for IAP
        if (mIAPManager != null)
        {
            mIAPManager.unbind();
        }   
    }
	
    
	// Method to handle touch event like left to right swap and right to left swap
    public boolean onTouchEvent(MotionEvent touchevent) 
    {
    	Log.d("gaurav", "onTouchEvent");
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
    		Log.d("gaurav", "onTouchEvent, lastX = " + lastX + ", currentX = " + currentX);

    		// if left to right swipe on screen
    		if (lastX < currentX && (currentX - lastX) > SWIPE_DISPLACEMENT_THRESHOLD) 
    		{
    			// If no more View/Child to flip
    			if (mViewFlipper.getDisplayedChild() == 0)
    				break;

    			// set the required Animation type to ViewFlipper
    			// The Next screen will come in form Left and current Screen will go OUT from Right 
    			Animation inFromLeftAnimation = AnimationUtils.loadAnimation(this, R.anim.in_from_left);
    			inFromLeftAnimation.setAnimationListener(this);
    			mViewFlipper.setInAnimation(inFromLeftAnimation);

    			Animation outToRightAnimation = AnimationUtils.loadAnimation(this, R.anim.out_to_right);
    			outToRightAnimation.setAnimationListener(this);
    			Log.d("gaurav", "set the animation listener 1");
    			mViewFlipper.setOutAnimation(outToRightAnimation);

    			//mViewFlipper.setInAnimation(this, R.anim.in_from_left);
    			//mViewFlipper.setOutAnimation(this, R.anim.out_to_right);
    			// Show the next Screen
    			mViewFlipper.showNext();
    		}

    		// if right to left swipe on screen
    		if (lastX > currentX && (lastX - currentX) > SWIPE_DISPLACEMENT_THRESHOLD)
    		{
    			if (mViewFlipper.getDisplayedChild() == 1)
    				break;
    			// set the required Animation type to ViewFlipper
    			// The Next screen will come in form Right and current Screen will go OUT from Left 
    			Animation inFromLeftAnimation = AnimationUtils.loadAnimation(this, R.anim.in_from_right);
    			inFromLeftAnimation.setAnimationListener(this);
    			mViewFlipper.setInAnimation(inFromLeftAnimation);

    			Animation outToRightAnimation = AnimationUtils.loadAnimation(this, R.anim.out_to_left);
    			outToRightAnimation.setAnimationListener(this);
    			Log.d("gaurav", "set the animation listener 2");
    			mViewFlipper.setOutAnimation(outToRightAnimation);

    			//mViewFlipper.setInAnimation(this, R.anim.in_from_right);
    			//mViewFlipper.setOutAnimation(this, R.anim.out_to_left);
    			// Show The Previous Screen
    			mViewFlipper.showPrevious();
    		}
    		break;
    	}
    	}
    	return false;
    }
    
	@Override
	public void onPurchaseFinished(String pid, boolean status) 
	{
		Log.d("gaurav", "onPurchaseFinished, pid [" + pid + "], status [" + status + "]");
		int buttonID = 0;
		
		if (pid.equals(MFGameConstants.IAP_ALACARTE_HURDLE_1))
		{
			buttonID = R.id.alacarte_layout_4_id;
		}
		else if (pid.equals(MFGameConstants.IAP_ALACARTE_HURDLE_2))
		{
			buttonID = R.id.alacarte_layout_5_id;
		}
		else if (pid.equals(MFGameConstants.IAP_ALACARTE_HURDLE_3))
		{
			buttonID = R.id.alacarte_layout_6_id;
		}
		else if (pid.equals(MFGameConstants.IAP_ALACARTE_HURDLE_4))
		{
			buttonID = R.id.alacarte_layout_7_id;
		}
		else if (pid.equals(MFGameConstants.IAP_ALACARTE_HURDLE_5))
		{
			buttonID = R.id.alacarte_layout_8_id;
		}
		else if (pid.equals(MFGameConstants.IAP_ALACARTE_HURDLE_6))
		{
			buttonID = R.id.alacarte_layout_9_id;
		}
		else if (pid.equals(MFGameConstants.IAP_COMBO_HURDLES_1))
		{
			buttonID = R.id.combo_layout_1_id;
		}
		else if (pid.equals(MFGameConstants.IAP_COMBO_HURDLES_2))
		{
			buttonID = R.id.combo_layout_2_id;
		}
		else if (pid.equals(MFGameConstants.IAP_COMBO_HURDLES_3))
		{
			buttonID = R.id.combo_layout_3_id;
		}
		else if (pid.equals(MFGameConstants.IAP_COMBO_HURDLES_4))
		{
			buttonID = R.id.combo_layout_4_id;
		}

		LinearLayout button = (LinearLayout) findViewById(buttonID);
		if (status == true)
		{
			button.setEnabled(false);
		}
		else
		{
			button.setEnabled(true);
		}
	}

	@Override
	public void onClick(View v) 
	{
		String pid = null;
		switch (v.getId())
		{
		case R.id.alacarte_layout_4_id:
			pid = MFGameConstants.IAP_ALACARTE_HURDLE_1;
			break;
		case R.id.alacarte_layout_5_id:
			pid = MFGameConstants.IAP_ALACARTE_HURDLE_2;
			break;
		case R.id.alacarte_layout_6_id:
			pid = MFGameConstants.IAP_ALACARTE_HURDLE_3;
			break;
		case R.id.alacarte_layout_7_id:
			pid = MFGameConstants.IAP_ALACARTE_HURDLE_4;
			break;
		case R.id.alacarte_layout_8_id:
			pid = MFGameConstants.IAP_ALACARTE_HURDLE_5;
			break;
		case R.id.alacarte_layout_9_id:
			pid = MFGameConstants.IAP_ALACARTE_HURDLE_6;
			break;
		case R.id.combo_layout_1_id:
			pid = MFGameConstants.IAP_COMBO_HURDLES_1;
			break;
		case R.id.combo_layout_2_id:
			pid = MFGameConstants.IAP_COMBO_HURDLES_2;
			break;
		case R.id.combo_layout_3_id:
			pid = MFGameConstants.IAP_COMBO_HURDLES_3;
			break;
		case R.id.combo_layout_4_id:
			pid = MFGameConstants.IAP_COMBO_HURDLES_4;
			break;
		}
		
		mIAPManager.purchaseItem(pid);
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) 
	{
		Log.d("gaurav", "onActivityResult(" + requestCode + "," + resultCode + "," + data);

		// Pass on the activity result to the helper for handling
		if (!mIAPManager.handleActivityResult(requestCode, resultCode, data)) {
			// not handled, so handle it ourselves (here's where you'd
			// perform any handling of activity results not related to in-app
			// billing...
			super.onActivityResult(requestCode, resultCode, data);
		}
		else {
			Log.d("gaurav", "onActivityResult handled by IABUtil.");
		}
	}

	@Override
	public void onAnimationEnd(Animation arg0) 
	{
		
		int childIndex = mViewFlipper.getDisplayedChild();
		Log.d("gaurav", "onAnimationEnd, childIndex = " + childIndex);
		if (childIndex == 0)
		{
			mFirstChildIndicatorView.setImageResource(R.drawable.ic_viewflipper_indicator_selected);
			mSecondChildIndicatorView.setImageResource(R.drawable.ic_viewflipper_indicator_unselected);
			mThirdChildIndicatorView.setImageResource(R.drawable.ic_viewflipper_indicator_unselected);
		}
		else if (childIndex == 1)
		{
			mFirstChildIndicatorView.setImageResource(R.drawable.ic_viewflipper_indicator_unselected);
			mSecondChildIndicatorView.setImageResource(R.drawable.ic_viewflipper_indicator_selected);
			mThirdChildIndicatorView.setImageResource(R.drawable.ic_viewflipper_indicator_unselected);
		}
		else if (childIndex == 2)
		{
			mFirstChildIndicatorView.setImageResource(R.drawable.ic_viewflipper_indicator_unselected);
			mSecondChildIndicatorView.setImageResource(R.drawable.ic_viewflipper_indicator_unselected);
			mThirdChildIndicatorView.setImageResource(R.drawable.ic_viewflipper_indicator_selected);
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
	
	private ViewFlipper mViewFlipper;
	private float lastX;
	MFInAppPurchaseManager mIAPManager = null;
	private static final int SWIPE_DISPLACEMENT_THRESHOLD = 10; //no. of pixels to displace, to recognize a "swipe" gesture
	
	private ImageView mFirstChildIndicatorView, mSecondChildIndicatorView, mThirdChildIndicatorView;

}