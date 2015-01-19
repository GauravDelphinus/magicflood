package com.ezeeideas.magicflood;

import android.content.Context;
import android.graphics.Typeface;
import android.util.AttributeSet;
import android.util.Log;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;

public class MFLevelLayout extends LinearLayout implements OnTouchListener
{
	public MFLevelLayout(Context context) 
	{
		super(context);
		mContext = context;
		// TODO Auto-generated constructor stub
	}
	
	public MFLevelLayout(Context context, AttributeSet attrs)
	{
		super(context, attrs);
		mContext = context;
	}
	
	public void setProperties(int level, int lockStatus)
	{
		mLevel = level;
		
		TextView tvDetail = (TextView) findViewById(R.id.textview_level_name_id);
		tvDetail.setText(Integer.toString(level));
		Typeface face = MFUtils.FontCache.get("ArchitectsDaughter.ttf", mContext);
    	tvDetail.setTypeface(face);
		
		ImageView imageView = (ImageView) findViewById(R.id.image_level_status_id);
		
		if (lockStatus == LEVEL_STATUS_COMPLETED)
		{	
			imageView.setBackgroundResource(R.drawable.ic_iap_tick);
			setEnabled(true);
		}
		else if (lockStatus == LEVEL_STATUS_UNLOCKED)
		{
			imageView.setBackgroundResource(R.drawable.ic_iap_unlocked);
			setEnabled(true);
		}
		else
		{
			imageView.setBackgroundResource(R.drawable.ic_iap_lock);
			setEnabled(false);
		}
		
		//hook on the touch listener
		setOnTouchListener(this);
	}
	
	public void updateLockedStatus(int lockStatus)
	{
		ImageView imageView = (ImageView) findViewById(R.id.image_iap_status_id);
		if (lockStatus == LEVEL_STATUS_COMPLETED)
		{	
			imageView.setBackgroundResource(R.drawable.ic_iap_tick);
			setEnabled(true);
		}
		else if (lockStatus == LEVEL_STATUS_UNLOCKED)
		{
			imageView.setBackgroundResource(R.drawable.ic_iap_unlocked);
			setEnabled(true);
		}
		else
		{
			imageView.setBackgroundResource(R.drawable.ic_iap_lock);
			setEnabled(false);
		}
	}
	
	public int getLevel()
	{
		return mLevel;
	}
	
	private int mLevel;
	private Context mContext;
	
	@Override
	public boolean onTouch(View v, MotionEvent event) 
	{
		Log.d("gaurav", "MFLevelLayout's onTouch called");
		return false;
	}
	
	public static final int LEVEL_STATUS_LOCKED = 1;
	public static final int LEVEL_STATUS_UNLOCKED = 2;
	public static final int LEVEL_STATUS_COMPLETED = 3;
}