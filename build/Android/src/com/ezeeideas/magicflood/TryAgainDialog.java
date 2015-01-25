package com.ezeeideas.magicflood;

import android.content.Context;

public class TryAgainDialog extends GameDialogType3 {

	public TryAgainDialog(Context context, int clientdata) 
	{
		super(context, clientdata);
		
		setupViews();
		
		postSetupViews();
	}

	protected void setupViews() 
	{
		setContentView(R.layout.dialog_try_again);
	}

	@Override
	protected void setupRootView() 
	{
		mRootView = findViewById(R.id.game_dialog_root_layout);
	}

	@Override
	protected void setupPositiveAction1View() 
	{
		mPositiveAction1View = findViewById(R.id.try_again_button);
	}
	
	@Override
	protected void setupNegativeAction1View() 
	{
		mNegativeAction1View = findViewById(R.id.cancel_button);
	}
}
