package com.ezeeideas.magicflood;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.media.AudioManager;
import android.media.SoundPool;
import android.media.SoundPool.OnLoadCompleteListener;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MFGameActivity extends Activity implements View.OnClickListener, DialogInterface.OnClickListener {

	
	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_game);
        
    	mGameView = (MFGameView) findViewById(R.id.game_view_id);
    	mMovesLabel = (TextView) findViewById(R.id.moves_label_id);
    	mExitButton = (Button) findViewById(R.id.exit_game_button_id);
    	mExitButton.setOnClickListener(this);
    	mRedButton = (Button) findViewById(R.id.red_button_id);
    	mRedButton.setOnClickListener(this);
    	mGreenButton = (Button) findViewById(R.id.green_button_id);
    	mGreenButton.setOnClickListener(this);
    	mBlueButton = (Button) findViewById(R.id.blue_button_id);
    	mBlueButton.setOnClickListener(this);
    	mYellowButton = (Button) findViewById(R.id.yellow_button_id);
    	mYellowButton.setOnClickListener(this);
    	mOrangeButton = (Button) findViewById(R.id.orange_button_id);
    	mOrangeButton.setOnClickListener(this);
    	mCyanButton = (Button) findViewById(R.id.cyan_button_id);
    	mCyanButton.setOnClickListener(this);
    	
    	mExitAlertDialog = null;
    	mSuccessAlertDialog = null;
    	mFailedAlertDialog = null;
    	
    	//initialize Sound
    	setupSound();
    	
    	mLevel = getIntent().getIntExtra(MFGameConstants.GAME_LEVEL_KEY, MFGameConstants.GAME_LEVEL_EASY);
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
		soundPool = new SoundPool(10, AudioManager.STREAM_MUSIC, 0);
		soundPool.setOnLoadCompleteListener(new OnLoadCompleteListener() 
		{
			@Override
			public void onLoadComplete(SoundPool soundPool, int sampleId, int status)
			{

				loaded = true;
			}
		});

		mButtonClickSoundID = soundPool.load(this, R.raw.button_press_sound, 1);
		mGameSuccessSoundID = soundPool.load(this, R.raw.game_success_sound, 1);
		mGameFailedSoundID = soundPool.load(this, R.raw.game_failed_sound, 1);
		
	}
	
	public void playSound(int resultType) 
	{
		// Is the sound loaded does it already play?
		if (loaded) 
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
			soundPool.play(soundID, volume, volume, 1, 0, 1f);
		}
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
		
		mMovesLabel.setText(String.format("Moves %d / %d", currMove, maxMoves));
	}

	
	@Override
	public void onClick(View arg0) {
		
		if (arg0.getId() ==  R.id.exit_game_button_id)
		{	
		
			AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(this);

			// set title
			alertDialogBuilder.setTitle("Exit?");

			// set dialog message
			alertDialogBuilder
			.setMessage("What would you like to do?")
			.setCancelable(true);

			// create alert dialog
			if (mExitAlertDialog == null)
			{
				mExitAlertDialog = alertDialogBuilder.create();
				mExitAlertDialog.setButton(AlertDialog.BUTTON_POSITIVE, "Menu", this);
				mExitAlertDialog.setButton(AlertDialog.BUTTON_NEUTRAL, "Resume Game", this);
				mExitAlertDialog.setButton(AlertDialog.BUTTON_NEGATIVE, "New Game", this);
			}
			// show it
			mExitAlertDialog.show(); 

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
		
		
		int result = playMove(gridHandle, colorValue);
		
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

		mMovesLabel.setText(String.format("Moves %d / %d", currMove, maxMoves));
		
		mGameView.updateGameData(gridData);
		mGameView.invalidate();

		if (result == MFGameConstants.RESULT_FAILED)
		{
			AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(this);

			// set title
			alertDialogBuilder.setTitle("Oops!");

			// set dialog message
			alertDialogBuilder
			.setMessage("Sorry, you've run out of moves!")
			.setCancelable(true);

			// create alert dialog
			if (mFailedAlertDialog == null)
			{
				mFailedAlertDialog = alertDialogBuilder.create();
				mFailedAlertDialog.setButton(AlertDialog.BUTTON_POSITIVE, "Menu", this);
				mFailedAlertDialog.setButton(AlertDialog.BUTTON_NEGATIVE, "New Game", this);
			}

			// show it
			mFailedAlertDialog.show();
			
			playSound(MFGameConstants.RESULT_FAILED);
		}
		else if (result == MFGameConstants.RESULT_SUCCESS)
		{
			AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(this);

			// set title
			alertDialogBuilder.setTitle("Great job!");

			// set dialog message
			alertDialogBuilder
			.setMessage("Well done - you nailed it!")
			.setCancelable(true);

			// create alert dialog
			if (mSuccessAlertDialog == null)
			{
				mSuccessAlertDialog = alertDialogBuilder.create();
				mSuccessAlertDialog.setButton(AlertDialog.BUTTON_POSITIVE, "Menu", this);
				mSuccessAlertDialog.setButton(AlertDialog.BUTTON_NEGATIVE, "Next Game", this);
			}

			// show it
			mSuccessAlertDialog.show();
			
			playSound(MFGameConstants.RESULT_SUCCESS);
		}
		else
		{
			playSound(MFGameConstants.RESULT_CONTINUE);
		}
	}

	@Override
	public void onClick(DialogInterface dialog, int which) {
		if (dialog == mExitAlertDialog)
		{
			switch (which)
			{
			case AlertDialog.BUTTON_POSITIVE:
				finish();
				break;

			case AlertDialog.BUTTON_NEUTRAL:
				dialog.cancel();
				break;
			case AlertDialog.BUTTON_NEGATIVE:
				dialog.cancel();
				startNewGame(mLevel);
				break;
			}
		}
		else if (dialog == mSuccessAlertDialog)
		{
			switch (which)
			{
			case AlertDialog.BUTTON_POSITIVE:
				finish();
				break;
			case AlertDialog.BUTTON_NEGATIVE:
				dialog.cancel();
				startNewGame(mLevel);
				break;
			}
		}
		else if (dialog == mFailedAlertDialog)
		{
			switch (which)
			{
			case AlertDialog.BUTTON_POSITIVE:
				finish();
				break;
			case AlertDialog.BUTTON_NEGATIVE:
				dialog.cancel();
				startNewGame(mLevel);
				break;
			}
		}
		
		
	}
	private MFGameView mGameView; //the game view
	private int mLevel;
	private TextView mMovesLabel; //label that shows the current moves
	private Button mExitButton;
	private Button mRedButton;
	private Button mBlueButton;
	private Button mGreenButton;
	private Button mYellowButton;
	private Button mOrangeButton;
	private Button mCyanButton;
	
	private AlertDialog mExitAlertDialog, mSuccessAlertDialog, mFailedAlertDialog;
	
	/**
	 * Sound related
	 */
	
	private SoundPool soundPool;
	private int mButtonClickSoundID, mGameSuccessSoundID, mGameFailedSoundID;
	boolean loaded = false;
	float actVolume, maxVolume, volume;
	AudioManager audioManager;

	
	private long gridHandle;
	private native long createNewGrid(int level);
	private native void deleteGrid(long handle);
	private native int getGridSize(long handle);
	private native int[] getStartPos(long handle);
	private native int getMaxMoves(long handle);
	private native int getCurrMove(long handle);
	private native int playMove(long handle, int color);
	private native int[] getGridData(long handle);
	
}