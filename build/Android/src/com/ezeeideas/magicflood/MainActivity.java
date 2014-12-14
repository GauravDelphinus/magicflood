package com.ezeeideas.magicflood;


import java.util.Vector;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;

import com.ezeeideas.magicflood.iabutil.IabHelper;

public class MainActivity extends Activity implements View.OnClickListener, PieButton.PieButtonListener
{
	static 
	{
		System.loadLibrary(MFGameConstants.NATIVE_LIBRARY_NAME);
	}
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        /*
        Button easyButton = (Button)findViewById(R.id.eazy_game_button);
        easyButton.setOnClickListener(this);
        Button mediumButton = (Button)findViewById(R.id.medium_game_button);
        mediumButton.setOnClickListener(this);
        Button hardButton = (Button)findViewById(R.id.hard_game_button);
        hardButton.setOnClickListener(this);
        */
        
        ImageButton storeButton = (ImageButton)findViewById(R.id.store_button_id);
        storeButton.setOnClickListener(this);
        
        ImageButton infoButton = (ImageButton) findViewById(R.id.about_button_id);
        infoButton.setOnClickListener(this);
        
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
        
        //bind the service manager (aka connection service) to Google In-App Billing
        //Intent serviceIntent = new Intent("com.android.vending.billing.InAppBillingService.BIND");
        //serviceIntent.setPackage("com.android.vending");
        //bindService(serviceIntent, mIAPManager, Context.BIND_AUTO_CREATE);
        
        //query the available in-app items, and update local cache (here and in C++ code)
        //mIAPManager.queryInAppItems();
        //mIAPManager.initialize();
        
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
			i = new Intent(this, MFStoreActivity.class);
			startActivity(i);
			break;
		case R.id.about_button_id:
			i = new Intent(this, MFAboutActivity.class);
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
			i = new Intent(this, MFGameActivity.class); 	
			i.putExtra(MFGameConstants.GAME_LEVEL_KEY, MFGameConstants.GAME_LEVEL_EASY);
			i.putExtra(MFGameConstants.PROMPT_USER_TO_STORE, false);
			startActivity(i);
			break;
		case 1:
			i = new Intent(this, MFGameActivity.class); 	
			i.putExtra(MFGameConstants.GAME_LEVEL_KEY, MFGameConstants.GAME_LEVEL_MEDIUM);
			i.putExtra(MFGameConstants.PROMPT_USER_TO_STORE, false);
			startActivity(i);
			break;
		case 2:
			i = new Intent(this, MFGameActivity.class); 	
			i.putExtra(MFGameConstants.GAME_LEVEL_KEY, MFGameConstants.GAME_LEVEL_HARD);
			i.putExtra(MFGameConstants.PROMPT_USER_TO_STORE, promptUserToStore);
			startActivity(i);
			break;
		}
	}
	
	private MFInAppPurchaseManager mIAPManager;
	private PieButton mGameLevelPieButton;
	
}
