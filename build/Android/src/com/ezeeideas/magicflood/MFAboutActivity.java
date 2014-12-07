package com.ezeeideas.magicflood;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.ViewFlipper;

public class MFAboutActivity extends Activity
{
	@Override
    protected void onCreate(Bundle savedInstanceState) 
	{
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_about);
	}
	
    @Override
    public void onDestroy() 
    {
        super.onDestroy(); 
    }
}