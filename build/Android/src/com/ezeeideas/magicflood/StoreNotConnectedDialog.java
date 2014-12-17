package com.ezeeideas.magicflood;

import android.content.Context;

public class StoreNotConnectedDialog extends GameDialogType0 {

	public StoreNotConnectedDialog(Context context) 
	{
		super(context);
		
		setupViews();
		
		postSetupViews();
	}

	protected void setupViews() 
	{
		setContentView(R.layout.dialog_store_not_connected);
	}

	@Override
	protected void setupRootView() 
	{
		mRootView = findViewById(R.id.dialog_store_not_connected_root_layout);
	}
}
