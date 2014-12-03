package com.ezeeideas.magicflood;

import com.ezeeideas.magicflood.iabutil.IabHelper;

import android.app.Activity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.ViewFlipper;

public class MFStoreActivity extends Activity implements MFInAppPurchaseManager.IAPPurchaseInterface, View.OnClickListener
{
	@Override
    protected void onCreate(Bundle savedInstanceState) 
	{
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_store);
        
        mIAPManager = new MFInAppPurchaseManager(this);
        mIAPManager.addPurchaseListener(this);
        
        mViewFlipper = (ViewFlipper) findViewById(R.id.view_flipper_id);
        
        Button alacarte1Button = (Button) findViewById(R.id.alacarte_button_1_id);
        String detailsArray[] = mIAPManager.getProductDetails(MFGameConstants.IAP_ALACARTE_HURDLE_1);
        boolean isProvisioned = mIAPManager.getProductProvisioned(MFGameConstants.IAP_ALACARTE_HURDLE_1);
        alacarte1Button.setText("Name: [" + detailsArray[0] + "], Description: [" + detailsArray[1] + "], Price: [" + detailsArray[2]
        		+ "], Currency Code: [" + detailsArray[3] + "], Status: [" + isProvisioned + "]");
        alacarte1Button.setOnClickListener(this);
        alacarte1Button.setEnabled(!isProvisioned);
        
        Button alacarte2Button = (Button) findViewById(R.id.alacarte_button_2_id);
        detailsArray = mIAPManager.getProductDetails(MFGameConstants.IAP_ALACARTE_HURDLE_2);
        isProvisioned = mIAPManager.getProductProvisioned(MFGameConstants.IAP_ALACARTE_HURDLE_2);
        alacarte2Button.setText("Name: [" + detailsArray[0] + "], Description: [" + detailsArray[1] + "], Price: [" + detailsArray[2]
        		+ "], Currency Code: [" + detailsArray[3] + "], Status: [" + isProvisioned + "]");
        alacarte2Button.setOnClickListener(this);
        alacarte2Button.setEnabled(!isProvisioned);
        
        Button alacarte3Button = (Button) findViewById(R.id.alacarte_button_3_id);
        detailsArray = mIAPManager.getProductDetails(MFGameConstants.IAP_ALACARTE_HURDLE_3);
        isProvisioned = mIAPManager.getProductProvisioned(MFGameConstants.IAP_ALACARTE_HURDLE_3);
        alacarte3Button.setText("Name: [" + detailsArray[0] + "], Description: [" + detailsArray[1] + "], Price: [" + detailsArray[2]
        		+ "], Currency Code: [" + detailsArray[3] + "], Status: [" + isProvisioned + "]");
        alacarte3Button.setOnClickListener(this);
        alacarte3Button.setEnabled(!isProvisioned);
        
        Button alacarte4Button = (Button) findViewById(R.id.alacarte_button_4_id);
        detailsArray = mIAPManager.getProductDetails(MFGameConstants.IAP_ALACARTE_HURDLE_4);
        isProvisioned = mIAPManager.getProductProvisioned(MFGameConstants.IAP_ALACARTE_HURDLE_4);
        alacarte4Button.setText("Name: [" + detailsArray[0] + "], Description: [" + detailsArray[1] + "], Price: [" + detailsArray[2]
        		+ "], Currency Code: [" + detailsArray[3] + "], Status: [" + isProvisioned + "]");
        alacarte4Button.setOnClickListener(this);
        alacarte4Button.setEnabled(!isProvisioned);
        
        Button alacarte5Button = (Button) findViewById(R.id.alacarte_button_5_id);
        detailsArray = mIAPManager.getProductDetails(MFGameConstants.IAP_ALACARTE_HURDLE_5);
        isProvisioned = mIAPManager.getProductProvisioned(MFGameConstants.IAP_ALACARTE_HURDLE_5);
        alacarte5Button.setText("Name: [" + detailsArray[0] + "], Description: [" + detailsArray[1] + "], Price: [" + detailsArray[2]
        		+ "], Currency Code: [" + detailsArray[3] + "], Status: [" + isProvisioned + "]");
        alacarte5Button.setOnClickListener(this);
        alacarte5Button.setEnabled(!isProvisioned);
        
        Button alacarte6Button = (Button) findViewById(R.id.alacarte_button_6_id);
        detailsArray = mIAPManager.getProductDetails(MFGameConstants.IAP_ALACARTE_HURDLE_6);
        isProvisioned = mIAPManager.getProductProvisioned(MFGameConstants.IAP_ALACARTE_HURDLE_6);
        alacarte6Button.setText("Name: [" + detailsArray[0] + "], Description: [" + detailsArray[1] + "], Price: [" + detailsArray[2]
        		+ "], Currency Code: [" + detailsArray[3] + "], Status: [" + isProvisioned + "]");
        alacarte6Button.setOnClickListener(this);
        alacarte6Button.setEnabled(!isProvisioned);
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
	
