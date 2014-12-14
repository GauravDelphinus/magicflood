package com.ezeeideas.magicflood;

import android.content.Context;
import android.widget.TextView;

public class GameMenuDialog extends GameDialogType2 {

	public GameMenuDialog(Context context) 
	{
		super(context);
		
		setupViews();
		
		postSetupViews();
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
		mPositiveAction2View = findViewById(R.id.new_game_button);
	}
}
