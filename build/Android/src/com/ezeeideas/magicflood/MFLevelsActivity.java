package com.ezeeideas.magicflood;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Typeface;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.view.ViewGroup.LayoutParams;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.ViewFlipper;

public class MFLevelsActivity extends MFViewFlipperActivity implements OnClickListener
{
	@Override
    protected void onCreate(Bundle savedInstanceState) 
	{
        super.onCreate(savedInstanceState, R.layout.activity_levels);
	}
	
	private void refreshViews()
	{
		int numLevels = getIntent().getIntExtra(MFGameConstants.NUM_LEVELS_KEY, 0);
		SharedPreferences settings;
		settings = getSharedPreferences(MFGameConstants.PREFERENCE_KEY, Context.MODE_PRIVATE);

		int lastUnlockedLevel = settings.getInt(MFGameConstants.PREFERENCE_LAST_UNLOCKED_LEVEL, MFGameConstants.DEFAULT_LAST_UNLOCKED_LEVEL);
		int lastCompletedLevel = settings.getInt(MFGameConstants.PREFERENCE_LAST_COMPLETED_LEVEL, MFGameConstants.DEFAULT_LAST_COMPLETED_LEVEL);
		
		enumerateLevelsAndSetProperties(mViewFlipper, 1, numLevels, lastUnlockedLevel, lastCompletedLevel);
	}
	
	private int enumerateLevelsAndSetProperties(View rootView, int levelNum, int numLevels, int lastUnlockedLevel, int lastCompletedLevel)
	{
		int numChildren = ((ViewGroup)rootView).getChildCount();
        for (int j = 0; j < numChildren; j++)
        {
        	View nextChild = ((ViewGroup)rootView).getChildAt(j);
        	Log.d("gaurav", "nextChild's class = " + nextChild.getClass());
        	if (nextChild.getClass() == MFLevelLayout.class)
        	{
        		Log.d("gaurav", "levelNum = " + levelNum + ", numLevels = " + numLevels);
        		if (levelNum <= numLevels)
        		{
	        		MFLevelLayout levelLayout = (MFLevelLayout)nextChild;
	        		if (levelNum <= lastCompletedLevel)
	        		{
	        			levelLayout.setProperties(levelNum, MFLevelLayout.LEVEL_STATUS_COMPLETED); //level is unlocked and completed
	        		}
	        		else if (levelNum <= lastUnlockedLevel)
	        		{
	        			levelLayout.setProperties(levelNum, MFLevelLayout.LEVEL_STATUS_UNLOCKED); //level is unlocked but not yet completed
	        		}
	        		else
	        		{
	        			levelLayout.setProperties(levelNum, MFLevelLayout.LEVEL_STATUS_LOCKED); //level is locked
	        		}
	        		levelLayout.setProperties(levelNum, MFLevelLayout.LEVEL_STATUS_UNLOCKED);
	        		levelLayout.setOnClickListener(this);
	        		levelNum++;
        		}
        		else
        		{
        			Log.d("gaurav", "setting visibility to fals for nextChild of type " + nextChild.getClass());
        			nextChild.setVisibility(View.INVISIBLE);
        		}
        	}
        	else if (nextChild instanceof ViewGroup)
        	{
        		levelNum = enumerateLevelsAndSetProperties(nextChild, levelNum, numLevels, lastUnlockedLevel, lastCompletedLevel);
        	}
        }
        
        return levelNum;
	}
	
    @Override
    public void onDestroy() 
    {
        super.onDestroy(); 
    }

