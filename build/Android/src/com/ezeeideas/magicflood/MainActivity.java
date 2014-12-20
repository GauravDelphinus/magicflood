package com.ezeeideas.magicflood;


import java.util.Vector;

import android.app.Activity;
import android.app.Dialog;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;

import com.ezeeideas.magicflood.GameDialog.GameDialogListener;
import com.ezeeideas.magicflood.iabutil.IabHelper;

public class MainActivity extends Activity implements View.OnClickListener, PieButton.PieButtonListener, GameDialogListener
{
	static 
	{
		System.loadLibrary(MFGameConstants.NATIVE_LIBRARY_NAME);
	}
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        ImageButton storeButton = (ImageButton)findViewById(R.id.store_button_id);
        storeButton.setOnClickListener(this);
        
        ImageButton infoButton = (ImageButton) findViewById(R.id.about_button_id);
        infoButton.setOnClickListener(this);
        
        ImageButton helpButton = (ImageButton) findViewById(R.id.help_button_id);
        helpButton.setOnClickListener(this);
        
        mGameLevelPieButton = (PieButton) findViewById(R.id.game_level_spinner_button_id);
        Vector<Integer> buttonPressedResources = new Vector<Integer>();
        buttonPressedResources.add(R.drawable.pie_button_level_selection_easy);
        buttonPressedResources.add(R.drawable.pie_button_level_selection_medium);
        buttonPressedResources.add(R.drawable.pie_button_level_selection_hard);
        mGameLevelPieButton.setAttributes(30, R.drawable.pie_button_level_selection_normal, buttonPressedResources);
        
        
        //set the package name
        MFGameConstants.PACKAGE_NAME = getPackageName();
        
        //initialize the in-app purchase manager
        mIAPManager = new MFInAppPurchaseManager(this);
        
        //print screen size category
        Log.d("gaurav", "screen category: " + MFUtils.getSizeName(this));
        Log.d("gaurav", "screen density: " + MFUtils.getDensityName(this));
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
		case R.id.store_button_id:
			if (mIAPManager.isSynchronized())
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_MAIN_VIEW, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_STORE_BUTTON, MFAnalytics.ANALYTICS_VALUE_STORE_SYNCHRONIZED);
				
				i = new Intent(this, MFStoreActivity.class);
				startActivity(i);
			}
			else
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_MAIN_VIEW, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_STORE_BUTTON, MFAnalytics.ANALYTICS_VALUE_STORE_NOT_SYNCHRONIZED);
				
				StoreNotConnectedDialog dialog = new StoreNotConnectedDialog(this);
				dialog.show();
			}
			break;
		case R.id.about_button_id:
			MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_MAIN_VIEW, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_ABOUT_BUTTON);
			
			i = new Intent(this, MFAboutActivity.class);
			startActivity(i);
			break;
		case R.id.help_button_id:
			MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_MAIN_VIEW, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_HELP_BUTTON);
			
			i = new Intent(this, MFHelpActivity.class);
			startActivity(i);
			break;
		}
	}
	
	@Override
	public void onPieButtonSelected(PieButton button, int index) 
	{
		//if the user has never purchased anything, we should try to prompt him to check out the store
		//once in a while
		boolean promptUserToStore = false;
		if (mIAPManager.isSynchronized())
		{
			promptUserToStore = true;
		}
		
		Intent i;
		switch (index)
		{
		case 0:
			MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_MAIN_VIEW, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_EASY_BUTTON);
			
			i = new Intent(this, MFGameActivity.class); 	
			i.putExtra(MFGameConstants.GAME_LEVEL_KEY, MFGameConstants.GAME_LEVEL_EASY);
			i.putExtra(MFGameConstants.PROMPT_USER_TO_STORE, false);
			startActivity(i);
			break;
		case 1:
			MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_MAIN_VIEW, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_MEDIUM_BUTTON);
			
			i = new Intent(this, MFGameActivity.class); 	
			i.putExtra(MFGameConstants.GAME_LEVEL_KEY, MFGameConstants.GAME_LEVEL_MEDIUM);
			i.putExtra(MFGameConstants.PROMPT_USER_TO_STORE, false);
			startActivity(i);
			break;
		case 2:
			MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_MAIN_VIEW, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_HARD_BUTTON);
			
			i = new Intent(this, MFGameActivity.class); 	
			i.putExtra(MFGameConstants.GAME_LEVEL_KEY, MFGameConstants.GAME_LEVEL_HARD);
			i.putExtra(MFGameConstants.PROMPT_USER_TO_STORE, promptUserToStore);
			startActivity(i);
			break;
		}
	}
	
	@Override
	public void onDialogOptionSelected(Dialog dialog, int option) 
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
	private PieButton mGameLevelPieButton;

	
}
