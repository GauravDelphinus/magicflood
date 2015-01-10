package com.ezeeideas.magicflood;

import android.content.Context;
import android.view.View;

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
	public GameDialogType2(Context context)
	{
		super(context);
	}

	protected void setupRequiredViews()
	{
		setupRootView();
		setupPositiveAction1View();
		setupPositiveAction2View();
	}

	protected boolean handleTouch(View v)
	{	
		boolean handled = false;
		
		if (v == mPositiveAction1View)
		{
			mListener.onDialogOptionSelected(this, GAME_DIALOG_ACTION_POSITIVE_1);
			this.dismiss();
			handled = true;
		}
		else if (v == mPositiveAction2View)
		{
			mListener.onDialogOptionSelected(this, GAME_DIALOG_ACTION_POSITIVE_2);
			this.dismiss();
			handled = true;
		}
		else if (v == mRootView)
		{
			mListener.onDialogOptionSelected(this, GAME_DIALOG_ACTION_NEGATIVE_1);
			this.dismiss();
			handled = true;
		}
		return handled;
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
}
