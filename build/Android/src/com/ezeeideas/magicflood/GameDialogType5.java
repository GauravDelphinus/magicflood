package com.ezeeideas.magicflood;

import android.content.Context;

/**
 * Game Dialog Type 5
 * 
 * - Four Positive buttons and One Negative Button
 * - Tap on positive buttons dismisses the dialog and executes positive action 1 or 2 or 3 or 4
 * - Tap on negative button dismisses the dialog and executes negative action 1
 * - Tap anywhere else on the dialog does nothing
 * - Hardware back dismisses the dialog and executes negative action 1
 */
public abstract class GameDialogType5 extends GameDialog
{
	public GameDialogType5(Context context, int clientdata)
	{
		super(context, clientdata);
	}

	protected void setupRequiredViews()
	{
		setupRootView();
		setupPositiveAction1View();
		setupPositiveAction2View();
		setupPositiveAction3View();
		setupPositiveAction4View();
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
	protected abstract void setupPositiveAction1View();
	protected abstract void setupPositiveAction2View();
	protected abstract void setupPositiveAction3View();
	protected abstract void setupPositiveAction4View();
	protected abstract void setupNegativeAction1View();
}
