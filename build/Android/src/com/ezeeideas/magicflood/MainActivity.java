package com.ezeeideas.magicflood;


import java.util.Vector;

import android.app.Activity;
import android.app.Dialog;
import android.content.Intent;
import android.graphics.Typeface;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.ezeeideas.magicflood.GameDialog.GameDialogListener;

public class MainActivity extends Activity implements View.OnClickListener, GameDialogListener
{
	static 
	{
		System.loadLibrary(MFGameConstants.NATIVE_LIBRARY_NAME);
	}
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        mPlayButton = (View)findViewById(R.id.play_game_button_id);
        mPlayButton.setOnClickListener(this);
        
        mHowToPlayButton = (View)findViewById(R.id.how_to_play_game_button_id);
        mHowToPlayButton.setOnClickListener(this);
        
        mAboutButton = (View)findViewById(R.id.about_game_button_id);
        mAboutButton.setOnClickListener(this);
        
        //set the typeface
        TextView companyNameTV = (TextView) findViewById(R.id.company_name_id);
        companyNameTV.setTypeface(MFUtils.getTextTypeface(this));
        
        TextView playGameTV = (TextView) findViewById(R.id.play_game_text_id);
        playGameTV.setTypeface(MFUtils.getTextTypeface(this));
        
        TextView howToPlayGameTV = (TextView) findViewById(R.id.how_to_play_game_text_id);
        howToPlayGameTV.setTypeface(MFUtils.getTextTypeface(this));
        
        TextView aboutGameTV = (TextView) findViewById(R.id.about_game_text_id);
        aboutGameTV.setTypeface(MFUtils.getTextTypeface(this));
        
        //set the package name
        MFGameConstants.PACKAGE_NAME = getPackageName();
        
        //initialize the in-app purchase manager
        mIAPManager = new MFInAppPurchaseManager(this);
    }

    @Override
    public void onDestroy() 
    {
        super.onDestroy();
        
        //Unbind the service manager for IAP
        if (mIAPManager != null)
        {
            mIAPManager.unbind();
        }   
    }
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }


	@Override
	public void onClick(View arg0) {
		// TODO Auto-generated method stub
		Intent i;
		switch (arg0.getId())
		{
		case R.id.about_game_button_id:
			MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_ABOUT_BUTTON);
			
			i = new Intent(this, MFAboutActivity.class);
			startActivity(i);
			break;
		case R.id.how_to_play_game_button_id:
			MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_HELP_BUTTON);
			
			i = new Intent(this, MFHelpActivity.class);
			startActivity(i);
			break;
		case R.id.play_game_button_id:
			MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_PLAY_BUTTON);
			
			i = new Intent(this, MFLevelsActivity.class);
			i.putExtra(MFGameConstants.NUM_LEVELS_KEY, getNumLevels());
			startActivity(i);
			break;
		}
	}
	
	@Override
	public void onDialogOptionSelected(Dialog dialog, int option, int clientdata) 
	{
		if (dialog.getClass() == StoreNotConnectedDialog.class)
		{
			if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_1) //Go back to Main Menu
			{
				dialog.cancel();
			}
		}			
	}
	
	private MFInAppPurchaseManager mIAPManager;
	//private PieButton mGameLevelPieButton;
	private View mPlayButton, mHowToPlayButton, mAboutButton;
	
	private native int getNumLevels();
	
}
