package com.ezeeideas.magicflood;

import android.app.Dialog;
import android.content.Context;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.content.DialogInterface;
import android.graphics.drawable.ColorDrawable;
import android.view.Window;

public abstract class GameDialog extends Dialog implements View.OnClickListener, DialogInterface.OnKeyListener
{
	public GameDialog(Context context, int data)
	{
		super(context);
		mContext = context;
		mClientData = data;
		
		mListener = (GameDialogListener) mContext;
		
		//don't show a title
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setBackgroundDrawable(new ColorDrawable(android.graphics.Color.TRANSPARENT));
	}

	/**
	 * Called AFTER the specific game dialog has completed
	 * setup of its views.
	 */
	protected void postSetupViews()
	{		
		/**
		 * Implemented by GameDialogType* class that implements a specific type of dialog.
		 * This will call the setupView* methods to set up the variosu required views
		 * for that given type.
		 */
		setupRequiredViews();
		
		/**
		 * Set up the listeners for all active views in the dialog
		 */
		setupListeners();
	}
	/**
	 * Set up the required views for this dialog type,
	 * such as root view, positive view 1, etc.
	 */
	protected abstract void setupRequiredViews();
	
	/**
	 * Called when the dialog was dismissed by the user
	 * by using the hardware back button.  Not called
	 * if the dismissal was programmatically done after
	 * a tap on some other button or view.
	 */
	protected abstract void handleDismiss();
	
	/**
	 * Set up listeners on all active views in the dialog.
	 */
	protected void setupListeners()
	{
		//set back key handler
		this.setOnKeyListener(this);
		
		if (mPositiveAction1View != null)
		{
			mPositiveAction1View.setOnClickListener(this);
		}
		
		if (mPositiveAction2View != null)
		{
			mPositiveAction2View.setOnClickListener(this);
		}
		
		if (mPositiveAction3View != null)
		{
			mPositiveAction3View.setOnClickListener(this);
		}
		
		if (mPositiveAction4View != null)
		{
			mPositiveAction4View.setOnClickListener(this);
		}
		
		if (mNegativeAction1View != null)
		{
			mNegativeAction1View.setOnClickListener(this);
		}
	}
	
	@Override
	public void onClick(View view)
	{
		if (view == mPositiveAction1View)
		{
			mListener.onDialogOptionSelected(this, GAME_DIALOG_ACTION_POSITIVE_1, mClientData);
			this.dismiss();
		}
		else if (view == mPositiveAction2View)
		{
			mListener.onDialogOptionSelected(this, GAME_DIALOG_ACTION_POSITIVE_2, mClientData);
			this.dismiss();
		}
		else if (view == mPositiveAction3View)
		{
			mListener.onDialogOptionSelected(this, GAME_DIALOG_ACTION_POSITIVE_3, mClientData);
			this.dismiss();
		}
		else if (view == mPositiveAction4View)
		{
			mListener.onDialogOptionSelected(this, GAME_DIALOG_ACTION_POSITIVE_4, mClientData);
			this.dismiss();
		}
		else if (view == mNegativeAction1View)
		{
			mListener.onDialogOptionSelected(this, GAME_DIALOG_ACTION_NEGATIVE_1, mClientData);
			this.dismiss();
		}
	}
	

	@Override
	public boolean onKey(DialogInterface dialog, int keyCode, KeyEvent event) 
	{
		Log.d("gaurav", "GameDialog.onKey, keyCode = " + keyCode);

		if ((event.getAction() == KeyEvent.ACTION_UP) && (keyCode == KeyEvent.KEYCODE_BACK)) 
		{
			handleDismiss();
			return true;
        }	
		
		return false;
	}

	/**
	 * The listener (typically the calling Activity) that needs to listen to
	 * events from the dialog, including button clicks, touches and dialog dismissal.
	 */
	public interface GameDialogListener
	{
		public void onDialogOptionSelected(Dialog dialog, int option, int clientData); //One of GAME_DIALOG_ACTION_*
	}
	
	protected GameDialogListener mListener;
	
	//Resultant actions after user acts on the dialog to pass on to the calling activity
	protected static final int GAME_DIALOG_ACTION_POSITIVE_1 = 1;
	protected static final int GAME_DIALOG_ACTION_POSITIVE_2 = 2;
	protected static final int GAME_DIALOG_ACTION_POSITIVE_3 = 3;
	protected static final int GAME_DIALOG_ACTION_POSITIVE_4 = 4;
	protected static final int GAME_DIALOG_ACTION_NEGATIVE_1 = 5;
	
	//The Views that all dialogs must implement
	protected View mRootView = null; //The root view (usually a layout) that listens to the "tap anywhere else" area
	protected View mPositiveAction1View = null; //View that corresponds to Positive Action 1
	protected View mPositiveAction2View = null; //View that corresponds to Positive Action 2
	protected View mPositiveAction3View = null; //View that corresponds to Positive Action 3
	protected View mPositiveAction4View = null; //View that corresponds to Positive Action 4
	protected View mNegativeAction1View = null; //View the corresponds to Negative Action 1
	
	private Context mContext; //the calling activity context
	
	protected int mClientData; //any data that the caller passed to te dialog, and that is passed back in te onDialogOptionSelected listener
}