	@Override
	public void onClick(View arg0) 
	{
		Log.d("gaurav", "onClick called");
		MFLevelLayout layout = (MFLevelLayout) arg0;
		
		SharedPreferences settings;
		settings = getSharedPreferences(MFGameConstants.PREFERENCE_KEY, Context.MODE_PRIVATE);

		int lastUnlockedLevel = settings.getInt(MFGameConstants.PREFERENCE_LAST_UNLOCKED_LEVEL, MFGameConstants.DEFAULT_LAST_UNLOCKED_LEVEL);
		Log.d("gaurav", "lastUnlockedLeve = " + lastUnlockedLevel);
		//if (layout.getLevel() <= lastUnlockedLevel)
		{
			Intent i = new Intent(this, MFGameActivity.class); 	
			i.putExtra(MFGameConstants.GAME_LEVEL_KEY, layout.getLevel());
			i.putExtra(MFGameConstants.PROMPT_USER_TO_STORE, false);
			startActivityForResult(i, ACTIVITY_RESULT_FROM_GAME_ACTIVITY);
		}
	}
	
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) 
	{
		Log.d("gaurav", "onActivityResult, requestCode = " + requestCode + ", resultCode = " + resultCode);
	    // Check which request we're responding to
	    if (requestCode == ACTIVITY_RESULT_FROM_GAME_ACTIVITY) 
	    {
	            //refresh the status of levels
	        	refreshViews();
	    }
	}
	
	private static final int ACTIVITY_RESULT_FROM_GAME_ACTIVITY = 100;

	@Override
	protected ViewFlipper getViewFlipper() 
	{
		return (ViewFlipper) findViewById(R.id.view_flipper_id);
	}

	@Override
	protected int getNumScreens() 
	{
		int numLevels = getIntent().getIntExtra(MFGameConstants.NUM_LEVELS_KEY, 0);
		int numScreens = numLevels / MFConstants.NUM_LEVELS_PER_SCREEN; //9 levels per screen
    	int numLevelsOnLastScreen = numLevels % MFConstants.NUM_LEVELS_PER_SCREEN;
    	if (numLevelsOnLastScreen > 0)
    	{
    		numScreens ++;
    	}
    	
    	return numScreens;
	}

	@Override
	protected LinearLayout getIndicatorLayout() 
	{
		return (LinearLayout) findViewById(R.id.indicator_row_layout_id);
	}

	@Override
	protected void setupViewFlipper() 
	{
		mNumScreens = getNumScreens();
		
		int numLevels = getIntent().getIntExtra(MFGameConstants.NUM_LEVELS_KEY, 0);
    	ViewFlipper flipper = (ViewFlipper) findViewById(R.id.view_flipper_id);
    	LayoutInflater inflater = LayoutInflater.from(this);
    	
    	LinearLayout indicatorRowLayout = (LinearLayout) findViewById(R.id.indicator_row_layout_id);
    	
    	SharedPreferences settings;
		settings = getSharedPreferences(MFGameConstants.PREFERENCE_KEY, Context.MODE_PRIVATE);

		int lastUnlockedLevel = settings.getInt(MFGameConstants.PREFERENCE_LAST_UNLOCKED_LEVEL, MFGameConstants.DEFAULT_LAST_UNLOCKED_LEVEL);
		int lastPlayedLevel = settings.getInt(MFGameConstants.PREFERENCE_LAST_PLAYED_LEVEL, MFGameConstants.DEFAULT_LAST_PLAYED_LEVEL);
		int lastCompletedLevel = settings.getInt(MFGameConstants.PREFERENCE_LAST_COMPLETED_LEVEL, MFGameConstants.DEFAULT_LAST_COMPLETED_LEVEL);
		int screenToStartWith = (lastPlayedLevel - 1) / MFConstants.NUM_LEVELS_PER_SCREEN;
		
    	int levelNum = 1;
    	for (int i = 0; i < mNumScreens; i++)
    	{
	        View inflatedLayout = inflater.inflate(R.layout.layout_level_screen, null, false);
	        Log.d("gaurav", "infaltedLayout class = " + inflatedLayout.getClass());
	        
	        levelNum = enumerateLevelsAndSetProperties(inflatedLayout, levelNum, numLevels, lastUnlockedLevel, lastCompletedLevel);
	        
	        flipper.addView(inflatedLayout);
    	}
    	
    	flipper.setDisplayedChild(screenToStartWith);
    	
    	TextView titleTV = (TextView) findViewById(R.id.levels_title_text_id);
    	Typeface face = MFUtils.FontCache.get("ArchitectsDaughter.ttf", this);
    	titleTV.setTypeface(face);
	}

	@Override
	protected int getStartScreen() 
	{
		SharedPreferences settings;
		settings = getSharedPreferences(MFGameConstants.PREFERENCE_KEY, Context.MODE_PRIVATE);
		int lastPlayedLevel = settings.getInt(MFGameConstants.PREFERENCE_LAST_PLAYED_LEVEL, MFGameConstants.DEFAULT_LAST_PLAYED_LEVEL);
		int screenToStartWith = (lastPlayedLevel - 1) / MFConstants.NUM_LEVELS_PER_SCREEN;
		
		return screenToStartWith;
	}
}