package com.ezeeideas.magicflood;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ViewFlipper;

public class MFHelpActivity extends MFViewFlipperActivity
{
	@Override
    protected void onCreate(Bundle savedInstanceState) 
	{
        super.onCreate(savedInstanceState, R.layout.activity_help);
	}
	
    @Override
    public void onDestroy() 
    {
        super.onDestroy(); 
    }
}