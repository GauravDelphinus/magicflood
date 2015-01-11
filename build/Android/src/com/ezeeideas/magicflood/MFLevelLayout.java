package com.ezeeideas.magicflood;

import android.content.Context;
import android.util.AttributeSet;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

public class MFLevelLayout extends LinearLayout
{
	public MFLevelLayout(Context context) 
	{
		super(context);
		// TODO Auto-generated constructor stub
	}
	
	public MFLevelLayout(Context context, AttributeSet attrs)
	{
		super(context, attrs);
	}
	
	public void setProperties(int level, boolean isLocked)
	{
		mLevel = level;
		
		TextView tvDetail = (TextView) findViewById(R.id.textview_level_name_id);
		tvDetail.setText("Level " + level);
		
		ImageView imageView = (ImageView) findViewById(R.id.image_level_status_id);
		
		if (!isLocked) //set free text if the product is free
		{
			imageView.setBackgroundResource(R.drawable.ic_iap_tick);
			setBackgroundResource(R.drawable.background_iap_provisioned);			
		}
		else
		{	
			imageView.setBackgroundResource(R.drawable.ic_iap_lock);
			setBackgroundResource(R.drawable.background_iap_not_provisioned);			
		}
	}
	
	public void updateLockedStatus(boolean isLocked)
	{
		ImageView imageView = (ImageView) findViewById(R.id.image_iap_status_id);
		if (!isLocked)
		{	
			imageView.setBackgroundResource(R.drawable.ic_iap_tick);
			setBackgroundResource(R.drawable.background_iap_provisioned);
		}
		else
		{
			imageView.setBackgroundResource(R.drawable.ic_iap_lock);
			setBackgroundResource(R.drawable.background_iap_not_provisioned);
		}
	}
	
	public int getLevel()
	{
		return mLevel;
	}
	
	private int mLevel;
}