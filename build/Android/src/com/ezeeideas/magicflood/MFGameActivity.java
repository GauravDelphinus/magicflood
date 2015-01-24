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
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

public class MFGameActivity extends Activity implements View.OnClickListener, GameDialogListener, MFInAppPurchaseManager.IAPPurchaseInterface, MFGameView.GameViewTapHandler {

	
	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_game);
        
    	mGameView = (MFGameView) findViewById(R.id.game_view_id);
    	mMovesLabel = (TextView) findViewById(R.id.moves_label_id);
    	mMovesImage = (ImageView) findViewById(R.id.moves_image_id);
    	
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
    	
    	//initialize In-App Purchase
    	setupIAP();
    	
    	//initialize Ads
    	setupAds();
    	
    	setupAnimation();
    	
    	mLevel = getIntent().getIntExtra(MFGameConstants.GAME_LEVEL_KEY, 1);
    	mPromptUserToStore = getIntent().getBooleanExtra(MFGameConstants.PROMPT_USER_TO_STORE, false);
    	
    	//read system preferences of number of coins, and total points earned so far
		//get the sharepref
    	SharedPreferences settings;
		settings = getSharedPreferences(MFGameConstants.PREFERENCE_KEY, Context.MODE_PRIVATE);

		mTotalCoinsEarned = settings.getInt(MFGameConstants.PREFERENCE_TOTAL_COINS_EARNED, MFGameConstants.INITIAL_COINS_ALLOCATED);
		String coinsEarnedText = String.format(getResources().getString(R.string.coins_earned_text), mTotalCoinsEarned);
		mCoinsEarnedLabel = (TextView) findViewById(R.id.coins_text_id);
		mCoinsEarnedLabel.setText(coinsEarnedText);
		mCoinsEarnedLabel.setTypeface(face);
		
		mAddCoinsButton = (ImageButton) findViewById(R.id.add_coins_button_id);
		mAddCoinsButton.setOnClickListener(this);
		
		mAddMovesButton = (ImageButton) findViewById(R.id.add_moves_button_id);
		mAddMovesButton.setOnClickListener(this);
		
		mAddStarsButton = (ImageButton) findViewById(R.id.add_stars_button_id);
		mAddStarsButton.setOnClickListener(this);

		
		mAddHurdleSmasherButton = (ImageButton) findViewById(R.id.add_hurdle_smasher_button_id);
		mAddHurdleSmasherButton.setOnClickListener(this);
		if (mLevel <= MFGameConstants.MIN_LEVEL_TO_ADD_HURDLE_SMASHER)
		{
			mAddHurdleSmasherButton.setVisibility(View.INVISIBLE);
		}
		else
		{
			mAddHurdleSmasherButton.setVisibility(View.VISIBLE);
		}
		
		mLevelLabel = (TextView) findViewById(R.id.level_label_id);
		String levelText = String.format(getResources().getString(R.string.level_text), mLevel);
		mLevelLabel.setText(levelText);
		mLevelLabel.setTypeface(face);
		
		startNewGame(mLevel);
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
		mHurdleSmashedSoundID = mSoundPool.load(this, R.raw.hurdle_smashed_sound, 1);
		
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
		boolean showAds = true;
		
		mAdView = (AdView) findViewById(R.id.banner_ad_id);
		mRemoveAdsButton = (LinearLayout) findViewById(R.id.remove_ads_button_id);
		TextView removeAdsTV = (TextView) findViewById(R.id.remove_ads_button_text_id);
		removeAdsTV.setTypeface(MFUtils.getTextTypeface(this));
		
		SharedPreferences settings;
		settings = getSharedPreferences(MFGameConstants.PREFERENCE_KEY, Context.MODE_PRIVATE);
		boolean containsAdsKey = settings.contains(MFGameConstants.PREFERENCE_ADS_REMOVED);
		if (containsAdsKey)
		{
			showAds = !settings.getBoolean(MFGameConstants.PREFERENCE_ADS_REMOVED, false);
		}
		else
		{
			if (mIAPManager.getProductProvisioned(MFGameConstants.IAP_REMOVE_ADS))
			{
				Editor editor = settings.edit();
				editor.putBoolean(MFGameConstants.PREFERENCE_ADS_REMOVED, true);
				editor.commit();
				
				showAds = false;
			}
		}
		
		if (!showAds)
		{
			hideAds();
			
			return;
		}
		
		mRemoveAdsButton.setOnClickListener(this);
		
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
	
	private void hideAds()
	{
		mRemoveAdsButton.setVisibility(View.GONE);
		mAdView.setVisibility(View.GONE);
		
		//since the ad view is now gone, adjust dependencies
		
	}
	
	private void setupIAP()
	{
		mIAPManager = new MFInAppPurchaseManager(this);
        mIAPManager.addPurchaseListener(this);
	}
	
	private void setupAnimation()
	{
		mAnimScale = AnimationUtils.loadAnimation(this, R.anim.anim_scale);
	}
	
	private void playSound(int soundID) 
	{
		// Is the sound loaded does it already play?
		if (loaded && mPlaySound)
		{
			mCurrentlyPlayingStream = mSoundPool.play(soundID, volume, volume, 1, 0, 1f);
		}
	}
	
	private void refreshMovesUI(int currMove, int maxMoves)
	{
		//update the moves label
		String movesText = String.format(getResources().getString(R.string.moves_remaining_text), (maxMoves - currMove));	
		mMovesLabel.setText(movesText);

		/**
		 * If the moves come down to 5 or below, start animating the Add Moves button!
		 */
		if (maxMoves - currMove <= 5)
		{
			mMovesImage.setImageResource(R.drawable.ic_moves_red);
			mAddMovesButton.setImageResource(0);
			mAddMovesButton.setImageResource(R.drawable.ic_button_add_moves_red);
			mAddMovesButton.startAnimation(mAnimScale);
		}
		else
		{
			mMovesImage.setImageResource(R.drawable.ic_moves);
			mAddMovesButton.setImageResource(0);
			mAddMovesButton.setImageResource(R.drawable.ic_button_add_moves);
			mAddMovesButton.clearAnimation();
		}
	}
	
	@Override
	public void onBackPressed() 
	{
		MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_BACK_BUTTON);
		
		GameMenuDialog dialog = new GameMenuDialog(this);
		dialog.setCanceledOnTouchOutside(true);
		dialog.show();	
	}
	
	private void startNewGame(int level)
	{
		MFAnalytics.trackEvent(this,  MFAnalytics.ANALYTICS_CATEGORY_GAME,  MFAnalytics.ANALYTICS_ACTION_GAME_ACTION,  MFAnalytics.ANALYTICS_LABEL_NEW_GAME_BUTTON);
		
		Log.d("magicflood", "startNewGame, level = " + level);
		if (gridHandle != 0)
		{
			deleteGrid(gridHandle);
			gridHandle = 0;
		}
		
		/**
		 * Check if we've reached the last level!
		 */
		if (level > getNumLevels())
		{
			//reached the end of the game. Congratulate the user
			FinishedAllLevelsDialog dialog = new FinishedAllLevelsDialog(this);
			dialog.setCanceledOnTouchOutside(false);
			dialog.show();
			return;
		}
		
		//create a fresh grid by calling into the native library
		gridHandle = createNewGrid(level);
		
		int[] gridDataOneD = getGridData(gridHandle);
		int gridSize = getGridSize(gridHandle);
		
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
		
		//convert the one-dimensional array of start positions to 2D array for use in the game view
		int[] startPos = getStartPos(gridHandle);
		int numStartPos = getNumStartPos(gridHandle);
		int startPosArray[][] = new int[numStartPos][2];
		for (int i = 0; i < numStartPos; i++)
		{
			startPosArray[i][0] = startPos[2 * i];
			startPosArray[i][1] = startPos[2 * i + 1];
		}
		
		//initialize the game view with all the data for it to render the game board
		mGameView.initializeGameData(gridData, gridSize, startPosArray, numStartPos, maxMoves);
		mGameView.setTapHandler(this);
		mGameView.invalidate();
		
		refreshMovesUI(currMove, maxMoves);
		
		mLevel = level;
		String levelText = String.format(getResources().getString(R.string.level_text), mLevel);
		mLevelLabel.setText(levelText);
		
		//since we just started playing this level, update the corresponding preference
		SharedPreferences settings;
		settings = getSharedPreferences(MFGameConstants.PREFERENCE_KEY, Context.MODE_PRIVATE);
		int lastPlayedLevel = settings.getInt(MFGameConstants.PREFERENCE_LAST_PLAYED_LEVEL, 0);
		Editor editor = settings.edit();
		
		editor.putInt(MFGameConstants.PREFERENCE_LAST_PLAYED_LEVEL, mLevel);
		editor.commit();
		
		//reenable buttons if they were disabled
		enableDisableAllButtons(true);
		
		//if we are introducing stars or hurdles from this level, and this is the first time
		//play of this game, then show the introductory dialog
		refreshLifelinesUI();
	}
	
	private void refreshLifelinesUI()
	{
		if (mLevel == MFGameConstants.MIN_LEVEL_TO_ADD_STARS)
		{
			IntroduceStarsGameDialog dialog = new IntroduceStarsGameDialog(this);
			dialog.setCanceledOnTouchOutside(false);
			dialog.show();
		}
		else if (mLevel == MFGameConstants.MIN_LEVEL_TO_ADD_HURDLE_SMASHER)
		{
			IntroduceHurdleSmashersDialog dialog = new IntroduceHurdleSmashersDialog(this);
			dialog.setCanceledOnTouchOutside(false);
			dialog.show();
		}
		
		if (mLevel < MFGameConstants.MIN_LEVEL_TO_ADD_STARS)
		{
			mAddStarsButton.setVisibility(View.INVISIBLE);
		}
		else
		{
			mAddStarsButton.setVisibility(View.VISIBLE);
		}
		
		if (mLevel < MFGameConstants.MIN_LEVEL_TO_ADD_HURDLE_SMASHER)
		{
			mAddHurdleSmasherButton.setVisibility(View.INVISIBLE);
		}
		else
		{
			mAddHurdleSmasherButton.setVisibility(View.VISIBLE);
		}
	}
	
	@Override
	public void onClick(View arg0) {
		
		if (arg0.getId() ==  R.id.exit_game_button_id) //Menu button clicked
		{	
			MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_MENU_BUTTON);
			
			GameMenuDialog dialog = new GameMenuDialog(this);
			dialog.setCanceledOnTouchOutside(false);
			dialog.show();

			return;
		}	
		else if (arg0.getId() == R.id.mute_sound_id) //mute/unmute the sound
		{
			if (mPlaySound == true)
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_SOUND_ON);
				
				mPlaySound = false;
				mSoundButton.setBackgroundResource(R.drawable.ic_button_sound_off);
			}
			else
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_SOUND_OFF);
				
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
			startNewGame(mLevel + 1);
			/*
			MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_ADD_COINS_BUTTON);
			//redeem the coins, show a dialog
			if (mIAPManager.isSynchronized())
			{
				String addCoinsPriceList[] = new String[4];
				String details[] = mIAPManager.getProductDetails(MFGameConstants.IAP_COINS_FIRST);
				addCoinsPriceList[0] = details[2];
				details = mIAPManager.getProductDetails(MFGameConstants.IAP_COINS_SECOND);
				addCoinsPriceList[1] = details[2];
				details = mIAPManager.getProductDetails(MFGameConstants.IAP_COINS_THIRD);
				addCoinsPriceList[2] = details[2];
				details = mIAPManager.getProductDetails(MFGameConstants.IAP_COINS_FOURTH);
				addCoinsPriceList[3] = details[2];
				
				AddCoinsDialog dialog = new AddCoinsDialog(this, addCoinsPriceList);
				dialog.setCanceledOnTouchOutside(false);
				dialog.show();
			}
			else
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_IAP, MFAnalytics.ANALYTICS_ACTION_IAP_NOT_CONNECTED, MFAnalytics.ANALYTICS_VALUE_STORE_NOT_CONNECTED_WHILE_ADDING_COINS);
				
				StoreNotConnectedDialog dialog = new StoreNotConnectedDialog(this);
				dialog.setCanceledOnTouchOutside(false);
				dialog.show();
			}*/
			return;
		}
		else if (arg0.getId() == R.id.add_moves_button_id)
		{
			MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_ADD_MOVES_BUTTON);
			
			AddMovesDialog dialog = new AddMovesDialog(this);
			dialog.setCanceledOnTouchOutside(false);
			dialog.show();
			
			return;
		}
		else if (arg0.getId() == R.id.add_stars_button_id)
		{
			MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_ADD_STAR_BUTTON);
			
			AddStarDialog dialog = new AddStarDialog(this);
			dialog.setCanceledOnTouchOutside(false);
			dialog.show();
			
			return;
		}
		else if (arg0.getId() == R.id.add_hurdle_smasher_button_id)
		{
			MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_ADD_HURDLE_SMASHER_BUTTON);
			
			AddHurdleSmasherDialog dialog = new AddHurdleSmasherDialog(this);
			dialog.setCanceledOnTouchOutside(false);
			dialog.show();
			
			return;
		}
		else if (arg0.getId() == R.id.remove_ads_button_id)
		{
			MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_REMOVE_ADS_BUTTON);
			
			if (mIAPManager.isSynchronized())
			{
			    //Remove Ads IAP
		        String detailsArray[];
		        detailsArray = mIAPManager.getProductDetails(MFGameConstants.IAP_REMOVE_ADS);
		        
		        RemoveAdsDialog dialog = new RemoveAdsDialog(this, detailsArray[2]);
		        dialog.setCanceledOnTouchOutside(false);
		        dialog.show();
			}
			else
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_IAP, MFAnalytics.ANALYTICS_ACTION_IAP_NOT_CONNECTED, MFAnalytics.ANALYTICS_VALUE_STORE_NOT_CONNECTED_WHILE_REMOVING_ADS);
				
				StoreNotConnectedDialog dialog = new StoreNotConnectedDialog(this);
				dialog.setCanceledOnTouchOutside(false);
				dialog.show();
			}
	        
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
		
		
		
		MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_COLOR_BUTTON, colorValue);
		
		
		int[] result = playMove(gridHandle, colorValue);
		
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
		
		refreshMovesUI(currMove, maxMoves);
		
		mGameView.updateGameData(gridData);
		mGameView.invalidate();

		if (result[0] == MFGameConstants.RESULT_FAILED) //run out of moves
		{	
			enableDisableAllButtons(false);
			
			GameFailedDialog dialog = new GameFailedDialog(this);
			dialog.setCanceledOnTouchOutside(false);
			dialog.show();
			
			playSound(mGameFailedSoundID);
			
			MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_GAME_ENDED, MFAnalytics.ANALYTICS_LABEL_GAME_ENDED_FAILURE);

			
			//update the coins earned
			SharedPreferences settings;
			settings = getSharedPreferences(MFGameConstants.PREFERENCE_KEY, Context.MODE_PRIVATE);
			Editor editor = settings.edit();
			editor.putInt(MFGameConstants.PREFERENCE_TOTAL_COINS_EARNED, mTotalCoinsEarned);
			editor.commit();
			
			
			
			/** Update Points and Coins Earned **/
			//updateCoinsEarned(mTotalCoinsEarned + 1);
		}
		else if (result[0] == MFGameConstants.RESULT_SUCCESS) //game successful completed
		{	

			GameSuccessDialog dialog = new GameSuccessDialog(this);
			dialog.setCanceledOnTouchOutside(false);
			dialog.show();
			
			playSound(mGameSuccessSoundID);
			
			MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_GAME_ENDED, MFAnalytics.ANALYTICS_LABEL_GAME_ENDED_SUCCESS);
			
			//Update the last completed preference
			SharedPreferences settings;
			settings = getSharedPreferences(MFGameConstants.PREFERENCE_KEY, Context.MODE_PRIVATE);
			Editor editor = settings.edit();			
			int lastCompletedLevel = settings.getInt(MFGameConstants.PREFERENCE_LAST_COMPLETED_LEVEL, MFGameConstants.DEFAULT_LAST_COMPLETED_LEVEL);
			if (lastCompletedLevel <= mLevel)
			{
				editor.putInt(MFGameConstants.PREFERENCE_LAST_COMPLETED_LEVEL, mLevel);
				editor.commit();
			}
			
			//Unlock the next level
			int lastUnlockedLevel = settings.getInt(MFGameConstants.PREFERENCE_LAST_UNLOCKED_LEVEL, MFGameConstants.DEFAULT_LAST_UNLOCKED_LEVEL);
			if (lastUnlockedLevel <= mLevel)
			{
				lastUnlockedLevel ++;
				editor.putInt(MFGameConstants.PREFERENCE_LAST_UNLOCKED_LEVEL, lastUnlockedLevel);
				editor.commit();
			}
			
			//update the coins earned
			editor.putInt(MFGameConstants.PREFERENCE_TOTAL_COINS_EARNED, mTotalCoinsEarned);
			editor.commit();
			
			/** Update Coins Earned **/	
			updateCoinsEarned(mTotalCoinsEarned + MFGameConstants.COINS_EARNED_FACTOR_ON_GAME_COMPLETION + (maxMoves - currMove) * MFGameConstants.COINS_EARNED_FACTOR_ON_REMAINING_MOVES);
			
		}
		else
		{
			/** Normal move - didn't win or fail. **/
			playSound(mButtonClickSoundID);			
		}
		
	}
	
	private void enableDisableAllButtons(boolean enable)
	{
		mRedButton.setEnabled(enable);
		mGreenButton.setEnabled(enable);
		mBlueButton.setEnabled(enable);
		mYellowButton.setEnabled(enable);
		mOrangeButton.setEnabled(enable);
		mCyanButton.setEnabled(enable);
	}

	private void updateCoinsEarned(int newValue)
	{
		if (newValue > mTotalCoinsEarned)
		{
			CoinsUpdateHandler handler = new CoinsUpdateHandler(mCoinsEarnedLabel);
			Thread background = new Thread(new CoinsUpdaterRunnable(Math.max(mTotalCoinsEarned, newValue - 10), newValue, handler));
			background.start();
		}
		else
		{
			String coinsText = String.format(getResources().getString(R.string.coins_earned_text), newValue);
			mCoinsEarnedLabel.setText(coinsText);
		}
		
        mTotalCoinsEarned = newValue;
        
        SharedPreferences settings;
		settings = getSharedPreferences(MFGameConstants.PREFERENCE_KEY, Context.MODE_PRIVATE);
		Editor editor = settings.edit();
		editor.putInt(MFGameConstants.PREFERENCE_TOTAL_COINS_EARNED, mTotalCoinsEarned);
		editor.commit();
	}
	
	class CoinsUpdateHandler extends Handler
	{
		private static final String KEY = "i";
		private TextView mTextView;
		public CoinsUpdateHandler(TextView textView)
		{
			mTextView = textView;
		}
		public void handleMessage(Message msg) 
		{
            try {
                int i= msg.getData().getInt(KEY);
                
                String coinsText = String.format(getResources().getString(R.string.coins_earned_text), i);
                mTextView.setText(coinsText);

            } catch (Exception err) {
            }
        }
	}
	class CoinsUpdaterRunnable implements Runnable
	{
		private static final int FRAME_TIME_MS = 50;
	    private static final String KEY = "i";
		private int mFromValue, mToValue;
		private Handler mHandler;
		public CoinsUpdaterRunnable(int fromValue, int toValue, Handler handler)
		{
			mFromValue = fromValue;
			mToValue = toValue;
			mHandler = handler;
		}
		
		public void run() 
		{
            try {
                for (int i = mFromValue; i <= mToValue; i++) {
                    Thread.sleep(FRAME_TIME_MS);
                    Bundle data= new Bundle();
                    data.putInt(KEY, i);
                    Message message = mHandler.obtainMessage();
                    message.setData(data);
                    mHandler.sendMessage(message);
                }
            }
            catch (Throwable t) {
            }
        }
	}
	
	@Override
	public void onDialogOptionSelected(Dialog dialog, int option) 
	{		
		/**
		 * If there's a sound playing, stop it!
		 */
		mSoundPool.stop(mCurrentlyPlayingStream);
		
		if (dialog.getClass() == GameMenuDialog.class)
		{
			if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_1) //Go back to Levels Screen
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_VIEW_LEVELS_BUTTON);
				
				finish();
			}
			else if (option == GameDialog.GAME_DIALOG_ACTION_NEGATIVE_1) // Resume current game
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_CANCEL_GAME_MENU_DIALOG);
				
				if (getCurrMove(gridHandle) == getMaxMoves(gridHandle))
				{
					/**
					 * Came here when the game was already finished, so go back to the main menu
					 */
					finish();
				}
				else
				{
					//resume the game
					dialog.cancel();
				}
			}
			else if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_2) //Replay Game
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_REPLAY_GAME_BUTTON);
				
				dialog.cancel();
				startNewGame(mLevel);
			}
		}	
		else if (dialog.getClass() == GameFailedDialog.class)
		{
			if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_1) //Play On
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_PLAY_ON_BUTTON);
				
				dialog.cancel();
				
				/** Prompt the user with adding moves to continue playing the current game. **/
				AddMovesDialog addMovesDialog = new AddMovesDialog(this);
				addMovesDialog.setCanceledOnTouchOutside(false);
				addMovesDialog.show();
			}
			else if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_2 || option == GameDialog.GAME_DIALOG_ACTION_NEGATIVE_1) // End Game
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_END_GAME_BUTTON);
				
				/** Take the user to the Try Again dialog **/
				GameMenuDialog tryAgainDialog = new GameMenuDialog(this);
				tryAgainDialog.setCanceledOnTouchOutside(false);
				tryAgainDialog.show();
			}
		}	
		else if (dialog.getClass() == GameSuccessDialog.class)
		{
			if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_1) //Start the next game
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_NEXT_GAME_BUTTON);
				
				dialog.cancel();
				
				startNewGame(mLevel + 1);
			}
			else if (option == GameDialog.GAME_DIALOG_ACTION_NEGATIVE_1) // Go back to the Main Menu
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_CANCEL_GAME_SUCCESS_DIALOG);
				
				finish();
			}
		}
		else if (dialog.getClass() == RemoveAdsDialog.class)
		{
			if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_1)
			{
				//purchase for Remove Ads IAP requested
				mIAPManager.purchaseItem(MFGameConstants.IAP_REMOVE_ADS);
			}
			else if (option == GameDialog.GAME_DIALOG_ACTION_NEGATIVE_1)
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_CANCEL_REMOVE_ADS_DIALOG);
				
				dialog.dismiss();
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
			else if (option == GameDialog.GAME_DIALOG_ACTION_NEGATIVE_1) //cancel purchase
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_CANCEL_ADD_COINS_DIALOG);
				
				/**
				 * If the user landed here afer having 'failed' the game,
				 * show him the game menu dialog again
				 */
				if (getCurrMove(gridHandle) == getMaxMoves(gridHandle))
				{
					GameMenuDialog menuDialog = new GameMenuDialog(this);
					menuDialog.setCanceledOnTouchOutside(false);
					menuDialog.show();
				}
			}
		}
		else if (dialog.getClass() == AddMovesDialog.class)
		{
			if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_1)
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_REDEEM_COINS_FOR_MOVES_BUTTON);
				
				if (mTotalCoinsEarned >= MFGameConstants.COINS_TO_ADD_5_MOVES)
				{
					//go ahead and add moves, and adjust coins
					int maxMoves = getMaxMoves(gridHandle);
					maxMoves += MFGameConstants.MOVES_ADD_INCREMENT;
					setMaxMoves(gridHandle, maxMoves);
					
					updateCoinsEarned(mTotalCoinsEarned - MFGameConstants.COINS_TO_ADD_5_MOVES);
					MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_GAME_ACTION, MFAnalytics.ANALYTICS_LABEL_GAME_ACTION_COINS_REDEEMED_FOR_MOVES);
					
					int currMove = getCurrMove(gridHandle);
					refreshMovesUI(currMove, maxMoves);
					
					enableDisableAllButtons(true);
				}
				else
				{
					//alert hte user tht he must buy coins
					//redeem the coins, show a dialog
					if (mIAPManager.isSynchronized())
					{
						String addCoinsPriceList[] = new String[4];
						String details[] = mIAPManager.getProductDetails(MFGameConstants.IAP_COINS_FIRST);
						addCoinsPriceList[0] = details[2];
						details = mIAPManager.getProductDetails(MFGameConstants.IAP_COINS_SECOND);
						addCoinsPriceList[1] = details[2];
						details = mIAPManager.getProductDetails(MFGameConstants.IAP_COINS_THIRD);
						addCoinsPriceList[2] = details[2];
						details = mIAPManager.getProductDetails(MFGameConstants.IAP_COINS_FOURTH);
						addCoinsPriceList[3] = details[2];
						
						AddCoinsDialog addCoinsDialog = new AddCoinsDialog(this, addCoinsPriceList);
						addCoinsDialog.setCanceledOnTouchOutside(false);
						addCoinsDialog.show();
					}
					else
					{
						MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_IAP, MFAnalytics.ANALYTICS_ACTION_IAP_NOT_CONNECTED, MFAnalytics.ANALYTICS_VALUE_STORE_NOT_CONNECTED_WHILE_ADDING_MOVES);
						
						StoreNotConnectedDialog notConnectedDialog = new StoreNotConnectedDialog(this);
						notConnectedDialog.setCanceledOnTouchOutside(false);
						notConnectedDialog.show();
					}
				}
			}
			else if (option == GameDialog.GAME_DIALOG_ACTION_NEGATIVE_1)
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_CANCEL_ADD_MOVES_DIALOG);
				
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
		else if (dialog.getClass() == AddStarDialog.class)
		{
			if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_1)
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_REDEEM_COINS_FOR_STAR_BUTTON);
				
				if (mTotalCoinsEarned >= MFGameConstants.COINS_TO_ADD_A_STAR)
				{
					//go ahead and add star, and adjust coins
					addStartPos(gridHandle);
					
					updateCoinsEarned(mTotalCoinsEarned - MFGameConstants.COINS_TO_ADD_A_STAR);
					MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_GAME_ACTION, MFAnalytics.ANALYTICS_LABEL_GAME_ACTION_COINS_REDEEMED_FOR_STAR);
					
					//update the game view
					int[] startPos = getStartPos(gridHandle);
					int numStartPos = getNumStartPos(gridHandle);
					int startPosArray[][] = new int[numStartPos][2];
					for (int i = 0; i < numStartPos; i++)
					{
						startPosArray[i][0] = startPos[2 * i];
						startPosArray[i][1] = startPos[2 * i + 1];
					}
					mGameView.updateStartPos(startPosArray, numStartPos);
					mGameView.invalidate();
				}
				else
				{
					//alert hte user tht he must buy coins
					//redeem the coins, show a dialog
					if (mIAPManager.isSynchronized())
					{
						String addCoinsPriceList[] = new String[4];
						String details[] = mIAPManager.getProductDetails(MFGameConstants.IAP_COINS_FIRST);
						addCoinsPriceList[0] = details[2];
						details = mIAPManager.getProductDetails(MFGameConstants.IAP_COINS_SECOND);
						addCoinsPriceList[1] = details[2];
						details = mIAPManager.getProductDetails(MFGameConstants.IAP_COINS_THIRD);
						addCoinsPriceList[2] = details[2];
						details = mIAPManager.getProductDetails(MFGameConstants.IAP_COINS_FOURTH);
						addCoinsPriceList[3] = details[2];
						
						AddCoinsDialog addCoinsDialog = new AddCoinsDialog(this, addCoinsPriceList);
						addCoinsDialog.setCanceledOnTouchOutside(false);
						addCoinsDialog.show();
					}
					else
					{
						MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_IAP, MFAnalytics.ANALYTICS_ACTION_IAP_NOT_CONNECTED, MFAnalytics.ANALYTICS_VALUE_STORE_NOT_CONNECTED_WHILE_ADDING_STAR);
						
						StoreNotConnectedDialog notConnectedDialog = new StoreNotConnectedDialog(this);
						notConnectedDialog.setCanceledOnTouchOutside(false);
						notConnectedDialog.show();
					}
				}
			}
			else if (option == GameDialog.GAME_DIALOG_ACTION_NEGATIVE_1)
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_CANCEL_ADD_STAR_DIALOG);
				
				dialog.dismiss(); //resume current game
			}
		}
		else if (dialog.getClass() == AddHurdleSmasherDialog.class)
		{
			if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_1)
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_REDEEM_COINS_FOR_HURDLE_SMASHER);
				
				if (mTotalCoinsEarned >= MFGameConstants.COINS_TO_ADD_A_HURDLE_SMASHER)
				{				
					updateCoinsEarned(mTotalCoinsEarned - MFGameConstants.COINS_TO_ADD_A_HURDLE_SMASHER);
					MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_GAME_ACTION, MFAnalytics.ANALYTICS_LABEL_GAME_ACTION_COINS_REDEEMED_FOR_HURDLE_SMASHER);
					
					HurdleSmasherInfoDialog hurdleDialog = new HurdleSmasherInfoDialog(this, HurdleSmasherInfoDialog.TYPE_TAP);
					hurdleDialog.setCanceledOnTouchOutside(false);
					hurdleDialog.show();
					
					mHurdleSmashMode = true;
					enableDisableAllButtons(false);
					mGameView.setClickable(true);
				}
				else
				{
					//alert hte user tht he must buy coins
					//redeem the coins, show a dialog
					if (mIAPManager.isSynchronized())
					{
						String addCoinsPriceList[] = new String[4];
						String details[] = mIAPManager.getProductDetails(MFGameConstants.IAP_COINS_FIRST);
						addCoinsPriceList[0] = details[2];
						details = mIAPManager.getProductDetails(MFGameConstants.IAP_COINS_SECOND);
						addCoinsPriceList[1] = details[2];
						details = mIAPManager.getProductDetails(MFGameConstants.IAP_COINS_THIRD);
						addCoinsPriceList[2] = details[2];
						details = mIAPManager.getProductDetails(MFGameConstants.IAP_COINS_FOURTH);
						addCoinsPriceList[3] = details[2];
						
						AddCoinsDialog addCoinsDialog = new AddCoinsDialog(this, addCoinsPriceList);
						addCoinsDialog.setCanceledOnTouchOutside(false);
						addCoinsDialog.show();
					}
					else
					{
						MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_IAP, MFAnalytics.ANALYTICS_ACTION_IAP_NOT_CONNECTED, MFAnalytics.ANALYTICS_VALUE_STORE_NOT_CONNECTED_WHILE_ADDING_HURDLE_SMASHER);
						
						StoreNotConnectedDialog notConnectedDialog = new StoreNotConnectedDialog(this);
						notConnectedDialog.setCanceledOnTouchOutside(false);
						notConnectedDialog.show();
					}
				}
			}
			else if (option == GameDialog.GAME_DIALOG_ACTION_NEGATIVE_1)
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_CANCEL_ADD_HURDLE_SMASHER_DIALOG);
				
				dialog.dismiss(); //resume current game
			}
		}
		else if (dialog.getClass() == FinishedAllLevelsDialog.class)
		{
			if (option == GameDialog.GAME_DIALOG_ACTION_NEGATIVE_1)
			{
				//User has already completed ALL levels in the game.  So just finish the activity
				//and take him back to the main screen.
				finish();
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
				
				//hide Ads
				hideAds();
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
			updateCoinsEarned(mTotalCoinsEarned + MFGameConstants.COINS_IAP_COUNT_FIRST);
		}
		else if (pid.equals(MFGameConstants.IAP_COINS_SECOND))
		{
			updateCoinsEarned(mTotalCoinsEarned + MFGameConstants.COINS_IAP_COUNT_SECOND);
		}
		else if (pid.equals(MFGameConstants.IAP_COINS_THIRD))
		{
			updateCoinsEarned(mTotalCoinsEarned + MFGameConstants.COINS_IAP_COUNT_THIRD);
		}
		else if (pid.equals(MFGameConstants.IAP_COINS_FOURTH))
		{
			updateCoinsEarned(mTotalCoinsEarned + MFGameConstants.COINS_IAP_COUNT_FOURTH);
		}
		
		/*
		 * 
		 * if you landed here beucase of "play on" after failing the game, then take
		 * him back to the play on dialog
		 */
		if (getCurrMove(gridHandle) == getMaxMoves(gridHandle))
		{
			AddMovesDialog addMovesDialog = new AddMovesDialog(this);
			addMovesDialog.setCanceledOnTouchOutside(false);
			addMovesDialog.show();
		}
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
	
	@Override
	public void handleGameViewTap(int col, int row) 
	{
		int result = smashHurdle(gridHandle, col, row);
		if (result == 1)
		{
			/**
			 * Show the animation and play a sound!
			 */
			/*
			RelativeLayout rl = (RelativeLayout) findViewById(R.id.game_view_layout_id);
			ExplodeView explodeView = new ExplodeView(this);
			RelativeLayout.LayoutParams params = new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.WRAP_CONTENT, RelativeLayout.LayoutParams.WRAP_CONTENT);
			params.leftMargin = 50;
			params.topMargin = 60;
			rl.addView(explodeView, params);
			
			*/
			
			playSound(mHurdleSmashedSoundID);
			
			//successfuly smashed a hurdle
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
			
			mGameView.updateGameData(gridData);
			
			mGameView.invalidate();
			
			mNumHurdleSmashTries = 0;
			
			mHurdleSmashMode = false;
			enableDisableAllButtons(true);
			mGameView.setClickable(false);
		}
		else
		{
			mNumHurdleSmashTries++;
			if (mNumHurdleSmashTries > MAX_HURDLE_SMASH_TRIES)
			{
				//give up!
				mNumHurdleSmashTries = 0; //reset
				
				HurdleSmasherInfoDialog hurdleDialog = new HurdleSmasherInfoDialog(this, HurdleSmasherInfoDialog.TYPE_GIVING_UP);
				hurdleDialog.setCanceledOnTouchOutside(false);
				hurdleDialog.show();
				
				mHurdleSmashMode = false;
				enableDisableAllButtons(true);
				mGameView.setClickable(false);
			}
			else
			{
				HurdleSmasherInfoDialog hurdleDialog = new HurdleSmasherInfoDialog(this, HurdleSmasherInfoDialog.TYPE_RETRY);
				hurdleDialog.setCanceledOnTouchOutside(false);
				hurdleDialog.show();
			}
		}
	}
	
	private MFGameView mGameView; //the game view
	private int mLevel;
	private int mTotalCoinsEarned;
	private boolean mPromptUserToStore = false; // whether or not we should prompt the user to check out the store
	private TextView mMovesLabel; //label that shows the current moves
	private TextView mLevelLabel, mCoinsEarnedLabel;
	private ImageButton mExitButton;
	private ImageButton mSoundButton;
	private ImageButton mRedButton;
	private ImageButton mBlueButton;
	private ImageButton mGreenButton;
	private ImageButton mYellowButton;
	private ImageButton mOrangeButton;
	private ImageButton mCyanButton;
	
	private ImageButton mAddCoinsButton, mAddMovesButton, mAddStarsButton, mAddHurdleSmasherButton;
	private LinearLayout mRemoveAdsButton;
	private ImageView mMovesImage;
	
	private AlertDialog mExitAlertDialog, mSuccessAlertDialog, mFailedAlertDialog;
	
	/**
	 * Animations
	 */
	private Animation mAnimScale;
	
	/**
	 * Hurdle SMasher
	 */
	private boolean mHurdleSmashMode; //whether we're in the mode where user is selecting a hurdle to smash
	private int mNumHurdleSmashTries; //number of times the user has tried to unsuccessfully smash the hurdle
	private static final int MAX_HURDLE_SMASH_TRIES = 3;
	/**
	 * Sound related
	 */
	
	private SoundPool mSoundPool;
	private int mButtonClickSoundID, mGameSuccessSoundID, mGameFailedSoundID, mHurdleSmashedSoundID;
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
	private native int getNumLevels();
	private native long createNewGrid(int level);
	private native void deleteGrid(long handle);
	private native int getGridSize(long handle);
	private native int[] getStartPos(long handle);
	private native int getNumStartPos(long handle);
	private native void addStartPos(long handle);
	private native int getMaxMoves(long handle);
	private native void setMaxMoves(long handle, int maxMoves);
	private native int getCurrMove(long handle);
	private native int[] playMove(long handle, int color);
	private native int[] getGridData(long handle);
	private native int smashHurdle(long handle, int x, int y);



}