package com.ezeeideas.magicflood;

import android.content.Context;
import android.widget.TextView;

public class GameSuccessDialog extends GameDialogType3 {

	public GameSuccessDialog(Context context) 
	{
		super(context);
		
		setupViews();
		
		postSetupViews();
		
		TextView titleTV = (TextView) findViewById(R.id.dialog_game_success_title_text_id);
		titleTV.setTypeface(MFUtils.getTextTypeface(context));
		
		TextView descriptionTV = (TextView) findViewById(R.id.dialog_game_success_description_text_id);
		descriptionTV.setTypeface(MFUtils.getTextTypeface(context));
		
		TextView nextLevelButtonLabel = (TextView) findViewById(R.id.dialog_next_level_button_text_id);
		nextLevelButtonLabel.setTypeface(MFUtils.getTextTypeface(context));
	}

	protected void setupViews() 
	{
		setContentView(R.layout.dialog_game_success);
	}

	@Override
	protected void setupRootView() 
	{
		mRootView = findViewById(R.id.game_dialog_root_layout);
	}

	@Override
	protected void setupPositiveAction1View() 
	{
		mPositiveAction1View = findViewById(R.id.next_level_button);
	}

	@Override
	protected void setupNegativeAction1View() 
	{
		mNegativeAction1View = findViewById(R.id.menu_button);
	}
}
