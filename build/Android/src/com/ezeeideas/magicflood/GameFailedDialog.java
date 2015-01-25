package com.ezeeideas.magicflood;

import android.content.Context;
import android.content.DialogInterface;
import android.view.KeyEvent;
import android.widget.TextView;

public class GameFailedDialog extends GameDialogType4 {

	public GameFailedDialog(Context context, int clientdata) 
	{
		super(context, clientdata);
		
		setupViews();
		
		postSetupViews();
		
		TextView titleTV = (TextView) findViewById(R.id.dialog_game_failed_title_text_id);
		titleTV.setTypeface(MFUtils.getTextTypeface(context));
		
		TextView descriptionTV = (TextView) findViewById(R.id.dialog_game_failed_description_text_id);
		descriptionTV.setTypeface(MFUtils.getTextTypeface(context));
		
		TextView playOnButtonTV = (TextView) findViewById(R.id.dialog_play_on_button_text_id);
		playOnButtonTV.setTypeface(MFUtils.getTextTypeface(context));
		
		TextView endGameTV = (TextView) findViewById(R.id.dialog_end_game_button_text_id);
		endGameTV.setTypeface(MFUtils.getTextTypeface(context));
	}

	protected void setupViews() 
	{
		setContentView(R.layout.dialog_game_failed);
	}

	@Override
	protected void setupRootView() 
	{
		mRootView = findViewById(R.id.game_dialog_root_layout);
	}

	@Override
	protected void setupPositiveAction1View() 
	{
		mPositiveAction1View = findViewById(R.id.play_on_button);
	}
	
	@Override
	protected void setupPositiveAction2View() 
	{
		mPositiveAction2View = findViewById(R.id.end_game_button);
	}

	@Override
	protected void setupNegativeAction1View() 
	{
		mNegativeAction1View = findViewById(R.id.cancel_button);

	}
}
