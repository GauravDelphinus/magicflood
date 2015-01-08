package com.ezeeideas.magicflood;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.ViewFlipper;

public class MFLevelsActivity extends MFViewFlipperActivity implements OnClickListener
{
	@Override
    protected void onCreate(Bundle savedInstanceState) 
	{
        super.onCreate(savedInstanceState, R.layout.activity_levels);
        
        int numLevels = getIntent().getIntExtra(MFGameConstants.NUM_LEVELS_KEY, 0);
    	int numScreens = numLevels / MFConstants.NUM_LEVELS_PER_SCREEN; //9 levels per screen
    	int numLevelsOnLastScreen = numLevels % MFConstants.NUM_LEVELS_PER_SCREEN;
    	if (numLevelsOnLastScreen > 0)
    	{
    		numScreens ++;
    	}
    	Log.d("gaurav", "numLevels = " + numLevels + ", numScreens = " + numScreens + ", numLevelsOnLastScreen = " + numLevelsOnLastScreen);
    	ViewFlipper flipper = (ViewFlipper) findViewById(R.id.view_flipper_id);
    	LayoutInflater inflater = LayoutInflater.from(this);
    	int levelNum = 1;
    	for (int i = 0; i < numScreens; i++)
    	{
	        View inflatedLayout = inflater.inflate(R.layout.layout_level_screen, null, false);
	        Log.d("gaurav", "infaltedLayout class = " + inflatedLayout.getClass());
	        
	        enumerateLevelsAndSetProperties(inflatedLayout, levelNum, numLevels);
	        
	        flipper.addView(inflatedLayout);
    	}
	}
	
	private int enumerateLevelsAndSetProperties(View rootView, int levelNum, int numLevels)
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
	        		levelLayout.setProperties(levelNum, true);
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
        		levelNum = enumerateLevelsAndSetProperties(nextChild, levelNum, numLevels);
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
		
		
		Intent i = new Intent(this, MFGameActivity.class); 	
		i.putExtra(MFGameConstants.GAME_LEVEL_KEY, layout.getLevel());
		i.putExtra(MFGameConstants.PROMPT_USER_TO_STORE, false);
		startActivity(i);
	}
}