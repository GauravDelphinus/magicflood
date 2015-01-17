package com.ezeeideas.magicflood;

import android.content.Context;
import android.view.View;

/**
 * Game Dialog Type 4
 * 
 * - Two Positive buttons, and one negative button.
 * - Tap on positive buttons dismisses the dialog and executes positive action 1 or 2
 * - Tap on negative button dismisses the dialog and executes negative action 1
 * - Tap anywhere else on the dialog does nothing
 * - Hardware back dismisses the dialog and executes negative action 1
 */
public abstract class GameDialogType4 extends GameDialog
{
	public GameDialogType4(Context context)
	{
		super(context);
	}

	protected void setupRequiredViews()
	{
		setupRootView();
		setupPositiveAction1View();
		setupPositiveAction2View();
		setupNegativeAction1View();
	}

	protected void handleDismiss()
	{
		mListener.onDialogOptionSelected(this, GAME_DIALOG_ACTION_NEGATIVE_1);
		this.dismiss();
	}
	
	/**
	 * Clients must implement these functions.
	 */
	protected abstract void setupRootView();
	protected abstract void setupPositiveAction1View();
	protected abstract void setupPositiveAction2View();
	protected abstract void setupNegativeAction1View();
}
