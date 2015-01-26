package com.ezeeideas.magicflood;

import android.content.Context;
import android.graphics.Typeface;
import android.widget.TextView;

public class GameMenuDialog extends GameDialogType4 {

	public GameMenuDialog(Context context, int clientdata) 
	{
		super(context, clientdata);
		
		setupViews();
		
		postSetupViews();
		
		//set the font typeface for all text
		Typeface face = MFUtils.getTextTypeface(context);
		
		TextView titleLabel = (TextView) findViewById(R.id.dialog_game_menu_title_text_id);
		titleLabel.setTypeface(face);
		TextView descriptionLabel = (TextView) findViewById(R.id.dialog_game_menu_description_text_id);
		descriptionLabel.setTypeface(face);
		TextView replayLevelLabel = (TextView) findViewById(R.id.dialog_replay_game_button_text_id);
		replayLevelLabel.setTypeface(face);
		TextView mainMenuLabel = (TextView) findViewById(R.id.dialog_menu_button_text_id);
		mainMenuLabel.setTypeface(face);
	}

	protected void setupViews() 
	{
		setContentView(R.layout.dialog_game_menu);
	}

	@Override
	protected void setupRootView() 
	{
		mRootView = findViewById(R.id.game_dialog_root_layout);
	}

	@Override
	protected void setupPositiveAction1View() 
	{
		mPositiveAction1View = findViewById(R.id.menu_button);
	}
	
	@Override
	protected void setupPositiveAction2View() 
	{
		mPositiveAction2View = findViewById(R.id.replay_game_button);
	}
	
	@Override
	protected void setupNegativeAction1View() 
	{
		mNegativeAction1View = findViewById(R.id.cancel_button);
	}
}
