package com.ezeeideas.magicflood;

import android.app.Activity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.widget.Button;
import android.widget.ViewFlipper;

public class MFStoreActivity extends Activity
{
	@Override
    protected void onCreate(Bundle savedInstanceState) 
	{
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_store);
        
        mIAPManager = MFInAppPurchaseManager.create();
        
        mViewFlipper = (ViewFlipper) findViewById(R.id.view_flipper_id);
        
        Button alacarte1Button = (Button) findViewById(R.id.alacarte_button_1_id);
        String detailsArray[] = mIAPManager.getProductDetails(MFGameConstants.IAP_ALACARTE_HURDLE_1);
        boolean isProvisioned = mIAPManager.getProductProvisioned(MFGameConstants.IAP_ALACARTE_HURDLE_1);
        alacarte1Button.setText("Name: [" + detailsArray[0] + "], Description: [" + detailsArray[1] + "], Price: [" + detailsArray[2]
        		+ "], Currency Code: [" + detailsArray[3] + "], Status: [" + isProvisioned + "]");
        
        Button alacarte2Button = (Button) findViewById(R.id.alacarte_button_2_id);
        detailsArray = mIAPManager.getProductDetails(MFGameConstants.IAP_ALACARTE_HURDLE_2);
        isProvisioned = mIAPManager.getProductProvisioned(MFGameConstants.IAP_ALACARTE_HURDLE_2);
        alacarte2Button.setText("Name: [" + detailsArray[0] + "], Description: [" + detailsArray[1] + "], Price: [" + detailsArray[2]
        		+ "], Currency Code: [" + detailsArray[3] + "], Status: [" + isProvisioned + "]");
        
        Button alacarte3Button = (Button) findViewById(R.id.alacarte_button_3_id);
        detailsArray = mIAPManager.getProductDetails(MFGameConstants.IAP_ALACARTE_HURDLE_3);
        isProvisioned = mIAPManager.getProductProvisioned(MFGameConstants.IAP_ALACARTE_HURDLE_3);
        alacarte3Button.setText("Name: [" + detailsArray[0] + "], Description: [" + detailsArray[1] + "], Price: [" + detailsArray[2]
        		+ "], Currency Code: [" + detailsArray[3] + "], Status: [" + isProvisioned + "]");
        
        Button alacarte4Button = (Button) findViewById(R.id.alacarte_button_4_id);
        detailsArray = mIAPManager.getProductDetails(MFGameConstants.IAP_ALACARTE_HURDLE_4);
        isProvisioned = mIAPManager.getProductProvisioned(MFGameConstants.IAP_ALACARTE_HURDLE_4);
        alacarte4Button.setText("Name: [" + detailsArray[0] + "], Description: [" + detailsArray[1] + "], Price: [" + detailsArray[2]
        		+ "], Currency Code: [" + detailsArray[3] + "], Status: [" + isProvisioned + "]");
        
        Button alacarte5Button = (Button) findViewById(R.id.alacarte_button_5_id);
        detailsArray = mIAPManager.getProductDetails(MFGameConstants.IAP_ALACARTE_HURDLE_5);
        isProvisioned = mIAPManager.getProductProvisioned(MFGameConstants.IAP_ALACARTE_HURDLE_5);
        alacarte5Button.setText("Name: [" + detailsArray[0] + "], Description: [" + detailsArray[1] + "], Price: [" + detailsArray[2]
        		+ "], Currency Code: [" + detailsArray[3] + "], Status: [" + isProvisioned + "]");
        
        Button alacarte6Button = (Button) findViewById(R.id.alacarte_button_6_id);
        detailsArray = mIAPManager.getProductDetails(MFGameConstants.IAP_ALACARTE_HURDLE_6);
        isProvisioned = mIAPManager.getProductProvisioned(MFGameConstants.IAP_ALACARTE_HURDLE_6);
        alacarte6Button.setText("Name: [" + detailsArray[0] + "], Description: [" + detailsArray[1] + "], Price: [" + detailsArray[2]
        		+ "], Currency Code: [" + detailsArray[3] + "], Status: [" + isProvisioned + "]");
	}
	
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
    
	private ViewFlipper mViewFlipper;
	private float lastX;
	MFInAppPurchaseManager mIAPManager = null;
}