package com.ezeeideas.magicflood;

import android.os.Bundle;
import android.widget.LinearLayout;
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

	@Override
	protected void setupViewFlipper() 
	{
		
	}

	@Override
	protected ViewFlipper getViewFlipper() 
	{
		return (ViewFlipper) findViewById(R.id.view_flipper_id);
	}

	@Override
	protected LinearLayout getIndicatorLayout() 
	{
		return (LinearLayout) findViewById(R.id.indicator_row_layout_id);
	}

	@Override
	protected int getNumScreens() 
	{
		return 3;
	}

	@Override
	protected int getStartScreen() 
	{
		return 0;
	}
}