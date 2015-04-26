package com.ezeeideas.magicflood;

import java.util.Timer;
import java.util.TimerTask;

import com.ezeeideas.magicflood.GameDialog.GameDialogListener;
import com.ezeeideas.magicflood.iabutil.Purchase;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdView;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.media.AudioManager;
import android.media.SoundPool;
import android.media.SoundPool.OnLoadCompleteListener;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
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
    	mMovesLabel.setTypeface(MFUtils.getTextTypeface(this));
    
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

		int coins = settings.getInt(MFGameConstants.PREFERENCE_TOTAL_COINS_EARNED, MFGameConstants.INITIAL_COINS_ALLOCATED);
		setCoins(coins);
		String coinsEarnedText = String.format(getResources().getString(R.string.coins_earned_text), coins);
		mCoinsEarnedLabel = (TextView) findViewById(R.id.coins_text_id);
		mCoinsEarnedLabel.setText(coinsEarnedText);
		mCoinsEarnedLabel.setTypeface(MFUtils.getTextTypeface(this));
		
		mAddCoinsButton = (ImageButton) findViewById(R.id.add_coins_button_id);
		mAddCoinsButton.setOnClickListener(this);
		
		mAddMovesButton = (ImageButton) findViewById(R.id.add_moves_button_id);
		mAddMovesButton.setOnClickListener(this);
		
		mAddStarsButton = (ImageButton) findViewById(R.id.add_stars_button_id);
		mAddStarsButton.setOnClickListener(this);

		
		mAddHurdleSmasherButton = (ImageButton) findViewById(R.id.add_hurdle_smasher_button_id);
		mAddHurdleSmasherButton.setOnClickListener(this);
		
		mAddBridgeButton = (ImageButton) findViewById(R.id.add_bridge_button_id);
		mAddBridgeButton.setOnClickListener(this);
		
		mLevelLabel = (TextView) findViewById(R.id.level_label_id);
		String levelText = String.format(getResources().getString(R.string.level_text), mLevel);
		mLevelLabel.setText(levelText);
		mLevelLabel.setTypeface(MFUtils.getTextTypeface(this));
		
		startNewGame(mLevel);
    }
	
	@Override
	protected void onDestroy()
	{
		super.onDestroy();
		deleteGrid(gridHandle);
		
		//Unbind the service manager for IAP
        if (mIAPManager != null)
        {
            mIAPManager.unbind();
        } 
        
        //stop the timer
        if (mStarAnimationTimer != null)
        {
        	mStarAnimationTimer.cancel();
        }
	}
	
	private void startTimer()
	{
		mStarAnimationTimer = new Timer();
		mStarAnimationTimer.scheduleAtFixedRate(new AnimationTimerTask(), STAR_ANIMATION_INTERVAL, STAR_ANIMATION_INTERVAL);
		
		mGameView.mCurrentStarSize = STAR_ANIMATION_INITIAL_SIZE;
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
		mStarPlacedSoundID = mSoundPool.load(this, R.raw.star_placed_sound, 1);
		mBridgePlacedSoundID = mSoundPool.load(this, R.raw.bridge_created_sound, 1);
		
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
        //.addTestDevice("D270918A90127FD1558623AC978405DF") //Anu's Samsung Galaxy S3
        //.addTestDevice("EDA0579D1B567771CB429E8A84668A3D") //Galax Tab 10.1 "
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
		
		/**
		 * Check to see if we're in the mode where the hurdle smasher or a star
		 * needs to be placed, and hence waiting for user to tap on the screen.
		 * 
		 * If so, alert the user
		 */
		if (mHurdleSmashMode || mStarPlacementMode || mBridgeMode)
		{
			mHurdleSmashMode = false;
			mStarPlacementMode = false;
			mBridgeMode = false;
			
			refreshLifelinesUI();
		}
		else
		{
			GameMenuDialog dialog = new GameMenuDialog(this, DIALOG_DATA_NONE);
			dialog.setCanceledOnTouchOutside(true);
			dialog.show();
		}
	}
	
	private void startNewGame(int level)
	{
		MFAnalytics.trackEvent(this,  MFAnalytics.ANALYTICS_CATEGORY_GAME,  MFAnalytics.ANALYTICS_ACTION_GAME_ACTION,  MFAnalytics.ANALYTICS_LABEL_NEW_GAME_BUTTON);
		
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
			FinishedAllLevelsDialog dialog = new FinishedAllLevelsDialog(this, DIALOG_DATA_NONE);
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
		Editor editor = settings.edit();
		
		editor.putInt(MFGameConstants.PREFERENCE_LAST_PLAYED_LEVEL, mLevel);
		editor.commit();
		
		//reenable buttons if they were disabled
		enableDisableAllButtons(true);
		
		//if we are introducing stars or hurdles from this level, and this is the first time
		//play of this game, then show the introductory dialog
		refreshLifelinesUI();
		
		startTimer();
	}
	
	private void refreshLifelinesUI()
	{
		SharedPreferences settings;
		settings = getSharedPreferences(MFGameConstants.PREFERENCE_KEY, Context.MODE_PRIVATE);
		
		if (mLevel == getMinLevelToAddStars())
		{
			boolean alreadyShown = settings.getBoolean(MFGameConstants.PREFERENCE_STARS_UNLOCKED, false);
			Editor editor = settings.edit();
			editor.putBoolean(MFGameConstants.PREFERENCE_STARS_UNLOCKED, true);
			editor.commit();
			
			if (!alreadyShown)
			{
				IntroduceStarsGameDialog dialog = new IntroduceStarsGameDialog(this, DIALOG_DATA_NONE);
				dialog.setCanceledOnTouchOutside(false);
				dialog.show();
			}
		}
		else if (mLevel == getMinLevelToAddHurdleSmasher())
		{
			boolean alreadyShown = settings.getBoolean(MFGameConstants.PREFERENCE_HURDLE_SMASHERS_UNLOCKED, false);
			Editor editor = settings.edit();
			editor.putBoolean(MFGameConstants.PREFERENCE_HURDLE_SMASHERS_UNLOCKED, true);
			editor.commit();
			
			if (!alreadyShown)
			{
				IntroduceHurdleSmashersDialog dialog = new IntroduceHurdleSmashersDialog(this, DIALOG_DATA_NONE);
				dialog.setCanceledOnTouchOutside(false);
				dialog.show();
			}
		}
		else if (mLevel == getMinLevelToAddBridge())
		{
			boolean alreadyShown = settings.getBoolean(MFGameConstants.PREFERENCE_BRIDGES_UNLOCKED, false);
			Editor editor = settings.edit();
			editor.putBoolean(MFGameConstants.PREFERENCE_BRIDGES_UNLOCKED, true);
			editor.commit();
			
			if (!alreadyShown)
			{
				IntroduceBridgesDialog dialog = new IntroduceBridgesDialog(this, DIALOG_DATA_NONE);
				dialog.setCanceledOnTouchOutside(false);
				dialog.show();
			}
		}
		
		if (mLevel < getMinLevelToAddStars())
		{
			mAddStarsButton.setVisibility(View.INVISIBLE);
		}
		else
		{
			mAddStarsButton.setVisibility(View.VISIBLE);
			
			int numStars = settings.getInt(MFGameConstants.PREFERENCE_TOTAL_STARS_EARNED, MFGameConstants.INITIAL_STARS_ALLOCATED);
			if (numStars == 0)
			{
				mAddStarsButton.setImageResource(0);
				mAddStarsButton.setImageResource(R.drawable.ic_button_add_star);
			}
			else if (numStars == 1)
			{
				mAddStarsButton.setImageResource(0);
				mAddStarsButton.setImageResource(R.drawable.ic_button_use_star_1);
			}
			else if (numStars == 2)
			{
				mAddStarsButton.setImageResource(0);
				mAddStarsButton.setImageResource(R.drawable.ic_button_use_star_2);
			}
		}
		
		if (mLevel < getMinLevelToAddHurdleSmasher())
		{
			mAddHurdleSmasherButton.setVisibility(View.INVISIBLE);
		}
		else
		{
			mAddHurdleSmasherButton.setVisibility(View.VISIBLE);
			
			int numSmashers = settings.getInt(MFGameConstants.PREFERENCE_TOTAL_HURDLE_SMASHERS_EARNED, MFGameConstants.INITIAL_HURDLE_SMASHERS_ALLOCATED);
			if (numSmashers == 0)
			{
				mAddHurdleSmasherButton.setImageResource(0);
				mAddHurdleSmasherButton.setImageResource(R.drawable.ic_button_add_hurdle_smasher);
			}
			else if (numSmashers == 1)
			{
				mAddHurdleSmasherButton.setImageResource(0);
				mAddHurdleSmasherButton.setImageResource(R.drawable.ic_button_use_hurdle_smasher_1);
			}
			else if (numSmashers == 2)
			{
				mAddHurdleSmasherButton.setImageResource(0);
				mAddHurdleSmasherButton.setImageResource(R.drawable.ic_button_use_hurdle_smasher_2);
			}
		}
		
		if (mLevel < getMinLevelToAddBridge())
		{
			mAddBridgeButton.setVisibility(View.INVISIBLE);
		}
		else
		{
			mAddBridgeButton.setVisibility(View.VISIBLE);
			
			int numBridges = settings.getInt(MFGameConstants.PREFERENCE_TOTAL_BRIDGES_EARNED, MFGameConstants.INITIAL_BRIDGES_ALLOCATED);
			if (numBridges == 0)
			{
				mAddBridgeButton.setImageResource(0);
				mAddBridgeButton.setImageResource(R.drawable.ic_button_add_bridge);
			}
			else if (numBridges == 1)
			{
				mAddBridgeButton.setImageResource(0);
				mAddBridgeButton.setImageResource(R.drawable.ic_button_use_bridge_1);
			}
			else if (numBridges == 2)
			{
				mAddBridgeButton.setImageResource(0);
				mAddBridgeButton.setImageResource(R.drawable.ic_button_use_bridge_2);
			}
		}
		
		if (mStarPlacementMode)
		{
			enableDisableAllButtons(false);
			
			mAddStarsButton.setImageResource(0);
			mAddStarsButton.setImageResource(R.drawable.ic_button_star_mode);
			
			mAddStarsButton.setEnabled(true);
		}
		else if (mHurdleSmashMode)
		{
			enableDisableAllButtons(false);
			
			mAddHurdleSmasherButton.setImageResource(0);
			mAddHurdleSmasherButton.setImageResource(R.drawable.ic_button_hurdle_smasher_mode);
			
			mAddHurdleSmasherButton.setEnabled(true);
		}
		else if (mBridgeMode)
		{
			enableDisableAllButtons(false);
			
			mAddBridgeButton.setImageResource(0);
			mAddBridgeButton.setImageResource(R.drawable.ic_button_bridge_mode);
			
			mAddBridgeButton.setEnabled(true);
		}
		else
		{
			enableDisableAllButtons(true);
		}
	}
	
	@Override
	public void onClick(View arg0) {
		
		if (arg0.getId() ==  R.id.exit_game_button_id) //Menu button clicked
		{	
			MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_MENU_BUTTON);
			
			GameMenuDialog dialog = new GameMenuDialog(this, DIALOG_DATA_NONE);
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
			MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_ADD_COINS_BUTTON);

			AddCoinsDialog dialog = new AddCoinsDialog(this, 0, DIALOG_DATA_NONE, mIAPManager, getNumCoinsIAPFirst(), getNumCoinsIAPSecond(), getNumCoinsIAPThird(), getNumCoinsIAPFourth());
			dialog.setCanceledOnTouchOutside(false);
			dialog.show();

			return;
		}
		else if (arg0.getId() == R.id.add_moves_button_id)
		{
			MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_ADD_MOVES_BUTTON);
			
			AddMovesDialog dialog = new AddMovesDialog(this, DIALOG_DATA_NONE, getNumCoinsForMoves());
			dialog.setCanceledOnTouchOutside(false);
			dialog.show();
			
			return;
		}
		else if (arg0.getId() == R.id.add_stars_button_id)
		{
			MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_ADD_STAR_BUTTON);
			
			/**
			 * If in the Star Placement mode, exit the mode.
			 */
			if (mStarPlacementMode)
			{
				mStarPlacementMode = false;
				refreshLifelinesUI();
				
				return;
			}
			
			int numStars = MFUtils.prefGetInt(this, MFGameConstants.PREFERENCE_TOTAL_STARS_EARNED, MFGameConstants.INITIAL_STARS_ALLOCATED);
			if (numStars == 0)
			{
				AddStarDialog dialog = new AddStarDialog(this, DIALOG_DATA_NONE, getNumCoinsForStar(1), getNumCoinsForStar(2));
				dialog.setCanceledOnTouchOutside(false);
				dialog.show();
			}
			else
			{
				int starPlacementCount = MFUtils.prefGetInt(this, MFGameConstants.PREFERENCE_STAR_PLACEMENT_COUNT, 0);
				if (starPlacementCount < MFGameConstants.MAX_STAR_PLACEMENT_DIALOG_COUNT)
				{					
					//show the dialog
					StarPlacementInfoDialog starDialog = new StarPlacementInfoDialog(this, HurdleSmasherInfoDialog.TYPE_TAP, DIALOG_DATA_NONE);
					starDialog.setCanceledOnTouchOutside(false);
					starDialog.show();
					
					starPlacementCount ++;
					
					MFUtils.prefPutInt(this, MFGameConstants.PREFERENCE_STAR_PLACEMENT_COUNT, starPlacementCount);
				}
				else
				{
					//show the toast
					Toast.makeText(this, getResources().getString(R.string.toast_star_placement_info), Toast.LENGTH_SHORT).show();
				}

				/** Enter the Star Placement Mode **/
				mStarPlacementMode = true;
				
				refreshLifelinesUI();
			}
			
			return;
		}
		else if (arg0.getId() == R.id.add_hurdle_smasher_button_id)
		{
			MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_ADD_HURDLE_SMASHER_BUTTON);
			
			/**
			 * If in the Hurdle Smasher Placement mode, exit the mode.
			 */
			if (mHurdleSmashMode)
			{
				mHurdleSmashMode = false;
				refreshLifelinesUI();
				
				return;
			}
			
			int numSmashers = MFUtils.prefGetInt(this, MFGameConstants.PREFERENCE_TOTAL_HURDLE_SMASHERS_EARNED, MFGameConstants.INITIAL_HURDLE_SMASHERS_ALLOCATED);
			if (numSmashers == 0)
			{
				AddHurdleSmasherDialog dialog = new AddHurdleSmasherDialog(this, DIALOG_DATA_NONE, getNumCoinsForHurdleSmasher(1), getNumCoinsForHurdleSmasher(2));
				dialog.setCanceledOnTouchOutside(false);
				dialog.show();
			}
			else
			{
				int smasherPlacementCount = MFUtils.prefGetInt(this, MFGameConstants.PREFERENCE_HURDLE_SMASHER_PLACEMENT_COUNT, 0);
				if (smasherPlacementCount < MFGameConstants.MAX_HURDLE_SMASHER_PLACEMENT_DIALOG_COUNT)
				{				
					HurdleSmasherInfoDialog hurdleDialog = new HurdleSmasherInfoDialog(this, HurdleSmasherInfoDialog.TYPE_TAP, DIALOG_DATA_NONE);
					hurdleDialog.setCanceledOnTouchOutside(false);
					hurdleDialog.show();
					
					smasherPlacementCount ++;
					
					MFUtils.prefPutInt(this, MFGameConstants.PREFERENCE_HURDLE_SMASHER_PLACEMENT_COUNT, smasherPlacementCount);
				}
				else
				{
					//show the toast
					Toast.makeText(this, getResources().getString(R.string.toast_hurdle_smasher_placement_info), Toast.LENGTH_SHORT).show();
				}

				/** Enter the Hurdle Smashing Mode **/
				mHurdleSmashMode = true;
				
				refreshLifelinesUI();
			}
			
			return;
		}
		else if (arg0.getId() == R.id.add_bridge_button_id)
		{
			MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_ADD_BRIDGE_BUTTON);
			
			/**
			 * If in the Bridge Placement mode, exit the mode.
			 */
			if (mBridgeMode)
			{
				mBridgeMode = false;
				refreshLifelinesUI();
				
				return;
			}
			
			int numBridges = MFUtils.prefGetInt(this, MFGameConstants.PREFERENCE_TOTAL_BRIDGES_EARNED, MFGameConstants.INITIAL_BRIDGES_ALLOCATED);
			if (numBridges == 0)
			{
				AddBridgeDialog dialog = new AddBridgeDialog(this, DIALOG_DATA_NONE, getNumCoinsForBridge(1), getNumCoinsForBridge(2));
				dialog.setCanceledOnTouchOutside(false);
				dialog.show();
			}
			else
			{
				int bridgePlacementCount = MFUtils.prefGetInt(this, MFGameConstants.PREFERENCE_BRIDGE_PLACEMENT_COUNT, 0);
				if (bridgePlacementCount < MFGameConstants.MAX_BRIDGE_PLACEMENT_DIALOG_COUNT)
				{				
					BridgeInfoDialog bridgeDialog = new BridgeInfoDialog(this, DIALOG_DATA_NONE);
					bridgeDialog.setCanceledOnTouchOutside(false);
					bridgeDialog.show();
					
					bridgePlacementCount ++;
					
					MFUtils.prefPutInt(this, MFGameConstants.PREFERENCE_BRIDGE_PLACEMENT_COUNT, bridgePlacementCount);
				}
				else
				{
					//show the toast
					Toast.makeText(this, getResources().getString(R.string.toast_bridge_placement_info), Toast.LENGTH_SHORT).show();
				}

				/** Enter the Hurdle Smashing Mode **/
				mBridgeMode = true;
				
				refreshLifelinesUI();
				mGameView.enterExitBridgeBuildingMode(true, true);
			}
			
			return;
		}
		else if (arg0.getId() == R.id.remove_ads_button_id)
		{
			MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_REMOVE_ADS_BUTTON);

			RemoveAdsDialog dialog = new RemoveAdsDialog(this, DIALOG_DATA_NONE, mIAPManager);
			dialog.setCanceledOnTouchOutside(false);
			dialog.show();

			return;
		}
		
		int colorValue = MFGameConstants.GRID_OBSTACLE;
		if (arg0.getId() == R.id.red_button_id)
		{
			colorValue = MFGameConstants.GRID_COLOR_RED;
		}
		else if (arg0.getId() == R.id.blue_button_id)
		{
			colorValue = MFGameConstants.GRID_COLOR_BLUE;
		}
		else if (arg0.getId() == R.id.green_button_id)
		{
			colorValue = MFGameConstants.GRID_COLOR_GREEN;
		}
		else if (arg0.getId() == R.id.yellow_button_id)
		{
			colorValue = MFGameConstants.GRID_COLOR_YELLOW;
		}
		else if (arg0.getId() == R.id.orange_button_id)
		{
			colorValue = MFGameConstants.GRID_COLOR_ORANGE;
		}
		else if (arg0.getId() == R.id.cyan_button_id)
		{
			colorValue = MFGameConstants.GRID_COLOR_CYAN;
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
			
			GameFailedDialog dialog = new GameFailedDialog(this, DIALOG_DATA_NONE);
			dialog.setCanceledOnTouchOutside(false);
			dialog.show();
			
			playSound(mGameFailedSoundID);
			
			MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_GAME_ENDED, MFAnalytics.ANALYTICS_LABEL_GAME_ENDED_FAILURE);
		}
		else if (result[0] == MFGameConstants.RESULT_SUCCESS) //game successful completed
		{	
			GameSuccessDialog dialog = new GameSuccessDialog(this, DIALOG_DATA_NONE);
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
			
			/** Update Coins Earned **/	
			updateCoinsEarned(getCoins() + maxMoves);
			
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
		
		mExitButton.setEnabled(enable);
		mSoundButton.setEnabled(enable);
		mAddCoinsButton.setEnabled(enable);
		mAddMovesButton.setEnabled(enable);
		mAddStarsButton.setEnabled(enable);
		mAddHurdleSmasherButton.setEnabled(enable);
		mRemoveAdsButton.setEnabled(enable);
	}

	private void updateCoinsEarned(int coins)
	{
		int currCoins = getCoins();
		if (coins > currCoins)
		{
			CoinsUpdateHandler handler = new CoinsUpdateHandler(mCoinsEarnedLabel);
			Thread background = new Thread(new CoinsUpdaterRunnable(Math.max(currCoins, coins - 10), coins, handler));
			background.start();
		}
		else
		{
			String coinsText = String.format(getResources().getString(R.string.coins_earned_text), coins);
			mCoinsEarnedLabel.setText(coinsText);
		}
		
		setCoins(coins);
        
        SharedPreferences settings;
		settings = getSharedPreferences(MFGameConstants.PREFERENCE_KEY, Context.MODE_PRIVATE);
		Editor editor = settings.edit();
		editor.putInt(MFGameConstants.PREFERENCE_TOTAL_COINS_EARNED, coins);
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
	public void onDialogOptionSelected(Dialog dialog, int option, int clientdata) 
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
				AddMovesDialog addMovesDialog = new AddMovesDialog(this, DIALOG_DATA_NONE, getNumCoinsForMoves());
				addMovesDialog.setCanceledOnTouchOutside(false);
				addMovesDialog.show();
			}
			else if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_2 || option == GameDialog.GAME_DIALOG_ACTION_NEGATIVE_1) // End Game
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_END_GAME_BUTTON);
				
				/** Take the user to the Try Again dialog **/
				GameMenuDialog tryAgainDialog = new GameMenuDialog(this, DIALOG_DATA_NONE);
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
					GameMenuDialog menuDialog = new GameMenuDialog(this, DIALOG_DATA_NONE);
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
				
				int currCoins = getCoins();
				if (currCoins >= getNumCoinsForMoves())
				{
					//go ahead and add moves, and adjust coins
					int maxMoves = getMaxMoves(gridHandle);
					maxMoves += MFGameConstants.MOVES_ADD_INCREMENT;
					setMaxMoves(gridHandle, maxMoves);
					
					updateCoinsEarned(currCoins - getNumCoinsForMoves());
					MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_GAME_ACTION, MFAnalytics.ANALYTICS_LABEL_GAME_ACTION_COINS_REDEEMED_FOR_MOVES);
					
					int currMove = getCurrMove(gridHandle);
					refreshMovesUI(currMove, maxMoves);
					
					enableDisableAllButtons(true);
				}
				else
				{
					//alert hte user tht he must buy coins
					//redeem the coins, show a dialog
					int shortfall = getNumCoinsForMoves() - currCoins;
					AddCoinsDialog addCoinsDialog = new AddCoinsDialog(this, shortfall, DIALOG_DATA_FROM_ADD_MOVES_DIALOG, mIAPManager, getNumCoinsIAPFirst(), getNumCoinsIAPSecond(), getNumCoinsIAPThird(), getNumCoinsIAPFourth());
					addCoinsDialog.setCanceledOnTouchOutside(false);
					addCoinsDialog.show();
					mLastDialogData = DIALOG_DATA_FROM_ADD_MOVES_DIALOG;
				}
			}
			else if (option == GameDialog.GAME_DIALOG_ACTION_NEGATIVE_1)
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_CANCEL_ADD_MOVES_DIALOG);
				
				//if the game had failed and the user reached here, then take him to the main menu
				/**
				 * If the user landed here afer having 'failed' the game,
				 * show him the game menu dialog again
				 */
				if (getCurrMove(gridHandle) == getMaxMoves(gridHandle))
				{
					GameMenuDialog menuDialog = new GameMenuDialog(this, DIALOG_DATA_NONE);
					menuDialog.setCanceledOnTouchOutside(false);
					menuDialog.show();
				}
				else
				{
					dialog.dismiss(); //resume current game
				}
			}
		}
		else if (dialog.getClass() == AddStarDialog.class)
		{
			if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_1 || option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_2)
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_REDEEM_COINS_FOR_STAR_BUTTON);
				
				int numCoinsRequired = 0;
				int numStarsToBuy = 0;
				if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_1)
				{
					numStarsToBuy = 1;
				}
				else if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_2)
				{
					numStarsToBuy = 2;
				}
				numCoinsRequired = getNumCoinsForStar(numStarsToBuy);
				
				int currCoins = getCoins();
				if (currCoins >= numCoinsRequired)
				{
					updateCoinsEarned(currCoins - numCoinsRequired);
					MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_GAME_ACTION, MFAnalytics.ANALYTICS_LABEL_GAME_ACTION_COINS_REDEEMED_FOR_STAR);
					
					//update the number of stars
					int numStars = MFUtils.prefGetInt(this, MFGameConstants.PREFERENCE_TOTAL_STARS_EARNED, MFGameConstants.INITIAL_STARS_ALLOCATED);
					numStars += numStarsToBuy;
					MFUtils.prefPutInt(this, MFGameConstants.PREFERENCE_TOTAL_STARS_EARNED, numStars);
					
					refreshLifelinesUI();
				}
				else
				{
					//alert hte user tht he must buy coins
					//redeem the coins, show a dialog
					int shortfall = numCoinsRequired - currCoins;
					AddCoinsDialog addCoinsDialog = new AddCoinsDialog(this, shortfall, DIALOG_DATA_FROM_ADD_STAR_DIALOG, mIAPManager, getNumCoinsIAPFirst(), getNumCoinsIAPSecond(), getNumCoinsIAPThird(), getNumCoinsIAPFourth());
					addCoinsDialog.setCanceledOnTouchOutside(false);
					addCoinsDialog.show();
					mLastDialogData = DIALOG_DATA_FROM_ADD_STAR_DIALOG;
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
			if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_1 || option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_2)
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_REDEEM_COINS_FOR_HURDLE_SMASHER);
				
				int numCoinsRequired = 0;
				int numSmashersToBuy = 0;
				if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_1)
				{
					numSmashersToBuy = 1;
				}
				else if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_2)
				{
					numSmashersToBuy = 2;
				}
				
				numCoinsRequired = getNumCoinsForHurdleSmasher(numSmashersToBuy);
				int currCoins = getCoins();
				if (currCoins >= numCoinsRequired)
				{				
					updateCoinsEarned(currCoins - numCoinsRequired);
					MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_GAME_ACTION, MFAnalytics.ANALYTICS_LABEL_GAME_ACTION_COINS_REDEEMED_FOR_HURDLE_SMASHER);

					int numSmashers = MFUtils.prefGetInt(this, MFGameConstants.PREFERENCE_TOTAL_HURDLE_SMASHERS_EARNED, MFGameConstants.INITIAL_HURDLE_SMASHERS_ALLOCATED);
					numSmashers += numSmashersToBuy;
					MFUtils.prefPutInt(this, MFGameConstants.PREFERENCE_TOTAL_HURDLE_SMASHERS_EARNED, numSmashers);
					
					refreshLifelinesUI();
				}
				else
				{
					//alert hte user tht he must buy coins
					//redeem the coins, show a dialog
					int shortfall = numCoinsRequired - currCoins;
					AddCoinsDialog addCoinsDialog = new AddCoinsDialog(this, shortfall, DIALOG_DATA_FROM_ADD_HURDLE_SMASHER_DIALOG, mIAPManager, getNumCoinsIAPFirst(), getNumCoinsIAPSecond(), getNumCoinsIAPThird(), getNumCoinsIAPFourth());
					addCoinsDialog.setCanceledOnTouchOutside(false);
					addCoinsDialog.show();
					mLastDialogData = DIALOG_DATA_FROM_ADD_HURDLE_SMASHER_DIALOG;
				}
			}
			else if (option == GameDialog.GAME_DIALOG_ACTION_NEGATIVE_1)
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_CANCEL_ADD_HURDLE_SMASHER_DIALOG);
				
				dialog.dismiss(); //resume current game
			}
		}
		else if (dialog.getClass() == AddBridgeDialog.class)
		{
			if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_1 || option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_2)
			{
				MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_BUTTON_PRESS, MFAnalytics.ANALYTICS_LABEL_REDEEM_COINS_FOR_BRIDGE);
				
				int numCoinsRequired = 0;
				int numBridgesToBuy = 0;
				if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_1)
				{
					numBridgesToBuy = 1;
				}
				else if (option == GameDialog.GAME_DIALOG_ACTION_POSITIVE_2)
				{
					numBridgesToBuy = 2;
				}
				
				numCoinsRequired = getNumCoinsForBridge(numBridgesToBuy);
				
				int currCoins = getCoins();
				if (currCoins >= numCoinsRequired)
				{				
					updateCoinsEarned(currCoins - numCoinsRequired);
					MFAnalytics.trackEvent(this, MFAnalytics.ANALYTICS_CATEGORY_GAME, MFAnalytics.ANALYTICS_ACTION_GAME_ACTION, MFAnalytics.ANALYTICS_LABEL_GAME_ACTION_COINS_REDEEMED_FOR_BRIDGE);
					
					int numBridges = MFUtils.prefGetInt(this, MFGameConstants.PREFERENCE_TOTAL_BRIDGES_EARNED, MFGameConstants.INITIAL_BRIDGES_ALLOCATED);
					numBridges += numBridgesToBuy;
					MFUtils.prefPutInt(this, MFGameConstants.PREFERENCE_TOTAL_BRIDGES_EARNED, numBridges);
					
					refreshLifelinesUI();
				}
				else
				{
					//alert hte user tht he must buy coins
					//redeem the coins, show a dialog
					int shortfall = numCoinsRequired - currCoins;
					AddCoinsDialog addCoinsDialog = new AddCoinsDialog(this, shortfall, DIALOG_DATA_FROM_ADD_BRIDGE_DIALOG, mIAPManager, getNumCoinsIAPFirst(), getNumCoinsIAPSecond(), getNumCoinsIAPThird(), getNumCoinsIAPFourth());
					addCoinsDialog.setCanceledOnTouchOutside(false);
					addCoinsDialog.show();
					mLastDialogData = DIALOG_DATA_FROM_ADD_BRIDGE_DIALOG;
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
		else if (dialog.getClass() == IAPFailedDialog.class)
		{
			if (option == GameDialog.GAME_DIALOG_ACTION_NEGATIVE_1)
			{
				if (clientdata == DIALOG_DATA_EXIT)
				{
					//IAP isnt' working (query failed).  Exit
					finish();
					return;
				}
				
				//purchase failed for some reason.
				if (getCurrMove(gridHandle) == getMaxMoves(gridHandle))
				{
					//this happened after failing the game, so go back to the main menu dialog
					GameMenuDialog menuDialog = new GameMenuDialog(this, DIALOG_DATA_NONE);
					menuDialog.setCanceledOnTouchOutside(false);
					menuDialog.show();
				}
			}
		}
	}
	
	@Override
	public void onPurchaseFinished(Purchase purchase, String pid, boolean status, boolean cancelled) 
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
		else if (pid.equals(MFGameConstants.IAP_COINS_FIRST)
				|| pid.equals(MFGameConstants.IAP_COINS_SECOND)
				|| pid.equals(MFGameConstants.IAP_COINS_THIRD)
				|| pid.equals(MFGameConstants.IAP_COINS_FOURTH))
		{
			if (status == true)
			{
				//purchase successful.  Since these are consumable items, make the consume request
				mIAPManager.consumeItem(purchase);
			}
		}
		
		if (status == false && cancelled == false) //only show failure if not user cancelled
		{
			//show the "Purchase failed dialog"
			IAPFailedDialog iapFailedDialog = new IAPFailedDialog(this, IAPFailedDialog.TYPE_PURCHASE_FAILED, DIALOG_DATA_NONE);
			iapFailedDialog.setCanceledOnTouchOutside(false);
			iapFailedDialog.show();
		}
	}

	@Override
	public void onConsumeFinished(String pid, boolean status) 
	{
		if (status == true)
		{
			//consumed the item, now update the values
			int currCoins = getCoins();
			if (pid.equals(MFGameConstants.IAP_COINS_FIRST))
			{
				updateCoinsEarned(currCoins + getNumCoinsIAPFirst());
			}
			else if (pid.equals(MFGameConstants.IAP_COINS_SECOND))
			{
				updateCoinsEarned(currCoins + getNumCoinsIAPSecond());
			}
			else if (pid.equals(MFGameConstants.IAP_COINS_THIRD))
			{
				updateCoinsEarned(currCoins + getNumCoinsIAPThird());
			}
			else if (pid.equals(MFGameConstants.IAP_COINS_FOURTH))
			{
				updateCoinsEarned(currCoins + getNumCoinsIAPFourth());
			}
			
			/**
			 * Now check to see if the purchase was started for a specific workflow (e.g. AddMoves,
			 * AddStar, AddHurdleSmasher, or if it was started standalone (via AddCoinsDialog)
			 */
			if (mLastDialogData == DIALOG_DATA_FROM_ADD_MOVES_DIALOG)
			{
				mLastDialogData = DIALOG_DATA_NONE;
				
				//user landed here after starting the Add Moves.  So, show up the Add Moves dialog again
				AddMovesDialog addMovesDialog = new AddMovesDialog(this, DIALOG_DATA_NONE, getNumCoinsForMoves());
				addMovesDialog.setCanceledOnTouchOutside(false);
				addMovesDialog.show();		
			}
			else if (mLastDialogData == DIALOG_DATA_FROM_ADD_STAR_DIALOG)
			{
				mLastDialogData = DIALOG_DATA_NONE;
				
				//user landed here after starting the Add Star workflow.
				AddStarDialog addStarDialog = new AddStarDialog(this, DIALOG_DATA_NONE, getNumCoinsForStar(1), getNumCoinsForStar(2));
				addStarDialog.setCanceledOnTouchOutside(false);
				addStarDialog.show();
			}
			else if (mLastDialogData == DIALOG_DATA_FROM_ADD_HURDLE_SMASHER_DIALOG)
			{
				mLastDialogData = DIALOG_DATA_NONE;
				
				//user landed here after starting the Add Hurdle Smasher workflow
				AddHurdleSmasherDialog hurdleDialog = new AddHurdleSmasherDialog(this, DIALOG_DATA_NONE, getNumCoinsForHurdleSmasher(1), getNumCoinsForHurdleSmasher(2));
				hurdleDialog.setCanceledOnTouchOutside(false);
				hurdleDialog.show();
			}
		}
		else
		{
			//consume failed!
			//show the "Consume failed dialog"
			IAPFailedDialog iapFailedDialog = new IAPFailedDialog(this, IAPFailedDialog.TYPE_CONSUME_FAILED, DIALOG_DATA_NONE);
			iapFailedDialog.setCanceledOnTouchOutside(false);
			iapFailedDialog.show();
		}
	}
	
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) 
	{
		// Pass on the activity result to the helper for handling
		if (!mIAPManager.handleActivityResult(requestCode, resultCode, data)) {
			// not handled, so handle it ourselves (here's where you'd
			// perform any handling of activity results not related to in-app
			// billing...
			super.onActivityResult(requestCode, resultCode, data);
		}
	}
	
	@Override
	public void handleGameViewTap(int col, int row) 
	{
		if (mHurdleSmashMode)
		{
			int result = smashHurdle(gridHandle, col, row);
			if (result == 1)
			{
				mHurdleSmashMode = false;
				
				playSound(mHurdleSmashedSoundID);
				
				//successfuly smashed a hurdle
				int[] gridDataOneD = getGridData(gridHandle);
				int gridSize = getGridSize(gridHandle);

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
								
				/** Update the number of hurdle smashers remaining **/
				SharedPreferences settings;
				settings = getSharedPreferences(MFGameConstants.PREFERENCE_KEY, Context.MODE_PRIVATE);
				int numSmashers = settings.getInt(MFGameConstants.PREFERENCE_TOTAL_HURDLE_SMASHERS_EARNED, MFGameConstants.INITIAL_HURDLE_SMASHERS_ALLOCATED);
				numSmashers --;
				Editor editor = settings.edit();
				editor.putInt(MFGameConstants.PREFERENCE_TOTAL_HURDLE_SMASHERS_EARNED, numSmashers);
				editor.commit();
				
				refreshLifelinesUI();
			}
			else
			{
				HurdleSmasherInfoDialog hurdleDialog = new HurdleSmasherInfoDialog(this, HurdleSmasherInfoDialog.TYPE_RETRY, DIALOG_DATA_NONE);
				hurdleDialog.setCanceledOnTouchOutside(false);
				hurdleDialog.show();
			}
		}
		else if (mStarPlacementMode)
		{
			int result = addStartPos(gridHandle, col, row);
			if (result == 1)
			{
				mStarPlacementMode = false;
				playSound(mStarPlacedSoundID);
				
				//successfully placed the star
				
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
				
				/** Update the number of stars remaining **/
				SharedPreferences settings;
				settings = getSharedPreferences(MFGameConstants.PREFERENCE_KEY, Context.MODE_PRIVATE);
				int numStars = settings.getInt(MFGameConstants.PREFERENCE_TOTAL_STARS_EARNED, MFGameConstants.INITIAL_STARS_ALLOCATED);
				numStars --;
				Editor editor = settings.edit();
				editor.putInt(MFGameConstants.PREFERENCE_TOTAL_STARS_EARNED, numStars);
				editor.commit();
				
				refreshLifelinesUI();
			}
			else
			{
				//retry
				StarPlacementInfoDialog starDialog = new StarPlacementInfoDialog(this, StarPlacementInfoDialog.TYPE_RETRY, DIALOG_DATA_NONE);
				starDialog.setCanceledOnTouchOutside(false);
				starDialog.show();
			}
		}
	}
	
	@Override
	public void handleGameViewDragBegin(int col, int row) {
		if (mBridgeMode)
		{
			mGameView.setBridgeValid(false);
			
			if (isBridgeEndpointValid(gridHandle, row, col) > 0)
			{
				mBridgeStartRow = row;
				mBridgeStartCol = col;
			}
			
			mGameView.enterExitBridgeBuildingMode(true, false);
		}
	}

	@Override
	public void handleGameViewDragMove(int col, int row) {
		if (mBridgeMode)
		{
			int[] bridgeExtremes = checkBridgeValid(gridHandle, mBridgeStartRow, mBridgeStartCol, row, col);
			if (bridgeExtremes != null && bridgeExtremes.length == 4)
			{
				mGameView.setBridgeValid(true);
				
				mBridgeEndRow = row;
				mBridgeEndCol = col;
				
				mGameView.setBridgeExtremes(bridgeExtremes[0], bridgeExtremes[1], bridgeExtremes[2], bridgeExtremes[3]);
			}
			else
			{
				mGameView.setBridgeValid(false);
			}
		}
	}

	@Override
	public void handleGameViewDragEnd(int col, int row) {
		if (mBridgeMode)
		{
			int[] bridgeExtremes = checkBridgeValid(gridHandle, mBridgeStartRow, mBridgeStartCol, row, col);
			if (bridgeExtremes != null && bridgeExtremes.length == 4)
			{
				mGameView.setBridgeValid(true);
				
				mBridgeEndRow = row;
				mBridgeEndCol = col;
				
				playSound(mBridgePlacedSoundID);
				
				mBridgeMode = false;
				
				//actually build the bridge
				buildBridge(gridHandle, mBridgeStartRow, mBridgeStartCol, mBridgeEndRow, mBridgeEndCol);
				
				//update the game data
				int[] gridDataOneD = getGridData(gridHandle);
				int gridSize = getGridSize(gridHandle);

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
				
				/** Update the number of bridges remaining **/
				int numBridges = MFUtils.prefGetInt(this, MFGameConstants.PREFERENCE_TOTAL_BRIDGES_EARNED, MFGameConstants.INITIAL_BRIDGES_ALLOCATED);
				numBridges --;
				MFUtils.prefPutInt(this, MFGameConstants.PREFERENCE_TOTAL_BRIDGES_EARNED, numBridges);
				
				refreshLifelinesUI();
				
				mGameView.enterExitBridgeBuildingMode(false, false);
			}
			else
			{
				mGameView.enterExitBridgeBuildingMode(true, true);
			}
		}
		
	}
	
	private void starBlinkingTimerCallback()
	{
		if (mGameView.mCurrentStarSize < 0)
		{
			mGameView.mCurrentStarSize ++;

			if (mGameView.mCurrentStarSize == 0)
			{
				mStarAnimationTimer.cancel();
				
				mStarAnimationTimer = new Timer();
				mStarAnimationTimer.scheduleAtFixedRate(new AnimationTimerTask(), STAR_BLINK_INTERVAL, STAR_BLINK_INTERVAL);
			}
		}
		else if (mGameView.mCurrentStarSize == 0)
		{
			mGameView.mCurrentStarSize = 1;
		}
		else if (mGameView.mCurrentStarSize == 1)
		{
			mGameView.mCurrentStarSize = 0;
		}
		mGameView.postInvalidate();
	}
	
	public class AnimationTimerTask extends TimerTask
	{		
		public AnimationTimerTask()
		{
		}
		
		@Override
	    public void run()
		{
			starBlinkingTimerCallback();
		}
	}
	
	private MFGameView mGameView; //the game view
	private int mLevel;
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
	
	private ImageButton mAddCoinsButton, mAddMovesButton, mAddStarsButton, mAddHurdleSmasherButton, mAddBridgeButton;
	private LinearLayout mRemoveAdsButton;
	private ImageView mMovesImage;
	
	private AlertDialog mExitAlertDialog, mSuccessAlertDialog, mFailedAlertDialog;
	
	/**
	 * Animations
	 */
	private Animation mAnimScale;
	
	/**
	 * Placing a Star
	 */
	private boolean mStarPlacementMode; //whether we're in the mode where user is selecting a cell to place the star on
	
	/**
	 * Hurdle SMasher
	 */
	private boolean mHurdleSmashMode; //whether we're in the mode where user is selecting a hurdle to smash

	/**
	 * Bridge Creation
	 */
	private boolean mBridgeMode; //whether we'rein the mode of dragging and creating a bridge
	private int mBridgeStartRow, mBridgeEndRow, mBridgeStartCol, mBridgeEndCol;
	
	/**
	 * Star Blinking Timer related
	 */
	Timer mStarAnimationTimer = null;
	private static final long STAR_ANIMATION_INTERVAL = 50; //milli seconds
	private static final int STAR_ANIMATION_DURATION = 10; //steps
	private static final long STAR_BLINK_INTERVAL = 1000; //milli seconds
	private static final int STAR_ANIMATION_INITIAL_SIZE = -30;
	
	/**
	 * Sound related
	 */
	
	private SoundPool mSoundPool;
	private int mButtonClickSoundID, mGameSuccessSoundID, mGameFailedSoundID, mHurdleSmashedSoundID, mStarPlacedSoundID, mBridgePlacedSoundID;
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
	private native int addStartPos(long handle, int x, int y);
	private native int getMaxMoves(long handle);
	private native void setMaxMoves(long handle, int maxMoves);
	private native int getCurrMove(long handle);
	private native int[] playMove(long handle, int color);
	private native int[] getGridData(long handle);
	private native int smashHurdle(long handle, int x, int y);
	private native void setCoins(int coins);
	private native int getCoins();
	private native int getNumCoinsIAPFirst();
	private native int getNumCoinsIAPSecond();
	private native int getNumCoinsIAPThird();
	private native int getNumCoinsIAPFourth();
	private native int getNumCoinsForMoves();
	private native int getNumCoinsForStar(int numStars);
	private native int getNumCoinsForHurdleSmasher(int numSmashers);
	private native int getNumCoinsForBridge(int numBridges);
	private native int getMinLevelToAddStars();
	private native int getMinLevelToAddHurdleSmasher();
	private native int getMinLevelToAddBridge();
	private native int getNumCoinsForSuccessfulGame(int currMove, int maxMoves);
	private native int isBridgeEndpointValid(long handle, int row, int col);
	private native int[] checkBridgeValid(long handle, int startrow, int startcol, int endrow, int endcol);
	private native void buildBridge(long handle, int startrow, int startcol, int endrow, int endcol);
	
	
	/**
	 * Dialog data that is used to control workflow
	 */
	private static final int DIALOG_DATA_NONE = 0;
	private static final int DIALOG_DATA_FROM_ADD_STAR_DIALOG = 1;
	private static final int DIALOG_DATA_FROM_ADD_MOVES_DIALOG = 2;
	private static final int DIALOG_DATA_FROM_ADD_HURDLE_SMASHER_DIALOG = 3;
	private static final int DIALOG_DATA_FROM_ADD_BRIDGE_DIALOG = 4;
	private static final int DIALOG_DATA_EXIT = 5;
	private int mLastDialogData = DIALOG_DATA_NONE;


}