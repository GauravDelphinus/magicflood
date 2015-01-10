package com.ezeeideas.magicflood;

import android.content.Context;

public class RedeemCoinsDialog extends GameDialogType2 {

	public RedeemCoinsDialog(Context context) 
	{
		super(context);
		
		setupViews();
		
		postSetupViews();
	}

	protected void setupViews() 
	{
		setContentView(R.layout.dialog_redeem_coins);
	}

	@Override
	protected void setupRootView() 
	{
		mRootView = findViewById(R.id.game_dialog_root_layout);
	}

	@Override
	protected void setupPositiveAction1View() 
	{
		mPositiveAction1View = findViewById(R.id.earn_moves_button);
	}
	
	@Override
	protected void setupPositiveAction2View() 
	{
		mPositiveAction2View = findViewById(R.id.earn_stars_button);
	}
}
