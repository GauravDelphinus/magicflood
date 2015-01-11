package com.ezeeideas.magicflood;

import com.ezeeideas.magicflood.GameDialog.GameDialogListener;
import com.ezeeideas.magicflood.iabutil.Purchase;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.AdView;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.graphics.Typeface;
import android.media.AudioManager;
import android.media.SoundPool;
import android.media.SoundPool.OnLoadCompleteListener;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.TextView;

public class MFGameActivity extends Activity implements View.OnClickListener, GameDialogListener, MFInAppPurchaseManager.IAPPurchaseInterface {

	
	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_game);
        
    	mGameView = (MFGameView) findViewById(R.id.game_view_id);
    	mMovesLabel = (TextView) findViewById(R.id.moves_label_id);
    	
    	//Typeface face = Typeface.createFromAsset(getAssets(),
        //        "fonts/ArchitectsDaughter.ttf");
        Typeface face = MFUtils.FontCache.get("ArchitectsDaughter.ttf", this);
    	mMovesLabel.setTypeface(face);
    
    	mExitButton = (ImageButton) findViewById(R.id.exit_game_button_id);
    	mExitButton.setOnClickListener(this);
    	
    	mRedButton = (ImageButton) findViewById(R.id.red_button_id);
    	mRedButton.setOnClickListener(this);
    	//mRedButton.getBackground().setColorFilter(new LightingColorFilter(getResources().getColor(R.color.red_button_color_mul), getResources().getColor(R.color.red_button_color_mul)));
    	mGreenButton = (ImageButton) findViewById(R.id.green_button_id);
    	mGreenButton.setOnClickListener(this);
    	mBlueButton = (ImageButton) findViewById(R.id.blue_button_id);
    	mBlueButton.setOnClickListener(this);
    	mYellowButton = (ImageButton) findViewById(R.id.yellow_button_id);
    	mYellowButton.setOnClickListener(this);
    	mOrangeButton = (ImageButton) findViewById(R.id.orange_button_id);
    	mOrangeButton.setOnClickListener(this);
    	mCyanButton = (ImageButton) findViewById(R.id.cyan_button_id);
    	mCyanButton.setOnClickListener(this);
    	
    	mExitAlertDialog = null;
    	mSuccessAlertDialog = null;
    	mFailedAlertDialog = null;
    	
    	//initialize Sound
    	setupSound();
    	
    	//initialize Ads
    	setupAds();
    	
    	//initialize In-App Purchase
    	setupIAP();
    	
    	mLevel = getIntent().getIntExtra(MFGameConstants.GAME_LEVEL_KEY, 1);
    	mPromptUserToStore = getIntent().getBooleanExtra(MFGameConstants.PROMPT_USER_TO_STORE, false);
    	
    	startNewGame(mLevel);
    	
    	//read system preferences of number of coins, and total points earned so far
		//get the sharepref
    	SharedPreferences settings;
		settings = getSharedPreferences(MFGameConstants.PREFERENCE_KEY, Context.MODE_PRIVATE);

		mTotalCoinsEarned = settings.getInt(MFGameConstants.PREFERENCE_TOTAL_COINS_EARNED, MFGameConstants.INITIAL_COINS_ALLOCATED);
		String addCoinsText = String.format(getResources().getString(R.string.add_coins_text), mTotalCoinsEarned);
		mAddCoinsButton = (Button) findViewById(R.id.add_coins_button_id);
		mAddCoinsButton.setText(addCoinsText);
		mAddCoinsButton.setOnClickListener(this);
		
		mAddMovesButton = (Button) findViewById(R.id.add_moves_button_id);
		mAddMovesButton.setOnClickListener(this);
		
		mAddStarsButton = (Button) findViewById(R.id.add_stars_button_id);
		mAddStarsButton.setOnClickListener(this);
				
		mRemoveAdsButton = (Button) findViewById(R.id.remove_ads_button_id);
		mRemoveAdsButton.setOnClickListener(this);
		boolean removeAds = settings.getBoolean(MFGameConstants.PREFERENCE_ADS_REMOVED, false);
		if (removeAds)
		{
			mRemoveAdsButton.setVisibility(View.INVISIBLE);
		}
		
		mLevelLabel = (TextView) findViewById(R.id.level_label_id);
		String levelText = String.format(getResources().getString(R.string.level_text), mLevel);
		mLevelLabel.setText(levelText);
    }
	
	@Override
	protected void onDestroy()
	{
		super.onDestroy();
		deleteGrid(gridHandle);
	}
	
	private void setupSound()
	{
		// AudioManager audio settings for adjusting the volume
		audioManager = (AudioManager) getSystemService(AUDIO_SERVICE);
		actVolume = (float) audioManager.getStreamVolume(AudioManager.STREAM_MUSIC);
		maxVolume = (float) audioManager.getStreamMaxVolume(AudioManager.STREAM_MUSIC);
		volume = actVolume / maxVolume;
		
		 
		//Hardware buttons setting to adjust the media sound
		this.setVolumeControlStream(AudioManager.STREAM_MUSIC);
		
		// Load the sounds
		mSoundPool = new SoundPool(10, AudioManager.STREAM_MUSIC, 0);
		mSoundPool.setOnLoadCompleteListener(new OnLoadCompleteListener() 
		{
			@Override
			public void onLoadComplete(SoundPool soundPool, int sampleId, int status)
			{

				loaded = true;
			}
		});

		mButtonClickSoundID = mSoundPool.load(this, R.raw.button_press_sound, 1);
		mGameSuccessSoundID = mSoundPool.load(this, R.raw.game_success_sound, 1);
		mGameFailedSoundID = mSoundPool.load(this, R.raw.game_failed_sound, 1);
		
		//read the preference on whether the sound should be muted
		SharedPreferences settings;
		settings = getSharedPreferences(MFGameConstants.PREFERENCE_KEY, Context.MODE_PRIVATE);

		//get the sharepref
		mPlaySound = settings.getBoolean(MFGameConstants.PREFERENCE_SOUND, true);
		
		mSoundButton = (ImageButton) findViewById(R.id.mute_sound_id);
		if (mPlaySound)
		{
			mSoundButton.setBackgroundResource(R.drawable.ic_button_sound_on);
		}
		else
		{
			mSoundButton.setBackgroundResource(R.drawable.ic_button_sound_off);
		}
    	mSoundButton.setOnClickListener(this);
	}
	
	private void setupAds()
	{
		mAdView = (AdView) findViewById(R.id.banner_ad_id);
       // mAdView.setAdListener(new AdListener(this));
        AdRequest.Builder builder = new AdRequest.Builder();
        
        builder
        .addTestDevice("D270918A90127FD1558623AC978405DF") //Anu's Samsung Galaxy S3
        .addTestDevice("EDA0579D1B567771CB429E8A84668A3D") //Galax Tab 10.1 "
        .addTestDevice(AdRequest.DEVICE_ID_EMULATOR);

        for (int i = 0; i < MFConstants.ADS_KEYWORDS.length; i++)
        {
        	builder.addKeyword(MFConstants.ADS_KEYWORDS[i]);
        }
        
        AdRequest adRequest = builder.build();
        mAdView.loadAd(adRequest);
	}
	
	private void setupIAP()
	{
		mIAPManager = new MFInAppPurchaseManager(this);
        mIAPManager.addPurchaseListener(this);
	}
	
	private void playSound(int resultType) 
	{
		// Is the sound loaded does it already play?
		if (loaded && mPlaySound)
		{
			int soundID = mButtonClickSoundID;
			switch (resultType)
			{
			case MFGameConstants.RESULT_SUCCESS:
				soundID = mGameSuccessSoundID;
				break;
			case MFGameConstants.RESULT_FAILED:
				soundID = mGameFailedSoundID;
				break;
			}
			mCurrentlyPlayingStream = mSoundPool.play(soundID, volume, volume, 1, 0, 1f);
		}
	}

	@Override
	public void onBackPressed() 
	{
		MFAnalytics.trackEvent(this, getAnalyticsCategory(), MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_BACK_BUTTON);
		
		GameMenuDialog dialog = new GameMenuDialog(this);
		dialog.setCanceledOnTouchOutside(true);
		dialog.show();	
	}
	
	private void startNewGame(int level)
	{
		Log.d("magicflood", "startNewGame, level = " + level);
		if (gridHandle != 0)
		{
			deleteGrid(gridHandle);
			gridHandle = 0;
		}
		
		//create a fresh grid by calling into the native library
		gridHandle = createNewGrid(level);
		
		int[] gridDataOneD = getGridData(gridHandle);
		int gridSize = getGridSize(gridHandle);
		int[] startPos = getStartPos(gridHandle);
		int maxMoves = getMaxMoves(gridHandle);
		int currMove = getCurrMove(gridHandle);
		
		//convert the one-dimensional array passed from C++ back to 2D array for use in the game view in Java
		int gridData[][] = new int[gridSize][gridSize];
		for (int i = 0; i < gridDataOneD.length; i++)
		{
			int x = i % gridSize;
			int y = i / gridSize;
			gridData[x][y] = gridDataOneD[i];
		}
		
		//initialize the game view with all the data for it to render the game board
		mGameView.initializeGameData(gridData, gridSize, startPos, maxMoves);
		mGameView.invalidate();
		
		//update the moves label
		String movesText = String.format(getResources().getString(R.string.moves_remaining_text), (maxMoves - currMove));	
		mMovesLabel.setText(movesText);
	}

	/**
	 * Get the Analytics game category from the game level
	 * @return
	 */
	private String getAnalyticsCategory()
	{
		switch (mLevel)
		{
		case MFGameConstants.GAME_LEVEL_EASY:
			return MFAnalytics.ANALYTICS_CATEGORY_GAME_EASY;
		case MFGameConstants.GAME_LEVEL_MEDIUM:
			return MFAnalytics.ANALYTICS_CATEGORY_GAME_MEDIUM;
		case MFGameConstants.GAME_LEVEL_HARD:
			return MFAnalytics.ANALYTICS_CATEGORY_GAME_HARD;
		}
		
		return MFAnalytics.ANALYTICS_CATEGORY_GAME_EASY;
	}
	
	@Override
	public void onClick(View arg0) {
		
		if (arg0.getId() ==  R.id.exit_game_button_id) //Menu button clicked
		{	
			MFAnalytics.trackEvent(this, getAnalyticsCategory(), MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_MENU_BUTTON);
			
			GameMenuDialog dialog = new GameMenuDialog(this);
			dialog.setCanceledOnTouchOutside(false);
			dialog.show();

			return;
		}	
		else if (arg0.getId() == R.id.mute_sound_id) //mute/unmute the sound
		{
			if (mPlaySound == true)
			{
				MFAnalytics.trackEvent(this, getAnalyticsCategory(), MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_SOUND_ON);
				
				mPlaySound = false;
				mSoundButton.setBackgroundResource(R.drawable.ic_button_sound_off);
			}
			else
			{
				MFAnalytics.trackEvent(this, getAnalyticsCategory(), MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_SOUND_OFF);
				
				mPlaySound = true;
				mSoundButton.setBackgroundResource(R.drawable.ic_button_sound_on);
			}
			
			//set the sharedpref
			SharedPreferences settings;
			settings = getSharedPreferences(MFGameConstants.PREFERENCE_KEY, Context.MODE_PRIVATE);
			Editor editor = settings.edit();
			editor.putBoolean(MFGameConstants.PREFERENCE_SOUND, mPlaySound);
			editor.commit();
			
			return;
		}
		else if (arg0.getId() == R.id.add_coins_button_id)
		{
			//redeem the coins, show a dialog
			AddCoinsDialog dialog = new AddCoinsDialog(this);
			dialog.setCanceledOnTouchOutside(false);
			dialog.show();
			
			return;
		}
		else if (arg0.getId() == R.id.add_moves_button_id)
		{
			AddMovesDialog dialog = new AddMovesDialog(this);
			dialog.setCanceledOnTouchOutside(false);
			dialog.show();
			
			return;
		}
		else if (arg0.getId() == R.id.add_stars_button_id)
		{
			AddStarDialog dialog = new AddStarDialog(this);
			dialog.setCanceledOnTouchOutside(false);
			dialog.show();
			
			return;
		}
		else if (arg0.getId() == R.id.remove_ads_button_id)
		{
		    //Remove Ads IAP
	        String detailsArray[];
	        detailsArray = mIAPManager.getProductDetails(MFGameConstants.IAP_REMOVE_ADS);
	        
	        RemoveAdsDialog dialog = new RemoveAdsDialog(this, detailsArray[2]);
	        dialog.setCanceledOnTouchOutside(false);
	        dialog.show();
	        
			return;
		}
		
		int colorValue = MFGameConstants.GRID_OBSTACLE;
		switch (arg0.getId())
		{
		case R.id.red_button_id:
			colorValue = MFGameConstants.GRID_COLOR_RED;
			break;
		case R.id.blue_button_id:
			colorValue = MFGameConstants.GRID_COLOR_BLUE;
			break;
		case R.id.green_button_id:
			colorValue = MFGameConstants.GRID_COLOR_GREEN;
			break;
		case R.id.yellow_button_id:
			colorValue = MFGameConstants.GRID_COLOR_YELLOW;
			break;
		case R.id.orange_button_id:
			colorValue = MFGameConstants.GRID_COLOR_ORANGE;
			break;
		case R.id.cyan_button_id:
			colorValue = MFGameConstants.GRID_COLOR_CYAN;
			break;
		}
		
		MFAnalytics.trackEvent(this, getAnalyticsCategory(), MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_COLOR_BUTTON);
		
		
		int[] result = playMove(gridHandle, colorValue);
		Log.d("gaurav", "playMove returned 0 = " + result[0] + ", 1 = " + result[1]);
		
		int[] gridDataOneD = getGridData(gridHandle);
		int gridSize = getGridSize(gridHandle);
		int currMove = getCurrMove(gridHandle);
		int maxMoves = getMaxMoves(gridHandle);
		//convert the one-dimensional array passed from C++ back to 2D array for use in the game view in Java
		int gridData[][] = new int[gridSize][gridSize];
		for (int i = 0; i < gridDataOneD.length; i++)
		{
			int x = i % gridSize;
			int y = i / gridSize;
			gridData[x][y] = gridDataOneD[i];
		}

		String movesText = String.format(getResources().getString(R.string.moves_remaining_text), (maxMoves - currMove));	
		mMovesLabel.setText(movesText);
		
		mGameView.updateGameData(gridData);
		mGameView.invalidate();

		if (result[0] == MFGameConstants.RESULT_FAILED) //run out of moves
		{	
			MFAnalytics.trackEvent(this, getAnalyticsCategory(), MFAnalytics.ANALYTICS_ACTION_GAME_ENDED, MFAnalytics.ANALYTICS_LABEL_GAME_ENDED_FAILURE);
			
			GameFailedDialog dialog = new GameFailedDialog(this);
			dialog.setCanceledOnTouchOutside(false);
			dialog.show();
			
			playSound(MFGameConstants.RESULT_FAILED);
		}
		else if (result[0] == MFGameConstants.RESULT_SUCCESS) //game successful completed
		{	
			MFAnalytics.trackEvent(this, getAnalyticsCategory(), MFAnalytics.ANALYTICS_ACTION_GAME_ENDED, MFAnalytics.ANALYTICS_LABEL_GAME_ENDED_SUCCESS);
			
			playSound(MFGameConstants.RESULT_SUCCESS);

			//Unlock the next level.
			SharedPreferences settings;
			settings = getSharedPreferences(MFGameConstants.PREFERENCE_KEY, Context.MODE_PRIVATE);
			int lastUnlockedLevel = settings.getInt(MFGameConstants.PREFERENCE_LAST_UNLOCKED_LEVEL, MFGameConstants.DEFAULT_LAST_UNLOCKED_LEVEL);
			if (lastUnlockedLevel <= mLevel)
			{
				lastUnlockedLevel ++;
				Editor editor = settings.edit();
				editor.putInt(MFGameConstants.PREFERENCE_LAST_UNLOCKED_LEVEL, lastUnlockedLevel);
				editor.commit();
			}
			
			GameSuccessDialog dialog = new GameSuccessDialog(this);
			dialog.setCanceledOnTouchOutside(false);
			dialog.show();
			
			/** Update Coins Earned **/			
			mTotalCoinsEarned += MFGameConstants.COINS_EARNED_FACTOR_ON_GAME_COMPLETION + (mLevel - 1) * 10 + (maxMoves - currMove) * MFGameConstants.COINS_EARNED_FACTOR_ON_REMAINING_MOVES;
			String coinsText = String.format(getResources().getString(R.string.add_coins_text), mTotalCoinsEarned);
			mAddCoinsButton.setText(coinsText);
		}
		else
		{
			playSound(MFGameConstants.RESULT_CONTINUE);
			
			/** Update Points and Coins Earned **/
			mTotalCoinsEarned += result[1] * MFGameConstants.COINS_EARNED_FACTOR_ON_EACH_MOVE;
			String coinsText = String.format(getResources().getString(R.string.add_coins_text), mTotalCoinsEarned);
			mAddCoinsButton.setText(coinsText);
		}
	}

	@Override
	public void onDialogOptionSelected(Dialog dialog, int option) 
	{
		Log.d("gaurav", "onDialogOptionSelected, class = " + dialog.getClass() + ", option = " + option);
		
		/**
		 * If there's a sound playing, stop it!
		 */
		mSoundPool.stop(mCurrentlyPlayingStream);
		
		if (dialog.getClass() == GameMenuDialog.class)
		{
			if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_1) //Go back to Main Menu
			{
				MFAnalytics.trackEvent(this, getAnalyticsCategory(), MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_MAIN_MENU_BUTTON);
				
				finish();
			}
			else if (option == GameDialog.GAME_DIALOG_ACTION_NEGATIVE_1) // Resume current game
			{
				MFAnalytics.trackEvent(this, getAnalyticsCategory(), MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_RESUME_GAME_BUTTON);
				
				dialog.cancel();
			}
			else if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_2) //Replay Game
			{
				MFAnalytics.trackEvent(this, getAnalyticsCategory(), MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_NEW_GAME_BUTTON);
				
				dialog.cancel();
				startNewGame(mLevel);
			}
		}	
		else if (dialog.getClass() == GameFailedDialog.class)
		{
			if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_1) //Play On
			{
				dialog.cancel();
				
				/** Prompt the user with adding moves to continue playing the current game. **/
				AddMovesDialog addMovesDialog = new AddMovesDialog(this);
				addMovesDialog.setCanceledOnTouchOutside(false);
				addMovesDialog.show();
			}
			else if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_2 || option == GameDialog.GAME_DIALOG_ACTION_NEGATIVE_1) // End Game
			{
				/** Take the user to the Try Again dialog **/
				TryAgainDialog tryAgainDialog = new TryAgainDialog(this);
				tryAgainDialog.setCanceledOnTouchOutside(false);
				tryAgainDialog.show();
			}
		}	
		else if (dialog.getClass() == TryAgainDialog.class)
		{
			if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_1) // Try Again
			{
				dialog.cancel();
				
				startNewGame(mLevel);
			}
			else if (option == GameDialog.GAME_DIALOG_ACTION_NEGATIVE_1) //go to main menu
			{
				finish();
			}
		}
		else if (dialog.getClass() == GameSuccessDialog.class)
		{
			if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_1) //Start the next game
			{
				MFAnalytics.trackEvent(this, getAnalyticsCategory(), MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_NEXT_GAME_BUTTON);
				
				dialog.cancel();
				startNewGame(mLevel);
			}
			else if (option == GameDialog.GAME_DIALOG_ACTION_NEGATIVE_1) // Go back to the Main Menu
			{
				MFAnalytics.trackEvent(this, getAnalyticsCategory(), MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_MAIN_MENU_BUTTON);
				
				finish();
			}
		}
		else if (dialog.getClass() == GameSuccessStoreDialog.class)
		{
			if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_1) //Take to the store
			{
				MFAnalytics.trackEvent(this, getAnalyticsCategory(), MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_STORE_BUTTON);
				
				finish();
				Intent i = new Intent(this, MFStoreActivity.class);
				startActivity(i);
			}
			else if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_2) // Start the next game
			{
				MFAnalytics.trackEvent(this, getAnalyticsCategory(), MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_NEXT_GAME_BUTTON);
				
				dialog.cancel();
				startNewGame(mLevel);
			}
			else if (option == GameDialog.GAME_DIALOG_ACTION_NEGATIVE_1) // Go back to the main menu
			{
				MFAnalytics.trackEvent(this, getAnalyticsCategory(), MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_MAIN_MENU_BUTTON);
				
				finish();
			}
		}
		else if (dialog.getClass() == RedeemCoinsDialog.class)
		{
			if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_1) //Earn Moves
			{				
				finish();
				Intent i = new Intent(this, MFStoreActivity.class);
				startActivity(i);
			}
			else if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_2) //Earn Stars
			{				
				dialog.cancel();
				startNewGame(mLevel);
			}
			else if (option == GameDialog.GAME_DIALOG_ACTION_NEGATIVE_1) // Go back to the main menu
			{				
				//do nothing
			}
		}
		else if (dialog.getClass() == RemoveAdsDialog.class)
		{
			if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_1)
			{
				Log.d("gaurav", "calling purchaseItem... ");
				//purchase for Remove Ads IAP requested
				mIAPManager.purchaseItem(MFGameConstants.IAP_REMOVE_ADS);
			}
		}
		else if (dialog.getClass() == AddCoinsDialog.class)
		{
			if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_1) //First option
			{
				mIAPManager.purchaseItem(MFGameConstants.IAP_COINS_FIRST);
			}
			else if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_2) //Second option
			{
				mIAPManager.purchaseItem(MFGameConstants.IAP_COINS_SECOND);
			}
			else if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_3) //Third option
			{
				mIAPManager.purchaseItem(MFGameConstants.IAP_COINS_THIRD);
			}
			else if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_4) //Fourth option
			{
				mIAPManager.purchaseItem(MFGameConstants.IAP_COINS_FOURTH);
			}
		}
		else if (dialog.getClass() == AddMovesDialog.class)
		{
			if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_1)
			{
				Log.d("garuav", "AddMovesDialog result, mTotalCoinsEarned = " + mTotalCoinsEarned);
				if (mTotalCoinsEarned >= MFGameConstants.COINS_TO_ADD_5_MOVES)
				{
					//go ahead and add moves, and adjust coins
					int maxMoves = getMaxMoves(gridHandle);
					maxMoves += MFGameConstants.MOVES_ADD_INCREMENT;
					setMaxMoves(gridHandle, maxMoves);
					mTotalCoinsEarned -= MFGameConstants.COINS_TO_ADD_5_MOVES;
					
					String addCoinsText = String.format(getResources().getString(R.string.add_coins_text), mTotalCoinsEarned);
					mAddCoinsButton.setText(addCoinsText);
					
					int currMove = getCurrMove(gridHandle);
					String movesText = String.format(getResources().getString(R.string.moves_remaining_text), (maxMoves - currMove));
					mMovesLabel.setText(movesText);
				}
				else
				{
					//alert hte user tht he must buy coins
					//redeem the coins, show a dialog
					AddCoinsDialog addCoinsDialog = new AddCoinsDialog(this);
					addCoinsDialog.setCanceledOnTouchOutside(false);
					addCoinsDialog.show();
				}
			}
			else if (option == GameDialog.GAME_DIALOG_ACTION_NEGATIVE_1)
			{
				//if the game had failed and the user reached here, then take him to the main menu
				int currMove = getCurrMove(gridHandle);
				int maxMoves = getMaxMoves(gridHandle);
				if (currMove == maxMoves)
				{
					finish(); // go back to the main menu
				}
				else
				{
					dialog.dismiss(); //resume current game
				}
			}
		}
	}
	
	@Override
	public void onPurchaseFinished(Purchase purchase, String pid, boolean status) 
	{
		if (pid.equals(MFGameConstants.IAP_REMOVE_ADS))
		{
			if (status == true)
			{
				//successful purchase
				//set the sharedpref
				SharedPreferences settings;
				settings = getSharedPreferences(MFGameConstants.PREFERENCE_KEY, Context.MODE_PRIVATE);
				Editor editor = settings.edit();
				editor.putBoolean(MFGameConstants.PREFERENCE_ADS_REMOVED, true);
				editor.commit();
				
				//Hide the Remove Ads button
				mRemoveAdsButton.setVisibility(View.INVISIBLE);
			}
		}
		else if (pid.equals(MFGameConstants.IAP_COINS_FIRST))
		{
			if (status == true)
			{
				//purchase successful.  Since these are consumable items, make the consume request
				mIAPManager.consumeItem(purchase);
			}
		}
		else if (pid.equals(MFGameConstants.IAP_COINS_SECOND))
		{
			if (status == true)
			{
				//purchase successful.  Since these are consumable items, make the consume request
				mIAPManager.consumeItem(purchase);
			}
		}
		else if (pid.equals(MFGameConstants.IAP_COINS_THIRD))
		{
			if (status == true)
			{
				//purchase successful.  Since these are consumable items, make the consume request
				mIAPManager.consumeItem(purchase);
			}
		}
		else if (pid.equals(MFGameConstants.IAP_COINS_FOURTH))
		{
			if (status == true)
			{
				//purchase successful.  Since these are consumable items, make the consume request
				mIAPManager.consumeItem(purchase);
			}
		}
	}

	@Override
	public void onConsumeFinished(String pid, boolean status) 
	{
		//consumed the item, now update the values
		if (pid.equals(MFGameConstants.IAP_COINS_FIRST))
		{
			mTotalCoinsEarned += MFGameConstants.COINS_IAP_COUNT_FIRST;
		}
		else if (pid.equals(MFGameConstants.IAP_COINS_SECOND))
		{
			mTotalCoinsEarned += MFGameConstants.COINS_IAP_COUNT_SECOND;
		}
		else if (pid.equals(MFGameConstants.IAP_COINS_THIRD))
		{
			mTotalCoinsEarned += MFGameConstants.COINS_IAP_COUNT_THIRD;
		}
		else if (pid.equals(MFGameConstants.IAP_COINS_FOURTH))
		{
			mTotalCoinsEarned += MFGameConstants.COINS_IAP_COUNT_FOURTH;
		}
		
		String addCoinsText = String.format(getResources().getString(R.string.add_coins_text), mTotalCoinsEarned);
		mAddCoinsButton.setText(addCoinsText);
	}
	
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) 
	{
		Log.d("gaurav", "onActivityResult(" + requestCode + "," + resultCode + "," + data);

		// Pass on the activity result to the helper for handling
		if (!mIAPManager.handleActivityResult(requestCode, resultCode, data)) {
			// not handled, so handle it ourselves (here's where you'd
			// perform any handling of activity results not related to in-app
			// billing...
			super.onActivityResult(requestCode, resultCode, data);
		}
		else {
			Log.d("gaurav", "onActivityResult handled by IABUtil.");
		}
	}
	private MFGameView mGameView; //the game view
	private int mLevel;
	private int mTotalCoinsEarned;
	private boolean mPromptUserToStore = false; // whether or not we should prompt the user to check out the store
	private TextView mMovesLabel; //label that shows the current moves
	private TextView mLevelLabel;
	private ImageButton mExitButton;
	private ImageButton mSoundButton;
	private ImageButton mRedButton;
	private ImageButton mBlueButton;
	private ImageButton mGreenButton;
	private ImageButton mYellowButton;
	private ImageButton mOrangeButton;
	private ImageButton mCyanButton;
	
	private Button mAddCoinsButton, mAddMovesButton, mAddStarsButton, mRemoveAdsButton;
	
	private AlertDialog mExitAlertDialog, mSuccessAlertDialog, mFailedAlertDialog;
	
	/**
	 * Sound related
	 */
	
	private SoundPool mSoundPool;
	private int mButtonClickSoundID, mGameSuccessSoundID, mGameFailedSoundID;
	boolean loaded = false;
	float actVolume, maxVolume, volume;
	AudioManager audioManager;
	boolean mPlaySound = false;
	int mCurrentlyPlayingStream = 0; //currently playing stream, used to stop it if still running

	/**
	 * IAP related
	 */
	private MFInAppPurchaseManager mIAPManager = null;
	AdView mAdView; // banner ad view
	
	/**
	 * Native Hooks
	 */
	private long gridHandle;
	private native long createNewGrid(int level);
	private native void deleteGrid(long handle);
	private native int getGridSize(long handle);
	private native int[] getStartPos(long handle);
	private native int getMaxMoves(long handle);
	private native void setMaxMoves(long handle, int maxMoves);
	private native int getCurrMove(long handle);
	private native int[] playMove(long handle, int color);
	private native int[] getGridData(long handle);

}