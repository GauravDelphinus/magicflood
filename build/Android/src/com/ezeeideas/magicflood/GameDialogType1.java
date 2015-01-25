package com.ezeeideas.magicflood;

import android.content.Context;
import android.view.View;

/**
 * Game Dialog Type 1
 * 
 * - One Negative Button
 * - Tap on negative button dismisses the dialog and executes negative action 1
 * - Tap anywhere else on the dialog does nothing
 * - Hardware back dismisses the dialog and executes negative action 1
 */
public abstract class GameDialogType1 extends GameDialog
{
	public GameDialogType1(Context context, int clientdata)
	{
		super(context, clientdata);
	}

	protected void setupRequiredViews()
	{
		setupRootView();
		setupNegativeAction1View();
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
	protected abstract void setupNegativeAction1View();
}
