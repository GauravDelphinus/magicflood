package com.ezeeideas.magicflood;

import android.content.Context;

public class GameSuccessStoreDialog extends GameDialogType4 {

	public GameSuccessStoreDialog(Context context) 
	{
		super(context);
		
		setupViews();
		
		postSetupViews();
	}

	protected void setupViews() 
	{
		setContentView(R.layout.dialog_game_success_store);
	}

	@Override
	protected void setupRootView() 
	{
		mRootView = findViewById(R.id.game_dialog_root_layout);
	}

	@Override
	protected void setupPositiveAction1View() 
	{
		mPositiveAction1View = findViewById(R.id.store_button);
	}
	
	@Override
	protected void setupPositiveAction2View() 
	{
		mPositiveAction2View = findViewById(R.id.next_game_button);
	}

	@Override
	protected void setupNegativeAction1View() 
	{
		mNegativeAction1View = findViewById(R.id.menu_button);		
	}
}
