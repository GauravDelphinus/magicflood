package com.ezeeideas.magicflood;

import android.content.Context;

/**
 * Game Dialog Type 2
 * 
 * - Two Positive Buttons.
 * - Tap on either positive button dismisses the dialog and executes corresponding positive action (1 or 2)
 * - Tap anywhere else on the dialog dismisses the dialog and executes negative action 1
 * - Hardware back dismisses the dialog and executes negative action 1
 */
public abstract class GameDialogType2 extends GameDialog
{
	public GameDialogType2(Context context, int clientdata)
	{
		super(context, clientdata);
	}

	protected void setupRequiredViews()
	{
		setupRootView();
		setupPositiveAction1View();
		setupPositiveAction2View();
	}
	
	protected void handleDismiss()
	{
		mListener.onDialogOptionSelected(this, GAME_DIALOG_ACTION_NEGATIVE_1, mClientData);	
		this.dismiss();
	}
	
	/**
	 * Clients must implement these functions.
	 */
	protected abstract void setupRootView();
	protected abstract void setupPositiveAction1View();
	protected abstract void setupPositiveAction2View();
}
