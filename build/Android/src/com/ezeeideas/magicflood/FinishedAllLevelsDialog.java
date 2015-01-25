package com.ezeeideas.magicflood;

import android.content.Context;
import android.widget.TextView;

public class FinishedAllLevelsDialog extends GameDialogType1 {

	public FinishedAllLevelsDialog(Context context, int clientdata) 
	{
		super(context, clientdata);
		
		setupViews();
		
		postSetupViews();
		
		TextView titleTV = (TextView) findViewById(R.id.dialog_finished_all_levels_title_text_id);
		titleTV.setTypeface(MFUtils.getTextTypeface(context));
		
		TextView descriptionTV = (TextView) findViewById(R.id.dialog_finished_all_levels_description_text_id);
		descriptionTV.setTypeface(MFUtils.getTextTypeface(context));
	}

	protected void setupViews() 
	{
		setContentView(R.layout.dialog_finished_all_levels);
	}

	@Override
	protected void setupRootView() 
	{
		mRootView = findViewById(R.id.game_dialog_root_layout);
	}

	@Override
	protected void setupNegativeAction1View() 
	{
		mNegativeAction1View = findViewById(R.id.cancel_button);
	}
}
