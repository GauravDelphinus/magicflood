package com.ezeeideas.magicflood;

import android.os.Bundle;

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