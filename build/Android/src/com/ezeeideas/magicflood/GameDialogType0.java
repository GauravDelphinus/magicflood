package com.ezeeideas.magicflood;

import android.content.Context;
import android.view.View;

/**
 * GameDialog Type 0
 * 
 * - No explicit buttons.
 * - Tap anywhere dismisses the dialog and executes positive action 1
 * - Hardware back dismisses the dialog and executes positive action 1
 * - Examples: Pause/Resume Game Dialog
 */
public abstract class GameDialogType0 extends GameDialog
{
	public GameDialogType0(Context context)
	{
		super(context);
	}

	protected void setupRequiredViews()
	{
		setupRootView(); //no buttons in this view
	}

	protected void handleTouch(View v)
	{		
		if (v == mRootView)
		{
			mListener.onDialogOptionSelected(this, GAME_DIALOG_ACTION_POSITIVE_1);
			this.dismiss();
		}
	}

	protected void handleDismiss()
	{
		mListener.onDialogOptionSelected(this, GAME_DIALOG_ACTION_POSITIVE_1);	
		this.dismiss();
	}
	
	/**
	 * Clients must implement these functions
	 */
	protected abstract void setupRootView();
}
