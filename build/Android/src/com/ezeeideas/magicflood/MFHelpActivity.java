package com.ezeeideas.magicflood;

import android.os.Bundle;
import android.widget.LinearLayout;
import android.widget.TextView;
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
		mNumScreens = getNumScreens();
		
		//set up typefaces
		TextView tv = (TextView) findViewById(R.id.help_screen1_title_text_id);
		tv.setTypeface(MFUtils.getTextTypeface(this));
		
		tv = (TextView) findViewById(R.id.help_screen2_title_text_id);
		tv.setTypeface(MFUtils.getTextTypeface(this));
		
		tv = (TextView) findViewById(R.id.help_screen3_title_text_id);
		tv.setTypeface(MFUtils.getTextTypeface(this));
		
		tv = (TextView) findViewById(R.id.help_screen4_title_text_id);
		tv.setTypeface(MFUtils.getTextTypeface(this));
		
		tv = (TextView) findViewById(R.id.help_screen5_title_text_id);
		tv.setTypeface(MFUtils.getTextTypeface(this));
		
		tv = (TextView) findViewById(R.id.help_screen6_title_text_id);
		tv.setTypeface(MFUtils.getTextTypeface(this));
		
		tv = (TextView) findViewById(R.id.help_screen7_title_text_id);
		tv.setTypeface(MFUtils.getTextTypeface(this));
		
		tv = (TextView) findViewById(R.id.help_screen8_title_text_id);
		tv.setTypeface(MFUtils.getTextTypeface(this));
		
		tv = (TextView) findViewById(R.id.help_screen1_description_text_id);
		tv.setTypeface(MFUtils.getTextTypeface(this));
		
		tv = (TextView) findViewById(R.id.help_screen2_description_text_id);
		tv.setTypeface(MFUtils.getTextTypeface(this));
		
		tv = (TextView) findViewById(R.id.help_screen3_description_text_id);
		tv.setTypeface(MFUtils.getTextTypeface(this));
		
		tv = (TextView) findViewById(R.id.help_screen4_description_text_id);
		tv.setTypeface(MFUtils.getTextTypeface(this));
		
		tv = (TextView) findViewById(R.id.help_screen5_description_text_id);
		tv.setTypeface(MFUtils.getTextTypeface(this));
		
		tv = (TextView) findViewById(R.id.help_screen6_description_text_id);
		tv.setTypeface(MFUtils.getTextTypeface(this));
		
		tv = (TextView) findViewById(R.id.help_screen7_description_text_id);
		tv.setTypeface(MFUtils.getTextTypeface(this));
		
		tv = (TextView) findViewById(R.id.help_screen8_description_text_id);
		tv.setTypeface(MFUtils.getTextTypeface(this));
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
		return 8;
	}

	@Override
	protected int getStartScreen() 
	{
		return 0;
	}
}