    /*
	// Method to handle touch event like left to right swap and right to left swap
    public boolean onTouchEvent(MotionEvent touchevent) 
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
                             if (lastX < currentX) 
                             {
                                  // If no more View/Child to flip
                                 if (mViewFlipper.getDisplayedChild() == 0)
                                     break;
                                 
                                 // set the required Animation type to ViewFlipper
                                 // The Next screen will come in form Left and current Screen will go OUT from Right 
                                 mViewFlipper.setInAnimation(this, R.anim.in_from_left);
                                 mViewFlipper.setOutAnimation(this, R.anim.out_to_right);
                                 // Show the next Screen
                                 mViewFlipper.showNext();
                             }
                             
                             // if right to left swipe on screen
                             if (lastX > currentX)
                             {
                                 if (mViewFlipper.getDisplayedChild() == 1)
                                     break;
                                 // set the required Animation type to ViewFlipper
                                 // The Next screen will come in form Right and current Screen will go OUT from Left 
                                 mViewFlipper.setInAnimation(this, R.anim.in_from_right);
                                 mViewFlipper.setOutAnimation(this, R.anim.out_to_left);
                                 // Show The Previous Screen
                                 mViewFlipper.showPrevious();
                             }
                             break;
                         }
                 }
                 return false;
    }
    */
    
	private ViewFlipper mViewFlipper;
	private float lastX;
	MFInAppPurchaseManager mIAPManager = null;
	
	@Override
	public void onPurchaseFinished(String pid, boolean status) 
	{
		int buttonID = 0;
		if (pid.equals(MFGameConstants.IAP_ALACARTE_HURDLE_1))
		{
			buttonID = R.id.alacarte_button_1_id;
		}
		else if (pid.equals(MFGameConstants.IAP_ALACARTE_HURDLE_2))
		{
			buttonID = R.id.alacarte_button_2_id;
		}
		else if (pid.equals(MFGameConstants.IAP_ALACARTE_HURDLE_3))
		{
			buttonID = R.id.alacarte_button_3_id;
		}
		else if (pid.equals(MFGameConstants.IAP_ALACARTE_HURDLE_4))
		{
			buttonID = R.id.alacarte_button_4_id;
		}
		else if (pid.equals(MFGameConstants.IAP_ALACARTE_HURDLE_5))
		{
			buttonID = R.id.alacarte_button_5_id;
		}
		else if (pid.equals(MFGameConstants.IAP_ALACARTE_HURDLE_6))
		{
			buttonID = R.id.alacarte_button_6_id;
		}
		else if (pid.equals(MFGameConstants.IAP_COMBO_HURDLES_1))
		{
			buttonID = R.id.combo_button_1_id;
		}
		else if (pid.equals(MFGameConstants.IAP_COMBO_HURDLES_2))
		{
			buttonID = R.id.combo_button_2_id;
		}
		else if (pid.equals(MFGameConstants.IAP_COMBO_HURDLES_3))
		{
			buttonID = R.id.combo_button_3_id;
		}
		else if (pid.equals(MFGameConstants.IAP_COMBO_HURDLES_4))
		{
			buttonID = R.id.combo_button_4_id;
		}
		
		Button button = (Button) findViewById(buttonID);
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
		case R.id.alacarte_button_1_id:
			pid = MFGameConstants.IAP_ALACARTE_HURDLE_1;
			break;
		case R.id.alacarte_button_2_id:
			pid = MFGameConstants.IAP_ALACARTE_HURDLE_2;
			break;
		case R.id.alacarte_button_3_id:
			pid = MFGameConstants.IAP_ALACARTE_HURDLE_3;
			break;
		case R.id.alacarte_button_4_id:
			pid = MFGameConstants.IAP_ALACARTE_HURDLE_4;
			break;
		case R.id.alacarte_button_5_id:
			pid = MFGameConstants.IAP_ALACARTE_HURDLE_5;
			break;
		case R.id.alacarte_button_6_id:
			pid = MFGameConstants.IAP_ALACARTE_HURDLE_6;
			break;
		case R.id.combo_button_1_id:
			pid = MFGameConstants.IAP_COMBO_HURDLES_1;
			break;
		case R.id.combo_button_2_id:
			pid = MFGameConstants.IAP_COMBO_HURDLES_2;
			break;
		case R.id.combo_button_3_id:
			pid = MFGameConstants.IAP_COMBO_HURDLES_3;
			break;
		case R.id.combo_button_4_id:
			pid = MFGameConstants.IAP_COMBO_HURDLES_4;
			break;
		}
		
		mIAPManager.purchaseItem(pid);
	}
}